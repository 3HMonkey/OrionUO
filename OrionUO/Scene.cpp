/***********************************************************************************
**
** Scene.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "Scene.h"
#include "SmoothMonitor.h"
#include "GLEngine/GLEngine.h"
#include "SelectedObject.h"
#include "PressedObject.h"

CScene g_Scene;
//---------------------------------------------------------------------------
/*!
���������� ��������� ��������
@return ������ ���������
*/
int CScene::DrawSmoothMonitor()
{
	if (g_SmoothMonitor.Process())
	{
		ProcessSmoothAction();

		g_GL.EndDraw();

		return 1;
	}

	return 0;
}
//---------------------------------------------------------------------------
void CScene::ProcessSmoothAction(uchar action)
{
}
//---------------------------------------------------------------------------
/*!
��������� ������� ��������
@return 
*/
void CScene::DrawSmoothMonitorEffect()
{
	g_SmoothMonitor.Draw();
}
//---------------------------------------------------------------------------
/*!
�������� �������� ���������� ������
@param [__in] action ������������� ��������
@return 
*/
void CScene::CreateSmoothAction(uchar action)
{
	if (g_SmoothMonitor.UseSunset())
		m_SmoothScreenAction = action;
	else
		ProcessSmoothAction(action);
}
//---------------------------------------------------------------------------
void CScene::Init(const GAME_STATE &state)
{
	g_GameState = state;
	g_SelectedObject.Clear();
	g_PressedObject.ClearAll();
}
//---------------------------------------------------------------------------
void CScene::InitToolTip()
{
}
//---------------------------------------------------------------------------
void CScene::Render(const bool &mode)
{
}
//---------------------------------------------------------------------------
void CScene::OnLeftMouseButtonDown()
{
}
//---------------------------------------------------------------------------
void CScene::OnLeftMouseButtonUp()
{
}
//---------------------------------------------------------------------------
void CScene::OnRightMouseButtonDown()
{
}
//---------------------------------------------------------------------------
void CScene::OnRightMouseButtonUp()
{
}
//---------------------------------------------------------------------------
bool CScene::OnLeftMouseButtonDoubleClick()
{
	return false;
}
//---------------------------------------------------------------------------
bool CScene::OnRightMouseButtonDoubleClick()
{
	return false;
}
//---------------------------------------------------------------------------
void CScene::OnMouseWheel(const MOUSE_WHEEL_STATE &state)
{
}
//---------------------------------------------------------------------------
bool CScene::OnMouseWheelDoubleClick()
{
	return false;
}
//---------------------------------------------------------------------------
void CScene::OnDragging()
{
}
//---------------------------------------------------------------------------
void CScene::OnDragDrop()
{
}
//---------------------------------------------------------------------------
void CScene::OnCharPress(const WPARAM &wparam, const LPARAM &lparam)
{
}
//---------------------------------------------------------------------------
void CScene::OnKeyPress(const WPARAM &wparam, const LPARAM &lparam)
{
}
//---------------------------------------------------------------------------
