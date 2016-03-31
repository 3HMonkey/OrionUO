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
	//!������ ��������, ������� ���������� ��������� ����� ��������� �������� �������� ������������ ��������� ������
	BYTE m_SmoothScreenAction;

public:
	TBaseScreen() :m_SmoothScreenAction(0) {}
	virtual ~TBaseScreen() {}

	/*!
	�������������
	@return 
	*/
	virtual void Init() {}

	/*!
	������������� ����������� ���������
	@return 
	*/
	virtual void InitPopupHelp() {}

	/*!
	���������/����� ��������
	@param [__in] mode true - ���������, false - �����
	@return ��� ������ �������� - ������������� ���������� �������
	*/
	virtual int Render(__in bool mode) {return 0;}

	/*!
	���������� �������� �������� � ���� �����������
	@param [__out] currentLine ������� ������
	@param [__in] visibleLines ���������� ������� �����
	@param [__in] maxY ������������ �������� Y ����������
	@param [__in] currentY ������� �������� Y ����������
	@return ���������� Y ���������
	*/
	virtual int CalculateScrollerAndTextPosition(__out int &currentLine, __in int &visibleLines, __in int &maxY, __in int currentY);

	/*!
	���������� �������� ���������
	@param [__in] currentLine ������� ������
	@param [__in] visibleLines ���������� ������� �����
	@param [__in] maxY ������������ �������� Y ����������
	@return ���������� Y ���������
	*/
	virtual int CalculateScrollerY(__in int &currentLine, __in int &visibleLines, __in int &maxY);

	/*!
	�������� �������� ���������� ������
	@param [__in] action ������������� ��������
	@return 
	*/
	virtual void CreateSmoothAction(__in BYTE action);

	/*!
	��������� ������� ����� ��������
	@param [__in_opt] action ������������� ��������
	@return 
	*/
	virtual void ProcessSmoothAction(__in_opt BYTE action = 0xFF) {}

	/*!
	���������� ��������� ��������
	@return ������ ���������
	*/
	virtual int DrawSmoothMonitor();

	/*!
	��������� ������� ��������
	@return 
	*/
	virtual void DrawSmoothMonitorEffect();



	/*!
	������� ����� ������ ����
	@return 
	*/
	virtual void OnLeftMouseDown() {}

	/*!
	���������� ����� ������ ����
	@return 
	*/
	virtual void OnLeftMouseUp() {}

	/*!
	������� ������ ������ ����
	@return 
	*/
	virtual void OnRightMouseDown() {}

	/*!
	���������� ������ ������ ����
	@return 
	*/
	virtual void OnRightMouseUp() {}

	/*!
	������� ���� ����� ������� ����
	@return true ��� �������� ���������
	*/
	virtual bool OnLeftMouseDoubleClick() {return false;}

	/*!
	������� ���� ������ ������� ����
	@return true ��� �������� ���������
	*/
	virtual bool OnRightMouseDoubleClick() {return false;}

	/*!
	��������� ������� ������ (��������) ����
	@param [__in] state ��������� ��������
	@return 
	*/
	virtual void OnMouseWheel(__in MOUSE_WHEEL_STATE state) {}

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return 
	*/
	virtual void OnCharPress(__in WPARAM wparam, __in LPARAM lparam) {}

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return
	*/
	virtual void OnKeyPress(WPARAM wparam, LPARAM lparam) {}
};
//---------------------------------------------------------------------------
//!��������� �� ������� �����
extern TBaseScreen *CurrentScreen;
//---------------------------------------------------------------------------
#endif