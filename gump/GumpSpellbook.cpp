/****************************************************************************
**
** SpellbookGump.cpp
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

TTextTexture TGumpSpellbook::m_TextIndex;
TTextTexture TGumpSpellbook::m_TextReagents;
TTextTexture TGumpSpellbook::m_TextCircle[8];
TTextTexture TGumpSpellbook::m_TextReagent[8];
TTextTexture TGumpSpellbook::m_TextSpell[64];
//----------------------------------------------------------------------------
WORD TGumpSpellbook::m_ReagentsIndex[8] = 
{
	0x0F7A, 0x0F7B, 0x0F84, 0x0F85,
	0x0F86, 0x0F88, 0x0F8C, 0x0F8D
};
//----------------------------------------------------------------------------
TGumpSpellbook::TGumpSpellbook(DWORD serial, short x, short y)
: TGump(GT_SPELLBOOK, serial, x, y), m_Page(1)
{
}
//----------------------------------------------------------------------------
TGumpSpellbook::~TGumpSpellbook()
{
}
//----------------------------------------------------------------------------
int TGumpSpellbook::GetReagentIndex(WORD &id)
{
	switch (id)
	{
		case 0x0F7A:
			return 0;
		case 0x0F7B:
			return 1;
		case 0x0F84:
			return 2;
		case 0x0F85:
			return 3;
		case 0x0F86:
			return 4;
		case 0x0F88:
			return 5;
		case 0x0F8C:
			return 6;
		case 0x0F8D:
			return 7;
		default:
			break;
	}

	return 0;
}
//----------------------------------------------------------------------------
void TGumpSpellbook::InitTextTextures()
{
	FontManager->GenerateA(6, m_TextIndex, "INDEX", 0x0288);

	FontManager->GenerateA(6, m_TextReagents, "Reagents:", 0x0288);

	string str = "";

	IFOR(i, 0, 8)
	{
		FontManager->GenerateA(6, m_TextCircle[i], g_SpellCircles[i], 0x0288);
		
		str = GetReagentName(m_ReagentsIndex[i]);
		FontManager->GenerateA(9, m_TextReagent[i], str.c_str(), 0x0288);
	}

	IFOR(i, 0, 64)
	{
		WORD id = 0x2080 + i;
		str = UO->m_StaticData[id / 32].Tiles[id % 32].Name;
		FontManager->GenerateA(9, m_TextSpell[i], str.c_str(), 0x0288);
	}
}
//----------------------------------------------------------------------------
void TGumpSpellbook::ReleaseTextTextures()
{
	m_TextIndex.Clear();

	IFOR(i, 0, 8)
	{
		m_TextCircle[i].Clear();
		m_TextReagent[i].Clear();
	}

	IFOR(i, 0, 64)
		m_TextSpell[i].Clear();
}
//----------------------------------------------------------------------------
void TGumpSpellbook::PrepareTextures()
{
	UO->ExecuteGump(0x0835);
	UO->ExecuteGumpPart(0x08AC, 13);
	UO->ExecuteGumpPart(0x08B1, 8);
	UO->ExecuteGumpPart(0x08BB, 2);
	UO->ExecuteGumpPart(0x08C0, 64);
}
//----------------------------------------------------------------------------
void TGumpSpellbook::GenerateFrame(int posX, int posY)
{
	if (!g_DrawMode)
	{
		FrameRedraw = false;
		FrameCreated = false;

		return;
	}

	TGameItem *spellbook = World->FindWorldItem(Serial);
	if (spellbook == NULL)
		return; //���� ��� ��������� - ������ �� ����

	if (Minimized) //�������� � ��������� ��������
	{
		glNewList((GLuint)this, GL_COMPILE);

			UO->DrawGump(0x08BA, 0, posX, posY); //����-���� ���������

		glEndList();

		FrameCreated = true;

		return; //��� ������ ������ ������������
	}

	int spellCount = 0;

	BYTE spells[64] = {0}; //��������� �� ����������
	spellbook = (TGameItem*)spellbook->m_Items; //� ���� ������ �����

	while (spellbook != NULL) //��������� �� ���� ��������� ���������
	{
		int currentCount = spellbook->Count;

		if (currentCount > 0 && currentCount <= 64) //�������� ������ ����������
		{
			spells[currentCount - 1] = 1; //����������, ����� ���
			spellCount++; //����������� ������� ����������
		}

		spellbook = (TGameItem*)spellbook->m_Next;
	}

	int pageCount = 4 + (spellCount / 2); //��������� ���������� ������� �����
	if (spellCount % 2)
		pageCount++; //���� �������� - ����������� �� ������� (��������� ����� ������)

	if (m_Page < 1)
		m_Page = 1; //�� ������ ������ �������� ������� ��������

	if (FrameCreated)
		glDeleteLists((GLuint)this, 1);

	glNewList((GLuint)this, GL_COMPILE);

		UO->DrawGump(0x08AC, 0, posX, posY); //���� �����

		if (m_Page != 1)
			UO->DrawGump(0x08BB, 0, posX + 50, posY + 8); //������ "�����"

		if (m_Page != pageCount)
			UO->DrawGump(0x08BC, 0, posX + 321, posY + 8); //������ "������"

		//����� 1-4 (� ��������� �����)
		UO->DrawGump(0x08B1, 0, posX + 58, posY + 175);
		UO->DrawGump(0x08B2, 0, posX + 93, posY + 175);
		UO->DrawGump(0x08B3, 0, posX + 130, posY + 175);
		UO->DrawGump(0x08B4, 0, posX + 164, posY + 175);
		
		//����� 5-8 (� ��������� �����)
		UO->DrawGump(0x08B5, 0, posX + 227, posY + 175);
		UO->DrawGump(0x08B6, 0, posX + 260, posY + 175);
		UO->DrawGump(0x08B7, 0, posX + 297, posY + 175);
		UO->DrawGump(0x08B8, 0, posX + 332, posY + 175);
			
		if (m_Page <= 4) //���������� �����
		{
			int drawY = posY + 10;

			m_TextIndex.Draw(posX + 106, drawY);
			m_TextIndex.Draw(posX + 269, drawY);

			int pageIdx = (m_Page - 1) * 2;
			drawY += 20;

			m_TextCircle[pageIdx].Draw(posX + 62, drawY);
			m_TextCircle[pageIdx + 1].Draw(posX + 225, drawY);

			drawY += 22;

			//��������� �������� �������
			for (int i = 0, si1 = 0, si2 = 0; i < 8; i++)
			{
				int offs = i + ((8 * (m_Page - 1)) * 2);

				//��� ����� ��������
				if (spells[offs])
				{
					m_TextSpell[offs].Draw(posX + 62, drawY + (si1 * 15));

					//���� ������� � ��������� �������������� ����������� - ��������� ��������
					if (offs == g_LastSpellIndex - 1)
					{
						UO->DrawGump(0x08AD, 0, posX + 184, posY + 2);
						UO->DrawGump(0x08AF, 0, posX + 184, drawY + (si1 * 15));
					}

					si1++;
				}

				offs = 8 + i + ((8 * (m_Page - 1)) * 2);

				//��� ������ ��������
				if (spells[offs])
				{
					m_TextSpell[offs].Draw(posX + 225, drawY + (si2 * 15));

					//���� ������� � ��������� �������������� ����������� - ��������� ��������
					if (offs == g_LastSpellIndex - 1)
					{
						UO->DrawGump(0x08AE, 0, posX + 203, posY + 3);
						UO->DrawGump(0x08B0, 0, posX + 203, drawY + (si2 * 15));
					}

					si2++;
				}
			}
		}
		else //�������� � ������������� ����������
		{
			//��������, ������� ���������� ����� (1 ��� 2)
			bool oneSpell = ((m_Page == pageCount) && (spellCount % 2));

			int idx = ((m_Page - 5) * 2); //��������� ������
			if (oneSpell)
				idx++; //���� 1 ������ - ������ ������

			int SI = 0;
			int c = 0;

			for (SI = 0, c = 0; SI < 64; SI++)
			{
				if (spells[SI] != 0)
					c++; //���� ������� ���� - ����������� �������

				if (oneSpell && c == idx)
					break; //���� ����� 1 ����� � ��� ������� ������ - ������� �� �����

				if (c == idx + 1)
					break; //���� ������� ���������� �� ������� ������ + 1 - �������
			}

			if (oneSpell) //���� 1 �����
			{
				if (c != idx)
				{
					glEndList();

					FrameCreated = true;

					return; //���� ������� �� ��������� - ������, �������
				}
			}
			else if (c != idx + 1)
			{
				glEndList();

				FrameCreated = true;

				return; //��� ��, ���� ������� �� ����� ������ + 1 - ������, �������
			}

			if (SI == 64)
			{
				glEndList();

				FrameCreated = true;

				return; //������. �������� ����� ������ ����������, �������
			}

			//�������� �����
			m_TextCircle[(SI / 8)].Draw(posX + 87, posY + 10);

			//������ ����������
			UO->DrawGump(0x08C0 + SI, 0, posX + 62, posY + 40);

			WORD id = (0x2080 + SI); //��� �������� ����������
			TTextTexture th;
			FontManager->GenerateA(6, th, UO->m_StaticData[id / 32].Tiles[id % 32].Name, 0x0288, 80);
			th.Draw(posX + 112, posY + 34);

			//������������ ����������
			int addY = 26;
			if (th.Height < 24)
				addY = 31;
			FontManager->DrawA(8, g_SpellCastAbr[SI], 0x0288, posX + 112, posY + addY + th.Height);
			th.Clear();

			//�������
			UO->DrawGump(0x0835, 0, posX + 62, posY + 88, 120, 0);

			m_TextReagents.Draw(posX + 62, posY + 92);

			IFOR(i, 0, 4) //��������� ��������, ����������� �� ����
			{
				id = g_SpellReagents[SI][i];

				if (!id)
					break; //���� ���� ��� - �������, ������ ������ �� �����

				m_TextReagent[GetReagentIndex(id)].Draw(posX + 62, posY + 114 + (i * 14));
			}

			//���� ��� ��������� ������������ ���������� - ���������� ��������
			if (SI == g_LastSpellIndex - 1)
			{
				UO->DrawGump(0x08AD, 0, posX + 184, posY + 2);
				UO->DrawGump(0x08AF, 0, posX + 184, posY + 40);
			}

			//��������� �� ��������� ����������
			SI++;

			for (; SI < 64; SI++) //��������� �� ���������� �����������
			{
				if (spells[SI] != 0)
					break; //���� ���-�� ������� ������ ��������� ����� - ������� �� �����
			}

			if (SI == 64)
			{
				glEndList();

				FrameCreated = true;

				return; //���������� ������ ���, ����� ����� ���������, ������
			}

			//�������� �����
			m_TextCircle[(SI / 8)].Draw(posX + 244, posY + 10);

			//������ ����������
			UO->DrawGump(0x08C0 + SI, 0, posX + 225, posY + 40);

			id = (0x2080 + SI); //��� �������� ����������
			FontManager->GenerateA(6, th, UO->m_StaticData[id / 32].Tiles[id % 32].Name, 0x0288, 80);
			th.Draw(posX + 275, posY + 34);

			//������������ ����������
			addY = 26;
			if (th.Height < 24)
				addY = 31;
			FontManager->DrawA(8, g_SpellCastAbr[SI], 0x0288, posX + 275, posY + addY + th.Height);
			th.Clear();

			//�������
			UO->DrawGump(0x0835, 0, posX + 225, posY + 88, 120, 0);

			m_TextReagents.Draw(posX + 225, posY + 92);

			IFOR(i, 0, 4) //��������� �� ���� ���������
			{
				id = g_SpellReagents[SI][i];

				if (!id)
					break; //���� ���� ��� - �������, ������ ������ �� �����

				m_TextReagent[GetReagentIndex(id)].Draw(posX + 225, posY + 114 + (i * 14));
			}

			//���� ��� ��������� ������������ ���������� - ���������� ��������
			if (SI == g_LastSpellIndex - 1)
			{
				UO->DrawGump(0x08AE, 0, posX + 203, posY + 3);
				UO->DrawGump(0x08B0, 0, posX + 203, posY + 40);
			}
		}

	glEndList();

	FrameCreated = true;
}
//----------------------------------------------------------------------------
int TGumpSpellbook::Draw(bool &mode)
{
	TGameItem *spellbook = World->FindWorldItem(Serial);
	if (spellbook == NULL)
		return 0; //���� ��� ��������� - ������ �� ����

	//�� ����� ������ �������
	DWORD index = (DWORD)this;

	//������ �� ������ � ����?
	bool IsPressed = (g_LeftMouseDown && g_LastGumpLeftMouseDown == index && g_LastSelectedGump == index);

	//����� �������� ������ ����������
	if (IsPressed && m_Page > 4 && g_LastObjectLeftMouseDown >= ID_GSB_SPELL_ICON_LEFT && ((g_MouseX != g_DroppedLeftMouseX || g_MouseY != g_DroppedLeftMouseY) || (g_LastGumpMouseDownTime + DCLICK_DELAY < GetTickCount())))
	{
		//�������� ����� ������ �����, ��������� ��� ������ ����������
		if (g_LastObjectLeftMouseDown < ID_GSB_SPELL_ICON_RIGHT)
			g_LastObjectLeftMouseDown -= ID_GSB_SPELL_ICON_LEFT;
		else
			g_LastObjectLeftMouseDown -= ID_GSB_SPELL_ICON_RIGHT;

		TGumpSpell *newgump = new TGumpSpell(g_LastObjectLeftMouseDown + 1, g_MouseX - 20, g_MouseY - 20, 0x08C0 + g_LastObjectLeftMouseDown);

		//���� ���� ��������� � ������
		GumpManager->AddGump(newgump);

		//������� ���������� � ������� ��� �������� � � ����������� ������ �����
		CurrentScreen->OnLeftMouseDown();
	}

	//������� ���������� (��� �������� �������)
	int posX = X;
	int posY = Y;

	//���� ���� ������� - ������� ��������������� ����������
	if (Minimized)
	{
		posX = MinimizedX;
		posY = MinimizedY;
	}

	//���� ���� �������� - ��������� �������� ���������
	if (g_LeftMouseDown && g_LastGumpLeftMouseDown == index && !g_LastObjectLeftMouseDown)
	{
		posX += (g_MouseX - g_DroppedLeftMouseX);
		posY += (g_MouseY - g_DroppedLeftMouseY);

		//���������� ����
		if (mode)
			GenerateFrame(posX, posY);
	}

	if (mode) //���������
	{
		//���� ������ ����������� �� ������
		if (!FrameCreated)
			GenerateFrame(posX, posY);

		//�������� ����
		glCallList((GLuint)index);

		if (g_ShowGumpLocker)
			g_GL.Draw(g_TextureGumpState[LockMoving], (GLfloat)posX, (GLfloat)posY, 10.0f, 14.0f);
	}
	else //����� ��������
	{
		if (Minimized) //���� ��� ���������������� ������ �����
		{
			if (UO->GumpPixelsInXY(0x08BA, posX, posY))
			{
				g_LastSelectedObject = 0;
				g_LastSelectedGump = index;
			}

			return 0;
		}

		int spellCount = 0;

		//������ ���������� ����������
		BYTE spells[64] = {0};

		//��������� �� ����������
		spellbook = (TGameItem*)spellbook->m_Items;

		//��������� �� ���� �����������, �������� ����� ����
		while (spellbook != NULL)
		{
			int currentCount = spellbook->Count;
			if (currentCount > 0 && currentCount <= 64)
			{
				//������� ��������� ����������
				spells[currentCount - 1] = 1;
				spellCount++;
			}

			spellbook = (TGameItem*)spellbook->m_Next; //��������� ������� �����
		}

		int pageCount = 4 + (spellCount / 2); //��������� ���������� ������� �����
		if (spellCount % 2)
			pageCount++; //������ ���������� (���� ��������)

		if (!Minimized && m_Page < 1)
			m_Page = 1; //������ ������� ��������

		//���� ���������
		if (UO->GumpPixelsInXY(0x08AC, posX, posY))
		{
			g_LastSelectedObject = 0;
			g_LastSelectedGump = index;
		}

		//����� �� ��� ������, ���������� �������� �� ���������. ������ �� ����
		if (g_LastSelectedGump != index)
			return 0;

		int LSG = 0;

		//���� ������� ���������� ��������
		if (m_Page != 1)
		{
			if (UO->GumpPixelsInXY(0x08BB, posX + 50, posY + 8))
				LSG = ID_GSB_BUTTON_PREV; //Prev
		}

		//���� ������� ��������� ��������
		if (m_Page != pageCount)
		{
			if (UO->GumpPixelsInXY(0x08BC, posX + 321, posY + 8))
				LSG = ID_GSB_BUTTON_NEXT; //Next
		}

		int checkY = posY + 175;

		//����� 1-4 (� ��������� �����)
		if (UO->GumpPixelsInXY(0x08B1, posX + 58, checkY))
			LSG = ID_GSB_BUTTON_CIRCLE_1_2;
		else if (UO->GumpPixelsInXY(0x08B2, posX + 93, checkY))
			LSG = ID_GSB_BUTTON_CIRCLE_1_2;
		else if (UO->GumpPixelsInXY(0x08B3, posX + 130, checkY))
			LSG = ID_GSB_BUTTON_CIRCLE_3_4;
		else if (UO->GumpPixelsInXY(0x08B4, posX + 164, checkY))
			LSG = ID_GSB_BUTTON_CIRCLE_3_4;
		
		//����� 5-8 (� ��������� �����)
		else if (UO->GumpPixelsInXY(0x08B5, posX + 227, checkY))
			LSG = ID_GSB_BUTTON_CIRCLE_5_6;
		else if (UO->GumpPixelsInXY(0x08B6, posX + 260, checkY))
			LSG = ID_GSB_BUTTON_CIRCLE_5_6;
		else if (UO->GumpPixelsInXY(0x08B7, posX + 297, checkY))
			LSG = ID_GSB_BUTTON_CIRCLE_7_8;
		else if (UO->GumpPixelsInXY(0x08B8, posX + 332, checkY))
			LSG = ID_GSB_BUTTON_CIRCLE_7_8;

		//������ ����������� �����
		RECT rc = {0, 0, 16, 16};
		POINT p = {g_MouseX - (posX + 6), g_MouseY - (posY + 100)};
		if (PtInRect(&rc, p))
			LSG = ID_GSB_BUTTON_MINIMIZE;

		if (m_Page <= 4) //���� ��� ���������� �����
		{
			RECT rc = {0, 0, 100, 16};
			for (int i = 0, si1 = 0, si2 = 0; i < 8; i++)
			{
				int offs = i + ((8 * (m_Page - 1)) * 2);

				if (spells[offs]) //���������� ����� ��������
				{
					POINT p = {g_MouseX - (posX + 62), g_MouseY - (posY + 52 + (si1 * 15))};
					if (PtInRect(&rc, p))
					{
						LSG = offs + ID_GSB_SPELL_ICON_LEFT;
						break;
					}

					si1++;
				}

				offs = 8 + i + ((8 * (m_Page - 1)) * 2);

				if (spells[offs]) //���������� ������ ��������
				{
					POINT p = {g_MouseX - (posX + 225), g_MouseY - (posY + 52 + (si2 * 15))};
					if (PtInRect(&rc, p))
					{
						LSG = offs + ID_GSB_SPELL_ICON_RIGHT;
						break;
					}

					si2++;
				}
			}
		}
		else //�������� � ������������ ����������
		{
			//����� ���������� ������ ���� ����������
			bool oneSpell = ((m_Page == pageCount) && (spellCount % 2));

			//��������� ������� ������ ����������
			int idx = ((m_Page - 5) * 2);
			if (oneSpell)
				idx++; //���� ����� ���������� ���� ���������� - ������

			int SI = 0;
			int c = 0;

			//���������� �� ���� �����������
			for (SI = 0, c = 0; SI < 64; SI++)
			{
				if (spells[SI] != 0)
					c++; //���� ��� ���������� - ����������� �������

				if (oneSpell && c == idx)
					break; //���� ������������ ���� ���������� � ������ �� ��������� ��������� - ������� �� �����

				if (c == idx + 1)
					break; //��� ��, ���� ������ + 1 ����� �������� - ������� �� �����
			}

			if (oneSpell) //���� ���� ����������
			{
				//���� ������� �� ����� ������� - ������, ������� � ����������� ������� ��� ��������
				if (c != idx)
				{
					if (LSG != 0)
						g_LastSelectedObject = LSG;

					return LSG;
				}
			}
			else if (c != idx + 1)
			{
				//���� ������� �� ����� ������� + 1 - ������, ������� � ����������� ������� ��� ��������
				if (LSG != 0)
					g_LastSelectedObject = LSG;

				return LSG; //Error...
			}

			if (SI == 64)
			{
				//���� ������� ������ ����� ������ ���������� - ������, ������� � ����������� ������� ��� ��������
				if (LSG != 0)
					g_LastSelectedObject = LSG;

				return LSG; //Error...
			}

			//��������� ���� ������ ����������
			if (UO->GumpPixelsInXY(0x08C0 + SI, posX + 62, posY + 40))
				LSG = ID_GSB_SPELL_ICON_LEFT + SI;

			//����������� ������ ����������
			SI++;

			for (; SI < 64; SI++) //���������� �� ���� �����������
			{
				if (spells[SI] != 0)
					break; //���� ���-�� ������� - ������� �� �����
			}

			if (SI == 64)
			{
				//���� ������� �� ����� ����� ������ ���������� - ������, ������� � ����������� ������� ��� ��������
				if (LSG != 0)
					g_LastSelectedObject = LSG;

				return LSG; //End of spellbook
			}

			//�������� ���� ������ ����������
			if (UO->GumpPixelsInXY(0x08C0 + SI, posX + 225, posY + 40))
				LSG = ID_GSB_SPELL_ICON_RIGHT + SI;
		}

		//���� ���-�� ������� - ��������� ������ �������
		if (LSG != 0)
			g_LastSelectedObject = LSG;

		if (g_ShowGumpLocker && UO->PolygonePixelsInXY(posX, posY, 10, 14))
		{
			g_LastSelectedObject = ID_GSB_LOCK_MOVING;
			g_LastSelectedGump = index;
		}

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
void TGumpSpellbook::OnLeftMouseUp()
{
	//�������� ���������� ����������
	if (g_LastObjectLeftMouseDown != g_LastSelectedObject || !g_LastObjectLeftMouseDown || Minimized || !g_LastSelectedGump)
		return;

	//�������� ������� �������� � ������
	int lastPage = m_Page;

	if (g_LastObjectLeftMouseDown == ID_GSB_BUTTON_PREV) //Prev
	{
		//������ �� ������ "�����"

		//gump->SetPage(gump->GetPage() - 1);
		if (!g_ClickObjectReq) //���� �� ���� ������� �� ����
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
	else if (g_LastObjectLeftMouseDown == ID_GSB_BUTTON_NEXT) //Next
	{
		//������ �� ������ "�����"

		//gump->SetPage(gump->GetPage() + 1);
		if (!g_ClickObjectReq) //���� �� ���� ������� �� ����
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
	else if (g_LastObjectLeftMouseDown == ID_GSB_BUTTON_CIRCLE_1_2)
		m_Page = 1; //������� � ���������� �� ����� 1-2
	else if (g_LastObjectLeftMouseDown == ID_GSB_BUTTON_CIRCLE_3_4)
		m_Page = 2; //������� � ���������� �� ����� 3-4
	else if (g_LastObjectLeftMouseDown == ID_GSB_BUTTON_CIRCLE_5_6)
		m_Page = 3; //������� � ���������� �� ����� 5-6
	else if (g_LastObjectLeftMouseDown == ID_GSB_BUTTON_CIRCLE_7_8)
		m_Page = 4; //������� � ���������� �� ����� 7-8
	else if (g_LastObjectLeftMouseDown == ID_GSB_BUTTON_MINIMIZE) //�������� ����
	{
		Minimized = true;
		GenerateFrame(MinimizedX, MinimizedY);
	}
	else if (g_LastObjectLeftMouseDown == ID_GSB_LOCK_MOVING)
	{
		LockMoving = !LockMoving;
		g_CancelDoubleClick = true;
	}
	else if (g_LastObjectLeftMouseDown >= ID_GSB_SPELL_ICON_LEFT)
	{
		//���� ������� ����������. ����������� ��������� ������ �� ����������, ��������� ����

		TGameItem *spellbook = World->FindWorldItem(Serial);
		if (spellbook == NULL)
			return;

		int spellCount = 0;

		BYTE spells[64] = {0};
		spellbook = (TGameItem*)spellbook->m_Items;

		while (spellbook != NULL)
		{
			int currentCount = spellbook->Count;

			if (currentCount > 0 && currentCount < 64)
			{
				spells[currentCount - 1] = 1;
				spellCount++;
			}

			spellbook = (TGameItem*)spellbook->m_Next;
		}

		int pageCount = 4 + (spellCount / 2);
		if (spellCount % 2)
			pageCount++;

		if (m_Page < 1)
			m_Page = 1;

		if (m_Page <= 4) //List of spells
		{
			for (int i = 0, si1 = 0, si2 = 0; i < 8; i++)
			{
				int offs = i + ((8 * (m_Page - 1)) * 2);
				
				if (spells[offs])
				{
					if (g_LastObjectLeftMouseDown == offs + ID_GSB_SPELL_ICON_LEFT)
					{
						//gump->SetPage(5);

						int c = 0;

						for (int j = 0; j < 64; j++)
						{
							if (spells[j])
							{
								c++;

								if (j == offs)
									break;
							}
						}

						if (!g_ClickObjectReq)
						{
							g_ClickObjectReq = true;

							g_ClickObject.Init(COT_GUMP);
							g_ClickObject.GumpType = GumpType;
							g_ClickObject.Serial = Serial;
							g_ClickObject.GumpID = ID;
							g_ClickObject.GumpButtonID = 5 + ((c - 1) / 2);
							g_ClickObject.Timer = GetTickCount() + DCLICK_DELAY;
						}

						//gump->SetPage(5 + ((c - 1) / 2));

						return;
					}
					si1++;
				}

				offs = 8 + i + ((8 * (m_Page - 1)) * 2);

				if (spells[offs])
				{
					if (g_LastObjectLeftMouseDown == offs + ID_GSB_SPELL_ICON_RIGHT)
					{
						//gump->SetPage(5);

						int c = 0;

						for (int j = 0; j < 64; j++)
						{
							if (spells[j])
							{
								c++;

								if (j == offs)
									break;
							}
						}

						if (!g_ClickObjectReq)
						{
							g_ClickObjectReq = true;

							g_ClickObject.Init(COT_GUMP);
							g_ClickObject.GumpType = GumpType;
							g_ClickObject.Serial = Serial;
							g_ClickObject.GumpID = ID;
							g_ClickObject.GumpButtonID = 5 + ((c - 1) / 2);
							g_ClickObject.Timer = GetTickCount() + DCLICK_DELAY;
						}

						//gump->SetPage(5 + ((c - 1) / 2));

						return;
					}
					si2++;
				}
			}
		}
	}

	//���� ���� �������� �������� - ���������� ����
	if (lastPage != m_Page)
		UpdateFrame();
}
//----------------------------------------------------------------------------
bool TGumpSpellbook::OnLeftMouseDoubleClick()
{
	//���� ������ ������� �� ���� - ������ �� ����
	if (!g_LastSelectedGump)
		return false;

	if (!g_LastObjectLeftMouseDown && Minimized)
	{
		//���� ���� ������������� - ��������������� ��� ���������� ���
		Minimized = false;
		GenerateFrame(X, Y);

		return true;
	}
	else if (!Minimized && g_LastObjectLeftMouseDown)
	{
		//���� �� ������������� � ���-�� �������

		TGameItem *spellbook = World->FindWorldItem(Serial);
		if (spellbook == NULL)
			return false; //����� �����������, ��������� ������, ������

		int spellCount = 0;

		//����������� ���������, ��������� � �������� ����
		BYTE spells[64] = {0};
		spellbook = (TGameItem*)spellbook->m_Items;

		while (spellbook != NULL)
		{
			int currentCount = spellbook->Count;

			if (currentCount > 0 && currentCount < 64)
			{
				spells[currentCount - 1] = 1;
				spellCount++;
			}

			spellbook = (TGameItem*)spellbook->m_Next;
		}

		int pageCount = 4 + (spellCount / 2);
		if (spellCount % 2)
			pageCount++;

		if (m_Page < 1)
			m_Page = 1;

		if (g_LastObjectLeftMouseDown == ID_GSB_BUTTON_PREV) //Prev
		{
			//��� ����� ������ "�����", ��� ��������� ������������� 1 ��������
			m_Page = 1;

			//���������� ����
			UpdateFrame();

			return true;
		}
		else if (g_LastObjectLeftMouseDown == ID_GSB_BUTTON_NEXT) //Next
		{
			//��� ����� ������ "������", ��� ��������� ������������� ��������� ��������
			m_Page = pageCount;

			//���������� ����
			UpdateFrame();

			return true;
		}
		else if (g_LastObjectLeftMouseDown >= ID_GSB_SPELL_ICON_LEFT)
		{
			//���� ������������ ����������
			if (g_LastObjectLeftMouseDown < ID_GSB_SPELL_ICON_RIGHT)
				UO->CastSpellFromBook(g_LastObjectLeftMouseDown - ID_GSB_SPELL_ICON_LEFT + 1, Serial);
			else
				UO->CastSpellFromBook(g_LastObjectLeftMouseDown - ID_GSB_SPELL_ICON_RIGHT + 1, Serial);

			//����������� �����
			Minimized = true;
			GenerateFrame(MinimizedX, MinimizedY);

			return true;
		}
	}

	return false;
}
//----------------------------------------------------------------------------