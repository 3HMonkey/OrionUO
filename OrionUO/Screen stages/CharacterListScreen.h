/***********************************************************************************
**
** CharacterListScreen.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef CHARACTERLISTSCREEN_H
#define CHARACTERLISTSCREEN_H
//----------------------------------------------------------------------------------
#include "BaseScreen.h"
#include "../Gumps/GumpScreenCharacterList.h"
//----------------------------------------------------------------------------------
class CCharacterListScreen : public CBaseScreen
{
private:
	CGumpScreenCharacterList m_CharacterListGump;

public:
	CCharacterListScreen();
	virtual ~CCharacterListScreen();

	//!�������������� ������� ��� �������� ��������
	static const uchar ID_SMOOTH_CLS_QUIT = 1;
	static const uchar ID_SMOOTH_CLS_CONNECT = 2;
	static const uchar ID_SMOOTH_CLS_SELECT_CHARACTER = 3;
	static const uchar ID_SMOOTH_CLS_GO_SCREEN_PROFESSION_SELECT = 4;
	static const uchar ID_SMOOTH_CLS_GO_SCREEN_DELETE = 5;

	/*!
	�������������
	@return 
	*/
	void Init();

	/*!
	��������� ������� ����� ��������
	@param [__in_opt] action ������������� ��������
	@return 
	*/
	void ProcessSmoothAction(uchar action = 0xFF);
};
//----------------------------------------------------------------------------------
extern CCharacterListScreen g_CharacterListScreen;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
