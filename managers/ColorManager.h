/****************************************************************************
**
** ColorManager.h
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
#ifndef ColorManagerH
#define ColorManagerH
//---------------------------------------------------------------------------
//!��������� ������ ��� �������� � ������
struct INT_HUES
{
	//!������� ������, 32 �����
	GLint Palette[32];
};
//---------------------------------------------------------------------------
//!����� ��������� ������
class TColorManager
{
private:
	//!��������� �� �������
	PHUES_GROUP m_HuesRange;

	//!��������� �� ������ ������ ��� �������
	INT_HUES *m_HuesInt;

	//!���������� ������
	int m_HuesCount;

	//!������ ��� ������
	WORD m_Radarcol[0x10000];

	//!������ �� palette.mul
	PALETTE_BLOCK m_Palette[256];

public:
	TColorManager();
	~TColorManager();

	/*!
	�������� ��������� �� ������ ������
	@return ������ �� �����
	*/
	PHUES_GROUP GetHuesRangePointer() { return m_HuesRange; }

	/*!
	�������� ���������� ������
	@return ���������� ������
	*/
	int GetHuesCount() const { return m_HuesCount; }

	/*!
	���� ����� ������ �� �������
	@param [__in] index ������ � ������
	@param [__in] group ��������� �� ����� �����
	@return 
	*/
	void SetHuesBlock(__in int index, __in PVERDATA_HUES_GROUP group);

	/*!
	�������� ������� ������ ��� �������
	@return 
	*/
	void CreateHuesPalette();

	/*!
	�������� ������ � ������
	@param [__in] color ������ �����
	@return 
	*/
	void SendColorsToShader(__in WORD color);



	/*!
	��������������� ����� �� 32 ��� � 16 ���
	@param [__in] c 32-������ ����
	@return 16-������ ����
	*/
	WORD Color32To16(__in DWORD &c);

	/*!
	��������������� ����� �� 16 ��� � 32 ���
	@param [__in] c 16-������ ����
	@return 32-������ ����
	*/
	DWORD Color16To32(__in WORD &c);

	/*!
	������� � �����
	@param [__in] c 16-������ ����
	@return 16-������ ����
	*/
	WORD ConvertToGray(__in WORD &c);



	/*!
	�������� 16-������ ����
	@param [__in] c �������� ����
	@param [__in] color ������ ����� � �������
	@return 16-������ ����
	*/
	WORD GetColor16(__in WORD &c, __in WORD color);

	/*!
	�������� 16-������ ���� ��� ������
	@param [__in] c �������� 16-������ ����
	@return 16-������ ����
	*/
	WORD GetRadarColorData(__in WORD &c);

	/*!
	�������� 32-������ ���� ��� ������
	@param [__in] c �������� 16-������ ����
	@return 32-������ ����
	*/
	DWORD GetRadarColor(__in WORD &c);

	/*!
	�������� 32-������ ���� ��� ��������������� ��������� �����
	@param [__in] c �������� 16-������ ����
	@param [__in] color ������ ����� � �������
	@return 32-������ ����
	*/
	DWORD GetPolygoneColor(__in WORD c, __in WORD color);

	/*!
	�������� 32-������ ���� ��� Unicode-�������
	@param [__in] c �������� 16-������ ����
	@param [__in] color ������ ����� � �������
	@return 32-������ ����
	*/
	DWORD GetUnicodeFontColor(__in WORD &c, __in WORD color);

	/*!
	�������� 32-������ ����
	@param [__in] c �������� 16-������ ����
	@param [__in] color ������ ����� � �������
	@return 32-������ ����
	*/
	DWORD GetColor(__in WORD &c, __in WORD color);

	/*!
	�������� 32-������ ���� � ������ �������� ������
	@param [__in] c �������� 16-������ ����
	@param [__in] color ������ ����� � �������
	@return 32-������ ����
	*/
	DWORD GetPartialHueColor(__in WORD &c, __in WORD color);
 };
//---------------------------------------------------------------------------
//!������ �� �������� ������
extern TColorManager *ColorManager;
//---------------------------------------------------------------------------
#endif