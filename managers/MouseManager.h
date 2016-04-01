/****************************************************************************
**
** MouseManager.h
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
//--------------------------------------------------------------------------
#ifndef MouseManagerH
#define MouseManagerH
//--------------------------------------------------------------------------
//!�������� ������� �����
extern WORD g_CursorData[2][16];
//--------------------------------------------------------------------------
//!����� ��������� ����
class TMouseManager
{
private:
	//!�������� �������� ������������ �������
	int m_CursorOffset[2][16];

public:
	TMouseManager() {}
	~TMouseManager() {}

	/*!
	�������� ������� �������
	@return true ��� �������� ��������
	*/
	bool LoadCursorTextures();

	/*!
	�������� ���������� ����
	@return 
	*/
	void UpdateMouse();

	/*!
	��������������� �������� �����������
	@param [__in] val �������� �����������
	@return ��������
	*/
	int Sgn(__in int val);

	/*!
	�������� ����������� ������� ������������ ������ �������� ����
	@param [__in] x1 ���������� X ������
	@param [__in] y1 ���������� Y ������
	@param [__in] to_x ���������� X ����
	@param [__in] to_y ���������� Y ����
	@param [__in] current_facing ������� �����������
	@return ����������� �������
	*/
	int GetFacing(__in int x1, __in int  y1, __in int  to_x, __in int to_y, __in int current_facing);

	/*!
	�������� ������ �������� �������� �������
	@return ������ ��������
	*/
	WORD GetGameCursor();

	/*!
	���������� ������
	@param [__in] id ������ �������� �������
	@return 
	*/
	void Draw(__in WORD id);
};
//--------------------------------------------------------------------------
//!�������� ����
extern TMouseManager MouseManager;
//--------------------------------------------------------------------------
#endif