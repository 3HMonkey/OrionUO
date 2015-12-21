/****************************************************************************
**
** ObjectOnCursor.h
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
#ifndef ObjectOnCursorH
#define ObjectOnCursorH
//--------------------------------------------------------------------------
class TObjectOnCursor : public TGameItem
{
private:
	bool m_Separated; //������ ��� � �����
	bool m_Deleted; //������� ������
	bool m_Dropped; //������� ������� (�� �����/� ���������/�� ���������)
	bool m_IsGameFigure; //��� ������� ������
	WORD m_DragCount; //���������� ��� �����������

public:
	TObjectOnCursor();
	TObjectOnCursor(TGameItem *obj);
	virtual ~TObjectOnCursor() {}

	SETGET(bool, Separated)
	SETGET(bool, Deleted)
	SETGET(bool, Dropped)
	SETGET(bool, IsGameFigure)
	SETGET(WORD, DragCount)
};
//--------------------------------------------------------------------------
extern TObjectOnCursor *ObjectInHand; //��������� �� ������ � ���� (�� �������)
//--------------------------------------------------------------------------
#endif