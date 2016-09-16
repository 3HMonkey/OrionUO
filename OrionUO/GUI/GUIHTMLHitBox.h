/***********************************************************************************
**
** GUIHTMLHitBox.h
**
** ���������� ������ ���� ��� HTMLGump'�
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GUIHTMLHITBOX_H
#define GUIHTMLHITBOX_H
//----------------------------------------------------------------------------------
#include "GUIHitBox.h"
//----------------------------------------------------------------------------------
class CGUIHTMLHitBox : public CGUIHitBox
{
private:
	//!����-��������
	class CGUIHTMLGump *m_HTMLGump;

public:
	CGUIHTMLHitBox(class CGUIHTMLGump *htmlGump, const uint &serial, const int &x, const int &y, const int &width, const int &height, const bool &callOnMouseUp = false);
	virtual ~CGUIHTMLHitBox();

	//!������� ���������
	void Scroll(const bool &up, const uint &delay);

	virtual bool IsControlHTML() { return true; }
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
