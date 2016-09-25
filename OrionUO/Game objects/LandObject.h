/***********************************************************************************
**
** LandObject.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef LANDOBJECT_H
#define LANDOBJECT_H
//----------------------------------------------------------------------------------
#include "MapObject.h"
#include "../GLEngine/GLVector.h"
//----------------------------------------------------------------------------------
//����� ���������
class CLandObject : public CMapObject
{
	//���������� �������� ������
	SETGET(RECT, Rect);

	//����������� Z ����������
	SETGET(char, MinZ);

	//���� ����������� (true - �������� �� texmaps, false - �� art.mul)
	SETGET(bool, IsStretched);

	//������������ ������ ��������
	SETGET(ushort, OriginalGraphic);

public:
	CLandObject(const uint &serial, const ushort &graphic, const ushort &color, const short &x, const short &y, const char &z);
	virtual ~CLandObject() {}

	virtual void UpdateGraphicBySeason();

	//������� �������
	CVector m_Normals[4];

	//���������� ������
	virtual void Draw(const int &x, const int &y);

	//������� ������
	virtual void Select(const int &x, const int &y);

	//��� ������ ���������
	bool IsLandObject() {return true;}

	void UpdateZ(const char &zTop, const char &zRight, const char &zBottom);

	//������������� ��� ��������� ��������
	bool Ignored() {return (Graphic == 2 || Graphic == 0x1DB || (Graphic >= 0x1AE && Graphic <= 0x1B5));}

	virtual CLandObject *LandObjectPtr() { return this; }
};
//---------------------------------------------------------------------------
#endif