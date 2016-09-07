/***********************************************************************************
**
** GLVector.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GLVECTOR_H
#define GLVECTOR_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
//----------------------------------------------------------------------------------
//����� ������� �������
class CVector
{
	SETGET(double, X);
	SETGET(double, Y);
	SETGET(double, Z);

public:
	CVector(const double &x = 0, const double &y = 0, const double &z = 0);
	~CVector() {}

	//����������� ��������
	void Link(const CVector &v);

	//��������� ���������
	void Link(const double &x, const double &y, const double &z);

	//����������� ��������
	void Add(const CVector &v);

	//����������� ���������
	void Add(const double &x, const double &y, const double &z);

	//������� ��������
	void Merge(const CVector &v);

	//������� ���������
	void Merge(const double &x, const double &y, const double &z);

	//������������
	void Normalize();
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
