/***********************************************************************************
**
** EntryText.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "EntryText.h"
#include "GameConsole.h"
#include "../Managers/ConfigManager.h"
#include "../Managers/FontsManager.h"
#include "../Managers/GumpManager.h"
//----------------------------------------------------------------------------------
CEntryText *g_EntryPointer = NULL;
//----------------------------------------------------------------------------------
CEntryText::CEntryText(int maxLength, int width, int maxWidth, bool numberOnly)
: m_MaxLength(maxLength), m_Position(0), m_Changed(true), m_DrawOffset(0),
m_Width(width), m_MaxWidth(maxWidth), m_Color(0), m_NumberOnly(numberOnly)
{
	m_Text = L"";
	m_CText = "";
	memset(&m_CaretPos, 0, sizeof(m_CaretPos));
}
//----------------------------------------------------------------------------------
CEntryText::~CEntryText()
{
	//���� ��������� ���� - ������� �� �������� ������� �������� �������
	if (g_EntryPointer == this)
	{
		if (g_ConfigManager.GetConsoleNeedEnter())
			g_EntryPointer = NULL;
		else
		{
			if (g_GameState >= GS_GAME)
				g_EntryPointer = &g_GameConsole;
			else
				g_EntryPointer = NULL;
		}
	}

	//������� ������
	Clear();
}
//----------------------------------------------------------------------------------
//���������� ��� ����� �� ��������� ���� (���� ��� ������������� � �����������)
const char *CEntryText::c_str()
{
	m_CText = ToString(m_Text);
	return m_CText.c_str();
}
//----------------------------------------------------------------------------------
//���������� ��� ����� �� ��������� ���� (���� ��� ������������� � �����������)
void CEntryText::OnClick(CGump *gump, uchar font, bool unicode, int x, int y, TEXT_ALIGN_TYPE align, ushort flags)
{
	//��������� ���� - ������� ���� �����
	if (g_EntryPointer == this)
	{
		//�������� �������
		int oldPos = m_Position;

		//�������� ����� ������� �������� ���� ������
		if (unicode)
			m_Position = g_FontManager.CalculateCaretPosW(font, m_Text.c_str(), x, y, m_Width, align, flags);
		else
			m_Position = g_FontManager.CalculateCaretPosA(font, c_str(), x, y, m_Width, align, flags);

		//���� ������� ���������� - ������ ��� ����� �������
		if (oldPos != m_Position)
			m_Changed = true;
	}
	else //����� ������� ������� ���� ��� ���� ��� �����
	{
		//������� ���� � ���������� ���������� �����
		CGump *gumpEntry = g_GumpManager.GetTextEntryOwner();

		//���� ���� ������ - ������� ���� �����
		if (gumpEntry != NULL)
			gumpEntry->FrameCreated = false;

		//������� ���������
		g_EntryPointer = this;
	}

	//���� ��� ����� ����� - ������� ���
	if (gump != NULL)
		gump->FrameCreated = false;
}
//----------------------------------------------------------------------------------
//���������� ��� ��������� ������� �������
void CEntryText::OnKey(CGump *gump, WPARAM wParam)
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
//----------------------------------------------------------------------------------
//�������� ���������� �����
int CEntryText::GetLinesCountA(uchar font, TEXT_ALIGN_TYPE align, ushort flags, int width)
{
	if (!width)
		width = m_Width;

	MULTILINES_FONT_INFO *info = g_FontManager.GetInfoA(font, c_str(), Length(), align, flags, width);

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
//----------------------------------------------------------------------------------
//�������� ���������� �����
int CEntryText::GetLinesCountW(uchar font, TEXT_ALIGN_TYPE align, ushort flags, int width)
{
	if (!width)
		width = m_Width;

	MULTILINES_FONT_INFO *info = g_FontManager.GetInfoW(font, Data(), Length(), align, flags, width);

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
//----------------------------------------------------------------------------------
//�������� ������ ������������ m_Position
bool CEntryText::Insert(wchar_t ch, CGump *gump)
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

			if (_wtoi(wstr.c_str()) >= m_MaxLength) //������ ������������ ��������
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
//----------------------------------------------------------------------------------
//������� ������ ������������ m_Position (true - �����, false - ������)
void CEntryText::Remove(bool left, CGump *gump)
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
//----------------------------------------------------------------------------------
/*!
�������� ������
@return 
*/
void CEntryText::Clear()
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
//----------------------------------------------------------------------------------
//��������� ������� m_Position
void CEntryText::AddPos(int val, CGump *gump)
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
//----------------------------------------------------------------------------------
//��������� ������� m_Position
void CEntryText::SetPos(int val, CGump *gump)
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
//----------------------------------------------------------------------------------
//��������� ������
void CEntryText::SetText(const string &text)
{
	//������� ASCII � ������ ������
	wstring wtext = ToWString(text);

	//����������� ��������� ��������� ������
	SetText(wtext);
}
//----------------------------------------------------------------------------------
//��������� ������
void CEntryText::SetText(const wstring &text)
{
	//������� ����� ����������
	Clear();

	//������� ����� � �������� ��������� � ����� ������
	m_Text = text;
	m_Position = m_Text.length();

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
	CGump *gump = g_GumpManager.GetTextEntryOwner();

	if (gump != NULL)
		gump->FrameCreated = false;
}
//----------------------------------------------------------------------------------
//�������� ������ ������ � ������������� �������� ������ (��� �������������)
string CEntryText::CheckMaxWidthA(uchar font, string str)
{
	//���� ������ ������������ ������
	if (m_MaxWidth > 0)
	{
		//�������� ������� ������
		int width = g_FontManager.GetWidthA(font, str.c_str(), 0);
		int len = str.length();

		//� ���� ������ �� ����� ��������������� ��������� ���������� - ������� ��
		while (m_MaxWidth < width && len > 0)
		{
			str.erase(str.begin() + len);
			len--;
			width = g_FontManager.GetWidthA(font, str.c_str(), 0);
		}
	}

	return str;
}
//----------------------------------------------------------------------------------
wstring CEntryText::CheckMaxWidthW(uchar font, wstring str)
{
	//���� ������ ������������ ������
	if (m_MaxWidth > 0)
	{
		//�������� ������� ������
		int width = g_FontManager.GetWidthW(font, str.c_str(), 0);
		int len = str.length();

		//� ���� ������ �� ����� ��������������� ��������� ���������� - ������� ��
		while (m_MaxWidth < width && len > 0)
		{
			str.erase(str.begin() + len);
			len--;
			width = g_FontManager.GetWidthW(font, str.c_str(), 0);
		}
	}

	return str;
}
//----------------------------------------------------------------------------------
void CEntryText::FixMaxWidthA(uchar font)
{
	c_str();

	//���� ������ ������������ ������
	if (m_MaxWidth > 0)
	{
		//�������� ������� ������
		int width = g_FontManager.GetWidthA(font, m_CText.c_str(), 0);
		int len = m_CText.length();

		//� ���� ������ �� ����� ��������������� ��������� ���������� - ������� ��
		while (m_MaxWidth < width && len > 0)
		{
			Remove((m_Position > 0), NULL);
			len--;
			width = g_FontManager.GetWidthA(font, c_str(), 0);
		}
	}
}
//----------------------------------------------------------------------------------
void CEntryText::FixMaxWidthW(uchar font)
{
	//���� ������ ������������ ������
	if (m_MaxWidth > 0)
	{
		//�������� ������� ������
		int width = g_FontManager.GetWidthW(font, m_Text.c_str(), 0);
		int len = m_Text.length();

		//� ���� ������ �� ����� ��������������� ��������� ���������� - ������� ��
		while (m_MaxWidth < width && len > 0)
		{
			Remove((m_Position > 0), NULL);
			len--;
			width = g_FontManager.GetWidthW(font, m_Text.c_str(), 0);
		}
	}
}
//----------------------------------------------------------------------------------
void CEntryText::CreateTextureA(uchar font, string str, ushort color, int width, TEXT_ALIGN_TYPE align, ushort flags)
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
			m_CaretPos = g_FontManager.GetCaretPosA(font, str.c_str(), m_Position, width, align, flags);

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
		g_FontManager.GenerateA(font, m_Texture, str.c_str(), color, m_Width + abs(m_DrawOffset), align, flags);
	}
}
//----------------------------------------------------------------------------------
void CEntryText::CreateTextureW(uchar font, wstring str, ushort color, int width, TEXT_ALIGN_TYPE align, ushort flags)
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
			m_CaretPos = g_FontManager.GetCaretPosW(font, str.c_str(), m_Position, width, align, flags);

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
		g_FontManager.GenerateW(font, m_Texture, str.c_str(), color, 30, m_Width, align, flags);
	}
}
//----------------------------------------------------------------------------------
void CEntryText::DrawA(uchar font, ushort color, int x, int y, TEXT_ALIGN_TYPE align, ushort flags)
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
	if (this == g_EntryPointer)
	{
		//������� �������� �� ��� Y
		const int offsetTable[] = {1, 2, 1, 1, 1, 2, 1, 1, 2, 2};
		int offsY = offsetTable[font % 10];

		//�������� �������
		g_FontManager.DrawA(font, "_", color, x + m_DrawOffset + m_CaretPos.x, y + offsY + m_CaretPos.y);
	}
}
//----------------------------------------------------------------------------------
void CEntryText::DrawW(uchar font, ushort color, int x, int y, TEXT_ALIGN_TYPE align, ushort flags)
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
	if (this == g_EntryPointer)
		g_FontManager.DrawW(font, L"_", color, x + m_DrawOffset + m_CaretPos.x, y + m_CaretPos.y, 30);
}
//----------------------------------------------------------------------------------
void CEntryText::DrawMaskA(uchar font, ushort color, int x, int y, TEXT_ALIGN_TYPE align, ushort flags)
{
	//����������� �� ����� ����� �� "*"
	int len = Length();
	string str = "";
	IFOR(i, 0, len)
		str += "*";

	//���� ����� ���� - �������� ���
	if (len)
		g_FontManager.DrawA(font, str.c_str(), color, x + m_DrawOffset, y);

	//���� ��� ���� ��� ����� - ��������� �������
	if (this == g_EntryPointer)
	{
		//������� �������� �� ��� Y
		const int offsetTable[] = {1, 2, 1, 1, 1, 2, 1, 1, 2, 2};
		int offsY = offsetTable[font % 10];

		//������������ ��������
		if (m_Position)
			x += g_FontManager.GetWidthA(font, str.c_str(), m_Position);

		//�������� �������
		g_FontManager.DrawA(font, "_", color, x + m_DrawOffset, y + offsY);
	}
}
//----------------------------------------------------------------------------------
void CEntryText::DrawMaskW(uchar font, ushort color, int x, int y, TEXT_ALIGN_TYPE align, ushort flags)
{
	//����������� �� ����� ����� �� "*"
	int len = Length();
	wstring str = L"";
	IFOR(i, 0, len)
		str += L"*";

	//���� ����� ���� - �������� ���
	if (len)
		g_FontManager.DrawW(font, str.c_str(), color, x + m_DrawOffset, y, 30, 0, TS_LEFT, flags);

	//���� ��� ���� ��� ����� - ��������� �������
	if (this == g_EntryPointer)
	{
		//������������ ��������
		if (m_Position)
			x += g_FontManager.GetWidthW(font, str.c_str(), m_Position);

		//�������� �������
		g_FontManager.DrawW(font, L"_", color, x + m_DrawOffset, y, 30, 0, TS_LEFT, flags);
	}
}
//----------------------------------------------------------------------------------
