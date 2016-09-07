/***********************************************************************************
**
** ClilocManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef CLILOCMANAGER_H
#define CLILOCMANAGER_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../BaseQueue.h"
#include "../Wisp/WispMappedFile.h"
//----------------------------------------------------------------------------------
typedef map<uint, string> CLILOC_MAP;
//----------------------------------------------------------------------------------
//!����� � ������� ������-�����
class CCliloc : public CBaseQueueItem
{
	SETGET(string, Language);
	SETGET(bool, Loaded);

private:
	//!��������� ������� (id < 1000000)
	CLILOC_MAP m_ClilocSystem;

	//!������� ������� (id >= 1000000 && id < 3000000)
	CLILOC_MAP m_ClilocRegular;

	//!������� ��� ������ (id >= 3000000)
	CLILOC_MAP m_ClilocSupport;

	//!��������� �� �������� ����� � ������ (��� �� �����)
	WISP_FILE::CMappedFile m_File;

	/*!
	��������� ������
	@param [__in] id ������ �������
	@return ��������� �������� ��� ��������� � �������
	*/
	string Load(uint &id);

public:
	CCliloc(string lang);
	virtual ~CCliloc();

	/*!
	�������� ASCII ������ �� id (� ��������� ��� �������������)
	@param [__in] id ������ �������
	@param [__in] result ����������� ���������, ���� ������ �� ��� ������
	@return ���������� ���������, ������ ��� ��������� � �������
	*/
	string GetA(uint id, string result = "");

	/*!
	�������� Unicode ������ �� id (� ��������� ��� �������������)
	@param [__in] id ������ �������
	@param [__in] result ����������� ���������, ���� ������ �� ��� ������
	@return ���������� ���������, ������ ��� ��������� � �������
	*/
	wstring GetW(uint id, string result = "");
};
//----------------------------------------------------------------------------------
//!����� ��������� ��������
class CClilocManager : public CBaseQueue
{
private:
	//!������ �� ��������� �������������� ������ (��� ����� �������� �������)
	CCliloc *m_LastCliloc;

public:
	CClilocManager();
	virtual ~CClilocManager();

	/*!
	�������� ������ �� ������ ������� (� ��������� ��� �������������)
	@param [__in] lang ���������� �������
	@return ������ �� ������
	*/
	CCliloc *Cliloc(string lang);

	wstring ParseArgumentsToClilocString(uint cliloc, wstring args);
};
//----------------------------------------------------------------------------------
//!������ �� �������� ��������
extern CClilocManager g_ClilocManager;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
