/***********************************************************************************
**
** BaseScreen.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "BaseScreen.h"
#include "../GLEngine/GLEngine.h"
#include "../SelectedObject.h"
#include "../PressedObject.h"
//----------------------------------------------------------------------------------
CBaseScreen *g_CurrentScreen = NULL;
//----------------------------------------------------------------------------------
CBaseScreen::CBaseScreen(CGump &gump)
: CBaseQueue(), m_CursorGraphic(0x2073), m_SmoothScreenAction(0), m_Gump(gump)
{
}
//----------------------------------------------------------------------------------
/*!
���������/����� ��������
@param [__in] mode true - ���������, false - �����
@return ��� ������ �������� - ������������� ���������� �������
*/
void CBaseScreen::Render(const bool &mode)
{
	if (mode)
	{
		g_GL.BeginDraw();

		if (DrawSmoothMonitor())
			return;

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		m_Gump.Draw();

		InitToolTip();

		DrawSmoothMonitorEffect();

		g_MouseManager.Draw(m_CursorGraphic);

		g_GL.EndDraw();
	}
	else
	{
		g_SelectedObject.Clear();

		CRenderObject *selected = m_Gump.Select();

		if (selected != NULL)
			g_SelectedObject.Init(selected, &m_Gump);

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
���������� ��������� ��������
@return ������ ���������
*/
int CBaseScreen::DrawSmoothMonitor()
{
	if (g_SmoothMonitor.Process())
	{
		ProcessSmoothAction();

		g_GL.EndDraw();

		return 1;
	}

	return 0;
}
//----------------------------------------------------------------------------------
/*!
��������� ������� ��������
@return 
*/
void CBaseScreen::DrawSmoothMonitorEffect()
{
	g_SmoothMonitor.Draw();
}
//----------------------------------------------------------------------------------
/*!
�������� �������� ���������� ������
@param [__in] action ������������� ��������
@return 
*/
void CBaseScreen::CreateSmoothAction(__in BYTE action)
{
	if (g_SmoothMonitor.UseSunset())
		m_SmoothScreenAction = action;
	else
		ProcessSmoothAction(action);
}
//----------------------------------------------------------------------------------
