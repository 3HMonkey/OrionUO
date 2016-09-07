/***********************************************************************************
**
** PathFinder.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef PATHFINDER_H
#define PATHFINDER_H
//----------------------------------------------------------------------------------
#include "PathNode.h"
//----------------------------------------------------------------------------------
const int PATHFINDER_MAX_NODES = 10000;
//----------------------------------------------------------------------------------
//����� ��� ������ ���� � ����� ���� �� �����
class CPathFinder : public CBaseQueue
{
	//�������������� ������������ (�� �������� ����������� � ������)
	SETGET(bool, AutoWalking);
	SETGET(bool, PathFindidngCanBeCancelled);

private:
	//���������� ����� Z ����������
	bool CalculateNewZ(int &x, int &y, char &z);

	//���������� ����� XY ���������
	void GetNewXY(uchar &direction, int &x, int &y);

	//�������� ������ ���������, ����������� � ������ � ��������� �����������
	bool CreateItemsList(int &x, int &y, char &z);

	//����, �����������. ��� �������� ����� �� ������� ��������
	bool m_OnLongStair;

	//�������� �� �������� ��� ������
	void CheckLongStairUnderfoot(int &x, int &y, char &z);

	WISP_GEOMETRY::CPoint2Di m_StartPoint;
	WISP_GEOMETRY::CPoint2Di m_EndPoint;

	/*int m_StartX;
	int m_StartY;

	int m_EndX;
	int m_EndY;*/

	int m_GoalNode;
	bool m_GoalFound;

	int m_ActiveOpenNodes;
	int m_ActiveClosedNodes;

	int m_PathFindDistance;

	CPathNode m_OpenList[PATHFINDER_MAX_NODES];
	CPathNode m_ClosedList[PATHFINDER_MAX_NODES];

	//������ ����� ����
	CPathNode *m_Path[PATHFINDER_MAX_NODES];

	//������� ����� ����
	int m_PointIndex;

	//������ ����� ����
	int m_PathSize;

	int GetGoalDistCost(const WISP_GEOMETRY::CPoint2Di &p, int cost);

	bool DoesNotExistOnOpenList(int x, int y, int z);

	bool DoesNotExistOnClosedList(int x, int y, int z);

	int AddNodeToList(int list, int direction, int x, int y, int z, CPathNode *parentNode, int cost);

	bool OpenNodes(CPathNode *node);

	int FindCheapestNode();

	bool FindPath(int maxNodes);

public:
	CPathFinder();
	virtual ~CPathFinder();

	//�������� �� ����������� ������� ��� � ��������� ����������
	bool CanWalk(uchar &direction, int &x, int &y, char &z);

	//����� � ��������� ����������
	bool Walk(bool run, uchar direction);

	//������������� � ��������� ����������
	bool WalkTo(int x, int y, int z, int distance);

	//��������� ����
	void ProcessAutowalk();

	//���������� �������������� �������
	void StopAutoWalk();

	int GetWalkSpeed(const bool &run, const bool &onMount);
};
//----------------------------------------------------------------------------------
extern CPathFinder g_PathFinder;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
