/***********************************************************************************
**
** GUIHTMLText.h
**
** ���������� ������ � ������������ �������� �� HTML-������� ��� HTMLGump'�
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GUIHTMLTEXT_H
#define GUIHTMLTEXT_H
//----------------------------------------------------------------------------------
#include "BaseGUI.h"
#include "../GLEngine/GLHTMLTextTexture.h"
//----------------------------------------------------------------------------------
class CGUIHTMLText : public CBaseGUI
{
	//!������ ������
	SETGET(uint, TextID);

	//!��������� ���� ������
	SETGET(uint, HTMLStartColor);

	//!�����
	SETGET(wstring, Text);

	//!�����
	SETGET(uchar, Font);

	//!���������� ������
	SETGET(TEXT_ALIGN_TYPE, Align);

	//!����� ������
	SETGET(ushort, TextFlags);

	//!������ ������
	SETGET(int, Width);

public:
	CGUIHTMLText(const uint &index, const uchar &font, const ushort &color, const int &x, const int &y, const int &width = 0, const TEXT_ALIGN_TYPE &align = TS_LEFT, const ushort &textFlags = 0, const uint &htmlStartColor = 0xFFFFFFFF);
	virtual ~CGUIHTMLText();

	//!�������� ������
	CGLHTMLTextTexture m_Texture;

	virtual WISP_GEOMETRY::CSize GetSize() { return WISP_GEOMETRY::CSize(m_Texture.Width, m_Texture.Height); }

	//!������� �������� ������
	void CreateTexture();

	virtual void Draw(const bool &checktrans = false);
	virtual bool Select();
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
