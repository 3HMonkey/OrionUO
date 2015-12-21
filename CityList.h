/****************************************************************************
**
** CityList.h
**
** Copyright (C) October 2015 Hotride
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
#ifndef CityListH
#define CityListH
//--------------------------------------------------------------------------
class TCity;
//--------------------------------------------------------------------------
class TCityItem : public TBaseQueueItem
{
private:
	BYTE m_LocationIndex; //������ ������
	string m_Name; //��� ������
	string m_Area; //�������� ����������
	bool m_Selected; //������ �� ���� �����

public:
	TCityItem();
	virtual ~TCityItem();

	//������ �� �������� ������
	TCity *m_City;

	SETGET(BYTE, LocationIndex)
	SETGET(string, Name)
	SETGET(string, Area)
	SETGET(bool, Selected)

	//��� ������ ������ ������
	virtual bool IsNewCity() {return false;}

	//�������������
	void InitCity();
};
//--------------------------------------------------------------------------
class TCityItemNew : public TCityItem
{
private:
	//���������� ������, �����?
	DWORD m_X;
	DWORD m_Y;
	DWORD m_Z;
	//������ �����, �����?
	DWORD m_MapIndex;
	//DWORD m_Cliloc;

public:
	TCityItemNew();
	virtual ~TCityItemNew();

	//��� ����� ������ ������	
	bool IsNewCity() {return true;}

	//�������� ������
	TTextTexture m_Texture;

	SETGET(DWORD, X)
	SETGET(DWORD, Y)
	SETGET(DWORD, Z)
	SETGET(DWORD, MapIndex)
	//SETGET(DWORD, Cliloc)

	//��������� �������� �� �� �������
	void CreateTextTexture(DWORD clilocID);
};
//--------------------------------------------------------------------------
class TCityList : public TBaseQueue
{
private:

public:
	TCityList();
	virtual ~TCityList();

	//�������� ������ �� �����
	TCityItem *GetCity(int index);
};
//---------------------------------------------------------------------------
extern TCityList *CityList; //������ �� ������ �������
//---------------------------------------------------------------------------
#endif