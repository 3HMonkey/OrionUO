/***********************************************************************************
**
** CharacterList.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "CharacterList.h"

CCharacterList g_CharacterList;
//----------------------------------------------------------------------------------
CCharacterList::CCharacterList()
:m_Count(5), m_Selected(0), m_OnePerson(false), m_Have6Slot(false),
m_Have7Slot(false), m_ClientFlag(0)
{
	//!������ ��� ��������
	Clear();
}
//----------------------------------------------------------------------------------
/*!
������� ������
@return 
*/
void CCharacterList::Clear()
{
	IFOR(i, 0, 7)
		m_Name[i] = "";

	m_Selected = 0;
	m_OnePerson = false;
	m_Have6Slot = false;
	m_Have7Slot = false;
}
//----------------------------------------------------------------------------------
/*!
���������� ��� ��������� � ��������� �����
@param [__in] pos ������� � ������
@param [__in] name ����� ���
@return 
*/
void CCharacterList::SetName(__in int pos, __in string name)
{
	//!��� ���������� ������� ���������� ���
	if (pos >= 0 && pos < m_Count)
		m_Name[pos] = name;
}
//----------------------------------------------------------------------------------
/*!
�������� ��� ��������� � ��������� �����
@param [__in] pos ������� � ������
@return ��� ���������
*/
string CCharacterList::GetName(__in int pos) const
{
	string result = "";

	//!��� ���������� ������� ���������� ���
	if (pos >= 0 && pos < m_Count)
		result = m_Name[pos];

	return result;
}
//----------------------------------------------------------------------------------
/*!
�������� ��� ���������� ���������
@return ��� ���������
*/
string CCharacterList::GetSelectedName() const
{
	string result = "";

	//!��� ���������� ������� ���������� ���
	if (m_Selected >= 0 && m_Selected < m_Count)
		result = m_Name[m_Selected];

	return result;
}
//----------------------------------------------------------------------------------
