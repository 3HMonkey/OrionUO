/***********************************************************************************
**
** SkillGroup.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef SKILLGROUP_H
#define SKILLGROUP_H
//----------------------------------------------------------------------------------
#include "Globals.h"
#include "GLEngine/GLTextTexture.h"
//----------------------------------------------------------------------------------
//����� ������ �������
class CSkillGroupObject
{
	SETGET(int, Count);
	SETGET(bool, Maximized);
	SETGET(uchar, Selected);
	SETGETE(string, Name, OnChangeName);

private:
	//������ �������
	uchar m_Items[60];

public:
	//������ �� ��������� � ���������� ������
	CSkillGroupObject *m_Next;
	CSkillGroupObject *m_Prev;

	CSkillGroupObject();
	~CSkillGroupObject();

	//�������� ������ ������
	CGLTextTexture m_Texture;

	uchar GetItem(int index);

	//�������� ����� � ������	
	void Add(uchar index);

	//�������� ����� � �������������
	void AddSorted(uchar index);

	//������� �����
	void Remove(uchar index);

	//��������, �������� �� ������ �����
	bool Contains(uchar index);

	//����������� ������
	void Sort();

	//�������� ����� ������ ������
	void TransferTo(CSkillGroupObject *group);
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
