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
/*!
���������� ��������� ��������
@return ������ ���������
*/
int TBaseScreen::DrawSmoothMonitor()
{
	if (SmoothMonitor.Process())
	{
		ProcessSmoothAction();

		g_GL.EndDraw();

		return 1;
	}

	return 0;
}
//---------------------------------------------------------------------------
/*!
��������� ������� ��������
@return 
*/
void TBaseScreen::DrawSmoothMonitorEffect()
{
	SmoothMonitor.Draw();
}
//---------------------------------------------------------------------------
/*!
�������� �������� ���������� ������
@param [__in] action ������������� ��������
@return 
*/
void TBaseScreen::CreateSmoothAction( __in BYTE action)
{
	if (SmoothMonitor.UseSunset())
		m_SmoothScreenAction = action;
	else
		ProcessSmoothAction(action);
}
//---------------------------------------------------------------------------
/*!
���������� �������� �������� � ���� �����������
@param [__out] currentLine ������� ������
@param [__in] visibleLines ���������� ������� �����
@param [__in] maxY ������������ �������� Y ����������
@param [__in] currentY ������� �������� Y ����������
@return ���������� Y ���������
*/
int TBaseScreen::CalculateScrollerAndTextPosition( __out int &currentLine, __in int &visibleLines, __in int &maxY, __in int currentY)
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
/*!
���������� �������� ���������
@param [__in] currentLine ������� ������
@param [__in] visibleLines ���������� ������� �����
@param [__in] maxY ������������ �������� Y ����������
@return ���������� Y ���������
*/
int TBaseScreen::CalculateScrollerY( __in int &currentLine, __in int &visibleLines, __in int &maxY)
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