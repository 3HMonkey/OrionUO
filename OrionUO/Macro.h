/***********************************************************************************
**
** Macro.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef MACRO_H
#define MACRO_H
//----------------------------------------------------------------------------------
#include "BaseQueue.h"
#include "Globals.h"
#include "Wisp/WispMappedFile.h"
#include "Wisp/WispBinaryFileWritter.h"
//----------------------------------------------------------------------------------
//����� ������� �������
class CMacroObject : public CBaseQueueItem
{
	//��� ��������
	SETGET(MACRO_CODE, Code);

	//������ ��������
	SETGET(MACRO_SUB_CODE, SubCode);

	//����� �������
	SETGET(char, HasSubMenu);

public:
	CMacroObject(const MACRO_CODE &code, const MACRO_SUB_CODE &subCode);
	virtual ~CMacroObject();

	virtual bool HaveString() { return false; }
};
//----------------------------------------------------------------------------------
//����� ������� �������, ���������� ������
class CMacroObjectString : public CMacroObject
{
	//������ ��������
	SETGET(string, String);

public:
	CMacroObjectString(const MACRO_CODE &code, const MACRO_SUB_CODE &subCode, const string &str);
	virtual ~CMacroObjectString();

	virtual bool HaveString() { return true; }
};
//----------------------------------------------------------------------------------
//����� �������
class CMacro : public CBaseQueueItem
{
	//��� ������� ��� ������������ �������
	SETGET(ushort, Key);

	//����� �������������� ������
	SETGET(bool, Alt);
	SETGET(bool, Ctrl);
	SETGET(bool, Shift);

public:
	CMacro(const ushort &key, const bool &alt, const bool &ctrl, const bool &shift);
	virtual ~CMacro();

	static const int MACRO_ACTION_NAME_COUNT = 60;
	static const int MACRO_ACTION_COUNT = 210;

	//�������� ��������
	static const char *m_MacroActionName[MACRO_ACTION_NAME_COUNT];

	//�������� ��������
	static const char *m_MacroAction[MACRO_ACTION_COUNT];

	static const char *GetActionName(int index) { return m_MacroActionName[index]; }
	static const char *GetAction(int index) { return m_MacroAction[index]; }

	//�������� ������
	void ChangeObject(CMacroObject *source, CMacroObject *obj);

	//��������� ������� �� �����
	static CMacro *Load(WISP_FILE::CMappedFile &file);

	//��������� ������� � ����
	void Save(WISP_FILE::CBinaryFileWritter &writter);

	//������� ������ ������
	static CMacro *CreateBlankMacro();

	//������� ������ �� ����
	static CMacroObject *CreateMacro(const MACRO_CODE &code);

	//�������� �������� ������� �������� ������������ ������ ������ � ���������� � ������
	static void GetBoundByCode(const MACRO_CODE &code, int &count, int &offset);

	//�������� ����� ��������
	CMacro *GetCopy();
};
//----------------------------------------------------------------------------------
extern CMacroObject *g_MacroPointer;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
