/***********************************************************************************
**
** SkillGroupManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef SKILLGROUPMANAGER_H
#define SKILLGROUPMANAGER_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../SkillGroup.h"
//----------------------------------------------------------------------------------
//!����� ��������� ����� �������
class CSkillGroupManager
{
	SETGET(int, Count);

private:
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
	CSkillGroupObject *m_Groups;

	CSkillGroupManager();
	~CSkillGroupManager();


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
	void Add(CSkillGroupObject *group);

	/*!
	������� ������
	@param [__in] group ������ �� ������
	@return 
	*/
	void Remove(CSkillGroupObject *group);

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
	bool Load(string path);

	/*!
	���������� ����� � ���� ������
	@param [__in] path �����  ����� �������
	@return 
	*/
	void Save(string path);
};
//----------------------------------------------------------------------------------
//!�������� ����� �������
extern CSkillGroupManager g_SkillGroupManager;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
