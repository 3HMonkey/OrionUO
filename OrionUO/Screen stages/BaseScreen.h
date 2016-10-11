/***********************************************************************************
**
** BaseScreen.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef BASESCREEN_H
#define BASESCREEN_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../BaseQueue.h"
#include "../GUI/GUI.h"
#include "../Managers/ScreenEffectManager.h"
#include "../Gumps/Gump.h"
#include "../ToolTip.h"
#include "../SelectedObject.h"
#include "../PressedObject.h"
#include "../Managers/MouseManager.h"
//----------------------------------------------------------------------------------
//������� ����� ������ ���� �������
class CBaseScreen : public CBaseQueue
{
	SETGET(ushort, CursorGraphic);

protected:
	//!������ ��������, ������� ���������� ��������� ����� ��������� �������� �������� ������������ ��������� ������
	uchar m_SmoothScreenAction;

	CGump &m_Gump;

public:
	CBaseScreen(CGump &gump);
	virtual ~CBaseScreen() {}

	virtual void PrepareContent() { m_Gump.PrepareContent(); }

	virtual void UpdateContent() { m_Gump.UpdateContent(); }

	/*!
	�������������
	@return 
	*/
	virtual void Init() {}

	/*!
	������������� ����������� ���������
	@return 
	*/
	virtual void InitToolTip() { m_Gump.InitToolTip(); }

	/*!
	���������/����� ��������
	@param [__in] mode true - ���������, false - �����
	@return ��� ������ �������� - ������������� ���������� �������
	*/
	virtual void Render(const bool &mode);

	/*!
	�������� �������� ���������� ������
	@param [__in] action ������������� ��������
	@return 
	*/
	virtual void CreateSmoothAction(uchar action);

	/*!
	��������� ������� ����� ��������
	@param [__in_opt] action ������������� ��������
	@return 
	*/
	virtual void ProcessSmoothAction(uchar action = 0xFF) {}

	/*!
	���������� ��������� ��������
	@return ������ ���������
	*/
	virtual int DrawSmoothMonitor();

	/*!
	��������� ������� ��������
	@return 
	*/
	virtual void DrawSmoothMonitorEffect();



	virtual void OnLeftMouseButtonDown() { m_Gump.OnLeftMouseButtonDown(); }
	virtual void OnLeftMouseButtonUp() { m_Gump.OnLeftMouseButtonUp(); m_Gump.WantRedraw = true; }
	virtual bool OnLeftMouseButtonDoubleClick() { return m_Gump.OnLeftMouseButtonDoubleClick(); }
	virtual void OnRightMouseButtonDown() { m_Gump.OnRightMouseButtonDown(); }
	virtual void OnRightMouseButtonUp() { m_Gump.OnRightMouseButtonUp(); }
	virtual bool OnRightMouseButtonDoubleClick() { return m_Gump.OnRightMouseButtonDoubleClick(); }
	virtual void OnMidMouseButtonDown() { m_Gump.OnMidMouseButtonDown(); }
	virtual void OnMidMouseButtonUp() { m_Gump.OnMidMouseButtonUp(); }
	virtual bool OnMidMouseButtonDoubleClick() { return m_Gump.OnMidMouseButtonDoubleClick(); }
	virtual void OnMidMouseButtonScroll(const bool &up) { m_Gump.OnMidMouseButtonScroll(up); }
	virtual void OnDragging() { m_Gump.OnDragging(); }
	virtual void OnCharPress(const WPARAM &wParam, const LPARAM &lParam) { m_Gump.OnCharPress(wParam, lParam); }
	virtual void OnKeyDown(const WPARAM &wParam, const LPARAM &lParam) { m_Gump.OnKeyDown(wParam, lParam); }
	virtual void OnKeyUp(const WPARAM &wParam, const LPARAM &lParam) { m_Gump.OnKeyUp(wParam, lParam); }
};
//----------------------------------------------------------------------------------
//!��������� �� ������� �����
extern CBaseScreen *g_CurrentScreen;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
