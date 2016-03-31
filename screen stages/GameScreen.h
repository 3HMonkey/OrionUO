/****************************************************************************
**
** GameScreen.h
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
#ifndef GameScreenH
#define GameScreenH
//---------------------------------------------------------------------------
//!��������� � ������� � ���������� � ������������ �������� ����
struct RENDER_VARIABLES_FOR_GAME_WINDOW
{
	//!��������� ����
	int GameWindowPosX;
	int GameWindowPosY;

	//!�������� ����
	int GameWindowSizeX;
	int GameWindowSizeY;

	//!����� ����
	int GameWindowCenterX;
	int GameWindowCenterY;

	//!��������� �����������
	int RealMinRangeX;
	int RealMaxRangeX;
	int RealMinRangeY;
	int RealMaxRangeY;

	//!������� ������ ��� �����������
	int MinBlockX;
	int MinBlockY;
	int MaxBlockX;
	int MaxBlockY;

	//!���������� �������� ��� �����������
	int MinPixelsX;
	int MaxPixelsX;
	int MinPixelsY;
	int MaxPixelsY;

	//!���������� ������
	int PlayerX;
	int PlayerY;
	int PlayerZ;
};
//---------------------------------------------------------------------------
//!��������� ������ � ��������� �����
struct LIGHT_DATA
{
	//!������ �����
	BYTE ID;

	//!���� �����
	WORD Color;

	//!�������� ����������
	int DrawX;
	int DrawY;
};
//---------------------------------------------------------------------------
//!��������� ������ � ����������� ��� �������
struct RENDER_OBJECT_DATA
{
	//!������ �� ������ �������
	TRenderWorldObject *Obj;

	//!���� �������, ��������� �� ����� ��������� ������� (���� �������� �����)
	WORD GrayColor;

	//!�������� ���������� �������
	int X;
	int Y;
};
//---------------------------------------------------------------------------
//!��������� ������ � ����������� ��� ����� � ������ ������� (Object Handles)
struct OBJECT_HANDLES_DATA
{
	//!������ �� ������ �������
	TGameObject *Obj;

	//!�������� ���������� �������
	int X;
	int Y;
};
//---------------------------------------------------------------------------
class TGameScreen : public TBaseScreen
{
private:
	//!��������� � ������� � ���������� � ������������ �������� ����
	RENDER_VARIABLES_FOR_GAME_WINDOW m_RenderBounds;

	//!����������� ����������� �������� ����
	bool m_GameWindowMoving;

	//!����������� ��������� ������� �������� ����
	bool m_GameWindowResizing;

	//!������ �������� ��� ������
	OBJECT_HANDLES_DATA m_ObjectHandlesList[MAX_OBJECT_HANDLES];

	//!���������� �������� ��� ������
	int m_ObjectHandlesCount;

	//!������ �������� ��� �����������
	RENDER_OBJECT_DATA *m_RenderList;

	//!������ ������ �������� �������
	int m_RenderListSize;

	//!���������� �������� � ������
	int m_RenderListCount;

	//!����, ������������ ������������� ������ �������
	bool m_RenderListInitalized;

	//!������ ���������� �����
	LIGHT_DATA m_Light[MAX_LIGHT_SOURCES];

	//!���������� ���������� �����
	int m_LightCount;

	//!������������ �� ��������� ��� ����������� �������� �����
	bool m_UseLight;

	//!������������ �������� ����������� �� Z ����������
	int m_MaxDrawZ;

	//!��������� �� ������� ������
	TRenderTextObject *m_GameWindowText;

	/*!
	���������� �������� Z ���������� ��� �������
	@param [__out] noDrawRoof �� �������� ����� � ������� ����� ��������
	@param [__out] maxGroundZ ������������ Z ���������� ���������
	@return ������������ Z ���������� ���������
	*/
	int GetMaxDrawZ(__out bool &noDrawRoof, __out char &maxGroundZ);

	/*!
	��������� ��������� ���� (���������� �������. ����-����� � �.�.)
	@param [__out] charSelected ��������� ��������� ���������
	@return 
	*/
	void CheckMouseEvents(__out bool &charSelected);

	/*!
	���������� ���������� ������������� ������
	 @param [__in] mode true - ���������,
	 @return 
	*/
	void CalculateGameWindowText(__in bool &mode);

	/*!
	��������� �������� ����
	@param [__in] mode true - ���������, false - �����
	@return 
	*/
	void DrawGameWindow(__in bool &mode);

	/*!
	����������� ���������� �����
	@return 
	*/
	void DrawGameWindowLight();

	/*!
	����������� ������ ��� ��������� ����
	@param [__in] mode true - ���������, false - �����
	@return 
	*/
	void DrawGameWindowText(__in bool &mode);

	/*!
	���������� ������������ ���� �������� � ��������� �����������
	@param [__in] graphic ����� �������� ������
	@param [__in] x ���������� X ������
	@param [__in] y ���������� Y ������
	@param [__in] z ���������� Z ������
	@return 
	*/
	void ApplyTransparentFoliageToUnion(__in WORD &graphic, __in int &x, __in int &y, __in int &z);

	/*!
	�������� �������������� ����� � ������ ���� (� ����������� ����������� ������������ ���� ������)
	@param [__in] graphic ������ �������� ������
	@param [__in] x ���������� X ������
	@param [__in] y ���������� Y ������
	@param [__in] z ���������� Z ������
	@return 
	*/
	void CheckFoliageUnion(__in WORD graphic, __in int x, __in int y, __in int z);

	/*!
	������� ����������� ������� ������ �������
	@return 
	*/
	void IncreaseRenderList();

	int m_ObjCount;
	RENDER_OBJECT_DATA *m_ObjList;

	//������� ����������� ������� ������ �������
	void IncreaseObjList();
