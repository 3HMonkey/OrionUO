/****************************************************************************
**
** MultiMap.h
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
#ifndef MultiMapH
#define MultiMapH
//---------------------------------------------------------------------------
class TGumpMap;
//---------------------------------------------------------------------------
//����� ��� ������ � ������ (multimap.rle)
class TMultiMap
{
private:
	//�������� �����
	int m_Width;
	int m_Height;
public:
	TMultiMap();
	~TMultiMap();
	
	SETGET(int, Width);
	SETGET(int, Height);

	//��������� �����
	void LoadMap(TGumpMap *gump);
	void LoadMapEx(TGumpMap *gump);
};
//---------------------------------------------------------------------------
extern TMultiMap *MultiMap;
//---------------------------------------------------------------------------
#endif