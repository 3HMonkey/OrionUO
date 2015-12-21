/****************************************************************************
**
** GumpBulletinBoardItem.cpp
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
TGumpBulletinBoardItem::TGumpBulletinBoardItem(DWORD serial, short x, short y, BYTE variant, DWORD id, string poster, string subject, string dataTime, string data)
: TGump(GT_BULLETIN_BOARD_ITEM, serial, x, y), m_Variant(variant), m_Height(200),
m_HeightBuffer(0), m_CurrentLine(0), m_LastScrollChangeTime(0)
{
	ID = id;

	TextEntry = new TEntryText(0, 220);
	TextEntry->SetText(data);

	TextEntrySubject = new TEntryText(0, 0, 150);
	TextEntrySubject->SetText(subject);

	FontManager->GenerateA(9, m_Poster, poster.c_str(), 0x0386);
	FontManager->GenerateA(9, m_DataTime, dataTime.c_str(), 0x0386);

	FontManager->GenerateA(6, m_Text[0], "Author:", 0);
	FontManager->GenerateA(6, m_Text[1], "Time:", 0);
	FontManager->GenerateA(6, m_Text[2], "Subject:", 0);
}
//----------------------------------------------------------------------------
TGumpBulletinBoardItem::~TGumpBulletinBoardItem()
{
	if (TextEntrySubject != NULL)
	{
		delete TextEntrySubject;
		TextEntrySubject = NULL;
	}

	if (TextEntry != NULL)
	{
		delete TextEntry;
		TextEntry = NULL;
	}

	m_Poster.Clear();
	m_DataTime.Clear();

	IFOR(i, 0, 3)
		m_Text[i].Clear();
}
//----------------------------------------------------------------------------
void TGumpBulletinBoardItem::PrepareTextures()
{
	UO->ExecuteGumpPart(0x0820, 6);
	UO->ExecuteGump(0x0828);
	UO->ExecuteGump(0x0835);
	UO->ExecuteGump(0x082B);
	UO->ExecuteGumpPart(0x082E, 2);

	switch (m_Variant)
	{
		case 0:
		{
			UO->ExecuteGump(0x0883); //NEW MESSAGE
			UO->ExecuteGump(0x0886); //Pos

			break;
		}
		case 2:
			UO->ExecuteGump(0x0885); //Remove
		case 1:
		{
			UO->ExecuteGump(0x0884); //Reply

			break;
		}
		default:
			break;
	}
}
//----------------------------------------------------------------------------
void TGumpBulletinBoardItem::SetHeight(int val)
{
	//��������� � ������������� �������� ������ �����
	if (val < 120)
		val = 120;

	int buf = GetSystemMetrics(SM_CYSCREEN) - 30;
	if (val >= buf)
		val = (GetSystemMetrics(SM_CYSCREEN) - 30);

	m_Height = val;
}
//----------------------------------------------------------------------------
void TGumpBulletinBoardItem::ChangeHeight()
{
	//������� ��������� ������ ����� � ��������� ��������������
	if (m_HeightBuffer)
		SetHeight(m_Height + (g_MouseY - m_HeightBuffer));

	m_HeightBuffer = 0;
	g_ResizedGump = NULL;
}
//----------------------------------------------------------------------------
int TGumpBulletinBoardItem::GetHeight()
{
	return TextEntry->m_Texture.Height + 10;
}
//---------------------------------------------------------------------------
void TGumpBulletinBoardItem::GenerateFrame(int posX, int posY)
{
	if (!g_DrawMode)
	{
		FrameRedraw = false;
		FrameCreated = false;

		return;
	}

	DWORD index = (DWORD)this;

	int height = m_Height;

	if (m_HeightBuffer)
	{
		height += (g_MouseY - m_HeightBuffer);

		if (height < 120)
			height = 120;

		int buf = (GetSystemMetrics(SM_CYSCREEN) - 30);
		if (height >= buf)
			height = buf;
	}
	
	//������ �� ������ � ����?
	bool IsPressed = (g_LeftMouseDown && g_LastGumpLeftMouseDown == index && g_LastSelectedGump == index);
	
	//������ �� ������ � ����?
	bool IsScrollerPressed = (g_LeftMouseDown && g_LastGumpLeftMouseDown == index);

	//����� �� ���� ��������� �������?
	int CanSelectedButton = ((g_LastSelectedGump == index) ? g_LastSelectedObject : 0);

	//����� �� ���� ����� �������?
	int CanPressedButton = 0;
	if (IsPressed && g_LastObjectLeftMouseDown == g_LastSelectedObject)
		CanPressedButton = g_LastObjectLeftMouseDown;

	int scrollerY = 0;

	int heightToScrolling = 0;

	bool canMoveScroller = true;

	int curHeight = GetHeight();

	if (curHeight < height - 100)
		canMoveScroller = false;
	else
		heightToScrolling = curHeight - (height - 100);
	
	int maxScrollerY = height - 132;
	
	int visibleLines = heightToScrolling / GUMP_SCROLLING_PIXEL_STEP;

	if (IsScrollerPressed && g_LastObjectLeftMouseDown == ID_GBBI_SCROLLER && canMoveScroller) //Scroller pressed
	{
		int currentY = (g_MouseY - 10) - posY - 120; //Scroller position

		scrollerY = CalculateScrollerAndTextPosition(m_CurrentLine, visibleLines, maxScrollerY, currentY);
	}
	else if (m_CurrentLine && canMoveScroller)
		scrollerY = CalculateScrollerY(m_CurrentLine, visibleLines, maxScrollerY);

	//�������� ������� �����
	glNewList((GLuint)index, GL_COMPILE);

		UO->DrawGump(0x0820, 0, posX, posY); //Top scroll

		//Profile window body
		int curPosY = posY + 36;

		while (true)
		{
			int deltaHeight = (height + posY) - (curPosY - 36);
			if (deltaHeight  < 70)
			{
				if (deltaHeight > 0)
					UO->DrawGump(0x0821, 0, posX + 18, curPosY, 0, deltaHeight);

				break;
			}
			else
				UO->DrawGump(0x0821, 0, posX + 18, curPosY);

			curPosY += 70;

			deltaHeight = (height + posY) - (curPosY - 36);

			if (deltaHeight < 70)
			{
				if (deltaHeight > 0)
					UO->DrawGump(0x0822, 0, posX + 18, curPosY, 0, deltaHeight);

				break;
			}
			else
				UO->DrawGump(0x0822, 0, posX + 18, curPosY);

			curPosY += 70;
		}
		
		UO->DrawGump(0x082B, 0, posX + 30, posY + 34); //Top line
		
		//Author
		m_Text[0].Draw(posX + 30, posY + 40);
		m_Poster.Draw(posX + 30 + m_Text[0].Width, posY + 46);

		//Time
		m_Text[1].Draw(posX + 30, posY + 56);
		m_DataTime.Draw(posX + 30 + m_Text[1].Width, posY + 62);

		//Subject
		m_Text[2].Draw(posX + 30, posY + 72);
		WORD subjectColor = 0x0386;
		if (!m_Variant)
			subjectColor = 0x0008;
		TextEntrySubject->DrawA(9, subjectColor, posX + 30 + m_Text[2].Width, posY + 78);

		UO->DrawGump(0x0835, 0, posX + 30, posY + 110, 204, 0); //Line
		
		UO->DrawGump(0x0824, 0, posX + 246, posY + 106); //^ button
		UO->DrawGump(0x0828, 0, posX + 255, posY + 120 + scrollerY); //Scroller
		
		g_GL.ViewPort(posX + 30, posY + 120, 220, height - 100);

		int yPtr = posY + 120 - (m_CurrentLine * GUMP_SCROLLING_PIXEL_STEP);

		TextEntry->DrawA(9, 0x0386, posX + 30, yPtr, TS_LEFT, 0);
		
		g_GL.RestorePort();

		UO->DrawGump(0x0823, 0, posX + 18, posY + height + 34); //Bottom scroll
		UO->DrawGump(0x0825, 0, posX + 246, posY + height + 17); //v button
		UO->DrawGump(0x082B, 0, posX + 30, posY + height + 21); //Bottom line

		switch (m_Variant)
		{
			case 0:
			{
				UO->DrawGump(0x0883, 0, posX + 97, posY + 12); //NEW MESSAGE
				UO->DrawGump(0x0886, 0, posX + 37, posY + height + 45); //Post

				break;
			}
			case 2:
				UO->DrawGump(0x0885, 0, posX + 235, posY + height + 45); //Remove
			case 1:
			{
				UO->DrawGump(0x0884, 0, posX + 37, posY + height + 45); //Reply

				break;
			}
			default:
				break;
		}

		WORD gumpID = 0x082E + (int)(CanSelectedButton == ID_GBBI_BUTTON_RESIZE);
		UO->DrawGump(gumpID, 0, posX + 139, posY + height + 66); //Resize

	//��������� ������ ������� �����
	glEndList();

	FrameRedraw = true;
	FrameCreated = true;
}
//----------------------------------------------------------------------------
int TGumpBulletinBoardItem::Draw(bool &mode)
{
	DWORD index = (DWORD)this;

	//��� �������� �������
	int posX = X;
	int posY = Y;
	bool needRedraw = false;

	//���� ������ ��������� ��� ����������� - �������� �������
	if (mode && g_LeftMouseDown && g_LastGumpLeftMouseDown == index && (!g_LastObjectLeftMouseDown || g_LastObjectLeftMouseDown == ID_GBBI_TEXT_FIELD))
	{
		posX += (g_MouseX - g_DroppedLeftMouseX);
		posY += (g_MouseY - g_DroppedLeftMouseY);

		needRedraw = mode;
	}

	int height = m_Height;

	if (m_HeightBuffer)
	{
		height += (g_MouseY - m_HeightBuffer);

		if (height < 120)
			height = 120;

		int buf = (GetSystemMetrics(SM_CYSCREEN) - 30);
		if (height >= buf)
			height = buf;
		
		needRedraw = mode;
	}
	
	//������ �� ������ � ����?
	bool IsPressed = (g_LeftMouseDown && g_LastGumpLeftMouseDown == index && g_LastSelectedGump == index);
	
	//������ �� ������ � ����?
	bool IsScrollerPressed = (g_LeftMouseDown && g_LastGumpLeftMouseDown == index);

	//����� �� ���� ��������� �������?
	int CanSelectedButton = ((g_LastSelectedGump == index) ? g_LastSelectedObject : 0);

	//����� �� ���� ����� �������?
	int CanPressedButton = 0;
	if (IsPressed && g_LastObjectLeftMouseDown == g_LastSelectedObject)
		CanPressedButton = g_LastObjectLeftMouseDown;

	//��������, ����� ���������� �������� ��������� ������������� ��������
	if (IsPressed && m_LastScrollChangeTime < GetTickCount())
	{
		if (g_LastObjectLeftMouseDown == ID_GBBI_SCROLLER_UP) //��������� ����� (������-��������)
			ListingList(true, 10);
		else if (g_LastObjectLeftMouseDown == ID_GBBI_SCROLLER_DOWN) //��������� ���� (������-��������)
			ListingList(false, 10);
	}

	int scrollerY = 0;

	int heightToScrolling = 0;

	bool canMoveScroller = true;

	int curHeight = GetHeight();

	if (curHeight < height - 100)
		canMoveScroller = false;
	else
		heightToScrolling = curHeight - (height - 100);
	
	int maxScrollerY = height - 132;

	int visibleLines = heightToScrolling / GUMP_SCROLLING_PIXEL_STEP;

	if (IsScrollerPressed && g_LastObjectLeftMouseDown == ID_GBBI_SCROLLER && canMoveScroller) //Scroller pressed
	{
		int currentY = (g_MouseY - 10) - posY - 120; //Scroller position

		scrollerY = CalculateScrollerAndTextPosition(m_CurrentLine, visibleLines, maxScrollerY, currentY);
		
		needRedraw = mode;
	}
	else if (m_CurrentLine && canMoveScroller)
		scrollerY = CalculateScrollerY(m_CurrentLine, visibleLines, maxScrollerY);

	if (mode) //���������
	{
		if (CanSelectedButton || needRedraw)
			GenerateFrame(posX, posY);
		else if (FrameRedraw)
		{
			GenerateFrame(posX, posY);
			FrameRedraw = false;
		}
		//���� ����� �� ��� ������ - �������
		else if (!FrameCreated)
			GenerateFrame(posX, posY);

		//��������� �����
		glCallList((GLuint)index);
	}
	else //����� ��������
	{
		int LSG = 0;

		if (UO->GumpPixelsInXY(0x0820, posX, posY + 23)) //Top scroll
		{
			g_LastSelectedObject = 0;
			g_LastSelectedGump = index;
		}
		else if (UO->GumpPixelsInXY(0x0823, posX + 18, posY + height + 34)) //Bottom scroll
		{
			g_LastSelectedObject = 0;
			g_LastSelectedGump = index;
		}
		else if (UO->GumpPixelsInXY(0x0828, posX + 255, posY + 120 + scrollerY)) //Scroller
		{
			g_LastSelectedGump = index;
			LSG = ID_GBBI_SCROLLER;
		}
		else if (UO->GumpPixelsInXY(0x082E, posX + 139, posY + height + 66)) //Resize
		{
			g_LastSelectedGump = index;
			LSG = ID_GBBI_BUTTON_RESIZE;
		}
		else //body
		{
			int curPosY = posY + 59;

			while (true)
			{
				int deltaHeight = (height + posY) - (curPosY - 36);

				if (deltaHeight  < 70)
				{
					if (deltaHeight > 0)
					{
						if (UO->GumpPixelsInXY(0x0821, posX + 18, curPosY, 0, deltaHeight))
						{
							g_LastSelectedObject = 0;
							g_LastSelectedGump = index;
						}
					}

					break;
				}
				else if (UO->GumpPixelsInXY(0x0821, posX + 18, curPosY))
				{
					g_LastSelectedObject = 0;
					g_LastSelectedGump = index;

					break;
				}

				curPosY += 70;

				deltaHeight = (height + posY) - (curPosY - 36);

				if (deltaHeight < 70)
				{
					if (deltaHeight > 0)
					{
						if (UO->GumpPixelsInXY(0x0822, posX + 18, curPosY, 0, deltaHeight))
						{
							g_LastSelectedObject = 0;
							g_LastSelectedGump = index;
						}
					}

					break;
				}
				else if (UO->GumpPixelsInXY(0x0822, posX + 18, curPosY))
				{
					g_LastSelectedObject = 0;
					g_LastSelectedGump = index;

					break;
				}

				curPosY += 70;
			}
		}
		
		if (g_LastSelectedGump == index)
		{
			if (UO->PolygonePixelsInXY(posX + 246, posY + 106, 20, 18)) //^
				LSG = ID_GBBI_SCROLLER_UP;
			else if (UO->PolygonePixelsInXY(posX + 246, posY + height + 17, 20, 18)) //v
				LSG = ID_GBBI_SCROLLER_DOWN;
			else
			{
				switch (m_Variant)
				{
					case 0:
					{
						if (UO->PolygonePixelsInXY(posX + 30 + m_Text[2].Width, posY + 78, 160, 16)) //Subject text
							LSG = ID_GBBI_SUBJECT_TEXT_FIELD;
						else if (LSG != ID_GBBI_SCROLLER && UO->PolygonePixelsInXY(posX + 30, posY + 120, 220, height - 100)) //Text
							LSG = ID_GBBI_TEXT_FIELD;
						else if (UO->PolygonePixelsInXY(posX + 37, posY + height + 45, 30, 14)) //Post
							LSG = ID_GBBI_POST;

						break;
					}
					case 2:
					{
						if (UO->PolygonePixelsInXY(posX + 235, posY + height + 45, 50, 14)) //Remove
							LSG = ID_GBBI_REMOVE;
					}
					case 1:
					{
						if (UO->PolygonePixelsInXY(posX + 37, posY + height + 45, 40, 14)) //Reply
							LSG = ID_GBBI_REPLY;

						break;
					}
					default:
						break;
				}
			}
		}

		if (LSG != 0)
			g_LastSelectedObject = LSG; //���� ���-�� ������� - ��������

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
void TGumpBulletinBoardItem::OnLeftMouseDown()
{
	if (g_LastSelectedObject == ID_GBBI_SUBJECT_TEXT_FIELD)
	{
		int x = g_MouseX - (X + 40);
		int y = g_MouseY - (Y + 44);

		TextEntrySubject->OnClick(this, 9, true, x, y);
	}
	else if (g_LastSelectedObject == ID_GBBI_TEXT_FIELD)
	{
		int yPtr = 40 - (m_CurrentLine * GUMP_SCROLLING_PIXEL_STEP);

		int x = g_MouseX - (X + 40);
		int y = g_MouseY - (Y + yPtr + 44);

		TextEntry->OnClick(this, 1, true, x, y);
	}
}
//----------------------------------------------------------------------------
void TGumpBulletinBoardItem::OnLeftMouseUp()
{
	if (g_LastObjectLeftMouseDown != g_LastSelectedObject)
		return;

	if (g_LastObjectLeftMouseDown == ID_GBBI_BUTTON_RESIZE)
	{
		if (!m_HeightBuffer)
		{
			m_HeightBuffer = g_DroppedLeftMouseY;
			g_ResizedGump = this;
		}
		else
		{
			SetHeight(m_Height + (g_MouseY - m_HeightBuffer));
			m_HeightBuffer = 0;
			g_ResizedGump = NULL;
		}
	}
	else if (g_LastObjectLeftMouseDown == ID_GBBI_POST)
	{
		TPacketBulletinBoardPostMessage packet(ID, 0, TextEntrySubject->c_str(), TextEntry->c_str());
		packet.Send();
		packet.Free();
		
		GumpManager->RemoveGump(this);
	}
	else if (g_LastObjectLeftMouseDown == ID_GBBI_REPLY)
	{
		string subj("RE: ");
		subj += TextEntrySubject->c_str();

		TGumpBulletinBoardItem *gump = new TGumpBulletinBoardItem(0, 0, 0, 0, ID, g_Player->GetName(), subj, "Date/Time",  "");

		TGump *gumpEntry = GumpManager->GetTextEntryOwner();

		EntryPointer = gump->TextEntrySubject;

		if (gumpEntry != NULL)
			gumpEntry->UpdateFrame();

		GumpManager->AddGump(gump);
	}
	else if (g_LastObjectLeftMouseDown == ID_GBBI_REMOVE)
	{
		TPacketBulletinBoardRemoveMessage packet(ID, Serial);
		packet.Send();

		//GumpManager->CloseGump(Serial, ID, GT_BULLETIN_BOARD_ITEM);
	}
}
//----------------------------------------------------------------------------
void TGumpBulletinBoardItem::OnMouseWheel(MOUSE_WHEEL_STATE &state)
{
	if (!g_LeftMouseDown && !g_RightMouseDown)
	{
		if (m_LastScrollChangeTime < GetTickCount())
		{
			if (state == MWS_UP)
			{
				ListingList(true, 25);
				GenerateFrame(X, Y);
			}
			else if (state == MWS_DOWN)
			{
				ListingList(false, 25);
				GenerateFrame(X, Y);
			}
		}
	}
}
//----------------------------------------------------------------------------
void TGumpBulletinBoardItem::OnCharPress(WPARAM &wparam, LPARAM &lparam)
{
	EntryPointer->Insert(wparam);

	GenerateFrame(X, Y);
}
//----------------------------------------------------------------------------
void TGumpBulletinBoardItem::OnKeyPress(WPARAM &wparam, LPARAM &lparam)
{
	if (wparam == VK_RETURN && EntryPointer == TextEntry)
	{
		EntryPointer->Insert(L'\n');

		UpdateFrame(); //����������
	}
	else
		EntryPointer->OnKey(this, wparam);
}
//----------------------------------------------------------------------------
void TGumpBulletinBoardItem::ListingList(bool direction, int divizor)
{
	if (direction) //Up
	{
		if (m_CurrentLine > 1)
			m_CurrentLine--;
		else
			m_CurrentLine = 0;
	}
	else //Down
	{
		int maxidx = (GetHeight() - (m_Height - 100)) / GUMP_SCROLLING_PIXEL_STEP;

		if (maxidx < 0)
			maxidx = 0;

		if (m_CurrentLine < maxidx)
			m_CurrentLine++;
		else
			m_CurrentLine = maxidx;
	}

	m_LastScrollChangeTime = GetTickCount() + (SCROLL_LISTING_DELAY / divizor);
}
//----------------------------------------------------------------------------