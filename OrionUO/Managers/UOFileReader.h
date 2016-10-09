/***********************************************************************************
**
** UOFileReader.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef MULREADER_H
#define MULREADER_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../IndexObject.h"
#include "../GLEngine/GLTexture.h"
//----------------------------------------------------------------------------------
//!����� ��� ������ ������ �� ������ � �������� �������
class UOFileReader
{
public:
	UOFileReader() {}
	virtual ~UOFileReader() {}

	/*!
	�������� ������ �������� �����
	@param [__in] io ������ �� ������ � �����
	@return ������ �������� ��� NULL
	*/
	virtual USHORT_LIST GetGumpPixels(CIndexObject &io);

	/*!
	��������� ���� � ������������� ��������
	@param [__in] io ������ �� ������ � �����
	@return ������ �� ������ � ��������
	*/
	virtual CGLTexture *ReadGump(CIndexObject &io);

	/*!
	��������� ��� � ������������� ��������
	@param [__in] ID ������ ����
	@param [__in] io ������ �� ������ � ����
	@return ������ �� ������ � ��������
	*/
	virtual CGLTexture *ReadArt(const ushort &id, CIndexObject &io);

	/*!
	��������� ��� � ��������� �������� ����������� ������� ��������
	@param [__in] io ������ �� ������ � ����
	@param [__out] r ��������� � ���������� �� ������
	@return ������ �� ������ � ��������
	*/
	virtual WISP_GEOMETRY::CRect ReadStaticArtPixelDimension(CIndexObject &io);

	/*!
	��������� �������� ��������� � ������������� ��������
	@param [__in] io ������ �� ������ � �������� ���������
	@return ������ �� ������ � ��������
	*/
	virtual CGLTexture *ReadTexture(CIndexObject &io);

	/*!
	��������� ��������� � ������������� ��������
	@param [__in] io ������ �� ������ � ���������
	@return ������ �� ������ � ��������
	*/
	virtual CGLTexture *ReadLight(CIndexObject &io);

	/*!
	��������� ���������� ������� ����� � ��������� �����������
	@param [__in] io ������ �� ������ � �����
	@param [__in] checkX ���������� X
	@param [__in] checkY ���������� Y
	@return true � ������ ��������� �����
	*/
	virtual bool GumpPixelsInXY(CIndexObject &io, const int &checkX, const int &checkY);

	/*!
	��������� ���������� ������� ���� � ��������� �����������
	@param [__in] land �������� ��� �������
	@param [__in] io ������ �� ������ � ����
	@param [__in] checkX ���������� X
	@param [__in] checkY ���������� Y
	@return true � ������ ��������� �����
	*/
	virtual bool ArtPixelsInXY(const bool &land, CIndexObject &io, const int &checkX, const int &checkY);
};
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//!����� ������ ������
extern UOFileReader *g_UOFileReader;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
