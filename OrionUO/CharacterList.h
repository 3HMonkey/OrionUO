/***********************************************************************************
**
** CharacterList.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef CHARACTERLIST_H
#define CHARACTERLIST_H
//----------------------------------------------------------------------------------
#include "Globals.h"
//----------------------------------------------------------------------------------
//!����� ������ ���������� ��� ������ ������ ����������
class CCharacterList
{
	SETGET(int, Count);
	SETGET(int, Selected);
	SETGET(bool, OnePerson);
	SETGET(bool, Have6Slot);
	SETGET(bool, Have7Slot);
	SETGET(ushort, ClientFlag);

private:
	//!������ ��� 7 ����������
	string m_Name[7];

public:
	CCharacterList();
	virtual ~CCharacterList() {}

	/*!
	������� ������
	@return 
	*/
	void Clear();


	/*!
	���������� ��� ��������� � ��������� �����
	@param [__in] pos ������� � ������
	@param [__in] name ����� ���
	@return 
	*/
	void SetName(int pos, string name);

	/*!
	�������� ��� ��������� � ��������� �����
	@param [__in] pos ������� � ������
	@return ��� ���������
	*/
	string GetName(int pos) const;

	/*!
	�������� ��� ���������� ���������
	@return ��� ���������
	*/
	string GetSelectedName() const;
};
//----------------------------------------------------------------------------------
//!��������� �� ������ ����������
extern CCharacterList g_CharacterList;
//----------------------------------------------------------------------------------
#endif
