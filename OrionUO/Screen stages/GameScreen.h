/***********************************************************************************
**
** GameScreen.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GAMESCREEN_H
#define GAMESCREEN_H
//----------------------------------------------------------------------------------
#include "BaseScreen.h"
#include "../Gumps/GumpScreenGame.h"
//----------------------------------------------------------------------------------
//!��������� � ������� � ���������� � ������������ �������� ����
struct RENDER_VARIABLES_FOR_GAME_WINDOW
{
	//!��������� ����
	int GameWindowPosX;
	int GameWindowPosY;

	//!�������� ����
	int GameWindowWidth;
	int GameWindowHeight;

	//!�������� ����������������� ����
	int GameWindowScaledWidth;
	int GameWindowScaledHeight;

	//!�������� ����
	int GameWindowScaledOffsetX;
	int GameWindowScaledOffsetY;

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
//----------------------------------------------------------------------------------
//!��������� ������ � ��������� �����
struct LIGHT_DATA
{
	//!������ �����
	uchar ID;

	//!���� �����
	ushort Color;

	//!�������� ����������
	int DrawX;
	int DrawY;
};
//----------------------------------------------------------------------------------
//!��������� ������ � ����������� ��� �������
struct RENDER_OBJECT_DATA
{
	//!������ �� ������ �������
	class CRenderWorldObject *Object;

	//!���� �������, ��������� �� ����� ��������� ������� (���� �������� �����)
	ushort GrayColor;

	//!�������� ���������� �������
	int X;
	int Y;
};
//----------------------------------------------------------------------------------
//!��������� ������ � ����������� ��� �������
struct OBJECT_HITS_INFO
{
	//!�������� ����������
	int X;
	int Y;

	//!���� � ����������� �� ��������� ���������
	ushort Color;

	//!������ �����
	int Width;
};
//----------------------------------------------------------------------------------
//!��������� ������ � ����������� ��� ����� � ������ ������� (Object Handles)
struct OBJECT_HANDLES_DATA
{
	//!������ �� ������ �������
	class CGameObject *Obj;

	//!�������� ���������� �������
	int X;
	int Y;
};
//----------------------------------------------------------------------------------
class CGameScreen : public CBaseScreen
{
	//!������������ �� ��������� ��� ����������� �������� �����
	SETGET(bool, UseLight);
	//!����, ������������ ������������� ������ �������
	SETGET(bool, RenderListInitalized);

private:
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

	//!������ ���������� �����
	LIGHT_DATA m_Light[MAX_LIGHT_SOURCES];

	//!���������� ���������� �����
	int m_LightCount;

	//!������������ �������� ����������� �� Z ����������
	int m_MaxDrawZ;

	/*!
	���������� �������� Z ���������� ��� �������
	@param [__out] noDrawRoof �� �������� ����� � ������� ����� ��������
	@param [__out] maxGroundZ ������������ Z ���������� ���������
	@return ������������ Z ���������� ���������
	*/
	int GetMaxDrawZ(bool &noDrawRoof, char &maxGroundZ);

	/*!
	��������� �������� ����
	@param [__in] mode true - ���������, false - �����
	@return 
	*/
	void DrawGameWindow(const bool &mode);

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
	void DrawGameWindowText(const bool &mode);

	/*!
	���������� ������������ ���� �������� � ��������� �����������
	@param [__in] graphic ����� �������� ������
	@param [__in] x ���������� X ������
	@param [__in] y ���������� Y ������
	@param [__in] z ���������� Z ������
	@return 
	*/
	void ApplyTransparentFoliageToUnion(const ushort &graphic, const int &x, const int &y, const int &z);

	/*!
	�������� �������������� ����� � ������ ���� (� ����������� ����������� ������������ ���� ������)
	@param [__in] graphic ������ �������� ������
	@param [__in] x ���������� X ������
	@param [__in] y ���������� Y ������
	@param [__in] z ���������� Z ������
	@return 
	*/
	void CheckFoliageUnion(ushort graphic, int x, int y, int z);

	/*!
	������� ���������� ������� ������ �������
	@return 
	*/
	void IncreaseRenderList();

	void AddTileToRenderList(class CRenderWorldObject *obj, const int &drawX, const int &drawY, const int &worldX, const int &worldY, const uchar &renderIndex, const bool &useObjectHandles, const int &objectHandlesOffsetX, const int &maxZ = 150);

	void AddOffsetCharacterTileToRenderList(class CGameObject *obj, int drawX, int drawY, const uchar &renderIndex, const bool &useObjectHandles, const int &objectHandlesOffsetX);

	class CGumpScreenGame m_GameScreenGump;

public:
	CGameScreen();
	virtual ~CGameScreen();

	//�������������� ������� ��� �������� ��������
	static const uchar ID_SMOOTH_GS_LOGOUT = 1;

	/*!
	��������� ������� ����� �������� ���������� ������
	@param [__in_opt] action ������������� ��������
	@return 
	*/
	virtual void ProcessSmoothAction(uchar action = 0xFF);

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
	virtual void Init();

	/*!
	������������� ����������� ���������
	@return 
	*/
	virtual void InitToolTip();

	/*!
	������� ���������� ��������� �����
	@param [__in] rwo ������� ������, ���������� ����
	@param [__in] lightObject ������, ���������� ����
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@return 
	*/
	void AddLight(class CRenderWorldObject *rwo, class CRenderWorldObject *lightObject, const int &x, const int &y);

	virtual void PrepareContent();

	/*!
	���������/����� ��������
	@param [__in] mode true - ���������, false - �����
	@return ��� ������ �������� - ������������� ���������� �������
	*/
	virtual void Render(const bool &mode);



	virtual void OnLeftMouseButtonDown();
	virtual void OnLeftMouseButtonUp();
	virtual bool OnLeftMouseButtonDoubleClick();
	virtual void OnRightMouseButtonDown();
	virtual void OnRightMouseButtonUp();
	virtual bool OnRightMouseButtonDoubleClick();
	virtual void OnMidMouseButtonDown() {}
	virtual void OnMidMouseButtonUp() {}
	virtual bool OnMidMouseButtonDoubleClick() { return false; }
	virtual void OnMidMouseButtonScroll(const bool &up);
	virtual void OnDragging();
	virtual void OnCharPress(const WPARAM &wParam, const LPARAM &lParam);
	virtual void OnKeyDown(const WPARAM &wParam, const LPARAM &lParam);
	virtual void OnKeyUp(const WPARAM &wParam, const LPARAM &lParam);
};
//----------------------------------------------------------------------------------
//!������ �� �����
extern CGameScreen g_GameScreen;

//!��������� � ������� � ���������� � ������������ �������� ����
extern RENDER_VARIABLES_FOR_GAME_WINDOW g_RenderBounds;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
