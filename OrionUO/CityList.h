/***********************************************************************************
**
** CityList.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef CITYLIST_H
#define CITYLIST_H
//----------------------------------------------------------------------------------
#include "Globals.h"
#include "GLEngine/GLTextTexture.h"
#include "Managers/CityManager.h"
//----------------------------------------------------------------------------------
//!����� ������ (��� ������ ��������)
class CCityItem
{
	SETGET(uchar, LocationIndex);
	SETGET(string, Name);
	SETGET(string, Area);
	SETGET(bool, Selected);

public:
	CCityItem();
	virtual ~CCityItem();

	//!������ �� �������� ������
	class CCity m_City;

	/*!
	����������� ������ ������
	@return ����� ��� ������
	*/
	virtual bool IsNewCity() { return false; }

	/*!
	�������������
	@return 
	*/
	void InitCity();
};
//--------------------------------------------------------------------------
//!����� ������ (��� ����� ��������)
class CCityItemNew : public CCityItem
{
	SETGET(uint, X);
	SETGET(uint, Y);
	SETGET(uint, Z);
	SETGET(uint, MapIndex);
	SETGET(uint, Cliloc);

public:
	CCityItemNew();
	virtual ~CCityItemNew();

	/*!
	����������� ������ ������
	@return ����� ��� ������
	*/
	bool IsNewCity() { return true; }
};
//--------------------------------------------------------------------------
//!����� ������ �������
class CCityList
{
private:
	deque<CCityItem> m_CityList;

public:
	CCityList();
	virtual ~CCityList();

	int CityCount() { return m_CityList.size(); }

	void AddCity(CCityItem city) { m_CityList.push_back(city); }

	CCityItem GetCity(const int &index);

	void Clear();
};
//---------------------------------------------------------------------------
//!������ �� ������ �������
extern CCityList g_CityList;
//---------------------------------------------------------------------------
#endif