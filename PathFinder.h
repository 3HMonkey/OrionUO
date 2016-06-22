/****************************************************************************
**
** PathFinder.h
**
** Copyright (C) October 2015 Hotride
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
#ifndef PathFinderH
#define PathFinderH
//---------------------------------------------------------------------------
const int PATHFINDER_MAX_NODES = 10000;
//---------------------------------------------------------------------------
//����� ������� � ����� ����
class TPathObject : public TBaseQueueItem
{
private:
	//���������� Z �����
	int m_Z;

	//������ �����
	char m_Height;

	//������������� �����������
	BYTE m_Surface;

public:
	TPathObject(int z, char height, char surface);
	virtual ~TPathObject();

	SETGET(int, Z);
	SETGET(char, Height);
	SETGET(BYTE, Surface);
};
//---------------------------------------------------------------------------
//����� ������� � ����� ����
class TPathNode
{
private:
	TPathNode *m_Parent;

	int m_X;

	int m_Y;

	int m_Z;

	int m_Direction;

	bool m_Used;

	int m_Cost;

	int m_DistFromStartCost;

	int m_DistFromGoalCost;

public:
	TPathNode();
	virtual ~TPathNode();

	SETGET(TPathNode*, Parent);
	SETGET(int, X);
	SETGET(int, Y);
	SETGET(int, Z);
	SETGET(int, Direction);
	SETGET(bool, Used);
	SETGET(int, Cost);
	SETGET(int, DistFromStartCost);
	SETGET(int, DistFromGoalCost);

	void Reset();
};
//---------------------------------------------------------------------------
struct PATH_POINT
{
	int X;
	int Y;
	int Direction;
};
//---------------------------------------------------------------------------
//����� ��� ������ ���� � ����� ���� �� �����
class TPathFinder : public TBaseQueue
{
private:
	//���������� ����� Z ����������
	bool CalculateNewZ(int &x, int &y, char &z);

	//���������� ����� XY ���������
	void GetNewXY(BYTE &direction, int &x, int &y);

	//�������� ������ ���������, ����������� � ������ � ��������� �����������
	bool CreateItemsList(int &x, int &y, char &z);

	//����, �����������. ��� �������� ����� �� ������� ��������
	bool m_OnLongStair;

	//�������� �� �������� ��� ������
	void CheckLongStairUnderfoot(int &x, int &y, char &z);

	//�������������� ������������ (�� �������� ����������� � ������)
	bool m_AutoWalking;

	POINT m_StartPoint;
	POINT m_EndPoint;

	/*int m_StartX;
	int m_StartY;

	int m_EndX;
	int m_EndY;*/

	int m_GoalNode;
	bool m_GoalFound;

	int m_ActiveOpenNodes;
	int m_ActiveClosedNodes;

	int m_PathFindDistance;
	bool m_PathFindidngCanBeCancelled;

	TPathNode m_OpenList[PATHFINDER_MAX_NODES];
	TPathNode m_ClosedList[PATHFINDER_MAX_NODES];

	//������ ����� ����
	TPathNode *m_Path[PATHFINDER_MAX_NODES];

	//������� ����� ����
	int m_PointIndex;

	//������ ����� ����
	int m_PathSize;

	int GetGoalDistCost(const POINT &p, int cost);

	bool DoesNotExistOnOpenList(int x, int y, int z);

	bool DoesNotExistOnClosedList(int x, int y, int z);

	int AddNodeToList(int list, int direction, int x, int y, int z, TPathNode *parentNode, int cost);

	bool OpenNodes(TPathNode *node);

	int FindCheapestNode();

	bool FindPath(int maxNodes);

public:
	TPathFinder();
	virtual ~TPathFinder();

	SETGET(bool, AutoWalking);
	SETGET(bool, PathFindidngCanBeCancelled);

	//�������� �� ����������� ������� ��� � ��������� ����������
	bool CanWalk(BYTE &direction, int &x, int &y, char &z);

	//����� � ��������� ����������
	bool Walk(bool run, BYTE direction);

	//������������� � ��������� ����������
	bool WalkTo(int x, int y, int z, int distance);

	//��������� ����
	void ProcessAutowalk();

	//���������� �������������� �������
	void StopAutoWalk();

	int GetWalkSpeed(const bool &run, const bool &onMount, const bool &randomize = false);
};
//---------------------------------------------------------------------------
extern TPathFinder *PathFinder;
//---------------------------------------------------------------------------
#endif