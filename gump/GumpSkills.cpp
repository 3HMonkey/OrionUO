/****************************************************************************
**
** GumpSkills.cpp
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
TGumpSkills::TGumpSkills(DWORD serial, short x, short y, bool minimized)
: TGump(GT_SKILLS, serial, x, y), m_Height(200), m_LastResizeY(0),
m_ShowReal(false), m_ShowCap(false), m_LastChangedLineTime(0), m_CurrentLine(0)
{
	//�������� ��������� ��� ����� ������
	TextEntry = new TEntryText();

	//��������� ����������� ��������
	FontManager->GenerateA(1, m_Text, "Show:   Real    Cap", 0x0386);

	if (minimized)
	{
		m_Minimized = minimized;
		m_MinimizedX = x;
		m_MinimizedY = y;
	}
}
//----------------------------------------------------------------------------
TGumpSkills::~TGumpSkills()
{
	//��� �������� ����� �������� ��������� �� ���� ������
	if (TextEntry == EntryPointer)
	{
		//���� ��������� � ����� - ������� ���
		if (ConfigManager.GetConsoleNeedEnter())
			EntryPointer = NULL;
		else
			EntryPointer = GameConsole;
	}

	//������� ��������� �� ���� ������
	if (TextEntry != NULL)
	{
		delete TextEntry;
		TextEntry = NULL;
	}

	//�������� ��������
	m_Text.Clear();
}
//----------------------------------------------------------------------------
void TGumpSkills::Init()
{
	//������� ��� ��������� ������
	QFOR(group, SkillGroupManager.m_Groups, TSkillGroupObject*)
		group->Maximized = false;
}
//----------------------------------------------------------------------------
void TGumpSkills::SetHeight(short val)
{
	//��������� � ������������� �������� ������ �����
	if (val < 120)
		val = 120;

	int buf = (GetSystemMetrics(SM_CYSCREEN) - 50);
	if (val >= buf)
		val = buf;

	m_Height = val;
}
//----------------------------------------------------------------------------
void TGumpSkills::ChangeHeight()
{
	//������� ��������� ������ ����� � ��������� ��������������
	if (m_LastResizeY)
		SetHeight(m_Height + (g_MouseY - m_LastResizeY));

	m_LastResizeY = 0;
	g_ResizedGump = NULL;
}
//---------------------------------------------------------------------------
void TGumpSkills::PrepareTextures()
{
	UO->ExecuteGump(0x1F40); //Top scroll
	UO->ExecuteGump(0x1F43); //Bottom scroll
	UO->ExecuteGumpPart(0x0938, 2); //Real/Cap buttons
	UO->ExecuteGumpPart(0x1F41, 2); //Body
	UO->ExecuteGump(0x0984);
	UO->ExecuteGump(0x0986);
	UO->ExecuteGumpPart(0x0824, 12);
	UO->ExecuteGumpPart(0x0834, 7);
}
//---------------------------------------------------------------------------
void TGumpSkills::GenerateFrame()
{
	if (!g_DrawMode)
	{
		m_FrameRedraw = false;
		m_FrameCreated = false;

		return;
	}

	CalculateGumpState();

	int height = m_Height; //������ ��� �������� ������� � ������������� ��������� �������������

	if (m_LastResizeY) //���� ������������ ��������� ������ �����
	{
		//��������������� ��������� �������� ������
		height += (g_MouseY - m_LastResizeY);
		if (height < 120)
			height = 120;

		int bh = (GetSystemMetrics(SM_CYSCREEN) - 50);
		if (height >= bh)
			height = bh;
	}

	//����������� ������� ��������� (posY �� ����� ���������)
	int scrollerY = 0;

	//���� ���� �� ������� (��������� �������� ���� ��� ��� ������) �� ��������� ������� ���������
	if (!m_Minimized)
	{
		//������������ ���������� ������� �����
		int visibleLines = SkillGroupManager.GetVisibleLinesCount();

		//����������� ��������� �������� ������� ���������
		int maxScrollerY = height - 104;

		//���� �������� �������� ������
		if (g_GumpPressedScroller && g_LastObjectLeftMouseDown == ID_GS_SCROLLER)
		{
			//��������� ������� ������� ���������
			int currentY = (g_MouseY - 10) - (int)g_GumpTranslateY - 72;

			scrollerY = CalculateScrollerAndTextPosition(m_CurrentLine, visibleLines, maxScrollerY, currentY);
		}
		else if (m_CurrentLine) //��� ��, ��������� ������� ������� ����� �������
			scrollerY = CalculateScrollerY(m_CurrentLine, visibleLines, maxScrollerY);
	}

	//�������� ������� �����
	glNewList((GLuint)this, GL_COMPILE);

		if (m_Minimized) //���� ��� ��������� ����
		{
			//����-���� �������
			UO->DrawGump(0x0839, 0, 0, 0);

			//�������� �������� ����� � ������ �� ���������
			glEndList();

			m_FrameRedraw = true;
			m_FrameCreated = true;

			return;
		}

		//���������� ��������� �����

		UO->DrawGump(0x082D, 0, 167, 0); //Minimize
		
		UO->DrawGump(0x1F40, 0, 0, 23); //Top scroll
		UO->DrawGump(0x0834, 0, 82, 34); //Skills text gump
		UO->DrawGump(0x0938 + (int)m_ShowReal, 0, 226, 34); //Real
		UO->DrawGump(0x0938 + (int)m_ShowCap, 0, 280, 34); //Cap
		//UO->DrawFont(1, "Show:   Real    Cap", 0x0386, posX + 180, posY + 33);
		m_Text.Draw(180, 33);

		//Skills body
		int curposY = 59;

		//���� ���������� ������ ����-������ � ��������� ���� �����
		while (true)
		{
			int deltaHeight = height - (curposY - 36);

			if (deltaHeight  < 70)
			{
				if (deltaHeight > 0)
					UO->DrawGump(0x1F41, 0, 21, curposY, 0, deltaHeight);

				break;
			}
			else
				UO->DrawGump(0x1F41, 0, 21, curposY);

			curposY += 70;

			deltaHeight = height - (curposY - 36);

			if (deltaHeight < 70)
			{
				if (deltaHeight > 0)
					UO->DrawGump(0x1F42, 0, 21, curposY, 0, deltaHeight);

				break;
			}
			else
				UO->DrawGump(0x1F42, 0, 21, curposY);

			curposY += 70;
		}

		//Up
		//UO->DrawGump(0x0828, 0, posX + 296, posY + 72); //Scroller
		//Down
		//UO->DrawGump(0x0828, 0, posX + 296, posY + height - 32); //Scroller

		UO->DrawGump(0x0828, 0, 296, 72 + scrollerY); //Scroller

		//������ ������ ��� ������ �����������
		int startIndex = m_CurrentLine;
		int currentIndex = 0; //������ ��������
		
		int drawX = 30;
		int drawY = 72;

		//����������� ���� ���������� ������/������
		DWORD selectedPolygoneColor = 0x007F7F7F;

		//��������� ������� �������
		g_GL.Scissor((int)g_GumpTranslateX + drawX, (int)g_GumpTranslateY + drawY, 264, height - 74);

		//���������� ����� ��������
		const int drawStep = 17;

		//��������� ���������� ������ �����������
		drawX -= 2;
		drawY += 3;

		//������������ ���������� ����������� �� ��� Y
		int boundsY = height;
		
		int si = -1; //������ ���������� ������

		TSkillGroupObject *selectedGroup = NULL; //��������� �� ������, � ������� ������ �����
		bool removeIndexOnExit = false; //���� �������� ������ ��� ������ �� ���������

		//���� �������� �����
		if (g_LastObjectLeftMouseDown >= ID_GS_SKILL && g_LastObjectLeftMouseDown < 14000)
		{
			//�������� ������ ������
			si = g_LastObjectLeftMouseDown - ID_GS_SKILL;

			//������� ��������� ������
			selectedGroup = GetGroupUnderCursor(m_CurrentLine);

			//���� ������ ������� � � ��� ��� �������� ���������� ������
			//�� ������� ��� ���� (������������) � ��������� ���� �������� ��� ������
			if (selectedGroup != NULL && !selectedGroup->Contains(si))
			{
				selectedGroup->AddSorted(si);
				removeIndexOnExit = true;
			}
		}

		//���� ����� ������������
		if (g_Player != NULL)
		{
			PSKILLS_DATA Skills = g_Skills; //�������� ��������� �� ��������� ������

			TSkillGroupObject *group = SkillGroupManager.m_Groups; //��������� �� ������

			while (group != NULL)
			{
				if (drawY + 10 >= boundsY)
					break; //���� ����� �� ��������� ������� ���������

				//�������� �� ���������� �������?
				bool canDraw = (currentIndex >= startIndex);
				currentIndex++;

				if (canDraw) //��������� ��������
				{
					//�������� ��������� �� �������� �������� ������
					TTextTexture &th = group->m_Texture;

					//�������� ����
					if (!th.Empty())
					{
						//����� ������ ����� ������
						BYTE selname = group->GetSelected();

						if (selname == 2) //��������� ����� ������
						{
							//��������� ������� ���
							g_GL.DrawPolygone(drawX + 16, drawY, 200, 14);

							//������� ��������
							TextEntry->DrawA(6, 0, drawX + 16, drawY - 5);
						}
						else //������
						{
							//���������� �� ������������ ��� (��� ���������������� ������)
							bool hightlightGroup = false;
							if (group == selectedGroup && !group->Maximized && si != -1)
								hightlightGroup = true;

							//���� ������� ������ ��� ������������� ����� �� ������� ������ - ��������� ��
							if (selname == 1)
								g_GL.DrawPolygone(drawX + 16, drawY, th.Width - 10, 14);
							else if (hightlightGroup)
								g_GL.DrawPolygone(drawX + 16, drawY, 200, 14);

							//��������� ��� ������ (�� ������� ������������� ��������)
							th.Draw(drawX + 16, drawY - 5);

							//� "����" �� ����� ������
							int fw = 11 + th.Width;
							int lw = 215 - fw;
							if (lw > 0)
								UO->DrawGump(0x0835, 0, drawX + fw, drawY + 5, lw, 0);
						}
					}
				}

				if (group->GetMaximized()) //���� ������ ���������� - ���������� � ����������
				{
					if (canDraw) //����� ��������
					{
						//���� � ������ ���-�� ���� - ��������� �������
						if (group->GetCount())
							UO->DrawGump(0x0826, 0, drawX, drawY);

						//������� ��������� �� ����������� ��� + 2 (������ ��� ������)
						drawY += (drawStep + 2);
					}

					//���� ��� ������, ���������� ���������� ��������������� �����
					//� ����� ���� ������������ � ������ ������ �� ������ ������
					//�� �� ���������� ��� �����
					bool dontDrawSI = false;
					if (group != selectedGroup && removeIndexOnExit)
						dontDrawSI = true;

					int cnt = group->GetCount();

					IFOR(i, 0, cnt) //���� �� ��� ��������� ������
					{
						if (drawY + 10 >= boundsY)
							break; //����� �� ������� �������

						//�������� ��� �����������?
						canDraw = (currentIndex >= startIndex);
						currentIndex++;

						if (canDraw) //����� ��������
						{
							BYTE idx = group->GetItem(i); //�������� ������ ������ �� ����������� ������
							if (idx < g_SkillsCount) //�� �������
							{
								//���� ��� ��������������� ����� � ��� �� ����� ���������� - ������ �� ������
								if (idx == si && dontDrawSI)
								{
								}
								else //� ���� ������ - ������
								{
									WORD gumpID = 0x0837; //Button
									if (Skills[idx].m_Button) //���� � ������ ���� ������ - ��������� �
									{
										if (g_GumpSelectElement == ID_GS_SKILL_BUTTON + idx)
											gumpID = 0x0838; //Selected button

										UO->DrawGump(gumpID, 0, drawX + 8, drawY); //Button
									}

									TTextTexture &th = Skills[idx].m_Texture; //Name
									if (!th.Empty())
									{
										if (si == idx)
											g_GL.DrawPolygone(drawX + 20, drawY - 1, 250, 14);

										th.Draw(drawX + 22, drawY - 1);
									}

									BYTE status = g_Player->GetSkillStatus(idx); //������ (����/�����/�����)

									gumpID = 0x0984; //Up
									if (status == 1)
										gumpID = 0x0986; //Down
									else if (status == 2)
										gumpID = 0x082C; //Lock
									UO->DrawGump(gumpID, 0, drawX + 251, drawY - 1);

									//�������� ������ (�������� ��������� ���� �����������)
									float val = g_Player->GetSkillBaseValue(idx);
									if (m_ShowReal)
										val = g_Player->GetSkillValue(idx);
									else if (m_ShowCap)
										val = g_Player->GetSkillCap(idx);

									char sbf[20] = {0};
									sprintf(sbf, "%.1f", val);

									//����������� ��� � ������� ����
									int fw = FontManager->GetWidthA(9, sbf, strlen(sbf));
									FontManager->DrawA(9, sbf, 0x0288, drawX + 250 - fw, drawY - 1); //Value

									drawY += drawStep; //��������� �� ��������� ������� �� ��� Y
								}
							}
						}
					}
				}
				else if (canDraw) //������ ��������
				{
					//���� � ������ ���-�� ���� - �������� �������
					if (group->GetCount())
						UO->DrawGump(0x0827, 0, drawX, drawY);

					drawY += drawStep; //��������� �� ��������� ������� ���������
				}

				group = group->m_Next; //��������� �������
			}
		}

		//���� ���� ������������� ������� ������� - �������
		if (removeIndexOnExit)
			selectedGroup->Remove(si);

		//��������������� ������ ������� �������
		glDisable(GL_SCISSOR_TEST);

		UO->DrawGump(0x082B, 0, 30, 60); //Top line
		UO->DrawGump(0x0824, 0, 294, 56); //^ button
		
		UO->DrawGump(0x082B, 0, 31, height - 1); //Bottom line
		UO->DrawGump(0x0836, 0, 30, height + 13); //Skills comment gump
		UO->DrawGump(0x0825, 0, 294, height + 3); //v button

		UO->DrawGump(0x1F43, 0, 21, height + 34); //Bottom scroll
		UO->DrawGump(0x083A, 0, 60, height + 44); //New Group gump

		//����� ����� �������
		char totalSkills[20] = {0};
		sprintf(totalSkills, "%.1f", g_SkillsTotal);
		FontManager->DrawA(3, totalSkills, 0x0065, 235, height + 41);
		
		WORD gumpID = 0x082E;
		if (g_GumpSelectElement == ID_GS_BUTTON_RESIZE)
			gumpID = 0x082F;
		UO->DrawGump(gumpID, 0, 167, height + 66); //Resize

	//��������� ������ ������� �����
	glEndList();

	m_FrameRedraw = true;
	m_FrameCreated = true;
}
//----------------------------------------------------------------------------
int TGumpSkills::Draw(bool &mode)
{
	//������ �����
	DWORD index = (DWORD)this;

	//���� ���� ������� - ����� ��������������� ����������
	if (m_Minimized)
		m_LastResizeY = 0; //�������� �������� ��������� ������ � ����

	CalculateGumpState();

	//��� ����������� � �������� ������� � ������ �����
	int height = m_Height;

	//� ����� ����������� ������ ��������� ������
	if (m_LastResizeY)
	{
		//������������ ������� ������
		height += (g_MouseY - m_LastResizeY);
		if (height < 120)
			height = 120;

		int bh = (GetSystemMetrics(SM_CYSCREEN) - 50);
		if (height >= bh)
			height = bh;

		//���� ��� ����� ��������� - ������ ����� �����
		if (mode)
			m_FrameCreated = false;
	}

	//��� ���������� �������� ����� �����������
	DWORD ticks = GetTickCount();

	//��������, ����� ���������� �������� ��������� ������������� ��������
	if (g_GumpPressedScroller && m_LastChangedLineTime < ticks)
	{
		if (g_LastObjectLeftMouseDown == ID_GS_BUTTON_UP) //��������� ����� (������-��������)
		{
			if (m_CurrentLine > 0)
				m_CurrentLine--;
			else
				m_CurrentLine = 0;

			m_LastChangedLineTime = ticks + SCROLL_LISTING_DELAY;
		}
		else if (g_LastObjectLeftMouseDown == ID_GS_BUTTON_DOWN) //��������� ���� (������-��������)
		{
			int visibleLines = SkillGroupManager.GetVisibleLinesCount();

			if (m_CurrentLine < visibleLines)
				m_CurrentLine++;
			else
				m_CurrentLine = visibleLines;

			m_LastChangedLineTime = ticks + SCROLL_LISTING_DELAY;
		}
		else if (g_LastObjectLeftMouseDown >= ID_GS_SKILL && g_LastObjectLeftMouseDown < 14000) //Skill name pressed
		{
			//��������� ��������������� ������
			if (g_MouseY < ((int)g_GumpTranslateY + 72)) //��������� �����
			{
				if (m_CurrentLine > 0)
					m_CurrentLine--;
				else
					m_CurrentLine = 0;

				m_LastChangedLineTime = ticks + (SCROLL_LISTING_DELAY / 3);
			}
			else if (g_MouseY > ((int)g_GumpTranslateY + height)) //��������� ����
			{
				int visibleLines = SkillGroupManager.GetVisibleLinesCount();

				if (m_CurrentLine < visibleLines)
					m_CurrentLine++;
				else
					m_CurrentLine = visibleLines;
				
				m_LastChangedLineTime = ticks + (SCROLL_LISTING_DELAY / 3);
			}
		}
	}

	//��������� ������� ������ ����
	int scrollerY = 0;

	if (!m_Minimized) //������ ��� ������������� �����
	{
		//���������� ������� �����
		int visibleLines = SkillGroupManager.GetVisibleLinesCount();

		//������������ ������� ���������
		int maxScrollerY = height - 104;

		//�������� ��������
		if (g_GumpPressedScroller && g_LastObjectLeftMouseDown == ID_GS_SCROLLER) //Scroller pressed
		{
			//������� ������� ���������
			int currentY = (g_MouseY - 10) - (int)g_GumpTranslateY - 72; //Scroller position

			scrollerY = CalculateScrollerAndTextPosition(m_CurrentLine, visibleLines, maxScrollerY, currentY);

			if (mode)
				m_FrameCreated = false;
		}
		else if (m_CurrentLine) //��� ��, �������� ������, �� �� ���������
		{
			scrollerY = CalculateScrollerY(m_CurrentLine, visibleLines, maxScrollerY);

			//���� ����� ��������� - ���������� �����
			if (mode)
				m_FrameCreated = false;
		}
	}

	if (mode) //���������
	{
		//���� ����� �� ��� ������ - �������
		if (!m_FrameCreated || g_GumpSelectElement || g_GumpMovingOffsetX || g_GumpMovingOffsetY) // || g_GumpPressed
			GenerateFrame();
		else if (m_FrameRedraw)
		{
			GenerateFrame();
			m_FrameRedraw = false;
		}

		glTranslatef(g_GumpTranslateX, g_GumpTranslateY, 0.0f);

		//��������� �����
		glCallList((GLuint)index);

		DrawLocker();

		glTranslatef(-g_GumpTranslateX, -g_GumpTranslateY, 0.0f);
	}
	else //����� ��������
	{
		int oldMouseX = g_MouseX;
		int oldMouseY = g_MouseY;
		g_MouseX -= (int)g_GumpTranslateX;
		g_MouseY -= (int)g_GumpTranslateY;

		if (m_Minimized) //���� ���� �������
		{
			if (UO->GumpPixelsInXY(0x0839, 0, 0))
			{
				g_LastSelectedObject = 0;
				g_LastSelectedGump = index;
			}

			g_MouseX = oldMouseX;
			g_MouseY = oldMouseY;

			return 0;
		}

		//����������� ����
		//���� �� �� ��������, ��� � � ������� �������� ������, ������ ��� ������ ���������, �������� ����� ���������� ���

		int LSG = 0;

		if (UO->GumpPixelsInXY(0x082D, 167, 0)) //Minimize
		{
			LSG = ID_GS_BUTTON_MINIMIZE;
			g_LastSelectedGump = index;
		}
		else if (UO->GumpPixelsInXY(0x1F40, 0, 23)) //Top scroll
		{
			g_LastSelectedObject = 0;
			g_LastSelectedGump = index;
		}
		
		if (g_LastSelectedGump != index)
		{
			//Skills body
			int curposY = 59;

			while (true)
			{
				int deltaHeight = height - (curposY - 36);

				if (deltaHeight  < 70)
				{
					if (deltaHeight > 0)
					{
						if (UO->GumpPixelsInXY(0x1F41, 21, curposY, 0, deltaHeight))
						{
							g_LastSelectedObject = 0;
							g_LastSelectedGump = index;
						}
					}

					break;
				}
				else if (UO->GumpPixelsInXY(0x1F41, 21, curposY))
				{
					g_LastSelectedObject = 0;
					g_LastSelectedGump = index;

					break;
				}

				curposY += 70;

				deltaHeight = height - (curposY - 36);

				if (deltaHeight < 70)
				{
					if (deltaHeight > 0)
					{
						if (UO->GumpPixelsInXY(0x1F42, 21, curposY, 0, deltaHeight))
						{
							g_LastSelectedObject = 0;
							g_LastSelectedGump = index;
						}
					}

					break;
				}
				else if (UO->GumpPixelsInXY(0x1F42, 21, curposY))
				{
					g_LastSelectedObject = 0;
					g_LastSelectedGump = index;

					break;
				}

				curposY += 70;
			}
		}
		
		if (UO->GumpPixelsInXY(0x1F43, 21, height + 34)) //Bottom scroll
		{
			g_LastSelectedObject = 0;
			g_LastSelectedGump = index;
		}
		
		if (UO->GumpPixelsInXY(0x082E, 167, height + 66)) //Resize
		{
			LSG = ID_GS_BUTTON_RESIZE;
			g_LastSelectedGump = index;
		}
		else if (UO->GumpPixelsInXY(0x0938, 226, 34)) //Real
			LSG = ID_GS_SHOW_REAL;
		else if (UO->GumpPixelsInXY(0x0938, 280, 34)) //Cap
			LSG = ID_GS_SHOW_CAP;
		else if (UO->GumpPixelsInXY(0x0824, 294, 56)) //^ button
			LSG = ID_GS_BUTTON_UP;
		else if (UO->GumpPixelsInXY(0x0825, 294, height + 3)) //v button
			LSG = ID_GS_BUTTON_DOWN;
		else if (UO->GumpPixelsInXY(0x0828, 296, 72 + scrollerY)) //Scroller
			LSG = ID_GS_SCROLLER;
		else if (UO->PolygonePixelsInXY(60, height + 44, 80, 14))
			LSG = ID_GS_BUTTON_NEW_GROUP;
		
		int startIndex = m_CurrentLine;
		int currentIndex = 0;
		
		int drawX = 28;
		int drawY = 75;

		const int drawStep = 17;
		
		int boundsY = height;

		int groupIndex = 0;
		
		if (g_Player != NULL)
		{
			PSKILLS_DATA Skills = g_Skills;

			TSkillGroupObject *group = SkillGroupManager.m_Groups;
			while (group != NULL)
			{
				if (drawY + 10 >= boundsY)
					break;

				bool canDraw = (currentIndex >= startIndex);
				currentIndex++;

				if (canDraw)
				{
					TTextTexture &th = group->m_Texture;

					if (th.Width && UO->PolygonePixelsInXY(drawX + 16, drawY, th.Width - 10, 14))
					{
						LSG = ID_GS_GROUP + groupIndex;
						break;
					}
				}

				if (group->GetMaximized())
				{
					if (canDraw)
					{
						if (group->GetCount() && UO->PolygonePixelsInXY(drawX, drawY, 14, 14))
						{
							LSG = ID_GS_GROUP_MINIMIZE + groupIndex;

							break;
						}

						drawY += (drawStep + 2);
					}

					bool completedSearch = false;

					int cnt = group->GetCount();
					IFOR(i, 0, cnt)
					{
						if (completedSearch)
							break;

						if (drawY + 10 >= boundsY)
							break;

						canDraw = (currentIndex >= startIndex);
						currentIndex++;

						if (canDraw)
						{
							BYTE idx = group->GetItem(i);
							if (idx < g_SkillsCount)
							{
								if (Skills[idx].m_Button && UO->GumpPixelsInXY(0x0837, drawX + 8, drawY))
								{
									LSG = ID_GS_SKILL_BUTTON + idx; //Button
									completedSearch = true;

									break;
								}

								TTextTexture &th = Skills[idx].m_Texture;
								int width = 150;

								if (th.Width > 150)
									width = th.Width;

								if (UO->PolygonePixelsInXY(drawX + 22, drawY - 1, width, 14))
								{
									LSG = ID_GS_SKILL + idx; //Name
									completedSearch = true;

									break;
								}

								BYTE status = g_Player->GetSkillStatus(idx);

								WORD gumpID = 0x0984; //Up
								if (status == 1)
									gumpID = 0x0986; //Down
								else if (status == 2)
									gumpID = 0x082C; //Lock

								if (UO->GumpPixelsInXY(gumpID, drawX + 251, drawY - 1))
								{
									LSG = ID_GS_SKILL_STATE + idx;
									completedSearch = true;

									break;
								}
								
								drawY += drawStep;
							}
						}
					}

					if (completedSearch)
						break;
				}
				else if (canDraw)
				{
					if (group->GetCount() && UO->PolygonePixelsInXY(drawX, drawY, 14, 14))
					{
						LSG = ID_GS_GROUP_MINIMIZE + groupIndex;

						break;
					}

					drawY += drawStep;
				}

				groupIndex++;
				group = group->m_Next;
			}
		}

		if (g_ShowGumpLocker && UO->PolygonePixelsInXY(0, 0, 10, 14))
			g_LastSelectedObject = ID_GS_LOCK_MOVING;

		g_MouseX = oldMouseX;
		g_MouseY = oldMouseY;

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
TSkillGroupObject *TGumpSkills::GetGroupUnderCursor(int startIndex)
{
	//�������� ������ ��� ��������

	//���� ����� �� ������� ����� �� ��� X
	if (g_MouseX < (m_X + 30) || g_MouseX > (m_X + 250))
		return NULL; //Exit from bounds on X

	//���� ��������� � �������� ����� �� ��� Y
	if (g_MouseY > (m_Y + 72) && g_MouseY < (m_Y + m_Height)) //Bounds of Y
	{
		int currentIndex = 0; //��������� �� ������� ������

		//������ ���������
		int drawY = m_Y + 75;

		//��� ��������� (� ��������)
		const int drawStep = 17;

		//������������ ���������� Y ��� �����������
		int boundsY = m_Y + m_Height;

		//��������� �� ������
		TSkillGroupObject *group = SkillGroupManager.m_Groups;

		//���������� �� ���� �������
		while (group != NULL)
		{
			//����� �� �������, ���������� �����
			if (drawY >= boundsY)
				return NULL;

			//����� �� ����������?
			bool canDraw = (currentIndex >= startIndex);
			currentIndex++;

			//���� ������ ����������
			if (group->Maximized)
			{
				if (canDraw) //���� �������� ��� �����������
				{
					drawY += (drawStep + 2); //������� ���������� ���������

					if (g_MouseY < drawY)
						return group; //���� ����� ��� ���� ������ - ���������� ������
				}

				int cnt = group->GetCount();

				//��������� �� ��������� ������
				IFOR(i, 0, cnt)
				{
					if (drawY >= boundsY)
						return NULL; //����� �� �������, ����

					//������� ������
					if (currentIndex >= startIndex)
					{
						drawY += drawStep; //���������

						//���� ������ ��� ������ - ���������� ������
						if (g_MouseY < drawY)
							return group;
					}

					//����������� ������� ��������
					currentIndex++;
				}
			}
			else if (canDraw) //��� ���� ����� ����������
			{
				drawY += drawStep; //�������� ������

				//������ �������, ���������� �
				if (g_MouseY < drawY)
					return group;
			}

			group = group->m_Next; //��������� ������
		}
	}

	//������ �� �������
	return NULL;
}
//----------------------------------------------------------------------------
void TGumpSkills::OnLeftMouseDown()
{
	if (g_LastSelectedGump == (DWORD)this && (g_LastSelectedObject >= ID_GS_SKILL && g_LastSelectedObject < ID_GS_SKILL_STATE))
	{
		//��� ������� ������ ����� ���� � ����� �� ������ ����� ����� ��������� � �����
		//����� �� �������������� � �������� ������������� ���
		TSkillGroupObject *group = SkillGroupManager.m_Groups;
		while (group != NULL)
		{
			if (group->GetSelected() == 2)
			{
				if (TextEntry->Length() > 0)
					group->SetName(TextEntry->c_str());
			}

			if (!group->GetName().length())
				group->SetName("NoNameGroup");

			group->SetSelected(0);

			group = group->m_Next;
		}
	}
}
//----------------------------------------------------------------------------
void TGumpSkills::OnLeftMouseUp()
{
	if (m_Minimized)
		return; //�� ������������ ��� ��������� �����
	else if (g_LastObjectLeftMouseDown != g_LastSelectedObject)
	{
		//���� ����� ��������������� - ����� ��������� ��������
		if (g_LastObjectLeftMouseDown < ID_GS_SKILL || g_LastObjectLeftMouseDown >= ID_GS_SKILL_STATE)
			return;
	}

	//������� ���������� �����
	DWORD ticks = GetTickCount();

	if (g_LastObjectLeftMouseDown == ID_GS_BUTTON_MINIMIZE) //����������� ����
	{
		m_Minimized = true;
		m_FrameCreated = false;
	}
	else if (g_LastObjectLeftMouseDown == ID_GS_LOCK_MOVING)
	{
		LockMoving = !LockMoving;
		g_CancelDoubleClick = true;
	}
	else if (g_LastObjectLeftMouseDown == ID_GS_BUTTON_RESIZE) //���������
	{
		if (!m_LastResizeY)
		{
			m_LastResizeY = g_DroppedLeftMouseY;
			g_ResizedGump = this;
		}
		else
		{
			SetHeight(m_Height + (g_MouseY - m_LastResizeY));

			m_LastResizeY = 0;
			g_ResizedGump = NULL;
		}
	}
	else if (g_LastObjectLeftMouseDown == ID_GS_SHOW_REAL) //�������� �������� ��������
	{
		m_ShowReal = !m_ShowReal;
		m_ShowCap = false;
	}
	else if (g_LastObjectLeftMouseDown == ID_GS_SHOW_CAP) //�������� ��������� ������ ��������
	{
		m_ShowCap = !m_ShowCap;
		m_ShowReal = false;
	}
	else if (g_LastObjectLeftMouseDown == ID_GS_BUTTON_NEW_GROUP) //�������� ����� ������
	{
		TSkillGroupObject *group = new TSkillGroupObject();
		group->SetName("New Group");
		SkillGroupManager.Add(group);
	}
	else if (g_LastObjectLeftMouseDown == ID_GS_BUTTON_UP && m_LastChangedLineTime < ticks) //��������� �����
	{
		if (m_CurrentLine > 0)
			m_CurrentLine--;
		else
			m_CurrentLine = 0;

		m_LastChangedLineTime = ticks + SCROLL_LISTING_DELAY;
		m_FrameCreated = false;
	}
	else if (g_LastObjectLeftMouseDown == ID_GS_BUTTON_DOWN && m_LastChangedLineTime < ticks) //��������� ����
	{
		int visibleLines = SkillGroupManager.GetVisibleLinesCount();

		if (m_CurrentLine < visibleLines)
			m_CurrentLine++;
		else
			m_CurrentLine = visibleLines;

		m_LastChangedLineTime = ticks + SCROLL_LISTING_DELAY;
		m_FrameCreated = false;
	}
	else if (g_LastObjectLeftMouseDown >= ID_GS_GROUP_MINIMIZE) //�������� �� ��������
	{
		if (g_LastObjectLeftMouseDown >= ID_GS_SKILL_STATE) //��������� �������
		{
			int idx = g_LastObjectLeftMouseDown - ID_GS_SKILL_STATE;
			if (idx < 0 || idx >= g_SkillsCount)
				return;

			if (g_Player == NULL)
				return;

			BYTE status = g_Player->GetSkillStatus(idx);
			if (status < 2)
				status++;
			else
				status = 0;

			UO->SkillStatusChange(idx, status);
			g_Player->SetSkillStatus(idx, status);
		}
		else if (g_LastObjectLeftMouseDown >= ID_GS_SKILL) //����� �������� ������
		{
			int idx = g_LastObjectLeftMouseDown - ID_GS_SKILL;
			if (idx < 0 || idx >= g_SkillsCount)
				return;

			TSkillGroupObject *group = GetGroupUnderCursor(m_CurrentLine);
				
			if (group != NULL)
			{
				TSkillGroupObject *groups = SkillGroupManager.m_Groups;
				while (groups != NULL)
				{
					groups->Remove(idx);
					groups = groups->m_Next;
				}

				group->AddSorted(idx);

				return;
			}
		}
		else if (g_LastObjectLeftMouseDown >= ID_GS_SKILL_BUTTON) //����� ������ ��� ������������� ������
		{
			int idx = g_LastObjectLeftMouseDown - ID_GS_SKILL_BUTTON;
			if (idx < 0 || idx >= g_SkillsCount)
				return;

			UO->UseSkill(idx);
		}
		else if (g_LastObjectLeftMouseDown >= ID_GS_GROUP) //����� �������� ������
		{
			int idx = g_LastObjectLeftMouseDown - ID_GS_GROUP;
			int cidx = 0;

			TSkillGroupObject *group = SkillGroupManager.m_Groups;
			while (group != NULL)
			{
				if (idx == cidx)
				{
					BYTE sel = group->GetSelected();
					if (sel < 2)
						sel++;

					TSkillGroupObject *item = SkillGroupManager.m_Groups;
					while (item != NULL)
					{
						if (item->GetSelected() == 2)
						{
							if (TextEntry->Length() > 0)
								item->SetName(TextEntry->c_str());
						}

						item->SetSelected(0);
						if (!item->GetName().length())
							item->SetName("NoNameGroup");

						item = item->m_Next;
					}

					if (sel == 2)
					{
						EntryPointer = TextEntry;
						EntryPointer->SetText(group->GetName());
					}

					group->SetSelected(sel);

					break;
				}

				cidx++;
				group = group->m_Next;
			}
		}
		else if (g_LastObjectLeftMouseDown >= ID_GS_GROUP_MINIMIZE) //������/�������� ������
		{
			int idx = g_LastObjectLeftMouseDown - ID_GS_GROUP_MINIMIZE;
			int cidx = 0;

			TSkillGroupObject *group = SkillGroupManager.m_Groups;
			while (group != NULL)
			{
				if (idx == cidx)
				{
					group->SetMaximized(!group->GetMaximized());
					break;
				}

				cidx++;
				group = group->m_Next;
			}
		}
	}
}
//----------------------------------------------------------------------------
bool TGumpSkills::OnLeftMouseDoubleClick()
{
	if (m_Minimized) //��� ��������� �� ����-����� - ���������� ���
	{
		m_Minimized = false;
		m_FrameCreated = false;

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void TGumpSkills::OnMouseWheel(MOUSE_WHEEL_STATE &state)
{
	if (!m_Minimized && !g_LeftMouseDown && !g_RightMouseDown) //�������� ��� ����������
	{
		DWORD ticks = GetTickCount();

		if (state == MWS_UP && m_LastChangedLineTime < ticks) //��������� �����
		{
			if (m_CurrentLine > 0)
				m_CurrentLine--;
			else
				m_CurrentLine = 0;

			m_LastChangedLineTime = ticks + (SCROLL_LISTING_DELAY / 5);
			m_FrameCreated = false;
		}
		else if (state == MWS_DOWN && m_LastChangedLineTime < ticks) //��������� ����
		{
			int visibleLines = SkillGroupManager.GetVisibleLinesCount();

			if (m_CurrentLine < visibleLines)
				m_CurrentLine++;
			else
				m_CurrentLine = visibleLines;

			m_LastChangedLineTime = ticks + (SCROLL_LISTING_DELAY / 5);
			m_FrameCreated = false;
		}
	}
}
//----------------------------------------------------------------------------
void TGumpSkills::OnCharPress(WPARAM &wparam, LPARAM &lparam)
{
	//���� ������
	if (wparam == VK_RETURN || wparam == VK_BACK || wparam == VK_ESCAPE || EntryPointer != TextEntry)
		return; //Ignore no print keys

	EntryPointer->Insert(wparam);

	int val = FontManager->GetWidthA(6, EntryPointer->c_str(), EntryPointer->Length());
	if (val > 170)
		EntryPointer->Remove(true);
	else
		m_FrameCreated = false;
}
//----------------------------------------------------------------------------
void TGumpSkills::OnKeyPress(WPARAM &wparam, LPARAM &lparam)
{
	if (EntryPointer != TextEntry)
	{
		if (wparam == VK_DELETE)
		{
			TSkillGroupObject *item = SkillGroupManager.m_Groups;

			while (item != NULL)
			{
				if (item->GetSelected() == 1)
				{
					SkillGroupManager.Remove(item);
					m_FrameCreated = false;

					break;
				}

				item = item->m_Next;
			}
		}

		return;
	}

	//���������� ������� �������
	switch (wparam)
	{
		case VK_RETURN:
		{
			TSkillGroupObject *item = SkillGroupManager.m_Groups;
			while (item != NULL)
			{
				if (item->GetSelected() == 2)
				{
					if (TextEntry->Length() > 0)
						item->SetName(TextEntry->c_str());
				}

				item->SetSelected(0);
				if (!item->GetName().length())
					item->SetName("NoNameGroup");

				item = item->m_Next;
			}

			if (ConfigManager.GetConsoleNeedEnter())
				EntryPointer = NULL;
			else
				EntryPointer = GameConsole;

			m_FrameCreated = false;

			break;
		}
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
		case VK_BACK:
		{
			EntryPointer->Remove(true);
			m_FrameCreated = false;

			break;
		}
		case VK_DELETE:
		{
			EntryPointer->Remove(false);
			m_FrameCreated = false;

			break;
		}
		default:
			break;
	}
}
//----------------------------------------------------------------------------