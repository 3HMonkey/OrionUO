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
	bool CreateItemsList(int &x, int &y);

	//����, �����������. ��� �������� ����� �� ������� ��������
	bool m_OnLongStair;

	//�������� �� �������� ��� ������
	void CheckLongStairUnderfoot(int &x, int &y, char &z);

	//�������������� ������������ (�� �������� ����������� � ������)
	bool m_AutoWalking;

	//������ ����� ����
	PATH_POINT *m_Path;

	//������� ����� ����
	int m_PointIndex;

	//������ ����� ����
	int m_PathSize;
public:
	TPathFinder();
	virtual ~TPathFinder();

	SETGET(bool, AutoWalking);

	//�������� �� ����������� ������� ��� � ��������� ����������
	bool CanWalk(BYTE &direction, int &x, int &y, char &z);

	//����� � ��������� ����������
	bool Walk(bool run, BYTE direction);

	//��������� ����� ����
	PATH_POINT *CalculatePath(int &size, int x, int y, int z);

	//������������� � ��������� ����������
	bool WalkTo(int x, int y, int z);

	//��������� ����
	void ProcessAutowalk();

	//���������� �������������� �������
	void StopAutoWalk();
};
//---------------------------------------------------------------------------
extern TPathFinder *PathFinder;
//---------------------------------------------------------------------------
#endif