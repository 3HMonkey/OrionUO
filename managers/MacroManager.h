/****************************************************************************
**
** MacroManager.h
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
#ifndef MacroManagerH
#define MacroManagerH
//---------------------------------------------------------------------------
//!����� ��������� ��������
class TMacroManager : public TBaseQueue
{
private:
	//!����� ���������� ����������
	DWORD m_NextTimer;

	//!����� �������� �������
	DWORD m_WaitForTargetTimer;

	//!�������� ������� �� ������
	bool m_WaitingBandageTarget;

	//!������� ������� ��� �������������
	static BYTE m_SkillIndexTable[24];

	/*!
	��������� ������� �������
	@return 
	*/
	void ProcessSubMenu();

	/*!
	��������������� ������ � ����������� ��� �������
	@param [__in] strings �������� ������, ��� ������� ������� ������� ������
	@return ����
	*/
	WORD ConvertStringToKeyCode(__in const vector<string> &strings);

public:
	TMacroManager();
	virtual ~TMacroManager();

	SETGET(bool, WaitingBandageTarget);
	SETGET(DWORD, WaitForTargetTimer);

	/*!
	����� �������
	@param [__in] key ������ ������
	@param [__in] alt ������� ����
	@param [__in] ctrl ������� �������
	@param [__in] shift ������� ����
	@return ������ �� ������ ��� NULL
	*/
	TMacro *FindMacro(__in WORD key, __in bool alt, __in bool ctrl, __in bool shift);

	/*!
	��������������� ���� �������� ������������� �������
	@param [__in] path ���� � ����� � ���������
	@return true ��� �������� ���������������
	*/
	bool Convert(__in string path);

	/*!
	��������� ������� �� �������
	@param [__in] path ���� � ����� �������
	@param [__in] originalPath ���� � ����� � ��������� ������������� �������
	@return 
	*/
	bool Load(__in string path, __in string originalPath);

	/*!
	��������� ������� � ������
	@param [__in] path ���� � ����� �������
	@return 
	*/
	void Save(__in string path);

	/*!
	��������� ������� �� �����
	@return 
	*/
	void LoadFromOptions();

	/*!
	������ ���������� �������
	@return 
	*/
	void Execute();

	/*!
	��������� �������� ������� (��� ����� ��������)
	@return ��� ����������
	*/
	MACRO_RETURN_CODE Process();
};
//---------------------------------------------------------------------------
//!������ �� �������� ��������
extern TMacroManager *MacroManager;
//---------------------------------------------------------------------------
#endif