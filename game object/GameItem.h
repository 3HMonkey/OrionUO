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
private:
	BYTE m_Layer; //����
	WORD m_AnimID; //������ ��������
	WORD m_ImageID; //������ ����� ��� ����������
	BYTE m_UsedLayer; //������������ ��������� ���� (�� tiledata.mul (verdata))
	bool m_Opened; //������ �� ���������/��������
	bool m_Dragged; //������� �� ���� ���������� ����������?
	DWORD m_ObjectFlags; //����� ������� �� tiledata.mul (verdata.mul)

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
	SETGET(DWORD, ObjectFlags);

	//�������� ������ �������� (��� ��������)
	WORD GetMountAnimation();

	//����������� ��������� �� ������ �� �������� (�������)
	virtual bool IsBackground() {return (m_ObjectFlags & 0x00000001);}
	virtual bool IsWeapon() {return (m_ObjectFlags & 0x00000002);}
	virtual bool IsTransparent() {return (m_ObjectFlags & 0x00000004);}
	virtual bool IsTranslucent() {return (m_ObjectFlags & 0x00000008);}
	virtual bool IsWall() {return (m_ObjectFlags & 0x00000010);}
	virtual bool IsDamaging() {return (m_ObjectFlags & 0x00000020);}
	virtual bool IsImpassable() {return (m_ObjectFlags & 0x00000040);}
	virtual bool IsWet() {return (m_ObjectFlags & 0x00000080);}
	virtual bool IsUnknown() {return (m_ObjectFlags & 0x00000100);}
	virtual bool IsSurface() {return (m_ObjectFlags & 0x00000200);}
	virtual bool IsBridge() {return (m_ObjectFlags & 0x00000400);}
	virtual bool IsStackable() {return (m_ObjectFlags & 0x00000800);}
	virtual bool IsWindow() {return (m_ObjectFlags & 0x00001000);}
	virtual bool IsNoShoot() {return (m_ObjectFlags & 0x00002000);}
	virtual bool IsPrefixA() {return (m_ObjectFlags & 0x00004000);}
	virtual bool IsPrefixAn() {return (m_ObjectFlags & 0x00008000);}
	virtual bool IsInternal() {return ((m_ObjectFlags & 0x00010000) && Graphic != 0x2006);}
	virtual bool IsFoliage() {return (m_ObjectFlags & 0x00020000);}
	virtual bool IsPartialHue() {return (m_ObjectFlags & 0x00040000);}
	virtual bool IsUnknown1() {return (m_ObjectFlags & 0x00080000);}
	virtual bool IsMap() {return (m_ObjectFlags & 0x00100000);}
	virtual bool IsContainer() {return (m_ObjectFlags & 0x00200000);}
	virtual bool IsWearable() {return (m_ObjectFlags & 0x00400000);}
	virtual bool IsLightSource() {return (m_ObjectFlags & 0x00800000);}
	virtual bool IsAnimated() {return (m_ObjectFlags & 0x01000000);}
	virtual bool IsNoDiagonal() {return (m_ObjectFlags & 0x02000000);}
	virtual bool IsUnknown2() {return (m_ObjectFlags & 0x04000000);}
	virtual bool IsArmor() {return (m_ObjectFlags & 0x08000000);}
	virtual bool IsRoof() {return (m_ObjectFlags & 0x10000000);}
	virtual bool IsDoor() {return (m_ObjectFlags & 0x20000000);}
	virtual bool IsStairBack() {return (m_ObjectFlags & 0x40000000);}
	virtual bool IsStairRight() {return (m_ObjectFlags & 0x80000000);}

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