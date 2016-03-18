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
class TObjectOnCursor;
//--------------------------------------------------------------------------
class TGameItem : public TGameObject
{
protected:
	BYTE m_Layer; //����
	WORD m_AnimID; //������ ��������
	WORD m_ImageID; //������ ����� ��� ����������
	BYTE m_UsedLayer; //������������ ��������� ���� (�� tiledata.mul (verdata))
	bool m_Opened; //������ �� ���������/��������
	bool m_Dragged; //������� �� ���� ���������� ����������?

	//������� ��� ���������� �������-������
	void AddMultiObject(TMultiObject *obj);
public:
	TGameItem(DWORD serial = 0);
	virtual ~TGameItem();

	//��������� �� ������� ����� �������
	TShopItem *ShopItem;

	//������� ������ �� ������� � ���� (�� �������)
	void Paste(TObjectOnCursor *obj);

	virtual int Draw(bool &mode, int &drawX, int &drawY, DWORD &ticks);
	
	SETGET(BYTE, Layer);
	SETGET(WORD, AnimID);
	SETGET(WORD, ImageID);
	SETGET(BYTE, UsedLayer);
	SETGET(bool, Opened);
	SETGET(bool, Dragged);

	void OnGraphicChange(int direction = 0);

	//�������� ������ �������� (��� ��������)
	WORD GetMountAnimation();

	virtual bool IsInternal() { return ((m_TiledataPtr->Flags & 0x00010000) && !IsCorpse()); }
	bool IsHuman() { return (IsCorpse() && (m_Count >= 0x0190) && (m_Count <= 0x0193)); }

	//�������� ������ � ������� ������
	void LoadMulti();
	//��������� ������� ������ � �������� �����������
	TMulti *GetMultiAtXY(short x, short y);

	//����� ������ ������ (����������) �� ���� � ������ (� ���) �����
	TGameItem *FindItem(WORD graphic, WORD color = 0xFFFF);
	//����� ������ � ���������� �� ��������� ����
	TGameItem *FindLayer(int layer);
};
//---------------------------------------------------------------------------
#endif