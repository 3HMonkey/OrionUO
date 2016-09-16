/***********************************************************************************
**
** BaseGUI.h
**
** ������� ����� ���������� ����������������� ����������
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef BASEGUI_H
#define BASEGUI_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../RenderObject.h"
#include "../GLEngine/GLEngine.h"
//----------------------------------------------------------------------------------
class CBaseGUI : public CRenderObject
{
	//!��� ����������
	SETGET(GUMP_OBJECT_TYPE, Type);

	//!����������� ����������� �����, ���� ���������� ������
	SETGET(bool, MoveOnDrag);

	//!���� ������������� PartialHue
	SETGET(bool, PartialHue);

	//!����� ������������� ������� ������
	//!			true - ��������� ���������� ������� ����� � �������� �������� (��� CGUIPolygonal � ��������� � ������� � �������, ���� ����� �������� �������� ��������� ��������� m_Graphic)
	//!			false - ����������� ������� �������� ��������
	SETGET(bool, CheckPolygone);

	//!��������� ���������� ��������� ���������� (���������� ������������)
	SETGET(bool, Enabled);

	//!��������/������ ���������� � �� ���������
	SETGET(bool, Visible);

	//!����, ���������� ������ �� ����� ����������, ��� �� ����������� � �����
	SETGET(bool, SelectOnly);

	//!����, ���������� ������ �� ��������� ����������, ��� �� ������
	SETGET(bool, DrawOnly);

public:
	CBaseGUI(const GUMP_OBJECT_TYPE &type, const uint &serial, const ushort &graphic, const ushort &color, const int &x, const int &y);
	virtual ~CBaseGUI();

	/*
	GOT_SCOPE,				//!����� (������� �� 4 ������)
	GOT_SLIDER,				//!��������
	GOT_HTMLGUMP,			//!���� ����
	GOT_XFMHTMLGUMP,		//!���� ���� �� ������� (������� ��� ��)
	GOT_XFMHTMLTOKEN,		//
	*/

	//!��������� ���� g_EntryPointer � ������ ����������
	virtual bool EntryPointerHere() { return false; }

	//!���������� ������ ��� �������
	virtual void SetShaderMode() { }

	//!�������� �� �������� ��� �����������
	virtual ushort GetDrawGraphic() { return m_Graphic; }

	//!���������� ����������
	//!		checktrans - ������������ �������� +������������
	virtual void Draw(const bool &checktrans = false) {}

	//!��������� ���������� �� ����������� ������
	virtual bool Select() { return false; }

	//!�������� �������� �������� ����������
	virtual WISP_GEOMETRY::CSize GetSize() { return WISP_GEOMETRY::CSize(); }

	//!��� ���������� ����������������� ����������
	virtual bool IsGUI() { return true; }

	//!��� HTMLGump ����������
	virtual bool IsHTMLGump() { return false; }

	//!��� ���������� HTMLGump'� (������ ����������, ��������, ���, ������� ������)
	virtual bool IsControlHTML() { return false; }

	//!����������� ������������ ������� ����������, ���� ��� ������, �� ����� ��������� ���-�� ���
	virtual bool IsPressedOuthit() { return false; }
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
