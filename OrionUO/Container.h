/***********************************************************************************
**
** Container.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef CONTAINER_H
#define CONTAINER_H
//----------------------------------------------------------------------------------
#include "Globals.h"
//----------------------------------------------------------------------------------
//!����� ����� �����������, ������������ ��� �������� ���������� ��� �������� ������ ����������� �� ������� ��� ����� � ����
class CContainerStackItem
{
	SETGET(uint, Serial);
	SETGET(short, X);
	SETGET(short, Y);
	SETGET(short, MinimizedX);
	SETGET(short, MinimizedY);
	SETGET(bool, Minimized);
	SETGET(bool, LockMoving);

public:
	CContainerStackItem(uint serial, short x, short y, short minimizedX, short minimizedY, bool minimized, bool lockMoving);
	~CContainerStackItem();
};
//----------------------------------------------------------------------------------
//!��������� ������ � ����������� � ��������� ����������� ����� ��������� � ����� �����������
struct CONTAINER_OFFSET_RECT
{
	int MinX;
	int MinY;
	int MaxX;
	int MaxY;
};
//----------------------------------------------------------------------------------
//!���������� � ����� � ������ �����������
struct CONTAINER_OFFSET
{
	//!������ �������� �����
	ushort Gump;

	//!������ ����� �������� (0 - ��� �����)
	ushort OpenSound;

	//!������ ����� �������� (0 - ��� �����)
	ushort CloseSound;

	//!���������� � ����� ��� �����
	CONTAINER_OFFSET_RECT rect;
};
//----------------------------------------------------------------------------------
//!�������� ���������� � �������� � �����
struct CORPSE_EQUIPMENT_DATA
{
	//!��������
	uint Serial;

	//!����
	int Layer;
};
//----------------------------------------------------------------------------------
//!��������� ������� �������� �����������
const int CONTAINERS_RECT_DEFAULT_POS = 40;

//!�������� ��� ���������� �����
const int CONTAINERS_RECT_LINESTEP = 800;

//!��� ��������
const int CONTAINERS_RECT_STEP = 20;
//----------------------------------------------------------------------------------
//!����� ��� ���������� �������� �������� ������ �����������
class CContainerRect
{
	SETGET(short, X);
	SETGET(short, Y);

public:
	CContainerRect();
	~CContainerRect() {}

	/*!
	������� ���������� �������� ��� ������� ��������
	@param [__in] gumpID ������ ��������
	@return 
	*/
	void Calculate(ushort gumpID);

	/*!
	�������� ��������� ��-���������
	@return 
	*/
	void MakeDefault() { m_X = m_Y = CONTAINERS_RECT_DEFAULT_POS; }
};
//----------------------------------------------------------------------------------
//!���������� �����������
const int CONTAINERS_COUNT = 20;

//!������ � �����������
extern CONTAINER_OFFSET g_ContainerOffset[CONTAINERS_COUNT];

//!������ �� ���� �������� �����������
extern deque<CContainerStackItem> g_ContainerStack;

//!������ ����� �������� �����������
extern uint g_CheckContainerStackTimer;

//!���������� �������� �������� �����������
extern CContainerRect g_ContainerRect;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
