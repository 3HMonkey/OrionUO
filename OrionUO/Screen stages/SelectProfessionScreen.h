/***********************************************************************************
**
** SelectProfessionScreen.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef SELECTPROFESSIONSCREEN_H
#define SELECTPROFESSIONSCREEN_H
//----------------------------------------------------------------------------------
#include "BaseScreen.h"
#include "../Gumps/GumpScreenSelectProfession.h"
//----------------------------------------------------------------------------------
class CSelectProfessionScreen : public CBaseScreen
{
	//!��������� �����
	SETGETEXE(int, SkillSelection, OnChangeSkillSelection);

private:
	CGumpScreenSelectProfession m_SelectProfessionGump;

public:
	CSelectProfessionScreen();
	virtual ~CSelectProfessionScreen();

	//!�������������� ������� ��� �������� ��������
	static const uchar ID_SMOOTH_SPS_QUIT = 1;
	static const uchar ID_SMOOTH_SPS_GO_SCREEN_CHARACTER = 2;
	static const uchar ID_SMOOTH_SPS_GO_SCREEN_GAME_CONNECT = 3;
	static const uchar ID_SMOOTH_SPS_GO_SCREEN_CREATE = 4;

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
};
//----------------------------------------------------------------------------------
extern CSelectProfessionScreen g_SelectProfessionScreen;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
