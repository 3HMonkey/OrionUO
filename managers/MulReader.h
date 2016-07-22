/****************************************************************************
**
** MulReader.h
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
#ifndef MulReaderH
#define MulReaderH
//---------------------------------------------------------------------------
//!����� ��� ������ ������ �� ������ � �������� �������
class TMulReader
{
public:
	TMulReader() {}
	virtual ~TMulReader() {}

	/*!
	�������� ������ �������� �����
	@param [__in] io ������ �� ������ � �����
	@return ������ �������� ��� NULL
	*/
	virtual PWORD GetGumpPixels(__in TIndexObject &io);

	/*!
	��������� ���� � ������������� ��������
	@param [__in] io ������ �� ������ � �����
	@return ������ �� ������ � ��������
	*/
	virtual TTextureObject *ReadGump(__in TIndexObject &io);

	/*!
	��������� ��� � ������������� ��������
	@param [__in] ID ������ ����
	@param [__in] io ������ �� ������ � ����
	@return ������ �� ������ � ��������
	*/
	virtual TTextureObject *ReadArt(__in const WORD &id, __in TIndexObject &io);

	/*!
	��������� ��� � ��������� �������� ����������� ������� ��������
	@param [__in] io ������ �� ������ � ����
	@param [__out] r ��������� � ���������� �� ������
	@return ������ �� ������ � ��������
	*/
	virtual void ReadStaticArtPixelDimension(__in TIndexObject &io, __out RECT &r);

	/*!
	��������� �������� ��������� � ������������� ��������
	@param [__in] io ������ �� ������ � �������� ���������
	@return ������ �� ������ � ��������
	*/
	virtual TTextureObject *ReadTexture(__in TIndexObject &io);

	/*!
	��������� ��������� � ������������� ��������
	@param [__in] io ������ �� ������ � ���������
	@return ������ �� ������ � ��������
	*/
	TTextureObject *ReadLight(__in TIndexObject &io);

	/*!
	��������� ���������� ������� ����� � ��������� �����������
	@param [__in] io ������ �� ������ � �����
	@param [__in] checkX ���������� X
	@param [__in] checkY ���������� Y
	@return true � ������ ��������� �����
	*/
	virtual bool GumpPixelsInXY(__in TIndexObject &io, __in const int &checkX, __in const int &checkY);

	/*!
	��������� ���������� ������� ���� � ��������� �����������
	@param [__in] land �������� ��� �������
	@param [__in] io ������ �� ������ � ����
	@param [__in] checkX ���������� X
	@param [__in] checkY ���������� Y
	@return true � ������ ��������� �����
	*/
	virtual bool ArtPixelsInXY(__in const bool &land, __in TIndexObject &io, __in const int &checkX, __in const int &checkY);
};
//---------------------------------------------------------------------------
//!����� ��� ������ ������ �� ������ � �������� �������
class TUopReader : public TMulReader
{
public:
	TUopReader() : TMulReader() {}
	virtual ~TUopReader() {}

	/*!
	�������� ������ �������� �����
	@param [__in] io ������ �� ������ � �����
	@return ������ �������� ��� NULL
	*/
	virtual PWORD GetGumpPixels(__in TIndexObject &io);

	/*!
	��������� ���� � ������������� ��������
	@param [__in] io ������ �� ������ � �����
	@return ������ �� ������ � ��������
	*/
	virtual TTextureObject *ReadGump(__in TIndexObject &io);

	/*!
	��������� ��� � ������������� ��������
	@param [__in] ID ������ ����
	@param [__in] io ������ �� ������ � ����
	@return ������ �� ������ � ��������
	*/
	virtual TTextureObject *ReadArt(__in const WORD &id, __in TIndexObject &io);

	/*!
	��������� ��� � ��������� �������� ����������� ������� ��������
	@param [__in] io ������ �� ������ � ����
	@param [__out] r ��������� � ���������� �� ������
	@return ������ �� ������ � ��������
	*/
	virtual void ReadStaticArtPixelDimension(__in TIndexObject &io, __out RECT &r);

	/*!
	��������� �������� ��������� � ������������� ��������
	@param [__in] io ������ �� ������ � �������� ���������
	@return ������ �� ������ � ��������
	*/
	virtual TTextureObject *ReadTexture(__in TIndexObject &io);

	/*!
	��������� ���������� ������� ����� � ��������� �����������
	@param [__in] io ������ �� ������ � �����
	@param [__in] checkX ���������� X
	@param [__in] checkY ���������� Y
	@return true � ������ ��������� �����
	*/
	virtual bool GumpPixelsInXY(__in TIndexObject &io, __in const int &checkX, __in const int &checkY);

	/*!
	��������� ���������� ������� ���� � ��������� �����������
	@param [__in] land �������� ��� �������
	@param [__in] io ������ �� ������ � ����
	@param [__in] checkX ���������� X
	@param [__in] checkY ���������� Y
	@return true � ������ ��������� �����
	*/
	virtual bool ArtPixelsInXY(__in const bool &land, __in TIndexObject &io, __in const int &checkX, __in const int &checkY);
};
//---------------------------------------------------------------------------
//!����� ������ ������
extern TMulReader *MulReader;
//---------------------------------------------------------------------------
#endif