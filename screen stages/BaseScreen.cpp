/****************************************************************************
**
** ConnectionScreen.cpp
**
** Copyright (C) September 2015 Hotride
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
*****************************************************************************
*/
//---------------------------------------------------------------------------
#include "stdafx.h"

TBaseScreen *CurrentScreen = NULL;
//---------------------------------------------------------------------------
int TBaseScreen::DrawSmoothMonitor()
{
	if (g_SmoothMonitorMode == SMOOTH_MONITOR_SUNRISE)
	{
		g_SmoothMonitorColor += g_SmoothMonitorStep;

		if (g_SmoothMonitorColor >= 1.0f)
		{
			g_SmoothMonitorColor = 1.0f;
			g_SmoothMonitorMode = SMOOTH_MONITOR_NONE;
		}
	}
	else if (g_SmoothMonitorMode == SMOOTH_MONITOR_SUNSET)
	{
		g_SmoothMonitorColor -= g_SmoothMonitorStep;

		if (g_SmoothMonitorColor <= 0.0f)
		{
			g_SmoothMonitorColor = 1.0f;
			g_SmoothMonitorMode = SMOOTH_MONITOR_NONE;
			glColor3f(g_SmoothMonitorColor, g_SmoothMonitorColor, g_SmoothMonitorColor);

			ProcessSmoothAction();

			g_GL.EndDraw();
			return 1;
		}
	}
	else
		g_SmoothMonitorColor = 1.0f;

	//glColor3f(g_SmoothMonitorColor, g_SmoothMonitorColor, g_SmoothMonitorColor);

	return 0;
}
//---------------------------------------------------------------------------
void TBaseScreen::DrawSmoothMonitorEffect()
{
	if (g_SmoothMonitorColor != 1.0f && g_LightBuffer.Ready() && g_LightBuffer.Use())
	{
		glClearColor(g_SmoothMonitorColor, g_SmoothMonitorColor, g_SmoothMonitorColor, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_BLEND);

		g_LightBuffer.Release();

		g_GL.RestorePort();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glBlendFunc(GL_ZERO, GL_SRC_COLOR);

		g_LightBuffer.Draw(0.0f, 0.0f);

		glDisable(GL_BLEND);
	}
}
//---------------------------------------------------------------------------
void TBaseScreen::CreateSmoothAction(BYTE action)
{
	if (g_UseSmoothMonitor)
	{
		m_SmoothScreenAction = action;
		g_SmoothMonitorMode = SMOOTH_MONITOR_SUNSET;
		g_SmoothMonitorColor = 1.0f;
	}
	else
		ProcessSmoothAction(action);
}
//---------------------------------------------------------------------------
int TBaseScreen::CalculateScrollerAndTextPosition(int &currentLine, int &visibleLines, int &maxY, int currentY)
{
	//��� ��������
	int scrollerY = 0;

	//���� �� ������� �� ����� ����������� ���������
	if (currentY < maxY)
	{
		//���� �������� ������
		if (currentY > 0)
		{
			//��������� �������, �� ������� ��� ��������
			float per = (currentY / (float)maxY) * 100.0f;

			//��������� �������� ������� ������������ �����
			int jsize = (int)((visibleLines * per) / 100.0f);

			//������������ �������� (��� �������������)
			if (jsize < 1)
				jsize = 1;
			else if (jsize > visibleLines)
				jsize = visibleLines;

			//���������� ������� �������� �����
			currentLine = jsize;

			//��������� ��������� ���������
			if (jsize >= visibleLines) //������������ - ���� �������� ����� ������/��������
				scrollerY = maxY;
			else //��� ���-�� � �������� ��������
				scrollerY = (int)((maxY * per) / 100.0f);
		}
		else //�������� ���, ���� �������� �� �����������
		{
			scrollerY = 0;
			currentLine = 0;
		}
	}
	else //����� �� ���������� �������, ���������� ��� �� ���������
	{
		currentLine = visibleLines;
		scrollerY = maxY;
	}

	//���������� ������� ���������
	return scrollerY;
}
//---------------------------------------------------------------------------
int TBaseScreen::CalculateScrollerY(int &currentLine, int &visibleLines, int &maxY)
{
	//��������, ����������� ���� ���� ��� �������� ���������
	float per = (currentLine / (float)visibleLines) * 100.0f;

	int jsize = (int)((visibleLines * per) / 100.0f);

	if (jsize < 1)
		jsize = 1;
	else if (jsize > visibleLines)
		jsize = visibleLines;

	int scrollerY = 0;

	if (jsize >= visibleLines)
		scrollerY = maxY;
	else
		scrollerY = (int)((maxY * per) / 100.0f);

	return scrollerY;
}
//---------------------------------------------------------------------------