public:
	TGameScreen();
	virtual ~TGameScreen();

	//�������������� ������� ��� �������� ��������
	static const BYTE ID_SMOOTH_GS_LOGOUT = 1;

	SETGET(bool, UseLight);
	SETGET(bool, RenderListInitalized);

	/*!
	��������� ������� ����� �������� ���������� ������
	@param [__in_opt] action ������������� ��������
	@return 
	*/
	void ProcessSmoothAction(__in_opt BYTE action = 0xFF);

	/*!
	���������� ���������� �������� ����
	@return 
	*/
	void CalculateGameWindowBounds();

	/*!
	������ ������ �������� �������, ���������� ������������ ���� �������� (� �.�. ���������)
	@return 
	*/
	void CalculateRenderList();

	/*!
	�������������
	@return 
	*/
	void Init();

	/*!
	������������� ����������� ���������
	@return 
	*/
	void InitPopupHelp();

	/*!
	������� ���������� ��������� �����
	@param [__in] rwo ������� ������, ���������� ����
	@param [__in] lightObject ������, ���������� ����
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@return 
	*/
	void AddLight(__in TRenderWorldObject *rwo, __in TRenderWorldObject *lightObject, __in int x, __in int y);

	/*!
	���������/����� ��������
	@param [__in] mode true - ���������, false - �����
	@return ��� ������ �������� - ������������� ���������� �������
	*/
	int Render(__in bool mode);



	/*!
	������� ����� ������ ����
	@return 
	*/
	void OnLeftMouseDown();

	/*!
	���������� ����� ������ ����
	@return 
	*/
	void OnLeftMouseUp();

	/*!
	������� ������ ������ ����
	@return 
	*/
	void OnRightMouseDown();

	/*!
	���������� ������ ������ ����
	@return 
	*/
	void OnRightMouseUp();

	/*!
	������� ���� ����� ������� ����
	@return true ��� �������� ���������
	*/
	bool OnLeftMouseDoubleClick();

	/*!
	������� ���� ������ ������� ����
	@return true ��� �������� ���������
	*/
	bool OnRightMouseDoubleClick();

	/*!
	��������� ������� ������ (��������) ����
	@param [__in] state ��������� ��������
	@return 
	*/
	void OnMouseWheel(__in MOUSE_WHEEL_STATE state);

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return 
	*/
	void OnCharPress(__in WPARAM wparam, __in LPARAM lparam);

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return 
	*/
	void OnKeyPress(__in WPARAM wparam, __in LPARAM lparam);
 };
//---------------------------------------------------------------------------
 //!������ �� �����
 extern TGameScreen *GameScreen;

 //!������ �� ��������� � �������������� �������� ����
extern RENDER_VARIABLES_FOR_GAME_WINDOW *g_RenderBounds;
//---------------------------------------------------------------------------
#endif