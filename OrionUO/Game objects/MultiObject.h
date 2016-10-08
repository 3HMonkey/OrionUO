/***********************************************************************************
**
** MultiObject.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef MULTIOBJECT_H
#define MULTIOBJECT_H
//----------------------------------------------------------------------------------
#include "RenderStaticObject.h"
//----------------------------------------------------------------------------------
//������ ��� ������-�������
class CMultiObject : public CRenderStaticObject
{
	//������ � �������
	SETGET(bool, OnTarget);

	//������������ ������ ��������
	SETGET(ushort, OriginalGraphic);

public:
	CMultiObject(const ushort &graphic, const short &x, const short &y, const char &z, const uint &flags);
	virtual ~CMultiObject();

	virtual void UpdateGraphicBySeason();

	//���������� ������
	virtual void Draw(const int &x, const int &y);

	//������� ������
	virtual void Select(const int &x, const int &y);

	//��� ������ ������
	bool IsMultiObject() { return true; }
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
