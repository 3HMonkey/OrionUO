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
	~TMulReader() {}

	/*!
	�������� ������ �������� �����
	@param [__in] io ������ �� ������ � �����
	@return ������ �������� ��� NULL
	*/
	PWORD GetGumpPixels(__in TIndexObject &io);

	/*!
	��������� ���� � ������������� ��������
	@param [__in] io ������ �� ������ � �����
	@return ������ �� ������ � ��������
	*/
	TTextureObject *ReadGump(__in TIndexObject &io);

	/*!
	��������� ��� � ������������� ��������
	@param [__in] ID ������ ����
	@param [__in] io ������ �� ������ � ����
	@return ������ �� ������ � ��������
	*/
	TTextureObject *ReadArt(__in WORD id, __in TIndexObject &io);

	/*!
	��������� �������� ��������� � ������������� ��������
	@param [__in] io ������ �� ������ � �������� ���������
	@return ������ �� ������ � ��������
	*/
	TTextureObject *ReadTexture(__in TIndexObject &io);

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
	bool GumpPixelsInXY(__in TIndexObject &io, __in int &checkX, __in int &checkY);

	/*!
	��������� ���������� ������� ���� � ��������� �����������
	@param [__in] land �������� ��� �������
	@param [__in] io ������ �� ������ � ����
	@param [__in] checkX ���������� X
	@param [__in] checkY ���������� Y
	@return true � ������ ��������� �����
	*/
	bool ArtPixelsInXY(__in bool land, __in TIndexObject &io, __in  int &checkX, __in  int &checkY);
};
//---------------------------------------------------------------------------
//!����� ������ ������
extern TMulReader MulReader;
//---------------------------------------------------------------------------
#endif