/***********************************************************************************
**
** ColorManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef COLORMANAGER_H
#define COLORMANAGER_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../MulStruct.h"
//----------------------------------------------------------------------------------
//!��������� ������ ��� �������� � ������
struct FLOAT_HUES
{
	//!������� ������, 32 ����� �� 3 �����
	float Palette[32 * 3];
};
//----------------------------------------------------------------------------------
//!����� ��������� ������
class CColorManager
{
private:
	//!��������� �� �������
	vector<HUES_GROUP> m_HuesRange;

	//!��������� �� ������ ������ ��� �������
	vector<FLOAT_HUES> m_HuesFloat;

	//!���������� ������
	int m_HuesCount;

	//!������ ��� ������
	ushort m_Radarcol[0x10000];

	//!������ �� palette.mul
	PALETTE_BLOCK m_Palette[256];

public:
	CColorManager();
	~CColorManager();

	void Init();

	/*!
	�������� ��������� �� ������ ������
	@return ������ �� �����
	*/
	PHUES_GROUP GetHuesRangePointer() { return &m_HuesRange[0]; }

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
	void SetHuesBlock(int index, PVERDATA_HUES_GROUP group);

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
	void SendColorsToShader(ushort color);



	/*!
	��������������� ����� �� 32 ��� � 16 ���
	@param [__in] c 32-������ ����
	@return 16-������ ����
	*/
	ushort Color32To16(uint &c);

	/*!
	��������������� ����� �� 16 ��� � 32 ���
	@param [__in] c 16-������ ����
	@return 32-������ ����
	*/
	uint Color16To32(ushort &c);

	/*!
	������� � �����
	@param [__in] c 16-������ ����
	@return 16-������ ����
	*/
	ushort ConvertToGray(ushort &c);



	/*!
	�������� 16-������ ����
	@param [__in] c �������� ����
	@param [__in] color ������ ����� � �������
	@return 16-������ ����
	*/
	ushort GetColor16(const ushort &c, ushort color);

	/*!
	�������� 16-������ ���� ��� ������
	@param [__in] c �������� 16-������ ����
	@return 16-������ ����
	*/
	ushort GetRadarColorData(ushort &c);

	/*!
	�������� 32-������ ���� ��� ������
	@param [__in] c �������� 16-������ ����
	@return 32-������ ����
	*/
	uint GetRadarColor(ushort &c);

	/*!
	�������� 32-������ ���� ��� ��������������� ��������� �����
	@param [__in] c �������� 16-������ ����
	@param [__in] color ������ ����� � �������
	@return 32-������ ����
	*/
	uint GetPolygoneColor(ushort c, ushort color);

	/*!
	�������� 32-������ ���� ��� Unicode-�������
	@param [__in] c �������� 16-������ ����
	@param [__in] color ������ ����� � �������
	@return 32-������ ����
	*/
	uint GetUnicodeFontColor(ushort &c, ushort color);

	/*!
	�������� 32-������ ����
	@param [__in] c �������� 16-������ ����
	@param [__in] color ������ ����� � �������
	@return 32-������ ����
	*/
	uint GetColor(ushort &c, ushort color);

	/*!
	�������� 32-������ ���� � ������ �������� ������
	@param [__in] c �������� 16-������ ����
	@param [__in] color ������ ����� � �������
	@return 32-������ ����
	*/
	uint GetPartialHueColor(ushort &c, ushort color);
 };
 //----------------------------------------------------------------------------------
//!������ �� �������� ������
 extern CColorManager g_ColorManager;
 //----------------------------------------------------------------------------------
#endif
