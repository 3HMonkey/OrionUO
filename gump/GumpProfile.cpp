/****************************************************************************
**
** GumpProfile.cpp
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
TGumpProfile::TGumpProfile(DWORD serial, short x, short y, wstring topText, wstring bottomText, wstring dataText)
: TGump(GT_PROFILE, serial, x, y), m_Height(200), m_HeightBuffer(0), m_CurrentLine(0),
m_LastScrollChangeTime(0), m_Changed(false)
{
	FontManager->GenerateW(1, m_TopText, topText.c_str(), 0, 30, 140);
	FontManager->GenerateW(1, m_BottomText, bottomText.c_str(), 0, 30, 190);

	TextEntry = new TEntryText(0, 210);
	TextEntry->SetText(dataText);
}
//----------------------------------------------------------------------------
TGumpProfile::~TGumpProfile()
{
	m_TopText.Clear();
	m_BottomText.Clear();

	if (m_Changed)
	{
		TPacketProfileUpdate packet(Serial, TextEntry->Data(), TextEntry->Length());
		packet.Send();
		packet.Free();
	}

	if (TextEntry != NULL)
	{
		delete TextEntry;
		TextEntry = NULL;
	}
}
//----------------------------------------------------------------------------
void TGumpProfile::PrepareTextures()
{
	UO->ExecuteGump(0x001F);
	UO->ExecuteGumpPart(0x005C, 6);
	UO->ExecuteGumpPart(0x0820, 4);
	UO->ExecuteButton(0x082D);
	UO->ExecuteGump(0x09D4);
}
//----------------------------------------------------------------------------
void TGumpProfile::SetHeight(int val)
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
void TGumpProfile::ChangeHeight()
{
	//������� ��������� ������ ����� � ��������� ��������������
	if (m_HeightBuffer)
		SetHeight(m_Height + (g_MouseY - m_HeightBuffer));

	m_HeightBuffer = 0;
	g_ResizedGump = NULL;
}
//----------------------------------------------------------------------------
int TGumpProfile::GetHeight()
{
	int height = m_TopText.Height;

	if (TextEntry->Length())
		height += TextEntry->m_Texture.Height;
	else
		height += 14;

	height += 73;
		
	height += m_BottomText.Height;
	
	return height;
}
//---------------------------------------------------------------------------
void TGumpProfile::GenerateFrame(int posX, int posY)
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

	if (!Minimized)
	{
		bool canMoveScroller = true;

		int curHeight = GetHeight();

		if (curHeight < height - 30)
			canMoveScroller = false;
		else
			heightToScrolling = curHeight - (height - 30);
	
		int maxScrollerY = height - 89;

		int visibleLines = heightToScrolling / GUMP_SCROLLING_PIXEL_STEP;

		if (IsScrollerPressed && g_LastObjectLeftMouseDown == ID_GP_SCROLLER && canMoveScroller) //Scroller pressed
		{
			int currentY = (g_MouseY - 10) - posY - 72; //Scroller position

			scrollerY = CalculateScrollerAndTextPosition(m_CurrentLine, visibleLines, maxScrollerY, currentY);
		}
		else if (m_CurrentLine && canMoveScroller)
			scrollerY = CalculateScrollerY(m_CurrentLine, visibleLines, maxScrollerY);
	}

	//�������� ������� �����
	glNewList((GLuint)index, GL_COMPILE);

		if (Minimized)
		{
			UO->DrawGump(0x09D4, 0, posX, posY);

			//�������� �������� ����� � ������ �� ���������
			glEndList();

			FrameRedraw = true;
			FrameCreated = true;

			return;
		}

		UO->DrawGump(0x082D, 0, posX + 137, posY); //Minimize
		UO->DrawGump(0x0820, 0, posX, posY + 23); //Top scroll

		//Profile window body
		int curPosY = posY + 59;

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

		UO->DrawGump(0x001F, 0, posX + 257, posY + 72 + scrollerY); //Scroller
		
		int yPtr = posY + m_TopText.Height + 40;

		g_GL.ViewPort(posX + 36, yPtr, 220, height - 30);
		
		yPtr -= (m_CurrentLine * GUMP_SCROLLING_PIXEL_STEP);

		UO->DrawGump(0x005C, 0, posX + 40, yPtr); //top text ornament
		UO->DrawGump(0x005D, 0, posX + 92, yPtr, 138, 0); //top text ornament
		UO->DrawGump(0x005E, 0, posX + 230, yPtr); //top text ornament
		m_TopText.Draw(posX + 89, yPtr - m_TopText.Height + 22);

		if (TextEntry->Length())
		{
			TextEntry->DrawW(1, 0, posX + 40, yPtr + 44, TS_LEFT, 0);

			yPtr += TextEntry->m_Texture.Height;
		}
		else
			yPtr += 14;

		yPtr += 47;
		
		UO->DrawGump(0x005F, 0, posX + 40, yPtr); //bottom text ornament
		UO->DrawGump(0x0060, 0, posX + 49, yPtr + 9, 197, 0); //bottom text ornament
		UO->DrawGump(0x0061, 0, posX + 246, yPtr); //bottom text ornament

		m_BottomText.Draw(posX + 38, yPtr + 26);
		
		g_GL.RestorePort();

		UO->DrawGump(0x0823, 0, posX + 18, posY + height + 34); //Bottom scroll

		WORD gumpID = 0x082E + (int)(CanSelectedButton == ID_GP_BUTTON_RESIZE);
		UO->DrawGump(gumpID, 0, posX + 137, posY + height + 66); //Resize

	//��������� ������ ������� �����
	glEndList();

	FrameRedraw = true;
	FrameCreated = true;
}
//----------------------------------------------------------------------------
int TGumpProfile::Draw(bool &mode)
{
	DWORD index = (DWORD)this;

	//��� �������� �������
	int posX = X;
	int posY = Y;

	if (Minimized)
	{
		posX = MinimizedX;
		posY = MinimizedY;

		m_HeightBuffer = 0;
	}

	bool needRedraw = false;

	//���� ������ ��������� ��� ����������� - �������� �������
	if (mode && g_LeftMouseDown && g_LastGumpLeftMouseDown == index && (!g_LastObjectLeftMouseDown || g_LastObjectLeftMouseDown == ID_GP_TEXT_FIELD))
	{
		posX += (g_MouseX - g_DroppedLeftMouseX);
		posY += (g_MouseY - g_DroppedLeftMouseY);

		//���� ��� ����� ��������� - ������ ����� �����
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
		
		//���� ��� ����� ��������� - ������ ����� �����
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

	int scrollerY = 0;

	int heightToScrolling = 0;

	if (!Minimized)
	{
		bool canMoveScroller = true;

		int curHeight = GetHeight();

		if (curHeight < height - 30)
			canMoveScroller = false;
		else
			heightToScrolling = curHeight - (height - 30);
	
		int maxScrollerY = height - 89;

		int visibleLines = heightToScrolling / GUMP_SCROLLING_PIXEL_STEP;

		if (IsScrollerPressed && g_LastObjectLeftMouseDown == ID_GP_SCROLLER && canMoveScroller) //Scroller pressed
		{
			int currentY = (g_MouseY - 10) - posY - 72; //Scroller position

			scrollerY = CalculateScrollerAndTextPosition(m_CurrentLine, visibleLines, maxScrollerY, currentY);
			
			needRedraw = mode;
		}
		else if (m_CurrentLine && canMoveScroller)
			scrollerY = CalculateScrollerY(m_CurrentLine, visibleLines, maxScrollerY);
	}

	if (mode) //����������� ������, ��� ���������� ����������� �������
	{
		if (needRedraw)
			GenerateFrame(posX, posY);
		else if (FrameRedraw)
		{
			GenerateFrame(posX, posY);
			FrameRedraw = false;
		}
	}

	if (mode) //���������
	{
		//���� ����� �� ��� ������ - �������
		if (!FrameCreated)
			GenerateFrame(posX, posY);

		//��������� �����
		glCallList((GLuint)index);
	}
	else //����� ��������
	{
		if (Minimized)
		{
			if (UO->GumpPixelsInXY(0x09D4, posX, posY))
			{
				g_LastSelectedObject = 0;
				g_LastSelectedGump = index;
			}

			return 0;
		}
		
		int LSG = 0;
		
		if (UO->GumpPixelsInXY(0x082D, posX + 137, posY)) //Minimize
		{
			LSG = ID_GP_BUTTON_MINIMIZE;
			g_LastSelectedGump = index;
		}
		
		if (UO->GumpPixelsInXY(0x0820, posX, posY + 23)) //Top scroll
		{
			g_LastSelectedObject = 0;
			g_LastSelectedGump = index;
		}

		//Tip window body
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
		
		if (g_MouseY > posY + 58 && g_MouseY < posY + 58 + height - 30) //� ������� ����
		{
			int yPtr = posY + m_TopText.Height + 40 - (m_CurrentLine * GUMP_SCROLLING_PIXEL_STEP);

			if (UO->GumpPixelsInXY(0x005C, posX + 40, yPtr))
			{
				g_LastSelectedGump = index;
				LSG = ID_GP_APPLY;
			}
			
			int texHeight = 14;
			if (TextEntry->Length())
				texHeight = TextEntry->m_Texture.Height;

			RECT rc = {0, 0, 210, texHeight};
			POINT p = {g_MouseX - (posX + 40), g_MouseY - (yPtr + 44)};

			if (PtInRect(&rc, p))
				LSG = ID_GP_TEXT_FIELD;
		}

		if (UO->GumpPixelsInXY(0x0823, posX + 18, posY + height + 34)) //Bottom scroll
		{
			g_LastSelectedObject = 0;
			g_LastSelectedGump = index;
		}

		if (UO->GumpPixelsInXY(0x001F, posX + 257, posY + 72 + scrollerY)) //Scroller
		{
			g_LastSelectedGump = index;
			LSG = ID_GP_SCROLLER;
		}
		
		if (UO->GumpPixelsInXY(0x082E, posX + 137, posY + height + 66)) //Resize
		{
			g_LastSelectedGump = index;
			LSG = ID_GP_BUTTON_RESIZE;
		}

		if (LSG != 0)
			g_LastSelectedObject = LSG; //���� ���-�� ������� - ��������

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
void TGumpProfile::OnLeftMouseDown()
{
	if (Serial == g_PlayerSerial && g_LastSelectedObject == ID_GP_TEXT_FIELD)
	{
		int yPtr = m_TopText.Height + 40 - (m_CurrentLine * GUMP_SCROLLING_PIXEL_STEP);

		int x = g_MouseX - (X + 40);
		int y = g_MouseY - (Y + yPtr + 44);

		TextEntry->OnClick(this, 1, true, x, y);
	}
}
//----------------------------------------------------------------------------
void TGumpProfile::OnLeftMouseUp()
{
	if (g_LastObjectLeftMouseDown != g_LastSelectedObject)
		return;

	DWORD ticks = GetTickCount();

	if (g_LastObjectLeftMouseDown == ID_GP_BUTTON_MINIMIZE)
	{
		Minimized = true;

		GenerateFrame(MinimizedX, MinimizedY);
	}
	else if (g_LastObjectLeftMouseDown == ID_GP_BUTTON_RESIZE)
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
	else if (Serial == g_PlayerSerial && g_LastObjectLeftMouseDown == ID_GP_APPLY)
	{
		m_Changed = true;
		
		if (EntryPointer == TextEntry)
		{
			if (ConfigManager.GetConsoleNeedEnter())
				EntryPointer = NULL;
			else
				EntryPointer = GameConsole;
		}

		UpdateFrame();
	}
}
//----------------------------------------------------------------------------
bool TGumpProfile::OnLeftMouseDoubleClick()
{
	if (Minimized)
	{
		Minimized = false;
		GenerateFrame(X, Y);

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void TGumpProfile::OnMouseWheel(MOUSE_WHEEL_STATE &state)
{
	if (!Minimized && !g_LeftMouseDown && !g_RightMouseDown)
	{
		DWORD ticks = GetTickCount();

		if (m_LastScrollChangeTime < ticks)
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
void TGumpProfile::ListingList(bool direction, int divizor)
{
	DWORD ticks = GetTickCount();

	if (direction) //Up
	{
		if (m_CurrentLine > 1)
			m_CurrentLine--;
		else
			m_CurrentLine = 0;
	}
	else //Down
	{
		int maxidx = (GetHeight() - (m_Height - 30)) / GUMP_SCROLLING_PIXEL_STEP;

		if (maxidx < 0)
			maxidx = 0;

		if (m_CurrentLine < maxidx)
			m_CurrentLine++;
		else
			m_CurrentLine = maxidx;
	}

	m_LastScrollChangeTime = ticks + (SCROLL_LISTING_DELAY / divizor);
}
//----------------------------------------------------------------------------
void TGumpProfile::OnCharPress(WPARAM &wparam, LPARAM &lparam)
{
	if (wparam == VK_RETURN || wparam == VK_BACK || wparam == VK_ESCAPE || EntryPointer == NULL)
		return; //Ignore no print keys

	wchar_t wstr[2] = {0};
	wstr[0] = wparam;

	wstring str(wstr);
	if (!str.length())
		return;

	EntryPointer->Insert(wparam);

	GenerateFrame(X, Y);
}
//----------------------------------------------------------------------------
void TGumpProfile::OnKeyPress(WPARAM &wparam, LPARAM &lparam)
{
	if (wparam == VK_RETURN)
	{
		EntryPointer->Insert(0x000D);

		GenerateFrame(X, Y); //����������
	}
	else
		EntryPointer->OnKey(this, wparam);
}
//----------------------------------------------------------------------------