/****************************************************************************
**
** GumpManager.h
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
#ifndef GumpManagerH
#define GumpManagerH
//--------------------------------------------------------------------------
//!����� ��������� ������
class TGumpManager : public TBaseQueue
{
private:
	/*!
	��������� ���������� ����������� ��� ����
	@return ���������� non-party �����������
	*/
	int GetNonpartyStatusbarsCount();

public:
	TGumpManager() : TBaseQueue() {}
	virtual ~TGumpManager() {}

	/*!
	�������� ����
	@param [__in] obj ������ �� ����
	@return 
	*/
	void AddGump(__in TGump *obj);

	/*!
	�������� ����
	@param [__in] serial �������� �����
	@param [__in] ID ID �����
	@param [__in] Type ��� �����
	@return ������ �� ����������� ���� ��� NULL
	*/
	TGump *UpdateGump(__in DWORD serial, __in DWORD ID, __in GUMP_TYPE Type);

	/*!
	����� ����
	@param [__in] serial �������� �����
	@param [__in] ID ID �����
	@param [__in] Type ��� �����
	@return ������ �� ���� ��� NULL
	*/
	TGump *GetGump(__in DWORD serial, __in DWORD ID, __in GUMP_TYPE Type);

	/*!
	�������� ����-�������� ������� �������� TEntryText
	@return ������ �� ���� ��� NULL
	*/
	TGump *GetTextEntryOwner();

	/*!
	���������, ���������� �� ����
	@param [__in] gumpID ID ����� (� ������)
	@return 
	*/
	TGump *GumpExists(__in DWORD gumpID);

	/*!
	������� ��� ����� � ���������� �����������
	@param [__in] serial �������� �����
	@param [__in] ID ID �����
	@param [__in] Type ��� �����
	@return 
	*/
	void CloseGump(__in DWORD serial, __in DWORD ID, __in GUMP_TYPE Type);

	/*!
	������� ����
	@param [__in] obj ������ �� ����
	@return 
	*/
	void RemoveGump(__in TGump *obj);

	/*!
	������������ ��� �����
	@return 
	*/
	void RedrawAll();

	/*!
	���������� �������
	@return 
	*/
	void PrepareTextures();

	/*!
	���������/����� ������
	@param [__in] mode true - ���������, false - �����
	@param [__in] blocked ��������� ������, ��� �������� �������� �����
	@return 
	*/
	void Draw(__in bool &mode, __in bool blocked);

	void OnPopupHelp();



	/*!
	������� ����� ������ ����
	@param [__in] blocked ��������� ������
	@return 
	*/
	void OnLeftMouseDown(__in bool blocked);

	/*!
	���������� ����� ������ ����
	@param [__in] blocked ��������� ������
	@return 
	*/
	bool OnLeftMouseUp(__in bool blocked);

	/*!
	������� ������ ������ ����
	@param [__in] blocked ��������� ������
	@return 
	*/
	void OnRightMouseDown(__in bool blocked);

	/*!
	���������� ������ ������ ����
	@param [__in] blocked ��������� ������
	@return 
	*/
	void OnRightMouseUp(__in bool blocked);

	/*!
	������� ���� ����� ������� ����
	@param [__in] blocked ��������� ������
	@return true ��� �������� ���������
	*/
	bool OnLeftMouseDoubleClick(__in bool blocked);

	/*!
	������� ���� ������ ������� ����
	@param [__in] blocked ��������� ������
	@return true ��� �������� ���������
	*/
	bool OnRightMouseDoubleClick(__in bool blocked);

	/*!
	��������� ������� ������ (��������) ����
	@param [__in] state ��������� ��������
	@param [__in] blocked ��������� ������
	@return 
	*/
	void OnMouseWheel(__in MOUSE_WHEEL_STATE state, __in bool blocked);

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@param [__in] blocked ��������� ������
	@return true ��� �������� ���������
	*/
	bool OnCharPress(__in WPARAM wparam, __in LPARAM lparam, __in bool blocked);

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@param [__in] blocked ��������� ������
	@return true ��� �������� ���������
	*/
	bool OnKeyPress(__in WPARAM wparam, __in LPARAM lparam, __in bool blocked);

	/*!
	������� �������� ��������� (���������� ����� ���������)
	@return 
	*/
	void OnDelete();

	/*!
	������� �����, ������� �� ����� ���� ��������� ��-�� ��������� ��������� �� �������
	@return 
	*/
	void RemoveRangedGumps();

	/*!
	�������� ������ �� �������
	@param [__in] path ���� � ����� �������
	@return 
	*/
	void Load(__in string path);

	/*!
	��������� ����� � ������
	@param [__in] path ���� � ����� �������
	@return 
	*/
	void Save(__in string path);
 };
//--------------------------------------------------------------------------
//!������ �� �������� ������
extern TGumpManager *GumpManager;
//--------------------------------------------------------------------------
#endif