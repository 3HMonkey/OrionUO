/***********************************************************************************
**
** GameBlockedScreen.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GAMEBLOCKEDSCREEN_H
#define GAMEBLOCKEDSCREEN_H
//----------------------------------------------------------------------------------
#include "BaseScreen.h"
//----------------------------------------------------------------------------------
class CGameBlockedScreen : public CBaseScreen
{
	//!��� ����������
	SETGET(uchar, Code);

	CGump m_GameBlockedScreenGump;

public:
	CGameBlockedScreen();
	~CGameBlockedScreen();


	/*!
	�������������
	@return
	*/
	virtual void Init();

	/*!
	���������/����� ��������
	@param [__in] mode true - ���������, false - �����
	@return ��� ������ �������� - ������������� ���������� �������
	*/
	virtual void Render(const bool &mode);



	virtual void OnLeftMouseButtonDown();
	virtual void OnLeftMouseButtonUp();
	virtual void OnCharPress(const WPARAM &wParam, const LPARAM &lParam);
	virtual void OnKeyDown(const WPARAM &wParam, const LPARAM &lParam);
};
//----------------------------------------------------------------------------------
extern CGameBlockedScreen g_GameBlockedScreen;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
