/***********************************************************************************
**
** Scene.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef SCENE_H
#define SCENE_H
//----------------------------------------------------------------------------------
#include "Globals.h"
#include "EnumList.h"
//----------------------------------------------------------------------------------
class CScene
{
protected:
	//!������ ��������, ������� ���������� ��������� ����� ��������� �������� �������� ������������ ��������� ������
	uchar m_SmoothScreenAction;

public:
	CScene() : m_SmoothScreenAction(0) {}
	virtual ~CScene() {}

	/*!
	�������������
	@return 
	*/
	virtual void Init(const GAME_STATE &state);

	/*!
	������������� ����������� ���������
	@return 
	*/
	virtual void InitToolTip();

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
	virtual void ProcessSmoothAction(uchar action = 0xFF);

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



	/*!
	������� ����� ������ ����
	@return 
	*/
	virtual void OnLeftMouseButtonDown();

	/*!
	���������� ����� ������ ����
	@return 
	*/
	virtual void OnLeftMouseButtonUp();

	/*!
	������� ������ ������ ����
	@return 
	*/
	virtual void OnRightMouseButtonDown();

	/*!
	���������� ������ ������ ����
	@return 
	*/
	virtual void OnRightMouseButtonUp();

	/*!
	������� ���� ����� ������� ����
	@return true ��� �������� ���������
	*/
	virtual bool OnLeftMouseButtonDoubleClick();

	/*!
	������� ���� ������ ������� ����
	@return true ��� �������� ���������
	*/
	virtual bool OnRightMouseButtonDoubleClick();

	/*!
	��������� ������� ������ (��������) ����
	@param [__in] state ��������� ��������
	@return 
	*/
	virtual void OnMouseWheel(const MOUSE_WHEEL_STATE &state);

	virtual bool OnMouseWheelDoubleClick();

	virtual void OnDragging();

	virtual void OnDragDrop();

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return 
	*/
	virtual void OnCharPress(const WPARAM &wparam, const LPARAM &lparam);

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return
	*/
	virtual void OnKeyPress(const WPARAM &wparam, const LPARAM &lparam);
};
//----------------------------------------------------------------------------------
extern CScene g_Scene;
//----------------------------------------------------------------------------------
#endif
