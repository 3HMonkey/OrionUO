/***********************************************************************************
**
** MapBlock.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef MAPBLOCK_H
#define MAPBLOCK_H
//----------------------------------------------------------------------------------
#include "../BaseQueue.h"
#include "../Globals.h"
#include "../RenderWorldObject.h"
#include "../Game objects/LandObject.h"
//----------------------------------------------------------------------------------
//����� ��� ������ � ������� ����� 8�8
class CMapBlock : public CBaseQueueItem
{
	SETGET(uint, Index);
	SETGET(uint, LastAccessTime);
	SETGET(short, X);
	SETGET(short, Y);

private:
	//�������� Z ���������� ���������
	char GetLandZ(const int &x, const int &y, const int &map);

	//�������� Z ���������� ������� �������
	char GetRenderZ(CRenderWorldObject *item);

	//��������� ������ ��������� �� "���������������" ��� �������
	bool TestStretched(const int &x, const int &y, const char &z, const int &map, const bool &recurse);

public:
	CMapBlock(const uint &index);
	virtual ~CMapBlock();

	//������ �����
	CMapObject *Block[8][8];

	//�������� ������
	CMapObject *AddObject(CMapObject *obj, const int &x, const int &y);

	//�������� ��������� �� ������ ���������
	CLandObject *GetLand(const int &x, const int &y);

	//�������� ������ � ������� �������
	void AddRender(CRenderWorldObject *item, const int &x, const int &y);

	//�������� ������ ������� �������
	CRenderWorldObject *GetRender(const int &x, const int &y);

	//�������� ���� ����� ��� ������
	ushort GetRadarColor(const int &x, const int &y);

	//��������������� ������� ������� ���������
	void CreateLandTextureRect();

	bool HasNoExternalData();
};
//---------------------------------------------------------------------------
#endif