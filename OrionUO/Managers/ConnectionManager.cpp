/***********************************************************************************
**
** ConnectionManager.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "ConnectionManager.h"
#include "ConfigManager.h"
#include "../Wisp/WispDataStream.h"
#include "../Wisp/WispLogger.h"
#include "../OrionUO.h"
#include "PacketManager.h"
#include "../Screen stages/ConnectionScreen.h"
#include "../Screen stages/GameBlockedScreen.h"
#include "../ServerList.h"
#include "../Managers/GumpManager.h"
#include "../Managers/PacketManager.h"
#include "../Gumps/GumpNotify.h"
//----------------------------------------------------------------------------------
CConnectionManager g_ConnectionManager;
//----------------------------------------------------------------------------------
NETWORK_INIT_TYPE *g_NetworkInit = NULL;
NETWORK_ACTION_TYPE *g_NetworkAction = NULL;
//----------------------------------------------------------------------------------
CConnectionManager::CConnectionManager()
: m_IsLoginSocket(true), m_LoginSocket(false), m_GameSocket(true)
{
}
//----------------------------------------------------------------------------------
CConnectionManager::~CConnectionManager()
{
	//������������ �� ������������
	if (m_LoginSocket.Connected)
		m_LoginSocket.Disconnect();

	if (m_GameSocket.Connected)
		m_GameSocket.Disconnect();
}
//----------------------------------------------------------------------------------
/*!
������������ ����� ������
@return ��� ������
*/
void CConnectionManager::Init()
{
	//����� ��� ������, ������
	if (m_LoginSocket.Connected)
		return;

	m_IsLoginSocket = true;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(1, 1), &wsaData);

	char hostName[1024] = {0};

	//������� ������ ��� ����� ������
	if(!gethostname(hostName, 1024))
	{
		if (LPHOSTENT lphost = gethostbyname(hostName))
		{
			WISP_DATASTREAM::CDataWritter stream;
			stream.WriteUInt32BE(((LPIN_ADDR)lphost->h_addr)->s_addr);
			UCHAR_LIST &data = stream.Data();

			memcpy(&m_Seed[0], &data[0], 4);
			g_NetworkInit(true, &data[0]);
		}
	}

	WSACleanup();
}
//---------------------------------------------------------------------------
/*!
������������� �������� ������
@param [__in] GameSeed ���� ��� �������� ����������
@return ��� ������
*/
void CConnectionManager::Init(puchar gameSeed)
{
	//���� ����� ��� ������, ������
	if (m_GameSocket.Connected)
		return;

	m_IsLoginSocket = false;

	g_NetworkInit(false, &gameSeed[0]);
}
//---------------------------------------------------------------------------
/*!
����������� � �������
@param [__in] IP IP ����� �������
@param [__in] Port ���� �������
@param [__in] GameSeed ���� ��� ����������
@return ��� ������
*/
bool CConnectionManager::Connect(const string &address, int port, puchar gameSeed)
{
	if (m_IsLoginSocket) //����� �����
	{
		if (m_LoginSocket.Connected)
			return true; //��� ��������� ����-��

		bool result = m_LoginSocket.Connect(address, port);

		if (result) //���������� ������ �����������
		{
			//��� ������ �������� �������� ����� �� 4 �����
			g_TotalSendSize = 4;
			g_LastPacketTime = g_Ticks;
			g_LastSendTime = g_LastPacketTime;

			if (g_PacketManager.ClientVersion < CV_6060)
				m_LoginSocket.Send(m_Seed, 4);
			else //� ����� �������� ���������� ����������� ����� ������
			{
				BYTE buf = 0xEF;
				m_LoginSocket.Send(&buf, 1); //0xEF - �����������, 1 ����

				m_LoginSocket.Send(m_Seed, 4); //���, 4 �����

				WISP_DATASTREAM::CDataWritter stream;

				string str = g_Orion.ClientVersionText;

				if (str.length())
				{
					char ver[20] = {0};
					char *ptr = ver;
					strncpy_s(ver, str.c_str(), str.length());
					int idx = 0;

					for (int i = 0; i < (int)str.length(); i++)
					{
						if (ver[i] == '.')
						{
							ver[i] = 0;
							stream.WriteUInt32BE(atoi(ptr));
							ptr = ver + (i + 1);
							idx++;

							if (idx > 3)
								break;
						}
					}

					stream.WriteUInt32BE(atoi(ptr));
				}

				g_TotalSendSize = 21;
				m_LoginSocket.Send(stream.Data()); //������ �������, 16 ����
			}
		}
		else
			m_LoginSocket.Disconnect();

		return result;
	}
	else //���� �����
	{
		if (m_GameSocket.Connected)
			return true; //��� ����������

		g_TotalSendSize = 4;
		g_LastPacketTime = g_Ticks;
		g_LastSendTime = g_LastPacketTime;

		bool result = m_GameSocket.Connect(address, port);

		if (result)
			m_GameSocket.Send(gameSeed, 4); //���� �� ������ - ���� ���� �� ������ �����

		m_LoginSocket.Disconnect(); //�������� ����� �����

		return result;
	}

	return false;
}
//---------------------------------------------------------------------------
/*!
��������� �����������
@return
*/
void CConnectionManager::Disconnect()
{
	//!���������� �����, ��� ����������
	if (m_LoginSocket.Connected)
		m_LoginSocket.Disconnect();

	if (m_GameSocket.Connected)
		m_GameSocket.Disconnect();
}
//---------------------------------------------------------------------------
/*!
�������� ������ � �������
@return 
*/
void CConnectionManager::Recv()
{
	if (m_IsLoginSocket) //����� �����
	{
		if (!m_LoginSocket.Connected)
			return; //�� ����������

		if (!m_LoginSocket.ReadyRead())
		{
			if (m_LoginSocket.DataReady == SOCKET_ERROR)
			{
				LOG("Failed to Recv()...Disconnecting...\n");

				g_Orion.InitScreen(GS_MAIN_CONNECT);
				g_ConnectionScreen.Type = CST_CONLOST;
			}
			return; //�� ������ � ������ ������ �����
		}

		g_PacketManager.Read(&m_LoginSocket);
	}
	else //���� �����
	{
		if (!m_GameSocket.Connected)
			return; //�� ����������

		if (!m_GameSocket.ReadyRead())
		{
			if (m_GameSocket.DataReady == SOCKET_ERROR)
			{
				LOG("Failed to Recv()...Disconnecting...\n");

				if (g_GameState == GS_GAME || (g_GameState == GS_GAME_BLOCKED && g_GameBlockedScreen.Code))
				{
					string str = "Disconnected from " + g_ServerList.GetSelectedServer()->Name;
					g_Orion.CreateTextMessage(TT_SYSTEM, 0, 3, 0x21, str);

					int x = g_ConfigManager.GameWindowX + (g_ConfigManager.GameWindowWidth / 2) - 100;
					int y = g_ConfigManager.GameWindowY + (g_ConfigManager.GameWindowHeight / 2) - 62;

					CGumpNotify *gump = new CGumpNotify(0, x, y, CGumpNotify::ID_GN_STATE_LOGOUT, 200, 125, "Connection lost");

					g_GumpManager.AddGump(gump);

					g_Orion.InitScreen(GS_GAME_BLOCKED);
					g_GameBlockedScreen.Code = 0;
				}
				else
				{
					g_Orion.InitScreen(GS_MAIN_CONNECT);
					g_ConnectionScreen.Type = CST_CONLOST;
				}
			}

			return; //�� ������ � ������ ������ �����
		}

		g_PacketManager.Read(&m_GameSocket);
	}
}
//---------------------------------------------------------------------------
/*!
��������� ��������� �������
@param [__in] buf ����� � �������
@param [__in] size ������ ������
@return ������ ������������ ������ ��� ��� ������
*/
int CConnectionManager::Send(puchar buf, int size)
{
#if UO_ABYSS_SHARD == 1
	switch (buf[0])
	{
		case 0x34:
			buf[0] = 0x71;
			break;
		case 0x72:
			buf[0] = 0x6C;
			break;
		case 0x6C:
			buf[0] = 0x72;
			break;
		case 0x3B:
			buf[0] = 0x34;
			break;
		case 0x6F:
			buf[0] = 0x56;
			break;
		case 0x56:
			buf[0] = 0x6F;
			break;
		default:
			break;
	}
#endif

	if (m_IsLoginSocket) //����� �����
	{
		if (!m_LoginSocket.Connected)
			return 0; //��� �����������

		UCHAR_LIST cbuf(size); //������ ��� ������������� ������

		g_NetworkAction(true, &buf[0], &cbuf[0], size);

		return m_LoginSocket.Send(cbuf); //���������� ������������� �����
	}
	else
	{
		if (!m_GameSocket.Connected)
			return 0; //��� �����������

		UCHAR_LIST cbuf(size); //������ ��� ������������� ������

		g_NetworkAction(false, &buf[0], &cbuf[0], size);

		return m_GameSocket.Send(cbuf); //���������� ������������� �����
	}

	return 0;
}
//---------------------------------------------------------------------------
int CConnectionManager::Send(const UCHAR_LIST &data)
{
	return Send((puchar)&data[0], data.size());
}
//---------------------------------------------------------------------------