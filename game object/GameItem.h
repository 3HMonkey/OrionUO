/****************************************************************************
**
** GameObject.h
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
#ifndef GameItemH
#define GameItemH
//--------------------------------------------------------------------------
//!����� �������� �������� (��� �����)
class TGameItem : public TGameObject
{
protected:
	//!����, � ������� ���������� ������
	BYTE m_Layer;

	//!������ ��������
	WORD m_AnimID;

	//!������ ����� ��� ����������
	WORD m_ImageID;

	//!������������ ��������� ���� (�� tiledata.mul/verdata)
	BYTE m_UsedLayer;

	//!������ �� ���������/��������
	bool m_Opened;

	//!������� �� ���� ���������� ����������?
	bool m_Dragged;

	/*!
	�������� �������-������
	@param [__in] obj ������ �� ������-������
	@return 
	*/
	void AddMultiObject(__in TMultiObject *obj);
public:
	TGameItem(DWORD serial = 0);
	virtual ~TGameItem();

	//!��������� �� ������� ����� �������
	TShopItem *ShopItem;

	SETGET(BYTE, Layer);
	SETGET(WORD, AnimID);
	SETGET(WORD, ImageID);
	SETGET(BYTE, UsedLayer);
	SETGET(bool, Opened);
	SETGET(bool, Dragged);

	/*!
	������� ������ �� ������� � ���� (�� �������)
	@param [__in] obj ������ �� ������ �� �������
	@return 
	*/
	void Paste(__in class TObjectOnCursor *obj);

	/*!
	���������� �������
	@param [__in] mode ����� ���������. true - ���������, false - ����� ��������
	@param [__in] drawX �������� ���������� X �������
	@param [__in] drawY �������� ���������� Y �������
	@param [__in] ticks ������ �������
	@return ��� ������ �������� ���������� ��������� �������
	*/
	virtual int Draw(bool &mode, int &drawX, int &drawY, DWORD &ticks);

	/*!
	������� ��������� �������� �������
	@param [__in_opt] direction ����������� �������� (��� ������)
	@return
	*/
	void OnGraphicChange(__in_opt int direction = 0);

	/*!
	�������� ������ �������� (��� ��������)
	@return ������ ��������
	*/
	WORD GetMountAnimation();

	/*!
	���������� �� ��� ������, �������� �����
	@return 
	*/
	virtual bool IsInternal() { return ((m_TiledataPtr->Flags & 0x00010000) && !IsCorpse()); }

	/*!
	���������������� ���� �� ���?
	@return 
	*/
	bool IsHuman() { return (IsCorpse() && (m_Count >= 0x0190) && (m_Count <= 0x0193)); }

	/*!
	�������� ������ � ������� ������
	@return 
	*/
	void LoadMulti(__in);

	/*!
	��������� ������� ������ � �������� �����������
	@param [__in] x ���������� X
	@param [__in] y ���������� Y
	@return ������ �� ������ ��� NULL
	*/
	TMulti *GetMultiAtXY(__in short x, __in short y);

	/*!
	����� ������ ������ (����������) �� ���� � ������ (� ���) �����
	@param [__in] graphic ������ ��������
	@param [__in_opt] color ���� ��������
	@return ������ �� ��������� ������ ��� NULL
	*/
	TGameItem *FindItem(__in WORD graphic, __in_opt WORD color = 0xFFFF);

	/*!
	����� ������ �� ��������� ���� (��� ������)
	@param [__in] layer ����� ����
	@return ������ �� ��������� ������ ��� NULL
	*/
	TGameItem *FindLayer(__in int layer);

	virtual TGameItem *GameItemPtr() { return this; }
};
//---------------------------------------------------------------------------
#endif