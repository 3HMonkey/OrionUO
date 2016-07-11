/****************************************************************************
**
** EntryText.cpp
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

TEntryText *EntryPointer = NULL;
//---------------------------------------------------------------------------
TEntryText::TEntryText(int maxLength, int width, int maxWidth, bool numberOnly)
: m_MaxLength(maxLength), m_Position(0), m_Changed(true), m_DrawOffset(0),
m_Width(width), m_MaxWidth(maxWidth), m_Color(0), m_NumberOnly(numberOnly)
{
	m_Text = L"";
	m_CText = "";
	memset(&m_CaretPos, 0, sizeof(m_CaretPos));
}
//---------------------------------------------------------------------------
TEntryText::~TEntryText()
{
	//���� ��������� ���� - ������� �� �������� ������� �������� �������
	if (g_GameState >= GS_GAME && EntryPointer == this)
	{
		if (ConfigManager.GetConsoleNeedEnter())
			EntryPointer = NULL;
		else
			EntryPointer = GameConsole;
	}

	//������� ������
	Clear();
}
//---------------------------------------------------------------------------
//���������� ��� ����� �� ��������� ���� (���� ��� ������������� � �����������)
const char *TEntryText::c_str()
{
	m_CText = ToString(m_Text);
	return m_CText.c_str();
}
//---------------------------------------------------------------------------
//���������� ��� ����� �� ��������� ���� (���� ��� ������������� � �����������)
void TEntryText::OnClick(TGump *gump, BYTE font, bool unicode, int x, int y, TEXT_ALIGN_TYPE align, WORD flags)
{
	//��������� ���� - ������� ���� �����
	if (EntryPointer == this)
	{
		//�������� �������
		int oldPos = m_Position;

		//�������� ����� ������� �������� ���� ������
		if (unicode)
			m_Position = FontManager->CalculateCaretPosW(font, m_Text.c_str(), x, y, m_Width, align, flags);
		else
			m_Position = FontManager->CalculateCaretPosA(font, c_str(), x, y, m_Width, align, flags);

		//���� ������� ���������� - ������ ��� ����� �������
		if (oldPos != m_Position)
			m_Changed = true;
	}
	else //����� ������� ������� ���� ��� ���� ��� �����
	{
		//������� ���� � ���������� ���������� �����
		TGump *gumpEntry = GumpManager->GetTextEntryOwner();

		//���� ���� ������ - ������� ���� �����
		if (gumpEntry != NULL)
			gumpEntry->FrameCreated = false;

		//������� ���������
		EntryPointer = this;
	}

	//���� ��� ����� ����� - ������� ���
	if (gump != NULL)
		gump->FrameCreated = false;
}
//---------------------------------------------------------------------------
//���������� ��� ��������� ������� �������
void TEntryText::OnKey(TGump *gump, WPARAM wParam)
{
	switch (wParam)
	{
		case VK_HOME:
		{
			SetPos(0, gump);

			break;
		}
		case VK_END:
		{
			SetPos(Length(), gump);

			break;
		}
		case VK_LEFT:
		{
			AddPos(-1, gump);

			break;
		}
		case VK_RIGHT:
		{
			AddPos(1, gump);

			break;
		}
		case VK_BACK:
		{
			Remove(true, gump);

			break;
		}
		case VK_DELETE:
		{
			Remove(false, gump);

			break;
		}
		default:
			break;
	}
}
//---------------------------------------------------------------------------
//�������� ���������� �����
int TEntryText::GetLinesCountA(BYTE font, TEXT_ALIGN_TYPE align, WORD flags, int width)
{
	if (!width)
		width = m_Width;

	MULTILINES_FONT_INFO *info = FontManager->GetInfoA(font, c_str(), Length(), align, flags, width);

	int count = 0;

	while (info != NULL)
	{
		MULTILINES_FONT_INFO *next = info->m_Next;
		delete info;
		info = next;
		count++;
	}

	return count;
}
//---------------------------------------------------------------------------
//�������� ���������� �����
int TEntryText::GetLinesCountW(BYTE font, TEXT_ALIGN_TYPE align, WORD flags, int width)
{
	if (!width)
		width = m_Width;

	MULTILINES_FONT_INFO *info = FontManager->GetInfoW(font, Data(), Length(), align, flags, width);

	int count = 0;

	while (info != NULL)
	{
		MULTILINES_FONT_INFO *next = info->m_Next;
		delete info;
		info = next;
		count++;
	}

	return count;
}
//---------------------------------------------------------------------------
//�������� ������ ������������ m_Position
bool TEntryText::Insert(wchar_t ch, TGump *gump)
{
	//��������� �������
	if (m_Position < 0)
		m_Position = 0;

	//��������� �������
	if (m_Position > (int)m_Text.length())
		m_Position = m_Text.length();

	//���� ������������ ������ ������
	if (m_MaxLength > 0)
	{
		//���� ��� �������� ���� ��� �����
		if (m_NumberOnly)
		{
			wstring wstr = m_Text;
			wstr.insert(wstr.begin() + m_Position, ch);
			string str = ToString(wstr);

			if (std::atoi(str.c_str()) >= m_MaxLength) //������ ������������ ��������
				return false;
		}
		else if ((int)m_Text.length() >= m_MaxLength) //����� - ������ ����� � ������������
			return false;
	}

	//����� ����������� ���� �������� � ��������� - ��������� ������ � ��������� �������
	m_Text.insert(m_Text.begin() + m_Position, ch);

	//����������� ������ �������
	m_Position++;

	//��������� �������
	m_Changed = true;

	//��������� ���� (���� ����)
	if (gump != NULL)
		gump->FrameCreated = false;

	return true;
}
//---------------------------------------------------------------------------
//������� ������ ������������ m_Position (true - �����, false - ������)
void TEntryText::Remove(bool left, TGump *gump)
{
	//������ Backspace
	if (left)
	{
		//������� ������
		if (m_Position < 1)
			return;

		m_Position--;
	}
	else //��� ������ Delete
	{
		//��� � ����� ������
		if (m_Position >= (int)m_Text.length())
			return;
	}

	//������� ��������� ������
	m_Text.erase(m_Text.begin() + m_Position);

	//������������ ���������
	m_Changed = true;

	//��������� ���� (���� ����)
	if (gump != NULL)
		gump->FrameCreated = false;
}
//---------------------------------------------------------------------------
/*!
�������� ������
@return 
*/
void TEntryText::Clear()
{
	//�������
	m_Text = L"";
	m_CText = "";
	m_Position = 0;
	m_Changed = true;
	m_DrawOffset = 0;
	m_Texture.Clear();
	memset(&m_CaretPos, 0, sizeof(m_CaretPos));
}
//---------------------------------------------------------------------------
//��������� ������� m_Position
void TEntryText::AddPos(int val, TGump *gump)
{
	//��������� (��������) �������
	m_Position += val;

	//�������������
	if (m_Position < 0)
		m_Position = 0;

	//�������������
	if (m_Position > (int)m_Text.length())
		m_Position = m_Text.length();
	
	//������������ ���������
	m_Changed = true;

	//��������� ���� (���� ����)
	if (gump != NULL)
		gump->FrameCreated = false;
}
//---------------------------------------------------------------------------
//��������� ������� m_Position
void TEntryText::SetPos(int val, TGump *gump)
{
	//���������� ��������� �������
	m_Position = val;

	//�������������
	if (m_Position < 0)
		m_Position = 0;

	//�������������
	if (m_Position > (int)m_Text.length())
		m_Position = m_Text.length();
	
	//������������ ���������
	m_Changed = true;

	//��������� ���� (���� ����)
	if (gump != NULL)
		gump->FrameCreated = false;
}
//---------------------------------------------------------------------------
//��������� ������
void TEntryText::SetText(const string &text)
{
	//������� ASCII � ������ ������
	wstring wtext = ToWString(text);

	//����������� ��������� ��������� ������
	SetText(wtext);
}
//---------------------------------------------------------------------------
//��������� ������
void TEntryText::SetText(const wstring &text)
{
	//������� ����� ����������
	Clear();

	//������� ����� � �������� ��������� � ����� ������
	m_Text = text;
	m_Position = m_Text.length() - 1;

	if (m_Position < 0)
		m_Position = 0;

	//���� ������� ������������ �����
	if (m_MaxLength > 0)
	{
		//���� ��� �������� ���� ��� �����
		if (m_NumberOnly)
		{
			string str = ToString(m_Text);

			//���� ������ �� ������ � �������� ������ ����������� - ������� �� 1 ������� �����
			while (true)
			{
				int len = str.length();

				if (std::atoi(str.c_str()) >= m_MaxLength && len > 0)
					str.resize(len - 1);
				else
					break;
			}
		}
		else if ((int)m_Text.length() >= m_MaxLength) //����� - ������ �����
			m_Text.resize(m_MaxLength);
	}

	//������� ���� (���� ����)
	if (GumpManager != NULL)
	{
		TGump *gump = GumpManager->GetTextEntryOwner();

		if (gump != NULL)
			gump->FrameCreated = false;
	}
}
//---------------------------------------------------------------------------
//�������� ������ ������ � ������������� �������� ������ (��� �������������)
string TEntryText::CheckMaxWidthA(BYTE font, string str)
{
	//���� ������ ������������ ������
	if (m_MaxWidth > 0)
	{
		//�������� ������� ������
		int width = FontManager->GetWidthA(font, str.c_str(), 0);
		int len = str.length();

		//� ���� ������ �� ����� ��������������� ��������� ���������� - ������� ��
		while (m_MaxWidth < width && len > 0)
		{
			str.erase(str.begin() + len);
			len--;
			width = FontManager->GetWidthA(font, str.c_str(), 0);
		}
	}

	return str;
}
//---------------------------------------------------------------------------
wstring TEntryText::CheckMaxWidthW(BYTE font, wstring str)
{
	//���� ������ ������������ ������
	if (m_MaxWidth > 0)
	{
		//�������� ������� ������
		int width = FontManager->GetWidthW(font, str.c_str(), 0);
		int len = str.length();

		//� ���� ������ �� ����� ��������������� ��������� ���������� - ������� ��
		while (m_MaxWidth < width && len > 0)
		{
			str.erase(str.begin() + len);
			len--;
			width = FontManager->GetWidthW(font, str.c_str(), 0);
		}
	}

	return str;
}
//---------------------------------------------------------------------------
void TEntryText::FixMaxWidthA(BYTE font)
{
	c_str();

	//���� ������ ������������ ������
	if (m_MaxWidth > 0)
	{
		//�������� ������� ������
		int width = FontManager->GetWidthA(font, m_CText.c_str(), 0);
		int len = m_CText.length();

		//� ���� ������ �� ����� ��������������� ��������� ���������� - ������� ��
		while (m_MaxWidth < width && len > 0)
		{
			Remove((m_Position > 0), NULL);
			len--;
			width = FontManager->GetWidthA(font, c_str(), 0);
		}
	}
}
//---------------------------------------------------------------------------
void TEntryText::FixMaxWidthW(BYTE font)
{
	//���� ������ ������������ ������
	if (m_MaxWidth > 0)
	{
		//�������� ������� ������
		int width = FontManager->GetWidthW(font, m_Text.c_str(), 0);
		int len = m_Text.length();

		//� ���� ������ �� ����� ��������������� ��������� ���������� - ������� ��
		while (m_MaxWidth < width && len > 0)
		{
			Remove((m_Position > 0), NULL);
			len--;
			width = FontManager->GetWidthW(font, m_Text.c_str(), 0);
		}
	}
}
//---------------------------------------------------------------------------
void TEntryText::CreateTextureA(BYTE font, string str, WORD color, int width, TEXT_ALIGN_TYPE align, WORD flags)
{
	//���� ��� ������ ������ - ������� ���
	if (!str.length())
		Clear();
	else
	{
		//������ ��������
		m_Texture.Clear();

		//��������� ������� �������
		if (m_Position)
		{
			m_CaretPos = FontManager->GetCaretPosA(font, str.c_str(), m_Position, width, align, flags);

			if (flags & UOFONT_FIXED)
			{
				if (m_DrawOffset)
				{
					if (m_CaretPos.x + m_DrawOffset < 0)
						m_DrawOffset = -m_CaretPos.x;
					else if (m_Width + -m_DrawOffset < m_CaretPos.x)
						m_DrawOffset = m_Width - m_CaretPos.x;
				}
				else if (m_Width + m_DrawOffset < m_CaretPos.x)
					m_DrawOffset = m_Width - m_CaretPos.x;
				else
					m_DrawOffset = 0;

				/*if (m_Width + m_DrawOffset < m_CaretPos.x)
					m_DrawOffset = m_Width - m_CaretPos.x;
				else
					m_DrawOffset = 0;*/
			}
		}
		else //���� �������� ��
		{
			memset(&m_CaretPos, 0, sizeof(m_CaretPos));
			m_DrawOffset = 0;
		}

		//���������� ��������
		FontManager->GenerateA(font, m_Texture, str.c_str(), color, m_Width + abs(m_DrawOffset), align, flags);
	}
}
//---------------------------------------------------------------------------
void TEntryText::CreateTextureW(BYTE font, wstring str, WORD color, int width, TEXT_ALIGN_TYPE align, WORD flags)
{
	//���� ��� ������ ������ - ������� ���
	if (!str.length())
		Clear();
	else
	{
		//������ ��������
		m_Texture.Clear();

		//��������� ������� �������
		if (m_Position)
		{
			m_CaretPos = FontManager->GetCaretPosW(font, str.c_str(), m_Position, width, align, flags);

			if (flags & UOFONT_FIXED)
			{
				if (m_DrawOffset)
				{
					if (m_CaretPos.x + m_DrawOffset < 0)
						m_DrawOffset = -m_CaretPos.x;
					else if (m_Width + -m_DrawOffset < m_CaretPos.x)
						m_DrawOffset = m_Width - m_CaretPos.x;
				}
				else if (m_Width + m_DrawOffset < m_CaretPos.x)
					m_DrawOffset = m_Width - m_CaretPos.x;
				else
					m_DrawOffset = 0;
			}
		}
		else //���� �������� ��
		{
			memset(&m_CaretPos, 0, sizeof(m_CaretPos));
			m_DrawOffset = 0;
		}

		//���������� ��������
		FontManager->GenerateW(font, m_Texture, str.c_str(), color, 30, m_Width, align, flags);
	}
}
//---------------------------------------------------------------------------
void TEntryText::DrawA(BYTE font, WORD color, int x, int y, TEXT_ALIGN_TYPE align, WORD flags)
{
	//���� ��������� ����� ��� ����
	if (m_Changed || m_Color != color)
	{
		//������� ������ �� ������������ ���������
		FixMaxWidthA(font);

		//������� ��������
		CreateTextureA(font, m_CText, color, /*m_MaxWidth*/m_Width, align, flags);

		//������������ ���������
		m_Changed = false;
		m_Color = color;
	}

	//��������� ��������
	m_Texture.Draw(x + m_DrawOffset, y);

	//���� ��� ���� ��� ����� - ��������� �������
	if (this == EntryPointer)
	{
		//������� �������� �� ��� Y
		const int offsetTable[] = {1, 2, 1, 1, 1, 2, 1, 1, 2, 2};
		int offsY = offsetTable[font % 10];

		//�������� �������
		FontManager->DrawA(font, "_", color, x + m_DrawOffset + m_CaretPos.x, y + offsY + m_CaretPos.y);
	}
}
//---------------------------------------------------------------------------
void TEntryText::DrawW(BYTE font, WORD color, int x, int y, TEXT_ALIGN_TYPE align, WORD flags)
{
	//���� ��������� ����� ��� ����
	if (m_Changed || m_Color != color)
	{
		//������� ������ �� ������������ ���������
		FixMaxWidthW(font);

		//������� ��������
		CreateTextureW(font, m_Text, color, m_Width, align, flags);

		//������������ ���������
		m_Changed = false;
		m_Color = color;
	}

	//��������� ��������
	m_Texture.Draw(x + m_DrawOffset, y);

	//���� ��� ���� ��� ����� - ��������� �������
	if (this == EntryPointer)
		FontManager->DrawW(font, L"_", color, x + m_DrawOffset + m_CaretPos.x, y + m_CaretPos.y, 30);
}
//---------------------------------------------------------------------------
void TEntryText::DrawMaskA(BYTE font, WORD color, int x, int y, TEXT_ALIGN_TYPE align, WORD flags)
{
	//����������� �� ����� ����� �� "*"
	int len = Length();
	string str = "";
	IFOR(i, 0, len)
		str += "*";

	//���� ����� ���� - �������� ���
	if (len)
		FontManager->DrawA(font, str.c_str(), color, x + m_DrawOffset, y);

	//���� ��� ���� ��� ����� - ��������� �������
	if (this == EntryPointer)
	{
		//������� �������� �� ��� Y
		const int offsetTable[] = {1, 2, 1, 1, 1, 2, 1, 1, 2, 2};
		int offsY = offsetTable[font % 10];

		//������������ ��������
		if (m_Position)
			x += FontManager->GetWidthA(font, str.c_str(), m_Position);

		//�������� �������
		FontManager->DrawA(font, "_", color, x + m_DrawOffset, y + offsY);
	}
}
//---------------------------------------------------------------------------
void TEntryText::DrawMaskW(BYTE font, WORD color, int x, int y, TEXT_ALIGN_TYPE align, WORD flags)
{
	//����������� �� ����� ����� �� "*"
	int len = Length();
	wstring str = L"";
	IFOR(i, 0, len)
		str += L"*";

	//���� ����� ���� - �������� ���
	if (len)
		FontManager->DrawW(font, str.c_str(), color, x + m_DrawOffset, y, 30, 0, TS_LEFT, flags);

	//���� ��� ���� ��� ����� - ��������� �������
	if (this == EntryPointer)
	{
		//������������ ��������
		if (m_Position)
			x += FontManager->GetWidthW(font, str.c_str(), m_Position);

		//�������� �������
		FontManager->DrawW(font, L"_", color, x + m_DrawOffset, y, 30, 0, TS_LEFT, flags);
	}
}
//---------------------------------------------------------------------------