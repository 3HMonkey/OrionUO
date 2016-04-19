/****************************************************************************
**
** CreateCharacterGump.h
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
#ifndef CreateCharacterScreenH
#define CreateCharacterScreenH
//---------------------------------------------------------------------------
class TCreateCharacterScreen : public TBaseScreen
{
private:
	//!�������������� ������� ��� �������� ��������
	static const BYTE ID_SMOOTH_CCS_QUIT = 1;
	static const BYTE ID_SMOOTH_CCS_GO_SCREEN_CHARACTER = 2;
	static const BYTE ID_SMOOTH_CCS_GO_SCREEN_CONNECT = 3;
	static const BYTE ID_SMOOTH_CCS_GO_SCREEN_SELECT_TOWN = 4;

	//!�������������� ������
	static const int ID_CCS_QUIT = 1;
	static const int ID_CCS_ARROW_PREV = 2;
	static const int ID_CCS_ARROW_NEXT = 3;
	static const int ID_CCS_NAME_FIELD = 4;
	static const int ID_CCS_MALE_BUTTON = 5;
	static const int ID_CCS_FEMALE_BUTTON = 6;
	static const int ID_CCS_HUMAN_RACE_BUTTON = 7;
	static const int ID_CCS_ELVEN_RACE_BUTTON = 8;
	static const int ID_CCS_GARGOYLE_RACE_BUTTON = 9;

	static const int ID_CCS_HAIR_STYLE = 10;
	static const int ID_CCS_FACIAL_HAIR_STYLE = 11;
	static const int ID_CCS_SKIN_TONE = 12;
	static const int ID_CCS_SHIRT_COLOR = 13;
	static const int ID_CCS_SKIRT_OR_PANTS_COLOR = 14;
	static const int ID_CCS_HAIR_COLOR = 15;
	static const int ID_CCS_FACIAL_HAIR_COLOR = 16;

	static const int ID_CCS_STYLE_RANGE = 20;
	static const int ID_CCS_COLOR_RANGE = 40;

	enum
	{
		CCSID_HAIR_STYLE = 1,
		CCSID_FACIAL_HAIR_STYLE,
		CCSID_SKIN_TONE = 1,
		CCSID_SHIRT_COLOR,
		CCSID_SKIRT_OR_PANTS_COLOR,
		CCSID_HAIR_COLOR,
		CCSID_FACIAL_HAIR_COLOR
	};

	//!��������� ����� ��������/������
	int m_StyleSelection;

	//!��������� ���� ����/������/���������� �������
	int m_ColorSelection;

public:
	TCreateCharacterScreen();
	virtual ~TCreateCharacterScreen();

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
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return 
	*/
	void OnCharPress(__in WPARAM wparam, __in LPARAM lparam);

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return 
	*/
	void OnKeyPress(__in WPARAM wparam, __in LPARAM lparam);

};
//---------------------------------------------------------------------------
extern TCreateCharacterScreen *CreateCharacterScreen;
//---------------------------------------------------------------------------
#endif