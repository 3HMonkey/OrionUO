/***********************************************************************************
**
** GUIComboBox.h
**
** ���������� ��� ����������� ����������� ������
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GUICOMBOBOX_H
#define GUICOMBOBOX_H
//----------------------------------------------------------------------------------
#include "BaseGUI.h"
//----------------------------------------------------------------------------------
class CGUIComboBox : public CBaseGUI
{
	//!�� �������� � ����������� ���������
	SETGET(ushort, OpenGraphic);

	//!���� ���������� ����, ���� �������� - ������������ ������������� �������� (5 ����) m_OpenGraphic, � ����������� ��������� ������� Resizepic �� m_OpenGraphic
	SETGET(bool, CompositeBackground);

	//!���������� ������������ ����� � �������� ������
	SETGETE(int, ShowItemsCount, OnChangeShowItemsCount);

	//!������ � ��������� ��������� (������ ��� ��������� Resizepic)
	SETGET(int, Width);

	//!������ � ����������� ��������� (������ ��� ��������� Resizepic)
	SETGET(int, OpenedWidth);

	//!��������� ������ ��� ����������� � ����������� ���������
	SETGET(int, StartIndex);

	//!������� ��������� ������
	SETGET(int, SelectedIndex);

	//!����������� ���������� (����������� � Select())
	SETGET(int, ListingDirection);

	//!������ ����������
	SETGET(uint, ListingTimer);

	//!������������ ����������� ��������� �� ��� Y
	SETGET(bool, ShowMaximizedCenter);

	//!�������� ������ ��� �����������
	SETGET(int, TextOffsetY);

private:
	//!�������� ��������� �� ������ ������ �����������
	CBaseGUI *SkipToStart();
	
	//!������� ������� ����
	int m_ArrowX;

	//!�������� �� ��� Y
	int m_OffsetY;

	//!��� �� ��� Y
	int m_StepY;

	//!������� ������
	int m_WorkWidth;

	//!������� ������
	int m_WorkHeight;

	//!��������� � ��������� ��������� �����
	class CGUIText *m_Text;

public:
	CGUIComboBox(const uint &serial, const ushort &graphic, const bool &compositeBackground, const ushort &openGraphic, const int &x, const int &y, const int &width, const int &showItemsCount, const bool &showMaximizedCenter);
	virtual ~CGUIComboBox();

	//!���������� �����
	void SetText(class CGUIText *text) { m_Text = text; }

	//!����������� ������
	void RecalculateWidth();

	virtual WISP_GEOMETRY::CSize GetSize();

	virtual void PrepareTextures();

	virtual void Draw(const bool &checktrans = false);
	virtual bool Select();

	//!�������� ������ �� ��������� ������� ������ (��� �� ������ ����)
	CBaseGUI *SelectedItem();

	//!�������� ������ ���������� ��������, -1 ���� ������ �� �������
	int IsSelectedItem();
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
