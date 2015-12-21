/****************************************************************************
**
** GumpBook.cpp
**
** Copyright (C) October 2015 Hotride
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
//----------------------------------------------------------------------------
#include "stdafx.h"
//----------------------------------------------------------------------------
TGumpBook::TGumpBook(DWORD serial, short x, short y, short pageCount, bool writable, bool unicode)
: TGump(GT_BOOK, serial, x, y), m_PageCount(pageCount), m_Writable(writable),
m_Unicode(unicode), m_Page(0)
{
	TextEntryAuthor = new TEntryText();
	TextEntryTitle = new TEntryText();

	IFOR(i, 0, 2)
		TextEntry[i] = new TBookEntryText();
}
//----------------------------------------------------------------------------
TGumpBook::~TGumpBook()
{
	if (TextEntryAuthor != NULL)
	{
		delete TextEntryAuthor;
		TextEntryAuthor = NULL;
	}

	if (TextEntryTitle != NULL)
	{
		delete TextEntryTitle;
		TextEntryTitle = NULL;
	}

	IFOR(i, 0, 2)
	{
		if (TextEntry[i] != NULL)
		{
			delete TextEntry[i];
			TextEntry[i] = NULL;
		}
	}
}
//----------------------------------------------------------------------------
void TGumpBook::PrepareTextures()
{
}
//---------------------------------------------------------------------------
void TGumpBook::GenerateFrame(int posX, int posY)
{
	if (!g_DrawMode)
	{
		FrameRedraw = false;
		FrameCreated = false;

		return;
	}
}
//----------------------------------------------------------------------------
int TGumpBook::Draw(bool &mode)
{
	DWORD index = (DWORD)this;

	//��� �������� �������
	int posX = X;
	int posY = Y;

	if (Minimized)
	{
		posX = MinimizedX;
		posY = MinimizedY;
	}

	//������ �� ������ � ����?
	bool IsPressed = (g_LeftMouseDown && g_LastGumpLeftMouseDown == index && g_LastSelectedGump == index);

	//����� �� ���� ��������� �������?
	int CanSelectedButton = ((g_LastSelectedGump == index) ? g_LastSelectedObject : 0);

	//����� �� ���� ����� �������?
	int CanPressedButton = 0;
	if (IsPressed && g_LastObjectLeftMouseDown == g_LastSelectedObject)
		CanPressedButton = g_LastObjectLeftMouseDown;

	//���� ������ ��������� ��� ����������� - �������� �������
	if (mode && g_LeftMouseDown && g_LastGumpLeftMouseDown == index && !g_LastObjectLeftMouseDown)
	{
		posX += (g_MouseX - g_DroppedLeftMouseX);
		posY += (g_MouseY - g_DroppedLeftMouseY);
	}

	if (mode) //���������
	{
		//0x01FE
	}
	else //����� ��������
	{
		int LSG = 0;

		if (LSG != 0)
			g_LastSelectedObject = LSG; //���� ���-�� ������� - ��������

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
void TGumpBook::OnLeftMouseUp()
{
	//�������� ���������� ����������
	if (g_LastObjectLeftMouseDown != g_LastSelectedObject || !g_LastObjectLeftMouseDown || Minimized || !g_LastSelectedGump)
		return;

	//�������� ������� �������� � ������
	int lastPage = m_Page;

	if (g_LastObjectLeftMouseDown == ID_GB_BUTTON_PREV) //Prev
	{
		//������ �� ������ "�����"

		if (!g_ClickObjectReq && m_Page > 0) //���� �� ���� ������� �� ����
		{
			//���������� ������ �� ����
			g_ClickObjectReq = true;

			//�������������� ����-������
			g_ClickObject.Init(COT_GUMP);
			g_ClickObject.GumpType = GumpType;
			g_ClickObject.Serial = Serial;
			g_ClickObject.GumpID = ID;
			g_ClickObject.GumpButtonID = m_Page - 1;

			//������ ����� �� ����������
			g_ClickObject.Timer = GetTickCount() + DCLICK_DELAY;
		}
	}
	else if (g_LastObjectLeftMouseDown == ID_GB_BUTTON_NEXT) //Next
	{
		//������ �� ������ "�����"

		if (!g_ClickObjectReq && m_Page < m_PageCount) //���� �� ���� ������� �� ����
		{
			//���������� ������ �� ����
			g_ClickObjectReq = true;

			//�������������� ����-������
			g_ClickObject.Init(COT_GUMP);
			g_ClickObject.GumpType = GumpType;
			g_ClickObject.Serial = Serial;
			g_ClickObject.GumpID = ID;
			g_ClickObject.GumpButtonID = m_Page + 1;

			//������ ����� �� ����������
			g_ClickObject.Timer = GetTickCount() + DCLICK_DELAY;
		}
	}

	//���� ���� �������� �������� - ���������� ����
	if (lastPage != m_Page)
		UpdateFrame();
}
//----------------------------------------------------------------------------
bool TGumpBook::OnLeftMouseDoubleClick()
{
	//���� ������ ������� �� ���� - ������ �� ����
	if (!g_LastSelectedGump)
		return false;

	if (g_LastObjectLeftMouseDown == ID_GB_BUTTON_PREV) //Prev
	{
		//��� ����� ������ "�����", ��� ��������� ������������� 1 ��������
		m_Page = 1;

		//���������� ����
		UpdateFrame();

		return true;
	}
	else if (g_LastObjectLeftMouseDown == ID_GB_BUTTON_NEXT) //Next
	{
		//��� ����� ������ "������", ��� ��������� ������������� ��������� ��������
		m_Page = m_PageCount;

		//���������� ����
		UpdateFrame();

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------