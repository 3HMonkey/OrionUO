/****************************************************************************
**
** ConnectionManager.cpp
**
** Copyright (C) September 2015 Hotride
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
*****************************************************************************
*/
//---------------------------------------------------------------------------
#include "stdafx.h"

TConnectionManager ConnectionManager;
//---------------------------------------------------------------------------
TConnectionManager::TConnectionManager()
: m_LastMessageFragment(NULL), m_EncryptionType(ET_NOCRYPT), m_ClientVersion(CV_OLD),
m_SocketType(true)
{
}
//---------------------------------------------------------------------------
TConnectionManager::~TConnectionManager()
{
	//������������ �� ������������
	if (m_LoginSocket.Connected())
		m_LoginSocket.Disconnect();
	if (m_GameSocket.Connected())
		m_GameSocket.Disconnect();

	//������� ��������, ���� ����
	if (m_LastMessageFragment != NULL)
		delete m_LastMessageFragment;
	m_LastMessageFragment = NULL;
}
//---------------------------------------------------------------------------
/*!
������������ ����� ������
@param [__in] k1 ���� ���������� 1
@param [__in] k2 ���� ���������� 2
@param [__in] k3 ���� ���������� 3
@param [__in] seed_key ����� ��� ��������� ����������
@return ��� ������
*/
int TConnectionManager::Init( __in DWORD k1, __in DWORD k2, __in DWORD k3, __in DWORD seed_key)
{
	//����� ��� ������, ������
	if (m_LoginSocket.Connected())
		return CE_CONNECTED;

	m_SocketType = true;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(1, 1), &wsaData);

	char HostName[1024] = {0};

	//������� ������ ��� ����� ������
	if(!gethostname(HostName, 1024))
	{
		if (LPHOSTENT lphost = gethostbyname(HostName))
		{
			BYTE buf[4] = {0};
			pack32(buf,((LPIN_ADDR)lphost->h_addr)->s_addr);

			BYTE c = buf[0];
			buf[0] = buf[3];
			buf[3] = c;
			c = buf[1];
			buf[1] = buf[2];
			buf[2] = c;

			m_LoginCrypt.Init(buf, k1, k2, k3, seed_key);
		}
	}

	WSACleanup();
		
	return m_LoginSocket.Init();
}
//---------------------------------------------------------------------------
/*!
������������� �������� ������
@param [__in] GameSeed ���� ��� �������� ����������
@return ��� ������
*/
int TConnectionManager::Init(__in PBYTE GameSeed)
{
	//���� ����� ��� ������, ������
	if (m_GameSocket.Connected())
		return CE_CONNECTED;

	m_SocketType = false;

	//������������� ����������
	if (m_EncryptionType != ET_NOCRYPT)
		m_BlowfishCrypt.Init();

	if (m_EncryptionType == ET_203 || m_EncryptionType == ET_TFISH)
	{
		m_TwoFishCrypt.Init(GameSeed);

		if (m_EncryptionType == ET_TFISH)
			m_TwoFishCrypt.Init_MD5();
	}

	return m_GameSocket.Init();
}
//---------------------------------------------------------------------------
/*!
����������� � �������
@param [__in] IP IP ����� �������
@param [__in] Port ���� �������
@param [__in] GameSeed ���� ��� ����������
@return ��� ������
*/
int TConnectionManager::Connect( __in const char *IP, __in int Port, __in PBYTE GameSeed)
{
	if (m_SocketType) //����� �����
	{
		if (m_LoginSocket.Connected())
			return CE_CONNECTED; //��� ��������� ����-��

		int ret = m_LoginSocket.Connect(IP, Port);

		if (ret == CE_NO_ERROR) //���������� ������ �����������
		{
			//��� ������ �������� �������� ����� �� 4 �����
			g_TotalSendSize = 4;
			g_LastPacketTime = GetTickCount();
			g_LastSendTime = g_LastPacketTime;

			if (m_ClientVersion < CV_6060)
				m_LoginSocket.Send(m_LoginCrypt.m_seed, 4);
			else //� ����� �������� ���������� ����������� ����� ������
			{
				BYTE buf[16] = {0};
				buf[0] = 0xEF;
				m_LoginSocket.Send(buf, 1); //0xEF - �����������, 1 ����

				m_LoginSocket.Send(m_LoginCrypt.m_seed, 4); //���, 4 �����

				buf[0] = 0;
				string str = g_ClientVersionText;
				if (str.length())
				{
					char ver[20] = {0};
					char *ptr = ver;
					strncpy(ver, str.c_str(), str.length());
					int idx = 0;

					for (int i = 0; i < (int)str.length(); i++)
					{
						if (ver[i] == '.')
						{
							ver[i] = 0;
							pack32(buf + (idx * 4), atoi(ptr));
							ptr = ver + (i + 1);
							idx++;

							if (idx > 3)
								break;
						}
					}

					pack32(buf + (idx * 4), atoi(ptr));
				}

				g_TotalSendSize = 21;

				m_LoginSocket.Send(buf, 16); //������ �������, 16 ����
			}
		}
		else
			m_LoginSocket.Disconnect();

		return ret;
	}
	else //���� �����
	{
		if (m_GameSocket.Connected())
			return CE_CONNECTED; //��� ����������

		g_TotalSendSize = 4;
		g_LastPacketTime = GetTickCount();
		g_LastSendTime = g_LastPacketTime;
		int ret = m_GameSocket.Connect(IP, Port);

		if (ret == CE_NO_ERROR)
			m_GameSocket.Send(GameSeed, 4); //���� �� ������ - ���� ���� �� ������ �����

		m_LoginSocket.Disconnect(); //�������� ����� �����

		return ret;
	}

	return 0;
}
//---------------------------------------------------------------------------
/*!
��������� �����������
@return
*/
void TConnectionManager::Disconnect()
{
	//!���������� �����, ��� ����������
	if (m_LoginSocket.Connected())
		m_LoginSocket.Disconnect();

	if (m_GameSocket.Connected())
		m_GameSocket.Disconnect();
}
//---------------------------------------------------------------------------
/*!
�������� ������ � �������
@return 
*/
void TConnectionManager::Recv()
{
	if (m_SocketType) //����� �����
	{
		if (!m_LoginSocket.Connected())
			return; //�� ����������

		if (!m_LoginSocket.DataReady())
			return; //�� ������ � ������ ������ �����

		BYTE Data[SOCK_RECV_BUF_SIZE] = {0};
		int size = 0;

		if (m_LoginSocket.Recv(Data, size) > 0) //���� ������ �������� - ������������
		{
			PBYTE ptr = Data;
			PBYTE end = ptr + size;

			if (m_LastMessageFragment != NULL) //���������� ��������� �� ���� ���������� �������
			{
				ptr += m_LastMessageFragment->Append(ptr, size); //������� � �������� ������

				if (!m_LastMessageFragment->Complete())
					return; //��������� ������ ��������� �� ����������, ���������

				//��������� ������ ��������� ����������, ���������� ����� �� ������, � PacketManager
				PacketManager.ReceiveHandler(m_LastMessageFragment->Get(), m_LastMessageFragment->Size());

				//�������� ��� ������ �� ���������, ������ ���
				delete m_LastMessageFragment;
				m_LastMessageFragment = NULL;
			}

			while (ptr < end) //���������� �� ���������� � �������
			{
				//������ ��������������� ������
				int msg_size = PacketManager.GetPacketSize(*ptr);

				if (msg_size == -1) //����������� ����� (������ ��� ���� �� �����)
				{
					EPRINT("Length unknown for message 0x%02X\n", *ptr);
					msg_size = 0;
				}
				else
				{
					//���� ��� ������������ ����� ������
					if (msg_size == 0 && ptr + 3 <= end)
						msg_size = (ptr[1] << 8) | ptr[2];
				}

				//���� ��� ������������ ����� ������ ��� ����� �� ��� ��������� �������
				if (msg_size == 0 || ptr + msg_size > end)
				{
					m_LastMessageFragment = new TMessageFragment(ptr, end - ptr, msg_size);
					ptr = end;
				}
				else //��������� ������ ������ � ������ ���������� ��� ���������
				{
					//���������� ����� �� ������, � PacketManager
					PacketManager.ReceiveHandler(ptr, msg_size);
					ptr += msg_size;
				}
			}
		}
		else //������ ������, ��������������
		{
			TPRINT("Failed to Recv()...Disconnecting...\n");
			m_LoginSocket.Disconnect();

			UO->InitScreen(GS_MAIN_CONNECT);
			ConnectionScreen->Type = CST_CONLOST;
		}
	}
	else //���� �����
	{
		if (!m_GameSocket.Connected())
			return; //�� ����������

		if (!m_GameSocket.DataReady())
			return; //�� ������ � ������ ������ �����

		BYTE Data[SOCK_RECV_BUF_SIZE] = {0};
		int size = 0;

		if (m_GameSocket.Recv(Data, size) > 0) //���� ������ �������� - ������������
		{
			PBYTE dec_buf = new BYTE[size * 4 + 2];
			int in_bytes = size, out_bytes = 65536;

			m_Decompressor((char*)dec_buf, (char*)Data, out_bytes, in_bytes); //���������

			if (in_bytes != size) //������ ������������ ������������
			{
				EPRINT("decompression buffer too small\n");
				m_GameSocket.Disconnect();
				delete dec_buf;
				return;
			}

			PBYTE ptr = dec_buf;
			PBYTE end = ptr + out_bytes;
			
			if (m_LastMessageFragment != NULL) //���������� ��������� �� ���� ���������� �������
			{
				ptr += m_LastMessageFragment->Append(ptr, out_bytes); //������� � �������� ������

				if (!m_LastMessageFragment->Complete()) //��������� ������ ��������� �� ����������, ���������
				{
					delete dec_buf;
					return;
				}

				//��������� ������ ��������� ����������, ���������� ����� �� ������, � PacketManager
				PacketManager.ReceiveHandler(m_LastMessageFragment->Get(), m_LastMessageFragment->Size());

				//�������� ��� ������ �� ���������, ������ ���
				delete m_LastMessageFragment;
				m_LastMessageFragment = NULL;
			}

			while (ptr < end) //���������� �� ���������� � �������
			{
				//������ ��������������� ������
				int msg_size = PacketManager.GetPacketSize(*ptr);

				if (msg_size == -1) //����������� ����� (������ ��� ���� �� �����)
				{
					EPRINT("Length unknown for message 0x%02X\n", *ptr);
					msg_size = 0;
				}
				else
				{
					//���� ��� ������������ ����� ������
					if (msg_size == 0 && ptr + 3 <= end)
						msg_size = (ptr[1] << 8) | ptr[2];
				}

				//���� ��� ������������ ����� ������ ��� ����� �� ��� ��������� �������
				if (msg_size == 0 || ptr + msg_size > end)
				{
					m_LastMessageFragment = new TMessageFragment(ptr, end - ptr, msg_size);
					ptr = end;
				}
				else //��������� ������ ������ � ������ ���������� ��� ���������
				{
					//���������� ����� �� ������, � PacketManager
					PacketManager.ReceiveHandler(ptr, msg_size);
					ptr += msg_size;
				}
			}

			delete dec_buf;
		}
		else //������ ������, ��������������
		{
			TPRINT("Failed to Recv()...Disconnecting...\n");
			m_GameSocket.Disconnect();

			if (g_GameState == GS_GAME || (g_GameState == GS_GAME_BLOCKED && GameBlockedScreen->Code))
			{
				string str = "Disconnected from " + ServerList.GetServerName();
				UO->CreateTextMessage(TT_SYSTEM, 0, 3, 0x21, str);

				int x = g_GameWindowPosX + (g_GameWindowWidth / 2) - 100;
				int y = g_GameWindowPosY + (g_GameWindowHeight / 2) - 62;

				TGumpNotify *gump = new TGumpNotify(0, x, y, 1, 200, 125, "Connection lost");

				GumpManager->AddGump(gump);

				UO->InitScreen(GS_GAME_BLOCKED);
				GameBlockedScreen->Code = 0;
			}
			else
			{
				UO->InitScreen(GS_MAIN_CONNECT);
				ConnectionScreen->Type = CST_CONLOST;
			}
		}
	}
}
//---------------------------------------------------------------------------
/*!
��������� ��������� �������
@param [__in] buf ����� � �������
@param [__in] size ������ ������
@return ������ ������������ ������ ��� ��� ������
*/
int TConnectionManager::Send(PBYTE buf, int size)
{
#if UO_ABYSS_SHARD == 1
	if (buf[0] == 0x34)
		buf[0] = 0x71;
	else if (buf[0] == 0x72)
		buf[0] = 0x6C;
	else if (buf[0] == 0x6C)
		buf[0] = 0x72;
	else if (buf[0] == 0x3B)
		buf[0] = 0x34;
	else if (buf[0] == 0x6F)
		buf[0] = 0x56;
	else if (buf[0] == 0x56)
		buf[0] = 0x6F;
#endif

	if (m_SocketType) //����� �����
	{
		if (!m_LoginSocket.Connected())
			return CE_NOT_CONNECTED; //��� �����������

		PBYTE cbuf = new BYTE[size]; //������ ��� ������������� ������

		//�������, �������������� ��������� ����� ����������
		if (m_EncryptionType == ET_OLD_BFISH)
			m_LoginCrypt.Encrypt_Old(buf, cbuf, size);
		else if (m_EncryptionType == ET_1_25_36)
			m_LoginCrypt.Encrypt_1_25_36(buf, cbuf, size);
		else if (m_EncryptionType != ET_NOCRYPT)
			m_LoginCrypt.Encrypt(buf, cbuf, size);
		else
			memcpy(cbuf, buf, size); //��� ������ ��������� ������, ���� ���������� �����������

		int ret = m_LoginSocket.Send(cbuf, size); //���������� ������������� �����

		delete cbuf;

		return ret;
	}
	else
	{
		if (!m_GameSocket.Connected()) return CE_NOT_CONNECTED; //��� �����������

		PBYTE cbuf = new BYTE[size]; //������ ��� ������������� ������

		if (m_EncryptionType == ET_NOCRYPT)
			memcpy(cbuf, buf, size); //��������� ������, ���� ���������� �����������
		else
		{
			//�������, �������������� ��������� ����� ����������
			if (m_EncryptionType == ET_203)
			{
				m_BlowfishCrypt.Encrypt(buf, cbuf, size);
				m_TwoFishCrypt.Encrypt(cbuf, cbuf, size);
			}
			else if (m_EncryptionType == ET_TFISH)
				m_TwoFishCrypt.Encrypt(buf, cbuf, size);
			else
				m_BlowfishCrypt.Encrypt(buf, cbuf, size);
		}

		int ret = m_GameSocket.Send(cbuf, size); //���������� ������������� �����

		delete cbuf;

		return ret;
	}

	return 0;
}
//---------------------------------------------------------------------------