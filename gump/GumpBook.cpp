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

TTextTexture TGumpBook::m_TextTitle;
TTextTexture TGumpBook::m_TextBy;
//----------------------------------------------------------------------------
TGumpBook::TGumpBook(DWORD serial, short x, short y, short pageCount, bool writable, bool unicode)
: TGump(GT_BOOK, serial, x, y), m_PageCount(pageCount), m_Writable(writable),
m_Unicode(unicode), m_Page(0)
{
	TextEntryAuthor = new TEntryText();
	TextEntryTitle = new TEntryText();

	TextEntry = new TBookEntryText[pageCount];
	m_PageIndexText = new TTextTexture[pageCount];

	IFOR(i, 0, pageCount)
		FontManager->GenerateA(9, m_PageIndexText[i], std::to_string(i).c_str(), 0x0386);
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

	if (TextEntry != NULL)
	{
		delete[] TextEntry;
		TextEntry = NULL;
	}

	if (m_PageIndexText != NULL)
	{
		delete[] m_PageIndexText;
		m_PageIndexText = NULL;
	}
}
//----------------------------------------------------------------------------
void TGumpBook::InitTextTextures()
{
	FontManager->UnusePartialHue = true;
	FontManager->GenerateA(4, m_TextTitle, "TITLE", 0x0386);
	FontManager->GenerateA(4, m_TextBy, "by", 0x0386);
	FontManager->UnusePartialHue = false;
}
//----------------------------------------------------------------------------
void TGumpBook::ReleaseTextTextures()
{
	m_TextTitle.Clear();
	m_TextBy.Clear();
}
//----------------------------------------------------------------------------
void TGumpBook::PrepareTextures()
{
	UO->ExecuteGumpPart(0x01FE, 3);
}
//----------------------------------------------------------------------------
bool TGumpBook::EntryPointerHere()
{
	bool result = (EntryPointer == TextEntryAuthor || EntryPointer == TextEntryTitle);

	if (!result && TextEntry != NULL)
	{
		IFOR(i, 0, m_PageCount && !result)
			result = (EntryPointer == &TextEntry[i]);
	}

	return result;
}
//---------------------------------------------------------------------------
void TGumpBook::GenerateFrame()
{
	if (!g_DrawMode)
	{
		m_FrameRedraw = false;
		m_FrameCreated = false;

		return;
	}

	glNewList((GLuint)this, GL_COMPILE);

		UO->DrawGump(0x01FE, 0, 0, 0); //Body

		if (m_Page)
			UO->DrawGump(0x01FF, 0, 0, 0); //Last page

		if (m_Page + 2 < m_PageCount)
			UO->DrawGump(0x0200, 0, 356, 0); //Next page

		if (!m_Page)
		{
			//�������� �����
			m_TextTitle.Draw(78, 32);
			TextEntryTitle->DrawA(4, 0, 41, 65);

			//�����
			m_TextBy.Draw(88, 134);
			TextEntryAuthor->DrawA(4, 0, 41, 160);

			//������ ��������
			FontManager->UnusePartialHue = true;
			TextEntry[1].DrawA(4, 0x0012, 224, 34);
			m_PageIndexText[1].Draw(299, 202);
			FontManager->UnusePartialHue = false;
		}
		else
		{
			FontManager->UnusePartialHue = true;
			//����� ��������
			TextEntry[m_Page].DrawA(4, 0x0012, 38, 34);
			m_PageIndexText[m_Page].Draw(112, 202);

			if (m_Page + 1 < m_PageCount)
			{
				//������ ��������
				TextEntry[m_Page + 1].DrawA(4, 0x0012, 224, 34);
				m_PageIndexText[m_Page + 1].Draw(299, 202);
			}
			FontManager->UnusePartialHue = false;
		}

	glEndList();

	m_FrameCreated = true;
	m_FrameRedraw = true;
}
//----------------------------------------------------------------------------
int TGumpBook::Draw(bool &mode)
{
	DWORD index = (DWORD)this;

	CalculateGumpState();

	if (mode) //���������
	{
		if (!m_FrameCreated || g_GumpMovingOffsetX || g_GumpMovingOffsetY)
			GenerateFrame();
		else if (m_FrameRedraw)
		{
			GenerateFrame();
			m_FrameRedraw = false;
		}

		glTranslatef(g_GumpTranslateX, g_GumpTranslateY, 0.0f);

		glCallList((GLuint)this);

		glTranslatef(-g_GumpTranslateX, -g_GumpTranslateY, 0.0f);
	}
	else //����� ��������
	{
		int oldMouseX = g_MouseX;
		int oldMouseY = g_MouseY;
		g_MouseX -= (int)g_GumpTranslateX;
		g_MouseY -= (int)g_GumpTranslateY;

		int LSG = 0;

		if (UO->GumpPixelsInXY(0x01FE, 0, 0))
			g_LastSelectedGump = index;

		if (m_Page && UO->GumpPixelsInXY(0x01FF, 0, 0))
			LSG = ID_GB_BUTTON_PREV; //Last page
		else if (m_Page + 2 < m_PageCount && UO->GumpPixelsInXY(0x0200, 356, 0))
			LSG = ID_GB_BUTTON_NEXT; //Next page
		else if (!m_Page)
		{
			if (UO->PolygonePixelsInXY(41, 65, 150, 22))
				LSG = ID_GB_TEXT_AREA_TITLE; //Text title
			else if (UO->PolygonePixelsInXY(41, 160, 150, 44))
				LSG = ID_GB_TEXT_AREA_AUTHOR; //Text author
			else if (UO->PolygonePixelsInXY(224, 34, 160, 166))
				LSG = ID_GB_TEXT_AREA_PAGE_RIGHT; //Text right area
		}
		else
		{
			if (UO->PolygonePixelsInXY(38, 34, 160, 166))
				LSG = ID_GB_TEXT_AREA_PAGE_LEFT; //Text left area
			else if (UO->PolygonePixelsInXY(224, 34, 160, 166))
				LSG = ID_GB_TEXT_AREA_PAGE_RIGHT; //Text right area
		}

		g_MouseX = oldMouseX;
		g_MouseY = oldMouseY;

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

	int newPage = -1;

	if (g_LastObjectLeftMouseDown == ID_GB_BUTTON_PREV) //Prev
	{
		if (!g_ClickObjectReq && m_Page > 0) //���� �� ���� ������� �� ����
		{
			newPage = m_Page - 2;

			if (newPage < 0)
				newPage = 0;
		}
	}
	else if (g_LastObjectLeftMouseDown == ID_GB_BUTTON_NEXT) //Next
	{
		if (!g_ClickObjectReq && m_Page < m_PageCount) //���� �� ���� ������� �� ����
		{
			newPage = m_Page + 2;

			if (newPage >= m_PageCount)
				newPage = m_PageCount - 1;
		}
	}
	else if (m_Writable)
	{
		int x = g_MouseX - m_X;
		int y = g_MouseY - m_Y;

		TEntryText *entry = NULL;

		if (g_LastObjectLeftMouseDown == ID_GB_TEXT_AREA_AUTHOR)
		{
			entry = TextEntryAuthor;
			x -= 41;
			y -= 160;
		}
		else if (g_LastObjectLeftMouseDown == ID_GB_TEXT_AREA_TITLE)
		{
			entry = TextEntryTitle;
			x -= 41;
			y -= 65;
		}
		else if (g_LastObjectLeftMouseDown == ID_GB_TEXT_AREA_PAGE_LEFT)
		{
			entry = &TextEntry[m_Page];
			x -= 38;
			y -= 34;
		}
		else if (g_LastObjectLeftMouseDown == ID_GB_TEXT_AREA_PAGE_RIGHT)
		{
			entry = &TextEntry[m_Page + 1];
			x -= 224;
			y -= 34;
		}

		if (entry != NULL)
			entry->OnClick(this, 4, false /*m_Unicode*/, x, y);
	}

	if (newPage > -1)
	{
		//���������� ������ �� ����
		g_ClickObjectReq = true;

		//�������������� ����-������
		g_ClickObject.Init(COT_GUMP);
		g_ClickObject.GumpType = GumpType;
		g_ClickObject.Serial = Serial;
		g_ClickObject.GumpID = ID;
		g_ClickObject.GumpButtonID = newPage;

		//TEST~>>
		m_Page = newPage;
		m_FrameCreated = false;
		g_ClickObjectReq = false;
		//TEST~<<

		//������ ����� �� ����������
		g_ClickObject.Timer = GetTickCount() + DCLICK_DELAY;
	}
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
		m_Page = 0;

		//���������� ����
		m_FrameCreated = false;

		return true;
	}
	else if (g_LastObjectLeftMouseDown == ID_GB_BUTTON_NEXT) //Next
	{
		//��� ����� ������ "������", ��� ��������� ������������� ��������� ��������
		if (m_PageCount % 2)
			m_Page = m_PageCount - 2;
		else
			m_Page = m_PageCount - 1;

		//���������� ����
		m_FrameCreated = false;

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void TGumpBook::OnCharPress(WPARAM &wparam, LPARAM &lparam)
{
	if (wparam == VK_RETURN || wparam == VK_BACK || wparam == VK_ESCAPE || EntryPointer == NULL)
		return; //Ignore no print keys

	if (EntryPointer == TextEntryTitle)
	{
	}
	else if (EntryPointer == TextEntryAuthor)
	{
	}
	else
	{
		int page = m_Page;

		if (page > 0 && page < m_PageCount)
		{
			if (EntryPointer != &TextEntry[page])
			{
				if (page < m_PageCount - 1 && EntryPointer == &TextEntry[page + 1])
					page++;
				else
					return;
			}
		}
	}

	/*if (!result && TextEntry != NULL)
	{
		IFOR(i, 0, m_PageCount && !result)
			result = (EntryPointer == &TextEntry[i]);

	if (wparam >= '0' && wparam <= '9')
	{
		if (m_StartText)
		{
			EntryPointer->Clear();
			m_StartText = false;
		}

		if (EntryPointer->Insert(wparam))
		{
			int val = atoi(EntryPointer->c_str());

			float ValPer = (val * 100.0f) / item->Count;

			if (ValPer <= 0.0f)
				ValPer = 0.0f;
			else
				ValPer = (ValPer * 93.0f) / 100.0f;

			m_ScrollPos = 29 + (int)ValPer;

			m_FrameCreated = false;
		}
	}*/
}
//----------------------------------------------------------------------------
void TGumpBook::OnKeyPress(WPARAM &wparam, LPARAM &lparam)
{
	TGameItem *item = World->FindWorldItem(Serial);

	if (item != NULL)
	{
		switch (wparam)
		{
			/*case VK_RETURN:
			{
				if (ConfigManager.GetConsoleNeedEnter())
					EntryPointer = NULL;
				else
					EntryPointer = GameConsole;

				break;
			}*/
			case VK_HOME:
			{
				EntryPointer->SetPos(0);
				m_FrameCreated = false;

				break;
			}
			case VK_END:
			{
				EntryPointer->SetPos(EntryPointer->Length());
				m_FrameCreated = false;

				break;
			}
			case VK_LEFT:
			{
				EntryPointer->AddPos(-1);
				m_FrameCreated = false;

				break;
			}
			case VK_RIGHT:
			{
				EntryPointer->AddPos(1);
				m_FrameCreated = false;

				break;
			}
			case VK_DELETE:
			case VK_BACK:
			{
				EntryPointer->Remove(wparam == VK_BACK);
				m_FrameCreated = false;

				break;
			}
			default:
				break;
		}
	}
}
//----------------------------------------------------------------------------