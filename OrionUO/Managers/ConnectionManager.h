/***********************************************************************************
**
** ConnectionManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../Network/Connection.h"
#include "../Network/LoginCrypt.h"
#include "../Network/GameCrypt.h"
#include "../EnumList.h"
//----------------------------------------------------------------------------------
//!����� ��������� ����������� � �������
class CConnectionManager
{
	//!��� ����������
	SETGET(ENCRYPTION_TYPE, EncryptionType);

	//!������ ���������
	SETGET(CLIENT_VERSION, ClientVersion);

	SETGET(uint, CryptKey1);
	SETGET(uint, CryptKey2);
	SETGET(uint, CryptKey3);
	SETGET(ushort, CryptSeed);

private:
	//!����������� � ������ �����������
	CSocket m_LoginSocket;

	//!����������� � ������ �������
	CSocket m_GameSocket;

	//!���������� ��� ������ �����������
	CLoginCrypt m_LoginCrypt;

	//!����
	CBlowfishCrypt m_BlowfishCrypt;
	CTwofishCrypt m_TwoFishCrypt;

	//!��� ������. true - Login, false - game
	bool m_IsLoginSocket;

public:
	CConnectionManager();
	~CConnectionManager();

	/*!
	������������ ����� ������
	@return 
	*/
	void Init();

	/*!
	������������� �������� ������
	@param [__in] GameSeed ���� ��� �������� ����������
	@return ��� ������
	*/
	void Init(puchar GameSeed);

	/*!
	��������� �����������
	@return true - ����������
	*/
	bool Connected() { return (m_LoginSocket.Connected || m_GameSocket.Connected); }

	/*!
	����������� � �������
	@param [__in] IP IP ����� �������
	@param [__in] Port ���� �������
	@param [__in] GameSeed ���� ��� ����������
	@return ��� ������
	*/
	bool Connect(const string &address, int port, puchar gameSeed);

	/*!
	��������� �����������
	@return 
	*/
	void Disconnect();

	/*!
	�������� ������ � �������
	@return 
	*/
	void Recv();

	/*!
	��������� ��������� �������
	@param [__in] buf ����� � �������
	@param [__in] size ������ ������
	@return ������ ������������ ������ ��� ��� ������
	*/
	int Send(puchar buf, int size);

	int Send(const UCHAR_LIST &data);

	/*!
	�������� ���� IP-�����
	@return 
	*/
	puchar GetClientIP() const { return (puchar)m_LoginCrypt.m_seed; }
};
//---------------------------------------------------------------------------
//!�������� �����������
extern CConnectionManager g_ConnectionManager;
//---------------------------------------------------------------------------
#endif