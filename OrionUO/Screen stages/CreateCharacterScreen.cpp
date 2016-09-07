/***********************************************************************************
**
** CreateCharacterScreen.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "CreateCharacterScreen.h"
#include "ConnectionScreen.h"
#include "../Managers/CreateCharacterManager.h"
#include "../OrionWindow.h"
#include "../OrionUO.h"
#include "../Managers/FontsManager.h"
//----------------------------------------------------------------------------------
CCreateCharacterScreen g_CreateCharacterScreen;
//----------------------------------------------------------------------------------
CCreateCharacterScreen::CCreateCharacterScreen()
: CBaseScreen(m_CreateCharacterGump), m_StyleSelection(0), m_ColorSelection(0),
m_Name("")
{
}
//----------------------------------------------------------------------------------
CCreateCharacterScreen::~CCreateCharacterScreen()
{
}
//----------------------------------------------------------------------------------
void CCreateCharacterScreen::OnChangeStyleSelection(const int &val)
{
	m_Gump.WantUpdateContent = true;
}
//----------------------------------------------------------------------------------
void CCreateCharacterScreen::OnChangeColorSelection(const int &val)
{
	m_Gump.WantUpdateContent = true;
}
//----------------------------------------------------------------------------------
/*!
�������������
@return 
*/
void CCreateCharacterScreen::Init()
{
	g_CreateCharacterManager.Clear();

	m_Name = "";
	m_StyleSelection = 0;
	m_ColorSelection = 0;

	g_SmoothMonitor.UseSunrise();
	m_SmoothScreenAction = 0;

	m_Gump.PrepareTextures();
	m_Gump.WantUpdateContent = true;
}
//----------------------------------------------------------------------------------
/*!
��������� ������� ����� �������� ���������� ������
@param [__in_opt] action ������������� ��������
@return 
*/
void CCreateCharacterScreen::ProcessSmoothAction(uchar action)
{
	if (action == 0xFF)
		action = m_SmoothScreenAction;

	if (action == ID_SMOOTH_CCS_QUIT)
		g_OrionWindow.Destroy();
	else if (action == ID_SMOOTH_CCS_GO_SCREEN_CHARACTER)
		g_Orion.InitScreen(GS_CHARACTER);
	else if (action == ID_SMOOTH_CCS_GO_SCREEN_CONNECT)
	{
		g_Orion.InitScreen(GS_GAME_CONNECT);
		g_ConnectionScreen.Type = CST_GAME;
		g_ConnectionScreen.ConnectionFailed = true;
		g_ConnectionScreen.ErrorCode = 1;
	}
	else if (action == ID_SMOOTH_CCS_GO_SCREEN_SELECT_TOWN)
		g_Orion.InitScreen(GS_SELECT_TOWN);
}
//----------------------------------------------------------------------------------
/*!
������� ����� ������ ����
@return 
*/
void CCreateCharacterScreen::OnLeftMouseButtonDown()
{
	CBaseScreen::OnLeftMouseButtonDown();

	if (g_SelectedObject.Serial == 0)
	{
		if (m_StyleSelection != 0)
		{
			m_StyleSelection = 0;
			m_Gump.WantUpdateContent = true;
		}
	}
}
//----------------------------------------------------------------------------------
/*!
��������� ������� �������
@param [__in] wparam �� ����������� ��������
@param [__in] lparam �� ����������� ��������
@return 
*/
void CCreateCharacterScreen::OnCharPress(const WPARAM &wParam, const LPARAM &lParam)
{
	if (wParam >= 0x0100 || !g_FontManager.IsPrintASCII(wParam))
		return;
	else if (g_EntryPointer == NULL)
		return;

	if (g_EntryPointer->Length() < 20) //add char to text field
		g_EntryPointer->Insert(wParam);

	m_Name = g_EntryPointer->c_str();
}
//----------------------------------------------------------------------------------
/*!
��������� ������� �������
@param [__in] wparam �� ����������� ��������
@param [__in] lparam �� ����������� ��������
@return 
*/
void CCreateCharacterScreen::OnKeyDown(const WPARAM &wParam, const LPARAM &lParam)
{
	if (g_EntryPointer != NULL)
	{
		g_EntryPointer->OnKey(&m_Gump, wParam);

		m_Name = g_EntryPointer->c_str();
	}
}
//----------------------------------------------------------------------------------
