/****************************************************************************
**
** CharacterList.h
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
#ifndef CharacterListH
#define CharacterListH
//--------------------------------------------------------------------------
//!����� ������ ���������� ��� ������ ������ ����������
class TCharacterList
{
private:
	//!������� ���������� ���������� (�� ������)
	int m_Count;

	//!��������� �� ������ ���������� ���������
	int m_Selected;

	//!�������� ����� 1 �������� � ������� ��������
	bool m_OnePerson;

	//!������ ������� ����� 6 ����
	bool m_Have6Slot;

	//!������ ������� ����� 7 ����
	bool m_Have7Slot;

	//!����� ��� �������� �� ������ ��� �������� ���������
	WORD m_ClientFlag;

	//!������ ��� 7 ����������
	string m_Name[7];

public:
	TCharacterList();
	~TCharacterList() {}

	/*!
	������� ������
	@return 
	*/
	void Clear();

	SETGET(int, Count);
	SETGET(int, Selected);
	SETGET(bool, OnePerson);
	SETGET(bool, Have6Slot);
	SETGET(bool, Have7Slot);
	SETGET(WORD, ClientFlag);

	/*!
	���������� ��� ��������� � ��������� �����
	@param [__in] pos ������� � ������
	@param [__in] name ����� ���
	@return 
	*/
	void SetName(__in int pos, __in string name);

	/*!
	�������� ��� ��������� � ��������� �����
	@param [__in] pos ������� � ������
	@return ��� ���������
	*/
	string GetName(__in int pos) const;

	/*!
	�������� ��� ���������� ���������
	@return ��� ���������
	*/
	string GetSelectedName() const;
};
//---------------------------------------------------------------------------
//!��������� �� ������ ����������
extern TCharacterList CharacterList;
//---------------------------------------------------------------------------
#endif