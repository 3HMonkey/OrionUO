/****************************************************************************
**
** RenderObject.h
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
#ifndef RenderObjectH
#define RenderObjectH
//---------------------------------------------------------------------------
class TLandObject;

class TRenderStaticObject;
class TStaticObject;
class TGameObject;
class TGameItem;
class TGameCharacter;
//---------------------------------------------------------------------------
//����� ��� ������ � ��������� �������
class TRenderObject : public TBaseQueueItem
{
//private:
protected:
	//�������� �������
	DWORD m_Serial;

	//������ ��������
	WORD m_Graphic;

	//����
	WORD m_Color;

	//����������
	short m_X;
	short m_Y;
public:
	TRenderObject(DWORD serial, WORD graphic, WORD color, short x, short y);
	virtual ~TRenderObject();

	SETGET(DWORD, Serial);
	SETGET(WORD, Graphic);
	SETGET(WORD, Color);
	SETGETEX(short, X);
	SETGETEX(short, Y);

	//���������� �������
	virtual void PrepareTextures() {}

	//���������
	virtual int Draw(bool &mode) {return 0;}
};
//---------------------------------------------------------------------------
//����� ��� ������ � ��������� ������� � ����
class TRenderWorldObject : public TRenderObject
{
//private:
protected:
	//Z ����������
	char m_Z;

	//����� � Z ���������� � ������� �������
	BYTE m_RenderQueueIndex;

	//��� ������� �������
	RENDER_OBJECT_TYPE m_RenderType;

public:
	TRenderWorldObject(RENDER_OBJECT_TYPE renderType, DWORD serial, WORD graphic, WORD color, short x, short y, char z);
	virtual ~TRenderWorldObject();
	
	//TTextContainer *m_TextControl; //������ �� ��������� ��� ������
	
	//�������� ����� � ���������
	virtual void AddText(TTextData *td) {}

	//�������� �������� ������ �� ��� X
	virtual int GetTextOffsetX(TTextData *text) {return 0;}

	//�������� �������� ������ �� ��� Y
	virtual int GetTextOffsetY(TTextData *text) {return 0;}

	//���������, ����� �� ����� ���� ����������
	virtual bool TextCanBeTransparent(TRenderTextObject *text) {return false;}

	//�������� ������������ (��� ����� ������������)
	virtual bool TranparentTest(int &playerZ) {return false;}

	SETGETEX(char, Z);
	SETGETEX(BYTE, RenderQueueIndex);
	SETGET(RENDER_OBJECT_TYPE, RenderType);

	//������ �� ���������� � ��������� �������� � ������� �������
	TRenderWorldObject *m_NextXY;
	TRenderWorldObject *m_PrevXY;

	//�������� ��������� �� ������ ��������� � ������ �����������
	TLandObject *GetLand();

	//�������� ������ ����� �������
	virtual BYTE GetLightID() {return 0;}

	//���������� ������
	virtual int Draw(bool &mode, int &drawX, int &drawY, DWORD &ticks) { return 0; }

	//������� ������ �� ������� �������
	void RemoveRender();
	
	//����������� ��������� �� ������ �� �������� (�������)
	virtual bool IsBackground() {return false;}
	virtual bool IsWeapon() {return false;}
	virtual bool IsTransparent() {return false;}
	virtual bool IsTranslucent() {return false;}
	virtual bool IsWall() {return false;}
	virtual bool IsDamaging() {return false;}
	virtual bool IsImpassable() {return false;}
	virtual bool IsWet() {return false;}
	virtual bool IsUnknown() {return false;}
	virtual bool IsSurface() {return false;}
	virtual bool IsBridge() {return false;}
	virtual bool IsStackable() {return false;}
	virtual bool IsWindow() {return false;}
	virtual bool IsNoShoot() {return false;}
	virtual bool IsPrefixA() {return false;}
	virtual bool IsPrefixAn() {return false;}
	virtual bool IsInternal() {return false;}
	virtual bool IsFoliage() {return false;}
	virtual bool IsPartialHue() {return false;}
	virtual bool IsUnknown1() {return false;}
	virtual bool IsMap() {return false;}
	virtual bool IsContainer() {return false;}
	virtual bool IsWearable() {return false;}
	virtual bool IsLightSource() {return false;}
	virtual bool IsAnimated() {return false;}
	virtual bool IsNoDiagonal() {return false;}
	virtual bool IsUnknown2() {return false;}
	virtual bool IsArmor() {return false;}
	virtual bool IsRoof() {return false;}
	virtual bool IsDoor() {return false;}
	virtual bool IsStairBack() {return false;}
	virtual bool IsStairRight() {return false;}

	//���� ��� ������ ������ �������
	virtual bool IsStaticGroupObject() {return false;}

	//������������� ��������
	virtual bool IsLandObject() {return false;}
	virtual bool IsStaticObject() {return false;}
	virtual bool IsGameObject() {return false;}
	virtual bool IsMultiObject() {return false;}
	virtual bool IsEffectObject() {return false;}

	virtual TRenderStaticObject *StaticGroupObjectPtr() { return NULL; }
	virtual TLandObject *LandObjectPtr() { return NULL; }
	virtual TGameObject *GameObjectPtr() { return NULL; }
	virtual TGameItem *GameItemPtr() { return NULL; }
	virtual TGameCharacter *GameCharacterPtr() { return NULL; }
};
//---------------------------------------------------------------------------
extern TRenderWorldObject *g_SelectedObject;
//---------------------------------------------------------------------------
#endif