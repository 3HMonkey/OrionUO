/***********************************************************************************
**
** ServerScreen.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef SERVERSCREEN_H
#define SERVERSCREEN_H
//----------------------------------------------------------------------------------
#include "BaseScreen.h"
#include "../Gumps/GumpScreenServer.h"
//----------------------------------------------------------------------------------
class CServerScreen : public CBaseScreen
{
	//!��������� ���������� ��� ������������� ���������� �������
	SETGET(int, SelectionServerTempValue);

private:
	CGumpScreenServer m_ServerGump;

public:
	CServerScreen();
	virtual ~CServerScreen();

	//!�������������� ������� ��� �������� ��������
	static const uchar ID_SMOOTH_SS_QUIT = 1;
	static const uchar ID_SMOOTH_SS_SELECT_SERVER = 2;
	static const uchar ID_SMOOTH_SS_GO_SCREEN_MAIN = 3;

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
	


	virtual void OnKeyDown(const WPARAM &wParam, const LPARAM &lParam);
};
//----------------------------------------------------------------------------------
extern CServerScreen g_ServerScreen;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
