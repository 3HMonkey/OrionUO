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
#include "../EnumList.h"
//----------------------------------------------------------------------------------
typedef void __cdecl NETWORK_INIT_TYPE(const bool&, BYTE*);
typedef void __cdecl NETWORK_ACTION_TYPE(const bool&, BYTE*, BYTE*, const int&);
//----------------------------------------------------------------------------------
extern NETWORK_INIT_TYPE *g_NetworkInit;
extern NETWORK_ACTION_TYPE *g_NetworkAction;
//----------------------------------------------------------------------------------
//!����� ��������� ����������� � �������
class CConnectionManager
{
private:
	//!����������� � ������ �����������
	CSocket m_LoginSocket;

	//!����������� � ������ �������
	CSocket m_GameSocket;

	//!��� ������. true - Login, false - game
	bool m_IsLoginSocket;

	uchar m_Seed[4];

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
	puchar GetClientIP() const { return (puchar)m_Seed; }
};
//---------------------------------------------------------------------------
//!�������� �����������
extern CConnectionManager g_ConnectionManager;
//---------------------------------------------------------------------------
#endif