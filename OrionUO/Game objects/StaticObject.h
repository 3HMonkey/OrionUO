/***********************************************************************************
**
** StaticObject.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef STATICOBJECT_H
#define STATICOBJECT_H
//----------------------------------------------------------------------------------
#include "RenderStaticObject.h"
//----------------------------------------------------------------------------------
//����� ������� �������
class CStaticObject : public CRenderStaticObject
{
	//������������ ������ ��������
	SETGET(ushort, OriginalGraphic);

public:
	CStaticObject(const uint &serial, const ushort &graphic, const ushort &color, const short &x, const short &y, const char &z);
	virtual ~CStaticObject() {}

	virtual void UpdateGraphicBySeason();

	//���������� ������
	virtual void Draw(const int &x, const int &y);

	//������� ������
	virtual void Select(const int &x, const int &y);

	//��� ������ �������
	bool IsStaticObject() {return true;}
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
