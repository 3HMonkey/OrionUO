/****************************************************************************
**
** StatusbarGump.cpp
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
//---------------------------------------------------------------------------
TGumpStatusbar::TGumpStatusbar(DWORD serial, short x, short y, bool minimized)
: TGump(GT_STATUSBAR, serial, x, y), m_GroupNext(NULL), m_GroupPrev(NULL)
{
	TextEntry = new TEntryText(32, 150, 150);

	if (minimized)
	{
		Minimized = true;
		MinimizedX = x;
		MinimizedY = y;
	}
	
	TGameObject *character = World->FindWorldObject(serial);
	if (character != NULL)
		TextEntry->SetText(character->GetName());
}
//---------------------------------------------------------------------------
TGumpStatusbar::~TGumpStatusbar()
{
	if (ConnectionManager.Connected())
	{
		TPacketCloseStatusbarGump packet(Serial);
		packet.Send();
	}

	RemoveFromGroup();

	if (TextEntry != NULL)
	{
		delete TextEntry;
		TextEntry = NULL;
	}
}
//---------------------------------------------------------------------------
TGumpStatusbar *TGumpStatusbar::GetTopStatusbar()
{
	if (!InGroup())
		return NULL;

	if (m_GroupPrev == NULL)
		return this;

	TGumpStatusbar *gump = m_GroupPrev;

	while (gump != NULL && gump->m_GroupPrev != NULL)
		gump = gump->m_GroupPrev;

	return gump;
}
//---------------------------------------------------------------------------
TGumpStatusbar *TGumpStatusbar::GetNearStatusbar(int &x, int &y)
{
	if (InGroup() || !Minimized)
		return NULL;

	//154x59 mini-gump
	
	const int rangeX = 77;
	const int rangeY = 29;
	const int rangeOffsetX = 60;
	const int rangeOffsetY = 24;

	TGump *gump = (TGump*)GumpManager->m_Items;

	while (gump != NULL)
	{
		if (gump != this && gump->GumpType == GT_STATUSBAR && gump->Minimized)
		{
			int gumpX = gump->MinimizedX;
			int offsetX = abs(x - gumpX);
			int passed = 0;
			
			if (x >= gumpX && x <= (gumpX + 154))
				passed = 2;
			else if (offsetX < rangeOffsetX) //left part of gump
				passed = 1;
			else
			{
				offsetX = abs(x - (gumpX + 154));

				if (offsetX < rangeOffsetX) //right part of gump
					passed = -1;
				else if (x >= (gumpX - rangeX) && x <= (gumpX + 154 + rangeX))
					passed = 2;
			}

			int gumpY = gump->MinimizedY;

			if (abs(passed) == 1)
			{
				if (y < (gumpY - rangeY) || y > (gumpY + 59 + rangeY))
					passed = 0;
			}
			else if (passed == 2) //in gump range X
			{
				int offsetY = abs(y - gumpY);

				if (offsetY < rangeOffsetY) //top part of gump
					passed = 2;
				else
				{
					offsetY = abs(y - (gumpY + 59));

					if (offsetY < rangeOffsetY) //bottom part of gump
						passed = -2;
					else
						passed = 0;
				}
			}

			if (passed)
			{
				int testX = gumpX;
				int testY = gumpY;

				switch (passed)
				{
					case -2: //gump bottom
					{
						testY += 59;
						break;
					}
					case -1: //gump right
					{
						testX += 154;
						break;
					}
					case 1: //gump left
					{
						testX -= 154;
						break;
					}
					case 2: //gump top
					{
						testY -= 59;
						break;
					}
					default:
						break;
				}

				TGump *testGump = (TGump*)GumpManager->m_Items;

				while (testGump != NULL)
				{
					if (testGump != this && testGump->GumpType == GT_STATUSBAR && testGump->Minimized)
					{
						if (testGump->MinimizedX == testX && testGump->MinimizedY == testY)
							break;
					}

					testGump = (TGump*)testGump->m_Next;
				}

				if (testGump == NULL)
				{
					x = testX;
					y = testY;

					break;
				}
			}
		}

		gump = (TGump*)gump->m_Next;
	}

	return (TGumpStatusbar*)gump;
}
//---------------------------------------------------------------------------
bool TGumpStatusbar::GetStatusbarGroupOffset(int &x, int &y)
{
	if (InGroup() && Minimized && g_LeftMouseDown && !g_LastObjectLeftMouseDown)
	{
		TGumpStatusbar *gump = GetTopStatusbar();

		while (gump != NULL)
		{
			//���� ���� ��������� � (����� ����) �������
			if (gump != this && g_LastGumpLeftMouseDown == (DWORD)gump)
			{
				x += g_MouseX - g_DroppedLeftMouseX;
				y += g_MouseY - g_DroppedLeftMouseY;

				return true;
			}

			gump = gump->m_GroupNext;
		}
	}

	return false;
}
//---------------------------------------------------------------------------
void TGumpStatusbar::UpdateGroup(int x, int y)
{
	if (!InGroup())
		return;

	TGumpStatusbar *gump = GetTopStatusbar();

	while (gump != NULL)
	{
		if (gump != this)
		{
			gump->AddMinimizedX(x);
			gump->AddMinimizedY(y);

			GumpManager->MoveToBack(gump);
			gump->GenerateFrame(gump->MinimizedX, gump->MinimizedY);
		}

		gump = gump->m_GroupNext;
	}

	GumpManager->MoveToBack(this);
}
//---------------------------------------------------------------------------
void TGumpStatusbar::AddStatusbar(TGumpStatusbar *bar)
{
	if (m_GroupNext == NULL)
	{
		m_GroupNext = bar;
		bar->m_GroupPrev = this;
		bar->m_GroupNext = NULL;
	}
	else
	{
		TGumpStatusbar *gump = m_GroupNext;

		while (gump != NULL && gump->m_GroupNext != NULL)
			gump = gump->m_GroupNext;

		gump->m_GroupNext = bar;
		bar->m_GroupPrev = gump;
		bar->m_GroupNext = NULL;
	}

	UpdateFrame();
}
//---------------------------------------------------------------------------
void TGumpStatusbar::RemoveFromGroup()
{
	if (m_GroupNext != NULL)
		m_GroupNext->m_GroupPrev = m_GroupPrev;
	
	if (m_GroupPrev != NULL)
		m_GroupPrev->m_GroupNext = m_GroupNext;

	m_GroupNext = NULL;
	m_GroupPrev = NULL;
}
//---------------------------------------------------------------------------
void TGumpStatusbar::PrepareTextures()
{
	UO->ExecuteGumpPart(0x0802, 8);
}
//---------------------------------------------------------------------------
void TGumpStatusbar::GenerateFrame(int posX, int posY)
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

	//����� �� ���� ����� �������?
	int CanPressedButton = 0;
	if (IsPressed && g_LastObjectLeftMouseDown == g_LastSelectedObject)
		CanPressedButton = g_LastObjectLeftMouseDown;

	glNewList((GLuint)index, GL_COMPILE);

	if (Serial == g_PlayerSerial) //���� ��� ��������� ������
	{
		if (!Minimized) //���� ��� "������" ������ ����������
		{
			UO->DrawGump(0x0802, 0, posX, posY); //���� ����������

			//�������� ��� ������
			if (g_Player->GetName().length())
				FontManager->DrawA(1, g_Player->GetName().c_str(), 0x0386, posX + 86, posY + 42);

			//��������� ������ �������������, �������������� �� ����...

			char text[30] = {0};
			sprintf(text, "%d", g_Player->Str);
			FontManager->DrawA(1, text, 0x0386, posX + 86, posY + 61);
				
			sprintf(text, "%d", g_Player->Dex);
			FontManager->DrawA(1, text, 0x0386, posX + 86, posY + 73);
				
			sprintf(text, "%d", g_Player->Int);
			FontManager->DrawA(1, text, 0x0386, posX + 86, posY + 85);
				
			sprintf(text, "%s", (g_Player->Sex ? "F" : "M"));
			FontManager->DrawA(1, text, 0x0386, posX + 86, posY + 97);
				
			sprintf(text, "%d", g_Player->Armor);
			FontManager->DrawA(1, text, 0x0386, posX + 86, posY + 109);

			sprintf(text, "%d/%d", g_Player->Hits, g_Player->MaxHits);
			FontManager->DrawA(1, text, 0x0386, posX + 171, posY + 61);
				
			sprintf(text, "%d/%d", g_Player->Mana, g_Player->MaxMana);
			FontManager->DrawA(1, text, 0x0386, posX + 171, posY + 73);
				
			sprintf(text, "%d/%d", g_Player->Stam, g_Player->MaxStam);
			FontManager->DrawA(1, text, 0x0386, posX + 171, posY + 85);
				
			sprintf(text, "%d", g_Player->Gold);
			FontManager->DrawA(1, text, 0x0386, posX + 171, posY + 97);
				
			sprintf(text, "%d", g_Player->Weight);
			FontManager->DrawA(1, text, 0x0386, posX + 171, posY + 109);
		}
		else //��� ����������� ����� ���������� (� ���������)
		{
			if (Party.Leader != 0) //inParty
			{
				FontManager->DrawA(3, "[* SELF *]", 0x0481, posX + 16, posY - 2);

				WORD gumpID = 0x0938 + (CanPressedButton == ID_GSB_BUTTON_HEAL_1 ? 2 : 0);
				UO->DrawGump(gumpID, 0, posX + 16, posY + 20);

				gumpID = 0x0939 + (int)(CanPressedButton == ID_GSB_BUTTON_HEAL_2);
				UO->DrawGump(gumpID, 0, posX + 16, posY + 33);

				//Hits
				UO->DrawGump(0x0028, 0, posX + 34, posY + 20);

				int per = CalculatePercents(g_Player->MaxHits, g_Player->Hits, 96);
				if (per > 0)
					UO->DrawGump(0x0029, 0, posX + 34, posY + 20, per, 0);
				
				//Mana
				UO->DrawGump(0x0028, 0, posX + 34, posY + 33);

				per = CalculatePercents(g_Player->MaxMana, g_Player->Mana, 96);
				if (per > 0)
					UO->DrawGump(0x0029, 0x0482, posX + 34, posY + 33, per, 0); //0x0170 green //0x0035 yellow
				
				//Stam
				UO->DrawGump(0x0028, 0, posX + 34, posY + 45);

				per = CalculatePercents(g_Player->MaxStam, g_Player->Stam, 96);
				if (per > 0)
					UO->DrawGump(0x0029, 0x0075, posX + 34, posY + 45, per, 0);
			}
			else
			{
				WORD gumpid = 0x0803; //���� ����������
				if (g_Player->Warmode)
					gumpid = 0x0807; //������ � ���������� ��������
				UO->DrawGump(gumpid, 0, posX, posY);
			
				//Hits
				UO->DrawGump(0x0805, 0, posX + 34, posY + 12);

				int per = CalculatePercents(g_Player->MaxHits, g_Player->Hits, 109);
				if (per > 0)
				{
					gumpid = 0x0806; //Character status line (blue)
					if (g_Player->Poisoned())
						gumpid = 0x0808; //Character status line (green)
					else if (g_Player->YellowHits())
						gumpid = 0x0809; //Character status line (yellow)
				
					UO->DrawGump(gumpid, 0, posX + 34, posY + 12, per, 0);
				}
				
				//Mana
				UO->DrawGump(0x0805, 0, posX + 34, posY + 25);

				per = CalculatePercents(g_Player->MaxMana, g_Player->Mana, 109);
				if (per > 0)
					UO->DrawGump(0x0806, 0, posX + 34, posY + 25, per, 0);
				
				//Stam
				UO->DrawGump(0x0805, 0, posX + 34, posY + 38);

				per = CalculatePercents(g_Player->MaxStam, g_Player->Stam, 109);
				if (per > 0)
					UO->DrawGump(0x0806, 0, posX + 34, posY + 38, per, 0);
			}
			
			if (InGroup())
				UO->DrawGump(0x082C, 0, posX + 136, posY + 24);
		}
	}
	else //����� ���������
	{
		if (Party.Contains(Serial))
		{
			IFOR(i, 0, 10)
			{
				if (Party.Member[i].Serial == Serial)
				{
					TPartyObject &member = Party.Member[i];
					
					//��������� ���� ����������
					WORD color = ConfigManager.GetColorByNotoriety(member.Notoriety);
					string memberName = member.GetName(0);

					if (member.CanChangeName) //���� ����� ����� �������� ��� ��������
					{
						if (TextEntry != EntryPointer && !TextEntry->Length())
							TextEntry->SetText(memberName);

						TextEntry->DrawA(1, 0x000E, posX + 16, posY - 2, TS_LEFT, UOFONT_FIXED);
					}
					else if (memberName.length())
						FontManager->DrawA(1, memberName.c_str(), 0x0386, posX + 16, posY - 2);
					else if (TextEntry->Length())
						TextEntry->DrawA(1, 0x0386, posX + 16, posY - 2, TS_LEFT, UOFONT_FIXED);
		
					WORD gumpID = 0x0938 + (CanPressedButton == ID_GSB_BUTTON_HEAL_1 ? 2 : 0);
					UO->DrawGump(gumpID, 0, posX + 16, posY + 20);

					gumpID = 0x0939 + (int)(CanPressedButton == ID_GSB_BUTTON_HEAL_2);
					UO->DrawGump(gumpID, 0, posX + 16, posY + 33);

					//Hits
					UO->DrawGump(0x0028, 0, posX + 34, posY + 20);

					int per = CalculatePercents(member.MaxHits, member.Hits, 96);
					if (per > 0)
						UO->DrawGump(0x0029, 0, posX + 34, posY + 20, per, 0);
				
					//Mana
					UO->DrawGump(0x0028, 0, posX + 34, posY + 33);

					per = CalculatePercents(member.MaxMana, member.Mana, 96);
					if (per > 0)
						UO->DrawGump(0x0029, 0x0482, posX + 34, posY + 33, per, 0); //0x0170 green //0x0035 yellow
				
					//Stam
					UO->DrawGump(0x0028, 0, posX + 34, posY + 45);
					
					per = CalculatePercents(member.MaxStam, member.Stam, 96);
					if (per > 0)
						UO->DrawGump(0x0029, 0x0075, posX + 34, posY + 45, per, 0);

					break;
				}
			}
		}
		else
		{
			TGameCharacter *obj = World->FindWorldCharacter(Serial);
			if (obj != NULL)
			{
				//��������� ���� ����������
				WORD color = ConfigManager.GetColorByNotoriety(obj->Notoriety);

				if (obj->Notoriety == NT_CRIMINAL || obj->Notoriety == NT_SOMEONE_GRAY)
					color = 0;

				ColorizerShader->Use();

				//���� ������ ����
				UO->DrawGump(0x0804, color, posX, posY);

				UnuseShader();

				string objName = obj->GetName();

				if (obj->CanChangeName) //���� ����� ����� �������� ��� ��������
				{
					if (TextEntry != EntryPointer && !TextEntry->Length())
						TextEntry->SetText(objName);

					TextEntry->DrawA(1, 0x000E, posX + 16, posY + 14, TS_LEFT, UOFONT_FIXED);
				}
				else if (objName.length())
					FontManager->DrawA(1, objName.c_str(), 0x0386, posX + 16, posY + 14, 150, TS_LEFT, UOFONT_FIXED);
				else if (TextEntry->Length())
					TextEntry->DrawA(1, 0x0386, posX + 16, posY + 14, TS_LEFT, UOFONT_FIXED);
				
				//Hits
				UO->DrawGump(0x0805, 0, posX + 34, posY + 38);
				
				int per = CalculatePercents(obj->MaxHits, obj->Hits, 109);
				if (per > 0)
				{
					WORD gumpid = 0x0806; //Character status line (blue)
					if (obj->Poisoned())
						gumpid = 0x0808; //Character status line (green)
					else if (obj->YellowHits())
						gumpid = 0x0809; //Character status line (yellow)

					UO->DrawGump(gumpid, 0, posX + 34, posY + 38, per, 0);
				}
			}
			else //��������� ������
			{
				ColorizerShader->Use();

				//���� ������ ����
				UO->DrawGump(0x0804, 0x0386, posX, posY);

				//Hits
				UO->DrawGump(0x0805, 0x0386, posX + 34, posY + 38);
				
				UnuseShader();

				TextEntry->DrawA(1, 0x0386, posX + 16, posY + 14, TS_LEFT, UOFONT_FIXED);
			}
		}

		if (InGroup())
			UO->DrawGump(0x082C, 0, posX + 136, posY + 24);
	}

	glEndList();
	FrameCreated = true;
}
//----------------------------------------------------------------------------
int TGumpStatusbar::Draw(bool &mode)
{
	DWORD index = (DWORD)this;

	//��� �������� �������
	int posX = X;
	int posY = Y;

	if (Minimized) //��� ���������������� ������ ������ ����������
	{
		posX = MinimizedX;
		posY = MinimizedY;
	}

	//������ �� ������ � ����?
	bool IsPressed = (g_LeftMouseDown && g_LastGumpLeftMouseDown == index && g_LastSelectedGump == index);

	//����� �� ���� ����� �������?
	int CanPressedButton = 0;
	if (IsPressed && g_LastObjectLeftMouseDown == g_LastSelectedObject)
		CanPressedButton = g_LastObjectLeftMouseDown;

	//���� ���� ��������� � (����� ����) �������
	if (CanBeMoved() && g_LeftMouseDown && g_LastGumpLeftMouseDown == index && !g_LastObjectLeftMouseDown)
	{
		int offsetX = g_MouseX - g_DroppedLeftMouseX;
		if (offsetX && Target.IsTargeting())
			g_GeneratedMouseDown = true;

		int offsetY = g_MouseY - g_DroppedLeftMouseY;
		if (offsetY && Target.IsTargeting())
			g_GeneratedMouseDown = true;

		if (InGroup())
		{
			posX += offsetX;
			posY += offsetY;
		}
		else
		{
			int testX = g_MouseX;
			int testY = g_MouseY;

			if (GetNearStatusbar(testX, testY) != NULL)
			{
				posX = testX;
				posY = testY;
			}
			else
			{
				posX += offsetX;
				posY += offsetY;
			}
		}

		//���� ����� (�, ������ �����, ������) ���� ������������
		if (mode)
			GenerateFrame(posX, posY);
	}
	else if (mode)
	{
		if (GetStatusbarGroupOffset(posX, posY) || CanPressedButton != 0)
			GenerateFrame(posX, posY);
		else if (FrameRedraw)
		{
			GenerateFrame(posX, posY);
			FrameRedraw = false;
		}
	}
	else if (GetStatusbarGroupOffset(posX, posY))
		GenerateFrame(posX, posY);

	if (mode) //���������
	{
		//���� ������ ����������� �� ��� ������ - ������� ���
		if (!FrameCreated)
			GenerateFrame(posX, posY);

		//������ ������� ������������� ������ �����������
		//GenerateFrame(posX, posY);
		glCallList((GLuint)index);

		DrawLocker(posX, posY);
	}
	else //����� ��������
	{
		int LSG = 0;

		if (Serial == g_PlayerSerial) //���� ��� ������
		{
			if (!Minimized) //������ ������
			{
				if (UO->GumpPixelsInXY(0x0802, posX, posY))
				{
					g_LastSelectedObject = 0;
					g_LastSelectedGump = index;
				}

				//������ �����������
				RECT rc = {0, 0, 16, 16};
				POINT p = {g_MouseX - (posX + 244), g_MouseY - (posY + 112)};

				if (PtInRect(&rc, p))
					LSG = ID_GSB_MINIMIZE;
			}
			else //���������������� ���� (� ���������)
			{
				if (UO->GumpPixelsInXY(0x0803, posX, posY))
				{
					g_LastSelectedObject = 0;
					g_LastSelectedGump = index;

					if (Party.Leader != 0) //inParty
					{
						if (UO->GumpPixelsInXY(0x0938, posX + 16, posY + 20))
							LSG = ID_GSB_BUTTON_HEAL_1;
						else if (UO->GumpPixelsInXY(0x0938, posX + 16, posY + 33))
							LSG = ID_GSB_BUTTON_HEAL_2;
					}

					if (InGroup() && UO->GumpPixelsInXY(0x082C, posX + 136, posY + 24))
							LSG = ID_GSB_BUTTON_REMOVE_FROM_GROUP;
				}
			}
		}
		else //����� ����
		{
			if (UO->GumpPixelsInXY(0x0804, posX, posY))
			{
				g_LastSelectedObject = 0;
				g_LastSelectedGump = index;
				g_StatusbarUnderMouse = index;

				if (Party.Contains(Serial))
				{
					if (UO->GumpPixelsInXY(0x0938,posX + 16, posY + 20))
						LSG = ID_GSB_BUTTON_HEAL_1;
					else if (UO->GumpPixelsInXY(0x0938,posX + 16, posY + 33))
						LSG = ID_GSB_BUTTON_HEAL_2;
					
					TGameCharacter *obj = World->FindWorldCharacter(Serial);

					if (obj != NULL && obj->CanChangeName && TextEntry != NULL)
					{
						//��� ��������� �����
						RECT rc = {0, 0, 109, 16};
						POINT p = {g_MouseX - (posX + 16), g_MouseY - (posY - 2)};

						if (PtInRect(&rc, p))
							LSG = ID_GSB_TEXT_FIELD;
					}
				}
				else
				{
					TGameCharacter *obj = World->FindWorldCharacter(Serial);

					if (obj != NULL && obj->CanChangeName && TextEntry != NULL)
					{
						//��� ��������� �����
						RECT rc = {0, 0, 109, 16};
						POINT p = {g_MouseX - (posX + 16), g_MouseY - (posY + 14)};

						if (PtInRect(&rc, p))
							LSG = ID_GSB_TEXT_FIELD;
					}
				}

				if (InGroup() && UO->GumpPixelsInXY(0x082C, posX + 136, posY + 24))
						LSG = ID_GSB_BUTTON_REMOVE_FROM_GROUP;
			}
		}

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
void TGumpStatusbar::OnLeftMouseDown()
{
	if (g_GeneratedMouseDown)
		return;

	if (!g_LastObjectLeftMouseDown)
	{
		//��������, ����� ���� ���� ������, ������� ����� �������� �� ������� ����
		if (Target.IsTargeting())
		{
			Target.SendTargetObject(Serial);
			g_CancelDoubleClick = true;
		}
	}
}
//----------------------------------------------------------------------------
void TGumpStatusbar::OnLeftMouseUp()
{
	if (g_GeneratedMouseDown)
		return;

	if (g_LastObjectLeftMouseDown == ID_GSB_MINIMIZE && Serial == g_PlayerSerial)
	{
		//������ ����������� �� ������ ������ �����
		Minimized = true;
		GenerateFrame(MinimizedX, MinimizedY);
	}
	else if (g_LastObjectLeftMouseDown == ID_GSB_LOCK_MOVING)
	{
		LockMoving = !LockMoving;
		g_CancelDoubleClick = true;
	}
	else if (g_LastObjectLeftMouseDown == ID_GSB_TEXT_FIELD && Serial != g_PlayerSerial)
	{
		int bonusY = 14;

		if (Party.Contains(Serial))
			bonusY = -2;

		int x = g_MouseX - (MinimizedX + 16);
		int y = g_MouseY - (MinimizedY + bonusY);

		TextEntry->OnClick(this, 1, false, x, y, TS_LEFT, UOFONT_FIXED);
	}
	else if (g_LastObjectLeftMouseDown == ID_GSB_BUTTON_HEAL_1)
	{
		UO->CastSpell(29);
		g_PartyHelperTimer = GetTickCount() + 500;
		g_PartyHelperTarget = Serial;
		g_CancelDoubleClick = true;
		UpdateFrame();
	}
	else if (g_LastObjectLeftMouseDown == ID_GSB_BUTTON_HEAL_2)
	{
		UO->CastSpell(11);
		g_PartyHelperTimer = GetTickCount() + 500;
		g_PartyHelperTarget = Serial;
		g_CancelDoubleClick = true;
		UpdateFrame();
	}
	else if (g_LastObjectLeftMouseDown == ID_GSB_BUTTON_REMOVE_FROM_GROUP)
	{
		TGumpStatusbar *oldGroup = m_GroupNext;

		if (oldGroup == NULL)
			oldGroup = m_GroupPrev;

		RemoveFromGroup();
		UpdateFrame();

		if (oldGroup != NULL)
		{
			oldGroup->UpdateGroup(0, 0);
			oldGroup->UpdateFrame();
		}
	}
	else if (!g_LastObjectLeftMouseDown)
	{
		//��������, ����� ���� ���� ������, ������� ����� �������� �� ������� ����
		/*if (Target.IsTargeting())
			Target.SendTargetObject(Serial);*/
	}
}
//----------------------------------------------------------------------------
bool TGumpStatusbar::OnLeftMouseDoubleClick()
{
	if (g_GeneratedMouseDown)
		return false;

	DWORD serial = Serial;

	if (!g_LastObjectLeftMouseDown && serial == g_PlayerSerial && Minimized)
	{
		//���� ��� ��������� ������ (� ���������) �� ��������� ��� �� ������ ������
		Minimized = false;

		if (InGroup())
		{
			TGumpStatusbar *oldGroup = m_GroupNext;

			if (oldGroup == NULL)
				oldGroup = m_GroupPrev;

			RemoveFromGroup();

			if (oldGroup != NULL)
			{
				oldGroup->UpdateGroup(0, 0);
				oldGroup->UpdateFrame();
			}
		}

		UpdateFrame();

		return true;
	}
	else if (serial != g_PlayerSerial)
	{
		if (g_Player->Warmode)
			UO->Attack(serial); //���� � ������� - �������
		else
			UO->DoubleClick(serial); //��� ���������� �������

		return true;
	}
	else if (!Minimized)
	{
		//�� ��������� �� ������ ������ ���������� ������ ����������� ���������
		UO->PaperdollReq(serial);

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------
void TGumpStatusbar::OnCharPress(WPARAM &wparam, LPARAM &lparam)
{
	if (wparam == VK_RETURN || wparam == VK_BACK || wparam == VK_ESCAPE || EntryPointer == NULL)
		return; //Ignore no print keys

	wchar_t wstr[2] = {0};
	wstr[0] = wparam;

	wstring str(wstr);
	if (!str.length())
		return;

	//��������� ����� ��������
	if (Serial != g_PlayerSerial) //������ ����� ����������
	{
		if ((EntryPointer->Length() <= 15) && FontManager->GetWidthA(1, TextEntry->c_str(), TextEntry->Pos()) <= 100 && ((wparam >= 'a' && wparam <= 'z') || (wparam >= 'A' && wparam <= 'Z')))
		{
			EntryPointer->Insert(wparam);
			GenerateFrame(X, Y);
		}
	}
}
//----------------------------------------------------------------------------
void TGumpStatusbar::OnKeyPress(WPARAM &wparam, LPARAM &lparam)
{
	switch (wparam)
	{
		case VK_RETURN:
		{
			//���� �� �������� - �������� ���
			if (EntryPointer->Length())
				SendRenameRequest();
			else //������ �������� ��� �� ������
			{
				TGameObject *obj = World->FindWorldObject(Serial);
				if (obj != NULL)
					EntryPointer->SetText(obj->GetName());
			}

			if (ConfigManager.GetConsoleNeedEnter())
				EntryPointer = NULL;
			else
				EntryPointer = GameConsole;

			GenerateFrame(X, Y); //����������

			break;
		}
		case VK_HOME:
		{
			EntryPointer->SetPos(0);
			GenerateFrame(X, Y);

			break;
		}
		case VK_END:
		{
			EntryPointer->SetPos(EntryPointer->Length());
			GenerateFrame(X, Y);

			break;
		}
		case VK_LEFT:
		{
			EntryPointer->AddPos(-1);
			GenerateFrame(X, Y);

			break;
		}
		case VK_RIGHT:
		{
			EntryPointer->AddPos(1);
			GenerateFrame(X, Y);

			break;
		}
		case VK_BACK:
		{
			EntryPointer->Remove(true);
			GenerateFrame(X, Y);

			break;
		}
		case VK_DELETE:
		{
			EntryPointer->Remove(false);
			GenerateFrame(X, Y);

			break;
		}
		case VK_ESCAPE:
		{
			//�� ���� �� Esc ����� ����� �� �������������� ����� ��������

			TGameObject *obj = World->FindWorldObject(Serial);
			if (obj != NULL)
				EntryPointer->SetText(obj->GetName());

			if (ConfigManager.GetConsoleNeedEnter())
				EntryPointer = NULL;
			else
				EntryPointer = GameConsole;

			GenerateFrame(X, Y); //����������

			break;
		}
		default:
			break;
	}
}
//----------------------------------------------------------------------------