/****************************************************************************
**
** GumpSelectColor.cpp
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
//----------------------------------------------------------------------------
#include "stdafx.h"
//----------------------------------------------------------------------------
TGumpSelectColor::TGumpSelectColor(DWORD serial, short x, short y, SELECT_COLOR_GUMP_STATE state)
: TGump(GT_SELECT_COLOR, serial, x, y), m_State(state), m_ColorRef(1),
m_SliderPos(72), m_SelectedIndex(10)
{
}
//----------------------------------------------------------------------------
TGumpSelectColor::~TGumpSelectColor()
{
}
//---------------------------------------------------------------------------
void TGumpSelectColor::PrepareTextures()
{
	UO->ExecuteGump(0x0906);
	UO->ExecuteButton(0x0907);
	UO->ExecuteGumpPart(0x0845, 2);
}
//---------------------------------------------------------------------------
void TGumpSelectColor::GenerateFrame(int posX, int posY)
{
	if (!g_DrawMode)
	{
		FrameRedraw = false;
		FrameCreated = false;

		return;
	}

	DWORD index = (DWORD)this;

	//������ �� ������ � ����?
	bool IsPressed = (g_LeftMouseDown && g_LastGumpLeftMouseDown == index && g_LastSelectedGump == index);

	//����� �� ���� ��������� �������?
	int CanSelectedButton = ((g_LastSelectedGump == index) ? g_LastSelectedObject : 0);

	//����� �� ���� ����� �������?
	int CanPressedButton = 0;
	if (IsPressed && g_LastObjectLeftMouseDown == g_LastSelectedObject)
		CanPressedButton = g_LastObjectLeftMouseDown;
	
	glNewList((GLuint)index, GL_COMPILE);

		const int cellWidthX = 8;
		const int cellWidthY = 8;

		UO->DrawGump(0x0906, 0, posX, posY); //Body
		
		WORD gumpID = 0x0907;
		if (CanPressedButton == ID_GSC_BUTTON_OKAY)
			gumpID = 0x0908;
		else if (CanSelectedButton == ID_GSC_BUTTON_OKAY)
			gumpID = 0x0909;

		UO->DrawGump(gumpID, 0, posX + 208, posY + 138); //Okay button
		
		gumpID = 0x0845 + (int)(CanSelectedButton == ID_GSC_SLIDER); //Scroll button / selected
		UO->DrawGump(gumpID, 0, posX + m_SliderPos, posY + 142);

		glDisable(GL_TEXTURE_2D);
		
		WORD startColor = m_ColorRef + 2;

		posX += 34;
		posY += 34;
		
		const int cell = 5;

		IFOR(y, 0, 10)
		{
			IFOR(x, 0, 20)
			{
				WORD FColor = startColor + (x * 5 + (y * 100));

				DWORD clr = ColorManager->GetPolygoneColor(cell + (y / 2), FColor);

				g_GL.DrawPolygone(clr, (GLfloat)(posX + (x * cellWidthX)), (GLfloat)(posY + (y * cellWidthY)), (GLfloat)cellWidthX, (GLfloat)cellWidthY);

				if (m_SelectedIndex == ID_GSC_COLORS + (x * 30 + y))
					g_GL.DrawPolygone(0x007F7F7F, posX + (x * cellWidthX) + (cellWidthX / 2.0f) - 1.0f, posY + (y * cellWidthY) + (cellWidthY / 2.0f) - 1.0f, 2.0f, 2.0f);
			}
		}
		
		glColor3f(1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);

	glEndList();

	FrameRedraw = true;
	FrameCreated = true;
}
//----------------------------------------------------------------------------
int TGumpSelectColor::Draw(bool &mode)
{
	DWORD index = (DWORD)this;

	int posX = X;
	int posY = Y;
	
	//������ �� ������ � ����?
	bool IsPressed = (g_LeftMouseDown && g_LastGumpLeftMouseDown == index && g_LastSelectedGump == index);

	//����� �� ���� ��������� �������?
	int CanSelectedButton = ((g_LastSelectedGump == index) ? g_LastSelectedObject : 0);

	//����� �� ���� ����� �������?
	int CanPressedButton = 0;
	if (IsPressed && g_LastObjectLeftMouseDown == g_LastSelectedObject)
		CanPressedButton = g_LastObjectLeftMouseDown;
	
	//���� �������� �������� - �������� ��� ������� � �������� � ��������� ����
	if (mode && IsPressed && g_LastObjectLeftMouseDown == ID_GSC_SLIDER)
	{
		int currentX = g_MouseX - posX - 5; //������� ������� ��������

		if (currentX < 39)
			currentX = 39; //����� �� ���������� ������, ������������ �� �������
		else if (currentX > 172)
			currentX = 172; //����� �� ���������� ������, ������������ �� ��������

		m_SliderPos = currentX; //������������� �������� ��������

		int count = m_ColorRef; //���������� ��������� � �����
		if (currentX > 39) //������� �������� ������ ��������
		{
			if (currentX < 172) //������� �������� ������ ���������, ���������
			{
				float ValPer = ((currentX - 39.0f) / 133.0f) * 100.0f;

				if (ValPer == 0.0f)
					count = 0;
				else
					count = (int)((5.0f * ValPer) / 100.0f);
			}
		}
		else
			count = 0; //������� ����� ��������, ���������� ���������� 0

		m_ColorRef = count;
	}
	
	if (g_LeftMouseDown && g_LastGumpLeftMouseDown == index && !g_LastObjectLeftMouseDown)
	{
		posX += g_MouseX - g_DroppedLeftMouseX;
		posY += g_MouseY - g_DroppedLeftMouseY;
	
		if (mode)
			GenerateFrame(posX, posY);
	}
	else if (mode)
	{
		if (IsPressed || CanSelectedButton)
			GenerateFrame(posX, posY);
		else if (FrameRedraw)
		{
			GenerateFrame(posX, posY);
			FrameRedraw = false;
		}
	}

	if (mode)
	{
		if (!FrameCreated)
			GenerateFrame(posX, posY);

		glCallList((GLuint)index);
	}
	else
	{
		int LSG = 0;
		
		if (UO->GumpPixelsInXY(0x0906, posX, posY))
		{
			g_LastSelectedObject = 0;
			g_LastSelectedGump = index;
			
			if (UO->GumpPixelsInXY(0x0907, posX + 208, posY + 138))
				LSG = ID_GSC_BUTTON_OKAY; //Okay button
			else if (UO->GumpPixelsInXY(0x0845, posX + m_SliderPos, posY + 142))
				LSG = ID_GSC_SLIDER; //Scroll button
		
			posX += 34;
			posY += 34;
			
			const int cellWidthX = 8;
			const int cellWidthY = 8;

			bool found = false;
			RECT rc = {0, 0, cellWidthX, cellWidthY};
		
			IFOR(y, 0, 10)
			{
				IFOR(x, 0, 20)
				{
					POINT p = {g_MouseX - (posX + (x * cellWidthX)), g_MouseY - (posY + (y * cellWidthY))};

					if (PtInRect(&rc, p))
					{
						LSG = (ID_GSC_COLORS + (x * 30) + y);
						found = true;

						break;
					}
				}

				if (found)
					break;
			}

			if (LSG != 0)
				g_LastSelectedObject = LSG;
		}

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
void TGumpSelectColor::OnLeftMouseUp()
{
	if (g_LastObjectLeftMouseDown != g_LastSelectedObject)
		return;

	if (g_LastSelectedObject == ID_GSC_BUTTON_OKAY)
	{
		WORD color = 0;

		WORD startColor = m_ColorRef + 2;

		IFOR(y, 0, 10)
		{
			IFOR(x, 0, 20)
			{
				if (m_SelectedIndex == ID_GSC_COLORS + (x * 30 + y))
				{
					color = startColor + (x * 5 + (y * 100));
					break;
				}
			}

			if (color)
				break;
		}

		if (!color)
			return;

		OnSelectColor(color);
	}
	else if (g_LastSelectedObject >= ID_GSC_COLORS)
		m_SelectedIndex = g_LastSelectedObject;
}
//----------------------------------------------------------------------------
void TGumpSelectColor::OnSelectColor(WORD &color)
{
	switch (m_State)
	{
		case SCGS_OPT_POPUP_TEXT:
		{
			g_OptionsConfig.PopupHelpTextColor = color;
			break;
		}
		case SCGS_OPT_TOOLTIP_TEXT:
		{
			g_OptionsConfig.ToolTipsTextColor = color;
			break;
		}
		case SCGS_OPT_CHAT_INPUT_TEXT:
		{
			g_OptionsConfig.ChatColorInputText = color;
			break;
		}
		case SCGS_OPT_CHAT_MENU_OPTION:
		{
			g_OptionsConfig.ChatColorMenuOption = color;
			break;
		}
		case SCGS_OPT_CHAT_PLAYER_IN_MEMBER_LIST:
		{
			g_OptionsConfig.ChatColorPlayerInMemberList = color;
			break;
		}
		case SCGS_OPT_CHAT_TEXT:
		{
			g_OptionsConfig.ChatColorText = color;
			break;
		}
		case SCGS_OPT_CHAT_PLAYER_WITHOUT_PRIV:
		{
			g_OptionsConfig.ChatColorPlayerNameWithout = color;
			break;
		}
		case SCGS_OPT_CHAT_MUTED_TEXT:
		{
			g_OptionsConfig.ChatColorMuted = color;
			break;
		}
		case SCGS_OPT_CHAT_CHAN_MODER_NAME:
		{
			g_OptionsConfig.ChatColorChannelModeratorName = color;
			break;
		}
		case SCGS_OPT_CHAT_CHAN_MODER_TEXT:
		{
			g_OptionsConfig.ChatColorChannelModeratorText = color;
			break;
		}
		case SCGS_OPT_CHAT_MY_NAME:
		{
			g_OptionsConfig.ChatColorMyName = color;
			break;
		}
		case SCGS_OPT_CHAT_MY_TEXT:
		{
			g_OptionsConfig.ChatColorMyText = color;
			break;
		}
		case SCGS_OPT_CHAT_SYSTEM_MESSAGE:
		{
			g_OptionsConfig.ChatColorSystemMessage = color;
			break;
		}
		case SCGS_OPT_CHAT_BG_OUTPUT:
		{
			g_OptionsConfig.ChatColorBGOutputText = color;
			break;
		}
		case SCGS_OPT_CHAT_BG_INPUT:
		{
			g_OptionsConfig.ChatColorBGInputText = color;
			break;
		}
		case SCGS_OPT_CHAT_BG_USER_LIST:
		{
			g_OptionsConfig.ChatColorBGUserList = color;
			break;
		}
		case SCGS_OPT_CHAT_BG_CONF_LIST:
		{
			g_OptionsConfig.ChatColorBGCommandList = color;
			break;
		}
		case SCGS_OPT_CHAT_BG_COMMAND_LIST:
		{
			g_OptionsConfig.ChatColorBGCommandList = color;
			break;
		}
		case SCGS_OPT_DISPLAY_SPEECH:
		{
			g_OptionsConfig.SpeechColor = color;
			break;
		}
		case SCGS_OPT_DISPLAY_EMOTE:
		{
			g_OptionsConfig.EmoteColor = color;
			break;
		}
		case SCGS_OPT_DISPLAY_PARTY_MESSAGE:
		{
			g_OptionsConfig.PartyMessageColor = color;
			break;
		}
		case SCGS_OPT_REPSYS_INNOCENT:
		{
			g_OptionsConfig.InnocentColor = color;
			break;
		}
		case SCGS_OPT_REPSYS_FRIENDLY:
		{
			g_OptionsConfig.FriendlyColor = color;
			break;
		}
		case SCGS_OPT_REPSYS_SOMEONE:
		{
			g_OptionsConfig.SomeoneColor = color;
			break;
		}
		case SCGS_OPT_REPSYS_CRIMINAL:
		{
			g_OptionsConfig.CriminalColor = color;
			break;
		}
		case SCGS_OPT_REPSYS_ENEMY:
		{
			g_OptionsConfig.EnemyColor = color;
			break;
		}
		case SCGS_OPT_REPSYS_MURDERER:
		{
			g_OptionsConfig.MurdererColor = color;
			break;
		}
		default:
			break;
	}

	GumpManager->CloseGump(g_PlayerSerial, 0, GT_SELECT_COLOR);

	TGump *options = GumpManager->GetGump(g_PlayerSerial, 0, GT_OPTIONS);
	if (options != NULL)
		options->UpdateFrame();
}
//----------------------------------------------------------------------------