/***********************************************************************************
**
** GameBlockedScreen.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "GameBlockedScreen.h"
#include "../TextEngine/GameConsole.h"
#include "../Managers/GumpManager.h"
#include "../Gumps/GumpNotify.h"
//----------------------------------------------------------------------------------
CGameBlockedScreen g_GameBlockedScreen;
//----------------------------------------------------------------------------------
CGameBlockedScreen::CGameBlockedScreen()
: CBaseScreen(m_GameBlockedScreenGump), m_Code(0)
{
}
//----------------------------------------------------------------------------------
CGameBlockedScreen::~CGameBlockedScreen()
{
}
//----------------------------------------------------------------------------------
/*!
�������������
@return 
*/
void CGameBlockedScreen::Init()
{
	m_Code = 0;
}
//----------------------------------------------------------------------------------
/*!
���������/����� ��������
@param [__in] mode true - ���������, false - �����
@return ��� ������ �������� - ������������� ���������� �������
*/
void CGameBlockedScreen::Render(const bool &mode)
{
	if (mode)
	{
		g_GumpManager.Draw(true);
		
		InitToolTip();

		g_MouseManager.Draw(0x2073); //Main Gump mouse cursor
	}
	else
	{
		g_SelectedObject.Clear();

		g_GumpManager.Select(true);

		if (g_SelectedObject.Object() != g_LastSelectedObject.Object())
		{
			if (g_SelectedObject.Object() != NULL)
				g_SelectedObject.Object()->OnMouseEnter();

			if (g_LastSelectedObject.Object() != NULL)
				g_LastSelectedObject.Object()->OnMouseExit();
		}

		g_LastSelectedObject.Init(g_SelectedObject);
	}
}
//----------------------------------------------------------------------------------
/*!
������� ����� ������ ����
@return 
*/
void CGameBlockedScreen::OnLeftMouseButtonDown()
{
	if (g_SelectedObject.Gump() != NULL)
		g_GumpManager.OnLeftMouseButtonDown(true);
}
//----------------------------------------------------------------------------------
/*!
���������� ����� ������ ����
@return 
*/
void CGameBlockedScreen::OnLeftMouseButtonUp()
{
	if (g_PressedObject.LeftGump() != NULL)
		g_GumpManager.OnLeftMouseButtonUp(true);
}
//----------------------------------------------------------------------------------
/*!
��������� ������� �������
@param [__in] wparam �� ����������� ��������
@param [__in] lparam �� ����������� ��������
@return 
*/
void CGameBlockedScreen::OnCharPress(const WPARAM &wParam, const LPARAM &lParam)
{
	if (g_EntryPointer == NULL || g_EntryPointer == &g_GameConsole)
		return;

	g_GumpManager.OnCharPress(wParam, lParam, true);
}
//----------------------------------------------------------------------------------
/*!
��������� ������� �������
@param [__in] wparam �� ����������� ��������
@param [__in] lparam �� ����������� ��������
@return 
*/
void CGameBlockedScreen::OnKeyDown(const WPARAM &wParam, const LPARAM &lParam)
{
	CGumpNotify *notify = (CGumpNotify*)g_GumpManager.GetGump(0,0, GT_NOTIFY);

	if (g_EntryPointer == NULL || g_EntryPointer == &g_GameConsole)
	{
		if (wParam == VK_RETURN && notify != NULL)
			notify->OnKeyDown(wParam, lParam);
	}
	else
	{
		CGump *gump = g_GumpManager.GetTextEntryOwner();

		if (gump != NULL && gump->GumpType == GT_TEXT_ENTRY_DIALOG)
			gump->OnKeyDown(wParam, lParam);
		else if (notify != NULL)
			notify->OnKeyDown(wParam, lParam);
	}
}
//----------------------------------------------------------------------------------
