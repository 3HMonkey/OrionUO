/***********************************************************************************
**
** GUITextEntry.h
**
** ���������� ��� ����������� ���� ��� ����� ������
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GUITEXTENTRY_H
#define GUITEXTENTRY_H
//----------------------------------------------------------------------------------
#include "BaseGUI.h"
#include "../GLEngine/GLTextTexture.h"
#include "../TextEngine/EntryText.h"
//----------------------------------------------------------------------------------
class CGUITextEntry : public CBaseGUI
{
	//!���� ������ � ��������� ���������
	SETGET(ushort, ColorSelected);

	//!���� ������ � ��������� ������
	SETGET(ushort, ColorFocused);

	//!����� � �������
	SETGET(bool, Unicode);

	//!�����
	SETGET(uchar, Font);

	//!���������� ������
	SETGET(TEXT_ALIGN_TYPE, Align);

	//!����� ������
	SETGET(ushort, TextFlags);

	//!����������� ����� ������� �� ��������� ����� ���� ������ �����, ���-������ � �.�.)
	SETGET(bool, CheckOnSerial);

	//!������ ��� ������
	SETGET(bool, ReadOnly);

	//!���� ������
	SETGET(bool, Focused);

	//!���� ������������� ����������� �����
	SETGET(bool, UseGlobalColor);

	//!R-���������� ����������� OGL ����� ����� ���������� �������
	SETGET(uchar, GlobalColorSelectedR);

	//!G-���������� ����������� OGL ����� ����� ���������� �������
	SETGET(uchar, GlobalColorSelectedG);

	//!B-���������� ����������� OGL ����� ����� ���������� �������
	SETGET(uchar, GlobalColorSelectedB);

	//!�����-����� ����������� OGL ����� ����� ���������� �������
	SETGET(uchar, GlobalColorSelectedA);

	//!R-���������� ����������� OGL ����� ����� ���������� ��������� � ������
	SETGET(uchar, GlobalColorFocusedR);

	//!G-���������� ����������� OGL ����� ����� ���������� ��������� � ������
	SETGET(uchar, GlobalColorFocusedG);

	//!B-���������� ����������� OGL ����� ����� ���������� ��������� � ������
	SETGET(uchar, GlobalColorFocusedB);

	//!�����-����� ����������� OGL ����� ����� ���������� ��������� � ������
	SETGET(uchar, GlobalColorFocusedA);

	//!�������� ������ ����� ���������� ��������� � ������
	SETGET(char, FocusedOffsetY);

public:
	CGUITextEntry(const uint &serial, const ushort &color, const ushort &colorSelected, const ushort &colorFocused, const int &x, const int &y, const int &maxWidth = 0, const bool &unicode = true, const uchar &font = 0, const TEXT_ALIGN_TYPE &align = TS_LEFT, const ushort &textFlags = 0, const int &maxLength = 0);
	virtual ~CGUITextEntry();

	//!������ ������ ��� ����� ������
	class CEntryText m_Entry;

	virtual bool EntryPointerHere();

	virtual WISP_GEOMETRY::CSize GetSize();

	//!���������� ���������� OGL ���� ����� ���������� ������
	void SetGlobalColor(const bool &use, const uint &selected = 0, const uint &focused = 0);

	//!������� �� ����������
	void OnClick(CGump *gump, const int &x, const int &y);

	virtual void OnMouseEnter();
	virtual void OnMouseExit();

	virtual void Draw(const bool &checktrans = false);
	virtual bool Select();
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
