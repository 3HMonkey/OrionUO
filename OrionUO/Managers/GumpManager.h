/***********************************************************************************
**
** GumpManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GUMPMANAGER_H
#define GUMPMANAGER_H
//----------------------------------------------------------------------------------
#include "../BaseQueue.h"
#include "../Gumps/Gump.h"
//----------------------------------------------------------------------------------
//!����� ��������� ������
class CGumpManager : public CBaseQueue
{
private:
	/*!
	��������� ���������� ����������� ��� ����
	@return ���������� non-party �����������
	*/
	int GetNonpartyStatusbarsCount();

public:
	CGumpManager() : CBaseQueue() {}
	virtual ~CGumpManager() {}

	/*!
	�������� ����
	@param [__in] obj ������ �� ����
	@return 
	*/
	void AddGump(CGump *obj);

	/*!
	�������� ���������� �����
	@param [__in] serial �������� �����
	@param [__in] ID ID �����
	@param [__in] Type ��� �����
	@return ������ �� ����������� ���� ��� NULL
	*/
	CGump *UpdateContent(uint serial, uint ID, GUMP_TYPE Type);

	/*!
	�������� ����
	@param [__in] serial �������� �����
	@param [__in] ID ID �����
	@param [__in] Type ��� �����
	@return ������ �� ����������� ���� ��� NULL
	*/
	CGump *UpdateGump(uint serial, uint ID, GUMP_TYPE Type);

	/*!
	����� ����
	@param [__in] serial �������� �����
	@param [__in] ID ID �����
	@param [__in] Type ��� �����
	@return ������ �� ���� ��� NULL
	*/
	CGump *GetGump(uint serial, uint ID, GUMP_TYPE Type);

	/*!
	�������� ����-�������� ������� �������� TEntryText
	@return ������ �� ���� ��� NULL
	*/
	CGump *GetTextEntryOwner();

	/*!
	���������, ���������� �� ����
	@param [__in] gumpID ID ����� (� ������)
	@return 
	*/
	CGump *GumpExists(uint gumpID);

	/*!
	������� ��� ����� � ���������� �����������
	@param [__in] serial �������� �����
	@param [__in] ID ID �����
	@param [__in] Type ��� �����
	@return 
	*/
	void CloseGump(uint serial, uint ID, GUMP_TYPE Type);

	/*!
	������� ����
	@param [__in] obj ������ �� ����
	@return 
	*/
	void RemoveGump(CGump *obj);

	/*!
	������������ ��� �����
	@return 
	*/
	void RedrawAll();

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

	void PrepareContent();

	void RemoveMarked();

	/*!
	���������� �������
	@return 
	*/
	void PrepareTextures();

	void Draw(const bool &blocked);

	void Select(const bool &blocked);

	void InitToolTip();



	void OnLeftMouseButtonDown(const bool &blocked);
	bool OnLeftMouseButtonUp(const bool &blocked);
	bool OnLeftMouseButtonDoubleClick(const bool &blocked);

	void OnRightMouseButtonDown(const bool &blocked);
	void OnRightMouseButtonUp(const bool &blocked);
	bool OnRightMouseButtonDoubleClick(const bool &blocked) { return false; }

	void OnMidMouseButtonScroll(const bool &up, const bool &blocked);

	void OnDragging(const bool &blocked);

	bool OnCharPress(const WPARAM &wParam, const LPARAM &lParam, const bool &blocked);
	bool OnKeyDown(const WPARAM &wParam, const LPARAM &lParam, const bool &blocked);

	void Load(const string &path);
	void Save(const string &path);
};
//----------------------------------------------------------------------------------
//!������ �� �������� ������
extern CGumpManager g_GumpManager;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
