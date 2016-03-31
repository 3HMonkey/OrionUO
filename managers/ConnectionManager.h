/****************************************************************************
**
** ConnectionManager.h
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
#ifndef ConnectionManagerH
#define ConnectionManagerH
//---------------------------------------------------------------------------
//!����� ��������� ����������� � �������
class TConnectionManager
{
private:
	//!����������� � ������ �����������
	TConnection m_LoginSocket;

	//!����������� � ������ �������
	TConnection m_GameSocket;

	//!����������������� ���������
	TMessageFragment *m_LastMessageFragment;

	//!��� ����������
	ENCRYPTION_TYPE m_EncryptionType;

	//!������ ���������
	CLIENT_VERSION m_ClientVersion;

	//!���������� ��� ������ �����������
	TLoginCrypt m_LoginCrypt;

	//!����
	TBlowfishCrypt m_BlowfishCrypt;
	TTwofishCrypt m_TwoFishCrypt;

	//!����� ������������
	TDecompressingCopier m_Decompressor;

	//!��� ������. true - Login, false - game
	bool m_SocketType;

public:
	TConnectionManager();
	~TConnectionManager();

	SETGET(ENCRYPTION_TYPE, EncryptionType);
	SETGET(CLIENT_VERSION, ClientVersion);

	/*!
	������������ ����� ������
	@param [__in] k1 ���� ���������� 1
	@param [__in] k2 ���� ���������� 2
	@param [__in] k3 ���� ���������� 3
	@param [__in] seed_key ����� ��� ��������� ����������
	@return ��� ������
	*/
	int Init(__in DWORD k1, __in DWORD k2, __in DWORD k3, __in DWORD seed_key);

	/*!
	������������� �������� ������
	@param [__in] GameSeed ���� ��� �������� ����������
	@return ��� ������
	*/
	int Init(__in PBYTE GameSeed);

	/*!
	��������� �����������
	@return true - ����������
	*/
	bool Connected() {return (m_LoginSocket.Connected() || m_GameSocket.Connected());}

	/*!
	����������� � �������
	@param [__in] IP IP ����� �������
	@param [__in] Port ���� �������
	@param [__in] GameSeed ���� ��� ����������
	@return ��� ������
	*/
	int Connect(__in const char *IP, __in int Port, __in PBYTE GameSeed);

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
	int Send(__in PBYTE buf, __in int size);

	/*!
	�������� ���� IP-�����
	@return 
	*/
	PBYTE GetClientIP() const {return (PBYTE)m_LoginCrypt.m_seed;}
};
//---------------------------------------------------------------------------
//!�������� �����������
extern TConnectionManager ConnectionManager;
//---------------------------------------------------------------------------
#endif