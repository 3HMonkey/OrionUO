/***********************************************************************************
**
** GumpSkills.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "GumpSkills.h"
#include "../SkillGroup.h"
#include "../Managers/SkillGroupManager.h"
#include "../Managers/ConfigManager.h"
#include "../Managers/MouseManager.h"
#include "../TextEngine/GameConsole.h"
//----------------------------------------------------------------------------------
CGumpSkills::CGumpSkills(uint serial, short x, short y, bool minimized, int height)
: CGumpBaseScroll(GT_SKILLS, serial, 0x1F40, height, x, y, true, 0, true, 15),
m_ShowReal(false), m_ShowCap(false)
{
	m_Locker.Serial = ID_GS_LOCK_MOVING;

	if (minimized)
	{
		m_Page = 1;
		m_Minimized = minimized;
		m_MinimizedX = x;
		m_MinimizedY = y;
	}
	else
		m_Page = 2;

	Add(new CGUIPage(1));
	Add(new CGUIGumppic(0x0839, 0, 0));

	Add(new CGUIPage(2));
	Add(new CGUIGumppic(0x0834, 82, 34)); //Skills text gump

	CGUICheckbox *checkbox = (CGUICheckbox*)Add(new CGUICheckbox(ID_GS_SHOW_REAL, 0x0938, 0x0939, 0x0938, 226, 34));
	checkbox->Checked = m_ShowReal;
	checkbox = (CGUICheckbox*)Add(new CGUICheckbox(ID_GS_SHOW_CAP, 0x0938, 0x0939, 0x0938, 280, 34));
	checkbox->Checked = m_ShowCap;

	CGUIText *text = (CGUIText*)Add(new CGUIText(0x0386, 180, 33));
	text->CreateTextureA(1, "Show:   Real    Cap");

	Add(new CGUIGumppic(0x082B, 30, 60)); //Top line
	m_BottomLine = (CGUIGumppic*)Add(new CGUIGumppic(0x082B, 31, m_Height - 48)); //Bottom line
	m_Comment = (CGUIGumppic*)Add(new CGUIGumppic(0x0836, 30, m_Height - 35));//Skills comment gump
	m_CreateGroup = (CGUIButton*)Add(new CGUIButton(ID_GS_BUTTON_NEW_GROUP, 0x083A, 0x083A, 0x083A, 60, m_Height - 3)); //New Group gump

	m_SkillSum = (CGUIText*)Add(new CGUIText(0x0065, 235, m_Height - 6));
	UpdateSkillsSum();

	m_DataBox = (CGUIDataBox*)m_HTMLGump->Add(new CGUIDataBox());
}
//----------------------------------------------------------------------------------
CGumpSkills::~CGumpSkills()
{
}
//----------------------------------------------------------------------------------
void CGumpSkills::UpdateHeight()
{
	CGumpBaseScroll::UpdateHeight();

	m_BottomLine->Y = m_Height - 48; //Bottom line
	m_Comment->Y = m_Height - 35;//Skills comment gump
	m_CreateGroup->Y = m_Height - 3; //New Group gump
	m_SkillSum->Y = m_Height - 6;
}
//----------------------------------------------------------------------------------
void CGumpSkills::UpdateSkillsSum()
{
	char str[20] = { 0 };
	sprintf(str, "%.1f", g_SkillsTotal);
	m_SkillSum->CreateTextureA(3, str);
}
//----------------------------------------------------------------------------------
void CGumpSkills::Init()
{
	//������� ��� ��������� ������
	QFOR(group, g_SkillGroupManager.m_Groups, CSkillGroupObject*)
		group->Maximized = false;
}
//----------------------------------------------------------------------------------
void CGumpSkills::PrepareContent()
{
}
//----------------------------------------------------------------------------------
void CGumpSkills::UpdateContent()
{
	m_DataBox->Clear();

	/*//������ ������ ��� ������ �����������
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

	CSkillGroupObject *selectedGroup = NULL; //��������� �� ������, � ������� ������ �����
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
							Orion->DrawGump(0x0835, 0, drawX + fw, drawY + 5, lw, 0);
					}
				}
			}

			if (group->GetMaximized()) //���� ������ ���������� - ���������� � ����������
			{
				if (canDraw) //����� ��������
				{
					//���� � ������ ���-�� ���� - ��������� �������
					if (group->GetCount())
						Orion->DrawGump(0x0826, 0, drawX, drawY);

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

									Orion->DrawGump(gumpID, 0, drawX + 8, drawY); //Button
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
								Orion->DrawGump(gumpID, 0, drawX + 251, drawY - 1);

								//�������� ������ (�������� ��������� ���� �����������)
								float val = g_Player->GetSkillBaseValue(idx);
								if (m_ShowReal)
									val = g_Player->GetSkillValue(idx);
								else if (m_ShowCap)
									val = g_Player->GetSkillCap(idx);

								char sbf[20] = { 0 };
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
					Orion->DrawGump(0x0827, 0, drawX, drawY);

				drawY += drawStep; //��������� �� ��������� ������� ���������
			}

			group = group->m_Next; //��������� �������
		}
	}

	//���� ���� ������������� ������� ������� - �������
	if (removeIndexOnExit)
		selectedGroup->Remove(si);*/
}
//----------------------------------------------------------------------------------
/*int TGumpSkills::Draw(bool &mode)
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
	DWORD ticks = g_Ticks;

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
			if (Orion->GumpPixelsInXY(0x0839, 0, 0))
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

		if (Orion->GumpPixelsInXY(0x082D, 167, 0)) //Minimize
		{
			LSG = ID_GS_BUTTON_MINIMIZE;
			g_LastSelectedGump = index;
		}
		else if (Orion->GumpPixelsInXY(0x1F40, 0, 23)) //Top scroll
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
						if (Orion->GumpPixelsInXY(0x1F41, 21, curposY, 0, deltaHeight))
						{
							g_LastSelectedObject = 0;
							g_LastSelectedGump = index;
						}
					}

					break;
				}
				else if (Orion->GumpPixelsInXY(0x1F41, 21, curposY))
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
						if (Orion->GumpPixelsInXY(0x1F42, 21, curposY, 0, deltaHeight))
						{
							g_LastSelectedObject = 0;
							g_LastSelectedGump = index;
						}
					}

					break;
				}
				else if (Orion->GumpPixelsInXY(0x1F42, 21, curposY))
				{
					g_LastSelectedObject = 0;
					g_LastSelectedGump = index;

					break;
				}

				curposY += 70;
			}
		}
		
		if (Orion->GumpPixelsInXY(0x1F43, 21, height + 34)) //Bottom scroll
		{
			g_LastSelectedObject = 0;
			g_LastSelectedGump = index;
		}
		
		if (Orion->GumpPixelsInXY(0x082E, 167, height + 66)) //Resize
		{
			LSG = ID_GS_BUTTON_RESIZE;
			g_LastSelectedGump = index;
		}
		else if (Orion->GumpPixelsInXY(0x0938, 226, 34)) //Real
			LSG = ID_GS_SHOW_REAL;
		else if (Orion->GumpPixelsInXY(0x0938, 280, 34)) //Cap
			LSG = ID_GS_SHOW_CAP;
		else if (Orion->GumpPixelsInXY(0x0824, 294, 56)) //^ button
			LSG = ID_GS_BUTTON_UP;
		else if (Orion->GumpPixelsInXY(0x0825, 294, height + 3)) //v button
			LSG = ID_GS_BUTTON_DOWN;
		else if (Orion->GumpPixelsInXY(0x0828, 296, 72 + scrollerY)) //Scroller
			LSG = ID_GS_SCROLLER;
		else if (Orion->PolygonePixelsInXY(60, height + 44, 80, 14))
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

					if (th.Width && Orion->PolygonePixelsInXY(drawX + 16, drawY, th.Width - 10, 14))
					{
						LSG = ID_GS_GROUP + groupIndex;
						break;
					}
				}

				if (group->GetMaximized())
				{
					if (canDraw)
					{
						if (group->GetCount() && Orion->PolygonePixelsInXY(drawX, drawY, 14, 14))
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
								if (Skills[idx].m_Button && Orion->GumpPixelsInXY(0x0837, drawX + 8, drawY))
								{
									LSG = ID_GS_SKILL_BUTTON + idx; //Button
									completedSearch = true;

									break;
								}

								TTextTexture &th = Skills[idx].m_Texture;
								int width = 150;

								if (th.Width > 150)
									width = th.Width;

								if (Orion->PolygonePixelsInXY(drawX + 22, drawY - 1, width, 14))
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

								if (Orion->GumpPixelsInXY(gumpID, drawX + 251, drawY - 1))
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
					if (group->GetCount() && Orion->PolygonePixelsInXY(drawX, drawY, 14, 14))
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

		if (g_ShowGumpLocker && Orion->PolygonePixelsInXY(0, 0, 10, 14))
			g_LastSelectedObject = ID_GS_LOCK_MOVING;

		g_MouseX = oldMouseX;
		g_MouseY = oldMouseY;

		return LSG;
	}

	return 0;
}*/
//----------------------------------------------------------------------------------
CSkillGroupObject *CGumpSkills::GetGroupUnderCursor(int startIndex)
{
	//�������� ������ ��� ��������
	WISP_GEOMETRY::CPoint2Di mouse = g_MouseManager.Position;

	//���� ����� �� ������� ����� �� ��� X
	if (mouse.X < (m_X + 30) || mouse.X > (m_X + 250))
		return NULL; //Exit from bounds on X

	//���� ��������� � �������� ����� �� ��� Y
	if (mouse.Y > (m_Y + 72) && mouse.Y < (m_Y + m_Height)) //Bounds of Y
	{
		int currentIndex = 0; //��������� �� ������� ������

		//������ ���������
		int drawY = m_Y + 75;

		//��� ��������� (� ��������)
		const int drawStep = 17;

		//������������ ���������� Y ��� �����������
		int boundsY = m_Y + m_Height;

		//��������� �� ������
		CSkillGroupObject *group = g_SkillGroupManager.m_Groups;

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

					if (mouse.Y < drawY)
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
						if (mouse.Y < drawY)
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
				if (mouse.Y < drawY)
					return group;
			}

			group = group->m_Next; //��������� ������
		}
	}

	//������ �� �������
	return NULL;
}
//----------------------------------------------------------------------------------
/*void TGumpSkills::OnLeftMouseDown()
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
}*/
//----------------------------------------------------------------------------------
/*void TGumpSkills::OnLeftMouseUp()
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
	DWORD ticks = g_Ticks;

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

			Orion->SkillStatusChange(idx, status);
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

			Orion->UseSkill(idx);
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
//----------------------------------------------------------------------------------
bool TGumpSkills::OnLeftMouseDoubleClick()
{
	if (m_Minimized) //��� ��������� �� ����-����� - ���������� ���
	{
		m_Minimized = false;
		m_FrameCreated = false;

		return true;
	}

	return false;
}*/
//----------------------------------------------------------------------------------
void CGumpSkills::OnCharPress(const WPARAM &wParam, const LPARAM &lParam)
{
	g_EntryPointer->Insert(wParam);

	int val = g_FontManager.GetWidthA(6, g_EntryPointer->c_str(), g_EntryPointer->Length());

	if (val > 170)
		g_EntryPointer->Remove(true);
	else
		m_WantRedraw = true;
}
//----------------------------------------------------------------------------------
void CGumpSkills::OnKeyDown(const WPARAM &wParam, const LPARAM &lParam)
{
	/*if (g_EntryPointer != TextEntry)
	{
		if (wParam == VK_DELETE)
		{
			CSkillGroupObject *item = g_SkillGroupManager.m_Groups;

			while (item != NULL)
			{
				if (item->Selected == 1)
				{
					g_SkillGroupManager.Remove(item);
					m_FrameCreated = false;

					break;
				}

				item = item->m_Next;
			}
		}

		return;
	}

	//���������� ������� �������
	switch (wParam)
	{
		case VK_RETURN:
		{
			CSkillGroupObject *item = g_SkillGroupManager.m_Groups;

			while (item != NULL)
			{
				if (item->Selected == 2)
				{
					if (TextEntry->Length() > 0)
						item->Name = TextEntry->c_str();
				}

				item->Selected = 0;

				if (!item->Name.length())
					item->Name = "NoNameGroup";

				item = item->m_Next;
			}

			if (g_ConfigManager.ConsoleNeedEnter)
				g_EntryPointer = NULL;
			else
				g_EntryPointer = &g_GameConsole;

			m_WantRedraw = true;

			break;
		}
		case VK_HOME:
		case VK_END:
		case VK_LEFT:
		case VK_RIGHT:
		case VK_BACK:
		case VK_DELETE:
		{
			g_EntryPointer->OnKey(this, wParam);

			break;
		}
		default:
			break;
	}*/
}
//----------------------------------------------------------------------------------
