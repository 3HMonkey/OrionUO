/****************************************************************************
**
** SkillGroupManager.h
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
#ifndef SkillGroupManagerH
#define SkillGroupManagerH
//---------------------------------------------------------------------------
//!����� ��������� ����� �������
class TSkillGroupManager
{
private:
	//!���������� �����
	int m_Count;

	//!����������� �������� ��-��������� ��� ����������� �����
	void MakeDefaultMiscellaneous();
	void MakeDefaultCombat();
	void MakeDefaultTradeSkills();
	void MakeDefaultMagic();
	void MakeDefaultWilderness();
	void MakeDefaultThieving();
	void MakeDefaultBard();

public:
	//!��������� �� ������ �����
	TSkillGroupObject *m_Groups;

	TSkillGroupManager();
	~TSkillGroupManager();

	SETGET(int, Count);

	/*!
	��������� ������ ��-���������
	@return
	*/
	void MakeDefault();

	/*!
	�������� ������ �����
	@return 
	*/
	void Clear();

	/*!
	�������� ������
	@param [__in] group ������ �� ������
	@return 
	*/
	void Add(__in TSkillGroupObject *group);

	/*!
	������� ������
	@param [__in] group ������ �� ������
	@return 
	*/
	void Remove(__in TSkillGroupObject *group);

	/*!
	�������� ������ ������� �����
	@return ���������� ������� �����
	*/
	int GetVisibleLinesCount();

	/*!
	�������� ����� �� ����� �������
	@param [__in] path ���� � ����� �������
	@return 
	*/
	void Load(__in string path);

	/*!
	���������� ����� � ���� ������
	@param [__in] path �����  ����� �������
	@return 
	*/
	void Save(__in string path);
};
//---------------------------------------------------------------------------
//!�������� ����� �������
extern TSkillGroupManager SkillGroupManager;
//---------------------------------------------------------------------------
#endif