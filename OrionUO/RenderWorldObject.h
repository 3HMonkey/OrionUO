/***********************************************************************************
**
** RenderWorldObject.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef RENDERWORLDOBJECT_H
#define RENDERWORLDOBJECT_H
//----------------------------------------------------------------------------------
#include "RenderObject.h"
#include "TextEngine/TextData.h"
//----------------------------------------------------------------------------------
//����� ��� ������ � ��������� �������
class CRenderWorldObject : public CRenderObject
{
	SETGETEX(char, Z);
	SETGETEX(uchar, RenderQueueIndex);
	SETGET(RENDER_OBJECT_TYPE, RenderType);
#if UO_RENDER_LIST_SORT == 1
	SETGET(uchar, CurrentRenderIndex);
#endif

public:
	CRenderWorldObject(const RENDER_OBJECT_TYPE &renderType, const uint &serial, const ushort &graphic, const ushort &color, const int &x, const int &y, const char &z);
	virtual ~CRenderWorldObject();

	//TTextContainer *m_TextControl; //������ �� ��������� ��� ������

	//�������� ����� � ���������
	virtual void AddText(CTextData *td) {}

	//�������� �������� ������ �� ��� X
	virtual int GetTextOffsetX(CTextData *text) { return 0; }

	//�������� �������� ������ �� ��� Y
	virtual int GetTextOffsetY(CTextData *text) { return 0; }

	//���������, ����� �� ����� ���� ����������
	virtual bool TextCanBeTransparent(CRenderTextObject *text) { return false; }

	//�������� ������������ (��� ����� ������������)
	virtual bool TranparentTest(int &playerZ) { return false; }

	//������ �� ���������� � ��������� �������� � ������� �������
	CRenderWorldObject *m_NextXY;
	CRenderWorldObject *m_PrevXY;

	//�������� ��������� �� ������ ��������� � ������ �����������
	class CLandObject *GetLand();

	//�������� ������ ����� �������
	virtual uchar GetLightID() { return 0; }

	//���������� ������
	virtual void Draw(const int &x, const int &y) { }

	//������� ������
	virtual void Select(const int &x, const int &y) { }

	virtual void UpdateGraphicBySeason() {}

	//������� ������ �� ������� �������
	void RemoveRender();

	//����������� ��������� �� ������ �� �������� (�������)
	virtual bool IsBackground() { return false; }
	virtual bool IsWeapon() { return false; }
	virtual bool IsTransparent() { return false; }
	virtual bool IsTranslucent() { return false; }
	virtual bool IsWall() { return false; }
	virtual bool IsDamaging() { return false; }
	virtual bool IsImpassable() { return false; }
	virtual bool IsWet() { return false; }
	virtual bool IsUnknown() { return false; }
	virtual bool IsSurface() { return false; }
	virtual bool IsBridge() { return false; }
	virtual bool IsStackable() { return false; }
	virtual bool IsWindow() { return false; }
	virtual bool IsNoShoot() { return false; }
	virtual bool IsPrefixA() { return false; }
	virtual bool IsPrefixAn() { return false; }
	virtual bool IsInternal() { return false; }
	virtual bool IsFoliage() { return false; }
	virtual bool IsPartialHue() { return false; }
	virtual bool IsUnknown1() { return false; }
	virtual bool IsMap() { return false; }
	virtual bool IsContainer() { return false; }
	virtual bool IsWearable() { return false; }
	virtual bool IsLightSource() { return false; }
	virtual bool IsAnimated() { return false; }
	virtual bool IsNoDiagonal() { return false; }
	virtual bool IsUnknown2() { return false; }
	virtual bool IsArmor() { return false; }
	virtual bool IsRoof() { return false; }
	virtual bool IsDoor() { return false; }
	virtual bool IsStairBack() { return false; }
	virtual bool IsStairRight() { return false; }

	virtual bool IsWorldObject() { return true; }

	//���� ��� ������ ������ �������
	virtual bool IsStaticGroupObject() { return false; }

	//������������� ��������
	virtual bool IsLandObject() { return false; }
	virtual bool IsStaticObject() { return false; }
	virtual bool IsMultiObject() { return false; }
	virtual bool IsEffectObject() { return false; }

	virtual class CRenderStaticObject *StaticGroupObjectPtr() { return NULL; }
	virtual class CLandObject *LandObjectPtr() { return NULL; }
	virtual class CGameCharacter *GameCharacterPtr() { return NULL; }
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
