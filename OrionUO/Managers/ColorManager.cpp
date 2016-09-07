/***********************************************************************************
**
** ColorManager.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "ColorManager.h"
#include "FileManager.h"
#include "../Constants.h"

CColorManager g_ColorManager;
//----------------------------------------------------------------------------------
CColorManager::CColorManager()
: m_HuesCount(0)
{
}
//----------------------------------------------------------------------------------
CColorManager::~CColorManager()
{
}
//----------------------------------------------------------------------------------
void CColorManager::Init()
{
	uint addr = (uint)g_FileManager.m_HuesMul.Start;
	uint size = g_FileManager.m_HuesMul.Size;

	if (addr > 0 && size > 0 && addr != 0xFFFFFFFF && size != 0xFFFFFFFF)
	{
		int entryCount = size / sizeof(HUES_GROUP);

		m_HuesCount = entryCount * 8;
		m_HuesRange.resize(entryCount);

		memcpy(&m_HuesRange[0], (PVOID)addr, entryCount * sizeof(HUES_GROUP));
	}
	else
		m_HuesCount = 0;

	addr = (uint)g_FileManager.m_RadarcolMul.Start;
	if (addr > 0 && addr != 0xFFFFFFFF)
		memcpy(m_Radarcol, (PVOID)addr, 0x10000);
	else
		memset(m_Radarcol, 0, 0x10000);

	addr = (uint)g_FileManager.m_PaletteMul.Start;
	if (addr > 0 && addr != 0xFFFFFFFF)
		memcpy(m_Palette, (PVOID)addr, 256 * sizeof(PALETTE_BLOCK));
	else
		memset(m_Palette, 0, 256 * sizeof(PALETTE_BLOCK));
}
//----------------------------------------------------------------------------------
/*!
���� ����� ������ �� �������
@param [__in] index ������ � ������
@param [__in] group ��������� �� ����� �����
@return 
*/
void CColorManager::SetHuesBlock(int index, PVERDATA_HUES_GROUP group)
{
	if (index < 0 || index >= m_HuesCount)
		return;

	m_HuesRange[index].Header = group->Header;
	IFOR(i, 0, 8)
		memcpy(&m_HuesRange[index].Entries[i].ColorTable[0], &group->Entries[i].ColorTable[0], sizeof(ushort[32]));
}
//----------------------------------------------------------------------------------
/*!
�������� ������� ������ ��� �������
@return
*/
void CColorManager::CreateHuesPalette()
{
	m_HuesFloat.resize(m_HuesCount);
	int entryCount = m_HuesCount / 8;

	IFOR(i, 0, entryCount)
	{
		IFOR(j, 0, 8)
		{
			FLOAT_HUES &fh = m_HuesFloat[(i * 8) + j];

			IFOR(h, 0, 32)
			{
				int idx = h * 3;

				ushort c = m_HuesRange[i].Entries[j].ColorTable[h];

				fh.Palette[idx] = (((c >> 10) & 0x1F) / 31.0f);
				fh.Palette[idx + 1] = (((c >> 5) & 0x1F) / 31.0f);
				fh.Palette[idx + 2] = ((c & 0x1F) / 31.0f);
			}
		}
	}
}
//----------------------------------------------------------------------------------
/*!
�������� ������ � ������
@param [__in] color ������ �����
@return
*/
void CColorManager::SendColorsToShader(ushort color)
{
	if (color != 0)
	{
		if (color & SPECTRAL_COLOR)
			glUniform1fv(ShaderColorTable, 32 * 3, &m_HuesFloat[0].Palette[0]);
		else
		{
			if (color >= m_HuesCount)
			{
				color %= m_HuesCount;

				if (!color)
					color = 1;
			}

			glUniform1fv(ShaderColorTable, 32 * 3, &m_HuesFloat[color - 1].Palette[0]);
		}
	}
}
//----------------------------------------------------------------------------------
/*!
��������������� ����� �� 16 ��� � 32 ���
@param [__in] c 16-������ ����
@return 32-������ ����
*/
uint CColorManager::Color16To32(ushort &c)
{
	return
	(
		(((c >> 10) & 0x1F) * 0xFF / 0x1F) |
		((((c >> 5) & 0x1F) * 0xFF / 0x1F) << 8) |
		(((c & 0x1F) * 0xFF / 0x1F) << 16)
	);
}
//----------------------------------------------------------------------------------
/*!
��������������� ����� �� 32 ��� � 16 ���
@param [__in] c 32-������ ����
@return 16-������ ����
*/
ushort CColorManager::Color32To16(uint &c)
{
	return
	(
		((c & 0xFF) * 32) / 256) |
		(((((c >> 16) & 0xff) * 32) / 256) << 10) |
		(((((c >> 8) & 0xff) * 32) / 256) << 5
	);
}
//----------------------------------------------------------------------------------
/*!
������� � �����
@param [__in] c 16-������ ����
@return 16-������ ����
*/
ushort CColorManager::ConvertToGray(ushort &c)
{
	return ((c & 0x1F) * 299 + ((c >> 5) & 0x1F) * 587 + ((c >> 10) & 0x1F) * 114) / 1000;
}
//----------------------------------------------------------------------------------
/*!
�������� 16-������ ����
@param [__in] c �������� ����
@param [__in] color ������ ����� � �������
@return 16-������ ����
*/
ushort CColorManager::GetColor16(const ushort &c, ushort color)
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
//----------------------------------------------------------------------------------
/*!
�������� 16-������ ���� ��� ������
@param [__in] c �������� 16-������ ����
@return 16-������ ����
*/
ushort CColorManager::GetRadarColorData(ushort &c)
{
	return m_Radarcol[c];
}
//----------------------------------------------------------------------------------
/*!
�������� 32-������ ���� ��� ������
@param [__in] c �������� 16-������ ����
@return 32-������ ����
*/
uint CColorManager::GetRadarColor(ushort &c)
{
	return Color16To32(m_Radarcol[c]);
}
//----------------------------------------------------------------------------------
/*!
�������� 32-������ ���� ��� ��������������� ��������� �����
@param [__in] c �������� 16-������ ����
@param [__in] color ������ ����� � �������
@return 32-������ ����
*/
uint CColorManager::GetPolygoneColor(ushort c, ushort color)
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
//----------------------------------------------------------------------------------
/*!
�������� 32-������ ���� ��� Unicode-�������
@param [__in] c �������� 16-������ ����
@param [__in] color ������ ����� � �������
@return 32-������ ����
*/
uint CColorManager::GetUnicodeFontColor(ushort &c, ushort color)
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
//----------------------------------------------------------------------------------
/*!
�������� 32-������ ����
@param [__in] c �������� 16-������ ����
@param [__in] color ������ ����� � �������
@return 32-������ ����
*/
uint CColorManager::GetColor(ushort &c, ushort color)
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
//----------------------------------------------------------------------------------
/*!
�������� 32-������ ���� � ������ �������� ������
@param [__in] c �������� 16-������ ����
@param [__in] color ������ ����� � �������
@return 32-������ ����
*/
uint CColorManager::GetPartialHueColor(ushort &c, ushort color)
{
	if (color != 0 && color < m_HuesCount)
	{
		color -= 1;
		int g = color / 8;
		int e = color % 8;

		uint cl = Color16To32(c);

		if (GetRValue(cl) == GetGValue(cl) && GetBValue(cl) == GetGValue(cl))
			return Color16To32(m_HuesRange[g].Entries[e].ColorTable[(c >> 10) & 0x1F]);

		return cl;
	}

	return Color16To32(c);
}
//----------------------------------------------------------------------------------
