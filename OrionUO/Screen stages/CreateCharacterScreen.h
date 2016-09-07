/***********************************************************************************
**
** CreateCharacterScreen.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef CREATECHARACTERSCREEN_H
#define CREATECHARACTERSCREEN_H
//----------------------------------------------------------------------------------
#include "BaseScreen.h"
#include "../Gumps/GumpScreenCreateCharacter.h"
//----------------------------------------------------------------------------------
class CCreateCharacterScreen : public CBaseScreen
{
	//!��������� ����� ��������/������
	SETGETE(int, StyleSelection, OnChangeStyleSelection);

	//!��������� ���� ����/������/���������� �������
	SETGETE(int, ColorSelection, OnChangeColorSelection);
	SETGET(string, Name);

private:
	CGumpScreenCreateCharacter m_CreateCharacterGump;

public:
	CCreateCharacterScreen();
	virtual ~CCreateCharacterScreen();

	//!�������������� ������� ��� �������� ��������
	static const uchar ID_SMOOTH_CCS_QUIT = 1;
	static const uchar ID_SMOOTH_CCS_GO_SCREEN_CHARACTER = 2;
	static const uchar ID_SMOOTH_CCS_GO_SCREEN_CONNECT = 3;
	static const uchar ID_SMOOTH_CCS_GO_SCREEN_SELECT_TOWN = 4;

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
	void ProcessSmoothAction(uchar action = 0xFF);



	virtual void OnLeftMouseButtonDown();

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return 
	*/
	void OnCharPress(const WPARAM &wParam, const LPARAM &lParam);

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return 
	*/
	void OnKeyDown(const WPARAM &wParam, const LPARAM &lParam);
};
//----------------------------------------------------------------------------------
extern CCreateCharacterScreen g_CreateCharacterScreen;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
