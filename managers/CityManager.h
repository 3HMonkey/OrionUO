/****************************************************************************
**
** CityManager.h
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
#ifndef CityManagerH
#define CityManagerH
//---------------------------------------------------------------------------
//!����� � ������� � ������
class TCity : public TBaseQueueItem
{
private:
	//!�������� ������
	string m_Name;

public:
	TCity(string name);
	virtual ~TCity();

	SETGET(string, Name);

	//!��������� �� �������� ������
	TTextTexture m_Texture;
};
//---------------------------------------------------------------------------
//!����� ��������� ������ �������
class TCityManager : public TBaseQueue
{
public:
	TCityManager();
	virtual ~TCityManager();

	/*!
	�������� ��������� �� �����
	@param [__in] name ��� ������
	@return ������ �� ����� ��� NULL
	*/
	TCity *GetCity(__in string name);
};
//---------------------------------------------------------------------------
//!������ �� �������� �������
extern TCityManager *CityManager;
//---------------------------------------------------------------------------
#endif