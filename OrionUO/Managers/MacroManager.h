/***********************************************************************************
**
** MacroManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef MACROMANAGER_H
#define MACROMANAGER_H
//----------------------------------------------------------------------------------
#include "../BaseQueue.h"
#include "../Globals.h"
//----------------------------------------------------------------------------------
//!����� ��������� ��������
class CMacroManager : public CBaseQueue
{
	//!�������� ������� �� ������
	SETGET(bool, WaitingBandageTarget);
	//!����� �������� �������
	SETGET(uint, WaitForTargetTimer);

private:
	//!����� ���������� ����������
	uint m_NextTimer;

	//!������� ������� ��� �������������
	static uchar m_SkillIndexTable[24];

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
	ushort ConvertStringToKeyCode(const STRING_LIST &strings);

public:
	CMacroManager();
	virtual ~CMacroManager();

	/*!
	����� �������
	@param [__in] key ������ ������
	@param [__in] alt ������� ����
	@param [__in] ctrl ������� �������
	@param [__in] shift ������� ����
	@return ������ �� ������ ��� NULL
	*/
	class CMacro *FindMacro(const ushort &key, const bool &alt, const bool &ctrl, const bool &shift);

	/*!
	��������������� ���� �������� ������������� �������
	@param [__in] path ���� � ����� � ���������
	@return true ��� �������� ���������������
	*/
	bool Convert(const string &path);

	/*!
	��������� ������� �� �������
	@param [__in] path ���� � ����� �������
	@param [__in] originalPath ���� � ����� � ��������� ������������� �������
	@return 
	*/
	bool Load(const string &path, const string &originalPath);

	/*!
	��������� ������� � ������
	@param [__in] path ���� � ����� �������
	@return 
	*/
	void Save(const string &path);

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
//----------------------------------------------------------------------------------
//!������ �� �������� ��������
extern CMacroManager g_MacroManager;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
