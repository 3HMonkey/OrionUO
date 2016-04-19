/****************************************************************************
**
** Gump.h
**
** Copyright (C) September 2015 Hotride
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
*****************************************************************************
*/
//---------------------------------------------------------------------------
#ifndef GumpH
#define GumpH
//---------------------------------------------------------------------------
//!������� ����� ������
class TGump : public TRenderObject
{
protected:
	//!��� �����
	GUMP_TYPE m_GumpType;

	//!�� �����
	DWORD m_ID;

	//!���������� ����� � ���������������� ���������
	int m_MinimizedX;
	int m_MinimizedY;

	//!���� ������������� ������� ���� ������ ������� �����
	bool m_NoClose;

	//!���� ������������� ���������� ����
	bool m_NoMove;

	//!���� �������������
	bool m_Minimized;

	//!���� ����� ���������� � ���������� ��������� � �����������
	bool m_FrameCreated;

	//!������������� ������������ ����
	bool m_FrameRedraw;

	//!��� ����������� ����
	bool m_Blocked;

	//!���� ������������ �� ��������� ����������� � ��������
	bool m_LockMoving;

	/*!
	��������� ��������� ����� � ��� ��������� ��� ���������
	@return 
	*/
	virtual void CalculateGumpState();
public:
	TGump(GUMP_TYPE type, DWORD serial, short x, short y);
	virtual ~TGump();

	SETGET(GUMP_TYPE, GumpType);
	SETGET(DWORD, ID);
	SETGETEX(int, MinimizedX);
	SETGETEX(int, MinimizedY);
	SETGET(bool, NoMove);
	SETGET(bool, NoClose);
	SETGET(bool, Minimized);
	SETGET(bool, FrameCreated);
	SETGET(bool, FrameRedraw);
	SETGET(bool, Blocked);
	SETGET(bool, LockMoving);

	/*!
	�������� ������ ������� ������ �����
	@return 
	*/
	virtual TTextRenderer *GetTextRenderer() { return NULL; }

	/*!
	�������� �������� �������������� �����
	@param [__out] serial ��������
	@param [__out] graphic �������
	@param [__out] color ����
	@param [__out] x ���������� X
	@param [__out] y ���������� Y
	@return 
	*/
	virtual void GetBaseProperties(__out DWORD &serial, __out WORD &graphic, __out WORD &color, __out WORD &x, __out WORD &y);

	/*!
	�������� ������ �����
	@return 
	*/
	virtual void ChangeHeight() {}

	/*!
	������������ ����
	@return 
	*/
	virtual void GenerateFrame() {}

	/*!
	����� �� ���� ���� ���������
	@return 
	*/
	virtual bool CanBeDisplayed() {return true;}

	/*!
	����� �� ���� ���� ��������
	@return 
	*/
	bool CanBeMoved();

	/*!
	���������� ������� �����
	@return 
	*/
	void DrawLocker();

	/*!
	����������/������� ������� �����
	@param [__in] mode true - ���������, false - ����� ��������
	@return 
	*/
	virtual int Draw(__in bool &mode) { return 0; }

	virtual void OnToolTip() {}

	/*!
	������� ����� ������ ����
	@return
	*/
	virtual void OnLeftMouseDown() {}

	/*!
	���������� ����� ������ ����
	@return
	*/
	virtual void OnLeftMouseUp() {}

	/*!
	������� ������ ������ ����
	@return
	*/
	virtual void OnRightMouseDown() {}

	/*!
	���������� ������ ������ ����
	@return
	*/
	virtual void OnRightMouseUp() {}

	/*!
	������� ���� ����� ������� ����
	@return true ��� �������� ���������
	*/
	virtual bool OnLeftMouseDoubleClick() {return false;}

	/*!
	������� ���� ������ ������� ����
	@return true ��� �������� ���������
	*/
	virtual bool OnRightMouseDoubleClick() {return false;}

	/*!
	��������� ������� ������ (��������) ����
	@param [__in] state ��������� ��������
	@return
	*/
	virtual void OnMouseWheel(MOUSE_WHEEL_STATE &state) {}

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return
	*/
	virtual void OnCharPress(WPARAM &wparam, LPARAM &lparam) {}

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return
	*/
	virtual void OnKeyPress(WPARAM &wparam, LPARAM &lparam) {}

	virtual bool EntryPointerHere() {return false;}

	/*!
	���������� �������� �������� � ���� �����������
	@param [__out] currentLine ������� ������
	@param [__in] visibleLines ���������� ������� �����
	@param [__in] maxY ������������ �������� Y ����������
	@param [__in] currentY ������� �������� Y ����������
	@return ���������� Y ���������
	*/
	virtual int CalculateScrollerAndTextPosition(__out int &currentLine, __in int &visibleLines, __in int &maxY, __in int currentY);

	/*!
	���������� �������� ���������
	@param [__in] currentLine ������� ������
	@param [__in] visibleLines ���������� ������� �����
	@param [__in] maxY ������������ �������� Y ����������
	@return ���������� Y ���������
	*/
	virtual int CalculateScrollerY(__in int &currentLine, __in int &visibleLines, __in int &maxY);

	/*!
	��������� ����� �����
	@param [__in] index ������ ������
	@return 
	*/
	void SendGumpResponse(__in int index);

	/*!
	��������� ����� ����
	@param [__in] index ������ �������� ����
	@return 
	*/
	void SendMenuResponse(__in int index);

	/*!
	��������� ��������� ��������� �������� ����� ����
	@param [__in] code ��������� ��������
	@return 
	*/
	void SendTradingResponse(__in int code);

	/*!
	��������� ����� ����� �������
	@param [__in] mode ���������
	@return 
	*/
	void SendTextEntryDialogResponse(__in bool mode);

	/*!
	��������� ������ ��������� �����
	@return 
	*/
	void SendRenameRequest();

	/*!
	��������� ������ ���� �������
	@return 
	*/
	void SendSellList();

	/*!
	��������� ������ ���� �������
	@return 
	*/
	void SendBuyList();

	/*!
	��������� ������ ��� ������
	@param [__in] flag ���� ��� ����
	@return 
	*/
	void SendTipRequest(__in BYTE flag);
 };
//---------------------------------------------------------------------------
//!������ �� ����, ������� � ������ ������ �������� ������
extern TGump *g_ResizedGump;
//---------------------------------------------------------------------------
#endif