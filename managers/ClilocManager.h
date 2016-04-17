/****************************************************************************
**
** ClilocManager.h
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
#ifndef ClilocManagerH
#define ClilocManagerH
//---------------------------------------------------------------------------
typedef std::map<DWORD, string> CLILOC_MAP;
//---------------------------------------------------------------------------
//!����� � ������� ������-�����
class TCliloc : public TBaseQueueItem
{
private:
	//!��������� ������� (id < 1000000)
	CLILOC_MAP m_ClilocSystem;

	//!������� ������� (id >= 1000000 && id < 3000000)
	CLILOC_MAP m_ClilocRegular;

	//!������� ��� ������ (id >= 3000000)
	CLILOC_MAP m_ClilocSupport;

	//!��������� �� �������� ����� � ������ (��� �� �����)
	TMappedHeader m_File;

	//!��� �������
	string m_Language;

	//!������ ��������
	bool m_Loaded;

	/*!
	��������� ������
	@param [__in] id ������ �������
	@return ��������� �������� ��� ��������� � �������
	*/
	string Load(__in DWORD &id);

public:
	TCliloc(string lang);
	virtual ~TCliloc();

	SETGET(string, Language);
	SETGET(bool, Loaded);

	/*!
	�������� ASCII ������ �� id (� ��������� ��� �������������)
	@param [__in] id ������ �������
	@param [__in] result ����������� ���������, ���� ������ �� ��� ������
	@return ���������� ���������, ������ ��� ��������� � �������
	*/
	string GetA(__in DWORD id, __in string result = "");

	/*!
	�������� Unicode ������ �� id (� ��������� ��� �������������)
	@param [__in] id ������ �������
	@param [__in] result ����������� ���������, ���� ������ �� ��� ������
	@return ���������� ���������, ������ ��� ��������� � �������
	*/
	wstring GetW(__in DWORD id, __in string result = "");
};
//---------------------------------------------------------------------------
//!����� ��������� ��������
class TClilocManager : public TBaseQueue
{
private:
	//!������ �� ��������� �������������� ������ (��� ����� �������� �������)
	TCliloc *m_LastCliloc;

public:
	TClilocManager();
	virtual ~TClilocManager();

	/*!
	�������� ������ �� ������ ������� (� ��������� ��� �������������)
	@param [__in] lang ���������� �������
	@return ������ �� ������
	*/
	TCliloc *Cliloc(__in string lang);

	wstring ParseArgumentsToClilocString(DWORD cliloc, wstring args);
};
//---------------------------------------------------------------------------
//!������ �� �������� ��������
extern TClilocManager *ClilocManager;
//---------------------------------------------------------------------------
#endif