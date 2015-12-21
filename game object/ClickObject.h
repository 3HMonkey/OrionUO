/****************************************************************************
**
** ClickObject.h
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
#ifndef ClickObjectH
#define ClickObjectH
//---------------------------------------------------------------------------
class TClickObject
{
private:
	CLICK_OBJECT_TYPE m_Type; //��� ������� �����
	DWORD m_Serial; //��������
	DWORD m_GumpID; //�� �����
	DWORD m_Timer; //������ �����
	GUMP_TYPE m_GumpType; //��� ����� (���� ��� ����)
	WORD m_X; //���������� X
	WORD m_Y; //���������� Y
	char m_Z; //���������� Z
	int m_GumpButtonID; //������ ������ � ����� ��� ����� (���� ��� ����)

public:
	TClickObject();
	~TClickObject() {}

	SETGET(CLICK_OBJECT_TYPE, Type);
	SETGET(DWORD, Serial);
	SETGET(DWORD, GumpID);
	SETGET(DWORD, Timer);
	SETGET(GUMP_TYPE, GumpType);
	SETGET(WORD, X);
	SETGET(WORD, Y);
	SETGET(char, Z);
	SETGET(int, GumpButtonID);

	//������������� ��� ��� �������
	void Init(CLICK_OBJECT_TYPE type);
};
//---------------------------------------------------------------------------
extern TClickObject g_ClickObject; //������ �� ������ �����
//---------------------------------------------------------------------------
#endif