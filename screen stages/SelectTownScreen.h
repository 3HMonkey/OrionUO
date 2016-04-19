/****************************************************************************
**
** CreateCharacterSelectionTownGump.h
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
#ifndef SelectTownScreenH
#define SelectTownScreenH
//---------------------------------------------------------------------------
class TSelectTownScreen : public TBaseScreen
{
private:
	//!�������� � �������� ������������ ���������� � �����������
	int m_PixelOffset;

	//!��������� ����� ��������� ��������� ���������� � �����������
	DWORD m_LastScrollChangeTime;

	//!�������������� ������� ��� �������� ��������
	static const BYTE ID_SMOOTH_STS_QUIT = 1;
	static const BYTE ID_SMOOTH_STS_GO_SCREEN_CHARACTER = 2;
	static const BYTE ID_SMOOTH_STS_GO_SCREEN_GAME_CONNECT = 3;

	//!�������������� ������
	static const int ID_STS_QUIT = 1;
	static const int ID_STS_ARROW_PREV = 2;
	static const int ID_STS_ARROW_NEXT = 3;
	static const int ID_STS_SCROLLBAR_UP = 4;
	static const int ID_STS_SCROLLBAR_DOWN = 5;
	static const int ID_STS_SCROLLBAR = 6;
	static const int ID_STS_SCROLLBAR_BACKGROUND = 7;
	static const int ID_STS_TOWN = 10;

	//!������ ����� ��� ����������� ������ �������
	static POINT m_TownButtonText[9];

	/*!
	���������� ������
	@param [__in] direction �����������
	@param [__in] divizor ��������
	@return 
	*/
	void ListingList(__in bool direction, __in int divizor = 1);

	/*!
	�������� ������ �����������
	@return ������ �����������
	*/
	int GetScrollBoxHeight();

	/*!
	���������� ���������� � ������
	@param [__in] x ���������� X
	@param [__in] y ���������� Y
	@return 
	*/
	void DrawTownInfo(__in int x, __in int y);

public:
	TSelectTownScreen();
	~TSelectTownScreen();

	//!��������� �� ��������� �����
	TCityItem *m_City;

	/*!
	�������������
	@return 
	*/
	void Init();

	/*!
	��������� ������� ����� �������� ���������� ������
	@param [__in_opt] action ������������� ��������
	@return 
	*/
	void ProcessSmoothAction(__in_opt BYTE action = 0xFF);

	/*!
	������������� ����������� ���������
	@return 
	*/
	void InitToolTip();

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

};
//---------------------------------------------------------------------------
extern TSelectTownScreen *SelectTownScreen;
//---------------------------------------------------------------------------
#endif