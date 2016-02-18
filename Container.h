/****************************************************************************
**
** Container.h
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
#ifndef ContainerH
#define ContainerH
//---------------------------------------------------------------------------
//����� ����� �����������, ������������ ��� �������� ���������� ��� ��������
//������ ����������� �� ������� ��� ����� � ����
class TContainerStack
{
private:
	//�������� ����������
	DWORD m_Serial;

	//���������� �����
	short m_X;
	short m_Y;

	//���������� ����������������� �����
	short m_MinimizedX;
	short m_MinimizedY;

	//���� �����������
	bool m_Minimized;

	//���� ������� �����������/��������
	bool m_LockMoving;

public:
	TContainerStack(DWORD serial, short x, short y, short minimizedX, short minimizedY, bool minimized, bool lockMoving);
	~TContainerStack();

	SETGET(DWORD, Serial);
	SETGET(short, X);
	SETGET(short, Y);
	SETGET(short, MinimizedX);
	SETGET(short, MinimizedY);
	SETGET(bool, Minimized);
	SETGET(bool, LockMoving);

	//��������� �� ��������� � ���������� ��������
	TContainerStack *m_Next;
	TContainerStack *m_Prev;
};
//---------------------------------------------------------------------------
//��������� ������ � ����������� � ��������� ����������� ����� ��������� � ����� �����������
struct CONTAINER_OFFSET_RECT
{
	int MinX;
	int MinY;
	int MaxX;
	int MaxY;
};
//---------------------------------------------------------------------------
//���������� � ����� � ������ �����������
struct CONTAINER_OFFSET
{
	//������ �������� �����
	WORD Gump;

	//������ ����� �������� (0 - ��� �����)
	WORD OpenSound;

	//���������� � ����� ��� �����
	CONTAINER_OFFSET_RECT rect;
};
//---------------------------------------------------------------------------
//�������� ���������� � �������� � �����
struct CORPSE_EQUIPMENT_DATA
{
	//��������
	DWORD Serial;

	//����
	int Layer;
};
//---------------------------------------------------------------------------
const int CONTAINERS_RECT_DEFAULT_POS = 40; //��������� ������� �������� �����������
const int CONTAINERS_RECT_LINESTEP = 800; //�������� ��� ���������� �����
const int CONTAINERS_RECT_STEP = 20; //��� ��������
//---------------------------------------------------------------------------
//����� ��� ���������� �������� �������� ������ �����������
class TContainerRect
{
private:
	short m_X;
	short m_Y;

public:
	TContainerRect();
	~TContainerRect() {}

	SETGET(short, X);
	SETGET(short, Y);

	//������� ���������� �������� ��� ������� ��������
	void Calculate(WORD gumpID);
	//�������� ��������� ��-���������
	void MakeDefault() {m_X = m_Y = CONTAINERS_RECT_DEFAULT_POS;}
};
//---------------------------------------------------------------------------
const int CONTAINERS_COUNT = 20; //���������� �����������
extern CONTAINER_OFFSET g_ContainerOffset[CONTAINERS_COUNT]; //������ � �����������
extern TContainerStack *ContainerStack; //������ �� ���� �������� �����������
extern DWORD g_CheckContainerStackTimer; //������ ����� �������� �����������
extern TContainerRect ContainerRect; //���������� �������� �������� �����������
//---------------------------------------------------------------------------
#endif