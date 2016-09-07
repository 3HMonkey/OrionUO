/***********************************************************************************
**
** SpeechManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef SPEECHMANAGER_H
#define SPEECHMANAGER_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
//----------------------------------------------------------------------------------
class CLangCode
{
	SETGET(string, Code);

	//! ���������, ���������� ����������� ������.
	SETGET(string, LangString);

	//! �������� ����������� ������? ������.
	SETGET(uint, Unknown);

	//! �������� �����.
	SETGET(string, LangName);

	//! �������� ������.
	SETGET(string, LangCountry);

public:
	CLangCode();
	virtual ~CLangCode();
};
//----------------------------------------------------------------------------------
class CSpeechItem
{
	//! ��� ���������� �������.
	SETGET(ushort, Code);

	//! ������ � �������� ������ ��� ������ � �����.
	SETGET(wstring, Data);

	SETGET(bool, CheckStart);
	SETGET(bool, CheckEnd);

public:
	CSpeechItem();
	virtual ~CSpeechItem();
};
//----------------------------------------------------------------------------------
//!����� ��������� c����
class CSpeechManager
{
private:
	vector<CSpeechItem> m_SpeechEntries;
	vector<CLangCode> m_LangCodes;
	
public:
	CSpeechManager();
	~CSpeechManager();

	/*!
	�������� c��� ������
	@return true ��� �������� ��������
	*/
	bool LoadSpeech();

	/*!
	�������� ������ � �������
	@return true ��� �������� ��������
	*/
	bool LoadLangCodes();

	//������ ������ � ������ �������������� ��������� � �����
	void GetKeywords(const wchar_t *text, UINT_LIST &codes);
};
//----------------------------------------------------------------------------------
//!������ �� �������� c����
extern CSpeechManager g_SpeechManager;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
