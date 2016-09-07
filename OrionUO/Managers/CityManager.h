/***********************************************************************************
**
** CityManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef CITYMANAGER_H
#define CITYMANAGER_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../GLEngine/GLTextTexture.h"
//----------------------------------------------------------------------------------
//!����� � ������� � ������
class CCity
{
	SETGET(string, Name);
	SETGET(wstring, Description);

public:
	CCity(const string &name, const wstring &description);
	virtual ~CCity();
};
//---------------------------------------------------------------------------
//!����� ��������� ������ �������
class CCityManager
{
public:
	CCityManager();
	virtual ~CCityManager();

	void Init();

	deque<CCity> m_CityList;

	/*!
	�������� ��������� �� �����
	@param [__in] name ��� ������
	@return ������ �� ����� ��� NULL
	*/
	CCity GetCity(const string &name);

	void Clear();
};
//---------------------------------------------------------------------------
//!������ �� �������� �������
extern CCityManager g_CityManager;
//---------------------------------------------------------------------------
#endif