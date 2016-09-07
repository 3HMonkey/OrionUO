/***********************************************************************************
**
** SelectTownScreen.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef SELECTTOWNSCREEN_H
#define SELECTTOWNSCREEN_H
//----------------------------------------------------------------------------------
#include "BaseScreen.h"
#include "../Gumps/GumpScreenSelectTown.h"
#include "../CityList.h"
//----------------------------------------------------------------------------------
class CSelectTownScreen : public CBaseScreen
{
private:
	CGumpScreenSelectTown m_SelectTownGump;

public:
	CSelectTownScreen();
	~CSelectTownScreen();

	//!�������������� ������� ��� �������� ��������
	static const uchar ID_SMOOTH_STS_QUIT = 1;
	static const uchar ID_SMOOTH_STS_GO_SCREEN_CHARACTER = 2;
	static const uchar ID_SMOOTH_STS_GO_SCREEN_GAME_CONNECT = 3;

	//!��������� �� ��������� �����
	CCityItem m_City;

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
extern CSelectTownScreen g_SelectTownScreen;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
