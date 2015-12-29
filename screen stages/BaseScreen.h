/****************************************************************************
**
** BaseScreen.h
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
#ifndef BaseScreenH
#define BaseScreenH
//---------------------------------------------------------------------------
//������� ����� ������ ���� �������
class TBaseScreen
{
protected:
	BYTE m_SmoothScreenAction;
public:
	TBaseScreen() :m_SmoothScreenAction(0) {}
	virtual ~TBaseScreen() {}

	//�������������
	virtual void Init() {}

	//������������� �������
	virtual void InitTooltip() {}

	//���������/����� ��������
	virtual int Render(bool mode) {return 0;}

	//���������� �������� �������� � ���� ����������� � ���������
	virtual int CalculateScrollerAndTextPosition(int &currentLine, int &visibleLines, int &maxY, int currentY);
	virtual int CalculateScrollerY(int &currentLine, int &visibleLines, int &maxY);

	//������
	//������� ����� ������ ����
	virtual void OnLeftMouseDown() {}
	//���������� ����� ������ ����
	virtual void OnLeftMouseUp() {}
	//������� ������ ������ ����
	virtual void OnRightMouseDown() {}
	//���������� ������ ������ ����
	virtual void OnRightMouseUp() {}
	//������� ���� ����� ������� ����
	virtual bool OnLeftMouseDoubleClick() {return false;}
	//������� ���� ������ ������� ����
	virtual bool OnRightMouseDoubleClick() {return false;}
	//��������� ������� ������ (��������) ����
	virtual void OnMouseWheel(MOUSE_WHEEL_STATE state) {}
	//��������� ������� �������
	virtual void OnCharPress(WPARAM wparam, LPARAM lparam) {}
	virtual void OnKeyPress(WPARAM wparam, LPARAM lparam) {}
};
//---------------------------------------------------------------------------
extern TBaseScreen *CurrentScreen; //��������� �� ������� �����
//---------------------------------------------------------------------------
#endif