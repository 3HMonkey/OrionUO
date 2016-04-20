/****************************************************************************
**
** ColorManager.cpp
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

TColorManager *ColorManager;
//---------------------------------------------------------------------------
TColorManager::TColorManager()
: m_HuesInt(NULL)
{
	DWORD addr = (DWORD)FileManager.HuesMul.Address;
	DWORD size = FileManager.HuesMul.Size;

	if (addr > 0 && size > 0 && addr != 0xFFFFFFFF && size != 0xFFFFFFFF)
	{
		int entryCount = size / sizeof(HUES_GROUP);

		m_HuesCount = entryCount * 8;
		m_HuesRange = new HUES_GROUP[entryCount];

		memcpy(m_HuesRange, (PVOID)addr, entryCount * sizeof(HUES_GROUP));
	}
	else
	{
		m_HuesRange = NULL;
		m_HuesCount = 0;
	}

	addr = (DWORD)FileManager.RadarcolMul.Address;
	if (addr > 0 && addr != 0xFFFFFFFF)
		memcpy(m_Radarcol, (PVOID)addr, 0x10000);
	else
		memset(m_Radarcol, 0, 0x10000);

	addr = (DWORD)FileManager.PaletteMul.Address;
	if (addr > 0 && addr != 0xFFFFFFFF)
		memcpy(m_Palette, (PVOID)addr, 256 * sizeof(PALETTE_BLOCK));
	else
		memset(m_Palette, 0, 256 * sizeof(PALETTE_BLOCK));
}
//---------------------------------------------------------------------------
TColorManager::~TColorManager()
{
	if (m_HuesRange != NULL)
	{
		delete m_HuesRange;
		m_HuesRange = NULL;
	}

	if (m_HuesInt != NULL)
	{
		delete m_HuesInt;
		m_HuesInt = NULL;
	}

	m_HuesCount = 0;
}
//---------------------------------------------------------------------------
/*!
���� ����� ������ �� �������
@param [__in] index ������ � ������
@param [__in] group ��������� �� ����� �����
@return 
*/
void TColorManager::SetHuesBlock( __in int index, __in PVERDATA_HUES_GROUP group)
{
	if (index < 0 || index >= m_HuesCount)
		return;

	m_HuesRange[index].Header = group->Header;
	IFOR(i, 0, 8)
		memcpy(&m_HuesRange[index].Entries[i].ColorTable[0], &group->Entries[i].ColorTable[0], sizeof(WORD[32]));
}
//---------------------------------------------------------------------------
/*!
�������� ������� ������ ��� �������
@return 
*/
void TColorManager::CreateHuesPalette()
{
	m_HuesInt = new INT_HUES[m_HuesCount];
	int entryCount = m_HuesCount / 8;

	IFOR(i, 0, entryCount)
	{
		IFOR(j, 0, 8)
		{
			IFOR(h, 0, 32)
				m_HuesInt[(i * 8) + j].Palette[h] = (int)m_HuesRange[i].Entries[j].ColorTable[h];
		}
	}
}
//---------------------------------------------------------------------------
/*!
�������� ������ � ������
@param [__in] color ������ �����
@return 
*/
void TColorManager::SendColorsToShader( __in WORD color)
{
	if (color != 0)
	{
		if (color > SPECTRAL_COLOR)
			glUniform1ivARB(ShaderColorTable, 32, &m_HuesInt[0].Palette[0]);
		else
		{
			if (color >= m_HuesCount)
			{
				color %= m_HuesCount;

				if (!color)
					color = 1;
			}
			
			glUniform1ivARB(ShaderColorTable, 32, &m_HuesInt[color - 1].Palette[0]);
		}
	}
}
//---------------------------------------------------------------------------
/*!
��������������� ����� �� 16 ��� � 32 ���
@param [__in] c 16-������ ����
@return 32-������ ����
*/
DWORD TColorManager::Color16To32( __in WORD &c)
{
	return
	(
		(((c >> 10) & 0x1F) * 0xFF / 0x1F) |
		((((c >> 5) & 0x1F) * 0xFF / 0x1F) << 8) |
		(((c & 0x1F) * 0xFF / 0x1F) << 16)
	);
}
//---------------------------------------------------------------------------
/*!
��������������� ����� �� 32 ��� � 16 ���
@param [__in] c 32-������ ����
@return 16-������ ����
*/
WORD TColorManager::Color32To16( __in DWORD &c)
{
	return
	(
		((c & 0xFF) * 32) / 256) |
		(((((c >> 16) & 0xff) * 32) / 256) << 10) |
		(((((c >> 8) & 0xff) * 32) / 256) << 5
	);
}
//---------------------------------------------------------------------------
/*!
������� � �����
@param [__in] c 16-������ ����
@return 16-������ ����
*/
WORD TColorManager::ConvertToGray( __in WORD &c)
{
	return ((c & 0x1F) * 299 + ((c >> 5) & 0x1F) * 587 + ((c >> 10) & 0x1F) * 114) / 1000;
}
//---------------------------------------------------------------------------
/*!
�������� 16-������ ����
@param [__in] c �������� ����
@param [__in] color ������ ����� � �������
@return 16-������ ����
*/
WORD TColorManager::GetColor16( __in WORD &c, __in WORD color)
{
	if (color != 0 && color < m_HuesCount)
	{
		color -= 1;
		int g = color / 8;
		int e = color % 8;

		return m_HuesRange[g].Entries[e].ColorTable[(c >> 10) & 0x1F];
	}

	return c;
}
//---------------------------------------------------------------------------
/*!
�������� 16-������ ���� ��� ������
@param [__in] c �������� 16-������ ����
@return 16-������ ����
*/
WORD TColorManager::GetRadarColorData( __in WORD &c)
{
	return m_Radarcol[c];
}
//---------------------------------------------------------------------------
/*!
�������� 32-������ ���� ��� ������
@param [__in] c �������� 16-������ ����
@return 32-������ ����
*/
DWORD TColorManager::GetRadarColor( __in WORD &c)
{
	return Color16To32(m_Radarcol[c]);
}
//---------------------------------------------------------------------------
/*!
�������� 32-������ ���� ��� ��������������� ��������� �����
@param [__in] c �������� 16-������ ����
@param [__in] color ������ ����� � �������
@return 32-������ ����
*/
DWORD TColorManager::GetPolygoneColor( __in WORD c, __in WORD color)
{
	if (color != 0 && color < m_HuesCount)
	{
		color -= 1;
		int g = color / 8;
		int e = color % 8;

		return Color16To32(m_HuesRange[g].Entries[e].ColorTable[c]);
	}

	return 0xFF010101; //Black
}
//---------------------------------------------------------------------------
/*!
�������� 32-������ ���� ��� Unicode-�������
@param [__in] c �������� 16-������ ����
@param [__in] color ������ ����� � �������
@return 32-������ ����
*/
DWORD TColorManager::GetUnicodeFontColor( __in WORD &c, __in WORD color)
{
	if (color != 0 && color < m_HuesCount)
	{
		color -= 1;
		int g = color / 8;
		int e = color % 8;

		return Color16To32(m_HuesRange[g].Entries[e].ColorTable[8]);
	}

	return Color16To32(c);
}
//---------------------------------------------------------------------------
/*!
�������� 32-������ ����
@param [__in] c �������� 16-������ ����
@param [__in] color ������ ����� � �������
@return 32-������ ����
*/
DWORD TColorManager::GetColor( __in WORD &c, __in WORD color)
{
	if (color != 0 && color < m_HuesCount)
	{
		color -= 1;
		int g = color / 8;
		int e = color % 8;

		return Color16To32(m_HuesRange[g].Entries[e].ColorTable[(c >> 10) & 0x1F]);
	}

	return Color16To32(c);
}
//---------------------------------------------------------------------------
/*!
�������� 32-������ ���� � ������ �������� ������
@param [__in] c �������� 16-������ ����
@param [__in] color ������ ����� � �������
@return 32-������ ����
*/
DWORD TColorManager::GetPartialHueColor( __in WORD &c, __in WORD color)
{
	if (color != 0 && color < m_HuesCount)
	{
		color -= 1;
		int g = color / 8;
		int e = color % 8;

		DWORD cl = Color16To32(c);

		if (GetRValue(cl) == GetGValue(cl) && GetBValue(cl) == GetGValue(cl))
			return Color16To32(m_HuesRange[g].Entries[e].ColorTable[(c >> 10) & 0x1F]);

		return cl;
	}

	return Color16To32(c);
}
//---------------------------------------------------------------------------