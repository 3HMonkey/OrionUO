/***********************************************************************************
**
** ProfessionManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef PROFESSIONMANAGER_H
#define PROFESSIONMANAGER_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../BaseQueue.h"
#include "../Wisp/WispTextFileParser.h"
#include "../Profession.h"
//----------------------------------------------------------------------------------
//!����� ��������� ���������
class CProfessionManager : public CBaseQueue
{
private:
	//!���������� ������ �������
	static const int m_KeyCount = 18;

	//!����� �������
	static const string m_Keys[m_KeyCount];

	enum
	{
		PM_CODE_BEGIN = 1,
		PM_CODE_NAME,
		PM_CODE_TRUENAME,
		PM_CODE_DESC,
		PM_CODE_TOPLEVEL,
		PM_CODE_GUMP,
		PM_CODE_TYPE,
		PM_CODE_CHILDREN,
		PM_CODE_SKILL,
		PM_CODE_STAT,
		PM_CODE_STR,
		PM_CODE_INT,
		PM_CODE_DEX,
		PM_CODE_END,
		PM_CODE_TRUE,
		PM_CODE_CATEGORY,
		PM_CODE_NAME_CLILOC_ID,
		PM_CODE_DESCRIPTION_CLILOC_ID
	};

	/*!
	�������� ��� ������ �� ������
	@param [__in] key ������ �� �����
	@return ��� �������
	*/
	int GetKeyCode(const string &key);

	/*!
	���������� ����� ����� (�������� ���������)
	@param [__in] file ��������� �� ����
	@return true ��� �������� ���������
	*/
	bool ParseFilePart(WISP_FILE::CTextFileParser &file);

	/*!
	�������� ������� � ���������
	@param [__in] parent ������ �� ��������
	@param [__in] child ������ �� �������
	@return true � ������ ��������� ����������
	*/
	bool AddChild(CBaseProfession *parent, CBaseProfession *child);

	/*!
	�������� �������� ���������
	@return 
	*/
	void LoadProfessionDescription();

public:
	CProfessionManager();
	virtual ~CProfessionManager();

	//!�������� ��������� �� ��������� ���������
	CBaseProfession *Selected;

	/*!
	�������� �������� ���������
	@param [__in] obj ������ �� ������ ���������
	@param [__in_opt] check ������ �� ����������� ������ ���������
	@return ������ �� ���������� �������� ������� ���������
	*/
	CBaseProfession *GetParent(CBaseProfession *obj, CBaseProfession *check = NULL);

	/*!
	�������� ��������� �� �����
	@return true � ������ �������� ��������
	*/
	bool Load();
};
//---------------------------------------------------------------------------
//!������ �� �������� ���������
extern CProfessionManager g_ProfessionManager;
//---------------------------------------------------------------------------
#endif