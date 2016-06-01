/****************************************************************************
**
** SpeechManager.h
**
** Copyright (C) May 2016 Aimed
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
//--------------------------------------------------------------------------
#ifndef SpeechManagerH
#define SpeechManagerH

//--------------------------------------------------------------------------
class TLangCode
{
private:
	string m_Code;
	string m_LangString;	
	DWORD m_Unknown;	
	string m_LangName;	
	string m_LangCountry;
public:
	TLangCode();
	virtual ~TLangCode();

	SETGET(string, Code);

	//! ���������, ���������� ����������� ������.
	SETGET(string, LangString);

	//! �������� ����������� ������? ������.
	SETGET(DWORD, Unknown);

	//! �������� �����.
	SETGET(string, LangName);

	//! �������� ������.
	SETGET(string, LangCountry);
};
//--------------------------------------------------------------------------
class TSpeechItem
{
private:
	WORD m_Code;
	wstring m_Data;
	bool m_CheckStart;
	bool m_CheckEnd;

public:
	TSpeechItem();
	virtual ~TSpeechItem();

	//! ��� ���������� �������.
	SETGET(WORD, Code);

	//! ������ � �������� ������ ��� ������ � �����.
	SETGET(wstring, Data);

	SETGET(bool, CheckStart);
	SETGET(bool, CheckEnd);
};
//--------------------------------------------------------------------------
//!����� ��������� c����
class TSpeechManager
{
private:
	unordered_map<wstring, int> m_LocalsVectorPtrs;
	vector<TLangCode> m_LangCodes;
	
public:
	TSpeechManager();
	~TSpeechManager();

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
};
//--------------------------------------------------------------------------
//!������ �� �������� c����
extern TSpeechManager *SpeechManager;
//--------------------------------------------------------------------------
#endif