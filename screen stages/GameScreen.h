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
//��������� � ������� � ���������� � ������������ �������� ����
struct RENDER_VARIABLES_FOR_GAME_WINDOW
{
	//��������� ����
	int GameWindowPosX;
	int GameWindowPosY;

	//�������� ����
	int GameWindowSizeX;
	int GameWindowSizeY;

	//����� ����
	int GameWindowCenterX;
	int GameWindowCenterY;

	//��������� �����������
	int RealMinRangeX;
	int RealMaxRangeX;
	int RealMinRangeY;
	int RealMaxRangeY;

	//������� ������ ��� �����������
	int MinBlockX;
	int MinBlockY;
	int MaxBlockX;
	int MaxBlockY;

	//���������� �������� ��� �����������
	int MinPixelsX;
	int MaxPixelsX;
	int MinPixelsY;
	int MaxPixelsY;

	//���������� ������
	int PlayerX;
	int PlayerY;
	int PlayerZ;
};
//---------------------------------------------------------------------------
//��������� ������ � ��������� �����
struct LIGHT_DATA
{
	//������ �����
	BYTE ID;

	//���� �����
	WORD Color;

	//�������� ����������
	int DrawX;
	int DrawY;
};
//---------------------------------------------------------------------------
//��������� ������ � ����������� ��� �������
struct RENDER_OBJECT_DATA
{
	//������ �� ������ �������
	TRenderWorldObject *Obj;

	//���� �������, ��������� �� ����� ��������� ������� (���� �������� �����)
	WORD GrayColor;

	//�������� ���������� �������
	int X;
	int Y;
};
//---------------------------------------------------------------------------
//��������� ������ � ����������� ��� ����� � ������ ������� (Object Handles)
struct OBJECT_HANDLES_DATA
{
	//������ �� ������ �������
	TGameObject *Obj;

	//�������� ���������� �������
	int X;
	int Y;
};
//---------------------------------------------------------------------------
class TGameScreen : public TBaseScreen
{
private:
	//��������� � ������� � ���������� � ������������ �������� ����
	RENDER_VARIABLES_FOR_GAME_WINDOW m_RenderBounds;

	//����������� ����������� �������� ����
	bool m_GameWindowMoving;

	//����������� ��������� ������� �������� ����
	bool m_GameWindowResizing;

	//������ �������� ��� ������
	OBJECT_HANDLES_DATA m_ObjectHandlesList[MAX_OBJECT_HANDLES];

	//���������� �������� ��� ������
	int m_ObjectHandlesCount;

	//������ �������� ��� �����������
	RENDER_OBJECT_DATA *m_RenderList;

	//������ ������ �������� �������
	int m_RenderListSize;

	//���������� �������� � ������
	int m_RenderListCount;

	//����, ������������ ������������� ������ �������
	bool m_RenderListInitalized;

	//������ ���������� �����
	LIGHT_DATA m_Light[MAX_LIGHT_SOURCES];

	//���������� ���������� �����
	int m_LightCount;

	//������������ �� ��������� ��� ����������� �������� �����
	bool m_UseLight;

	//������������ �������� ����������� �� Z ����������
	int m_MaxDrawZ;

	//���������� �������� Z ���������� ��� �������
	int GetMaxDrawZ(bool &noDrawRoof, char &maxGroundZ);

	//��������� ��������� ���� (���������� �������. ����-����� � �.�.)
	void CheckMouseEvents(bool &charSelected);

	//��������� �� ������� ������
	TRenderTextObject *m_GameWindowText;

	//���������� ���������� ������������� ������
	void CalculateGameWindowText(bool &mode);

	//����������� �������� ����
	void DrawGameWindow(bool &mode);

	//����������� ���������� �����
	void DrawGameWindowLight();

	//����������� ������ ��� ��������� ����
	void DrawGameWindowText(bool &mode);

	//���������� ������������ ���� �������� � ��������� �����������
	void ApplyTransparentFoliageToUnion(WORD &graphic, int &x, int &y, int &z);

	//�������� �������������� ����� � ������ ���� (� ����������� ����������� ������������ ���� ������)
	void CheckFoliageUnion(WORD graphic, int x, int y, int z);

	//������� ����������� ������� ������ �������
	void IncreaseRenderList();

	int m_ObjCount;
	RENDER_OBJECT_DATA *m_ObjList;

	//������� ����������� ������� ������ �������
	void IncreaseObjList();
public:
	TGameScreen();
	virtual ~TGameScreen();

	//��������� ������� ����� �������� ���������� ������
	void ProcessSmoothAction(BYTE action = 0xFF);

	//�������������� ������� ��� �������� ��������
	static const BYTE ID_SMOOTH_GS_LOGOUT = 1;

	//���������� ���������� �������� ����
	void CalculateGameWindowBounds();

	//������ ������ �������� �������, ���������� ������������ ���� �������� (� �.�. ���������)
	void CalculateRenderList();

	//�������������
	void Init();

	//������������� �������
	void InitPopupHelp();

	//������� ���������� ��������� �����
	void AddLight(TRenderWorldObject *rwo, TRenderWorldObject *lightObject, int x, int y);

	//��������� ������
	int Render(bool mode);

	SETGET(bool, UseLight);
	SETGET(bool, RenderListInitalized);

	//�������
	void OnLeftMouseDown();
	void OnLeftMouseUp();
	void OnRightMouseDown();
	void OnRightMouseUp();
	bool OnLeftMouseDoubleClick();
	bool OnRightMouseDoubleClick();
	void OnMouseWheel(MOUSE_WHEEL_STATE state);
	void OnCharPress(WPARAM wparam, LPARAM lparam);
	void OnKeyPress(WPARAM wparam, LPARAM lparam);
};
//---------------------------------------------------------------------------
extern TGameScreen *GameScreen;
extern RENDER_VARIABLES_FOR_GAME_WINDOW *g_RenderBounds;
//---------------------------------------------------------------------------
#endif