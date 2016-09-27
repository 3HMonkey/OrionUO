/***********************************************************************************
**
** GUICheckbox.h
**
** ���������� ��� ����������� ��������
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GUICHECKBOX_H
#define GUICHECKBOX_H
//----------------------------------------------------------------------------------
#include "GUIDrawObject.h"
#include "../GLEngine/GLTextTexture.h"
//----------------------------------------------------------------------------------
class CGUICheckbox : public CGUIDrawObject
{
	//!�� �������� � ������� ���������
	SETGET(ushort, GraphicChecked);

	//!�� �������� � ��������� ���������
	SETGET(ushort, GraphicSelected);

	//!�� �������� � ����������� ���������
	SETGET(ushort, GraphicDisabled);

	//!��������� ����������
	SETGET(bool, Checked);

	//!������� ������
	SETGET(SLIDER_TEXT_POSITION, TextPosition);

	//!���������� ������ �� ��� X
	SETGET(int, TextX);

	//!���������� ������ �� ��� Y
	SETGET(int, TextY);

	//!����������� �������� ������
	SETGET(int, DefaultTextOffset);

protected:
	CGLTextTexture m_Text;

	void UpdateTextPosition();

public:
	CGUICheckbox(const uint &serial, const ushort &graphic, const ushort &graphicChecked, const ushort &graphicDisabled, const int &x, const int &y);
	virtual ~CGUICheckbox();

	//!���������� �����
	void SetTextParameters(const uchar &font, const wstring &text, const ushort &color, const SLIDER_TEXT_POSITION &textPosition = STP_RIGHT, const int &textWidth = 0, const TEXT_ALIGN_TYPE &align = TS_LEFT, const ushort &textFlags = 0);
	void SetTextParameters(const uchar &font, const string &text, const ushort &color, const SLIDER_TEXT_POSITION &textPosition = STP_RIGHT, const int &textWidth = 0, const TEXT_ALIGN_TYPE &align = TS_LEFT, const ushort &textFlags = 0);

	virtual void PrepareTextures();
	virtual ushort GetDrawGraphic();

	virtual void Draw(const bool &checktrans = false);
	virtual bool Select();

	virtual void OnMouseEnter();
	virtual void OnMouseExit();
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
