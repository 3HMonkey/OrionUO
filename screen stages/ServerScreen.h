/****************************************************************************
**
** ServerGump.h
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
#ifndef ServerScreenH
#define ServerScreenH
//---------------------------------------------------------------------------
class TServerScreen : public TBaseScreen
{
private:
	//!������� ������
	TTextTexture m_Text[2];

	//!�������������� ������� ��� �������� ��������
	static const BYTE ID_SMOOTH_SS_QUIT = 1;
	static const BYTE ID_SMOOTH_SS_SELECT_SERVER = 2;
	static const BYTE ID_SMOOTH_SS_GO_SCREEN_MAIN = 3;

	//!�������������� ������
	static const int ID_SS_QUIT = 1;
	static const int ID_SS_ARROW_PREV = 2;
	static const int ID_SS_ARROW_NEXT = 3;
	static const int ID_SS_TIME_ZONE = 4;
	static const int ID_SS_FULL = 5;
	static const int ID_SS_CONNECTION = 6;
	static const int ID_SS_EARTH = 7;
	static const int ID_SS_SCROLLBAR_UP = 8;
	static const int ID_SS_SCROLLBAR_DOWN = 9;
	static const int ID_SS_SCROLLBAR = 10;
	static const int ID_SS_SCROLLBAR_BACKGROUND = 11;
	static const int ID_SS_SERVER_LIST = 20;

	//!��������� ����� ��������� ��������� ���������� � �����������
	DWORD m_LastScrollChangeTime;

	//!�������� � �������� ������������ ���������� � �����������
	int m_PixelOffset;

	//!��������� ���������� ��� ������������� ���������� �������
	int m_SelectionServerTempValue;

	/*!
	�������� ������ ������ ��������
	@return 
	*/
	int GetServerListHeight();

	/*!
	���������� ������
	@param [__in] direction �����������
	@param [__in] divizor ��������
	@return 
	*/
	void ListingList(__in bool direction, __in int divizor = 1);

public:
	TServerScreen();
	virtual ~TServerScreen();

	/*!
	�������������
	@return 
	*/
	void Init();

	/*!
	������������� ����������� ���������
	@return 
	*/
	void InitToolTip();

	/*!
	��������� ������� ����� �������� ���������� ������
	@param [__in_opt] action ������������� ��������
	@return 
	*/
	void ProcessSmoothAction(__in_opt BYTE action = 0xFF);

	/*!
	���������/����� ��������
	@param [__in] mode true - ���������, false - �����
	@return ��� ������ �������� - ������������� ���������� �������
	*/
	int Render(__in bool mode);
	


	/*!
	������� ����� ������ ����
	@return 
	*/
	void OnLeftMouseDown();

	/*!
	���������� ����� ������ ����
	@return 
	*/
	void OnLeftMouseUp();

	/*!
	��������� ������� ������ (��������) ����
	@param [__in] state ��������� ��������
	@return 
	*/
	void OnMouseWheel(__in MOUSE_WHEEL_STATE state);

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return 
	*/
	void OnKeyPress(__in WPARAM wparam, __in LPARAM lparam);

};
//---------------------------------------------------------------------------
extern TServerScreen *ServerScreen;
//---------------------------------------------------------------------------
#endif