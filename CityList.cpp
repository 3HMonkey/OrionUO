/****************************************************************************
**
** CityList.cpp
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
#include "stdafx.h"

TCityList *CityList = NULL;
//---------------------------------------------------------------------------
//-----------------------------------TCityItem-------------------------------
//---------------------------------------------------------------------------
TCityItem::TCityItem()
: TBaseQueueItem(), m_LocationIndex(0), m_Name(""), m_Area(""), m_Selected(false),
m_City(NULL)
{
}
//---------------------------------------------------------------------------
TCityItem::~TCityItem()
{
}
//---------------------------------------------------------------------------
void TCityItem::InitCity()
{
	//������� �����
	m_City = CityManager->GetCity(m_Name);
}
//---------------------------------------------------------------------------
//---------------------------------TCityItemNew------------------------------
//---------------------------------------------------------------------------
TCityItemNew::TCityItemNew()
: TCityItem(), m_X(0), m_Y(0), m_Z(0), m_MapIndex(0) //, m_Cliloc(0)
{
}
//---------------------------------------------------------------------------
TCityItemNew::~TCityItemNew()
{
	//������� ��������
	m_Texture.Clear();
}
//---------------------------------------------------------------------------
void TCityItemNew::CreateTextTexture(DWORD clilocID)
{
	//������� ��������
	m_Texture.Clear();

	//���������� ��������� HTML-����� ��� �������� �������� ������
	FontManager->SetUseHTML(true);

	//�������� ������ ������� � ��������� ������
	wstring wtext = ClilocManager->Cliloc(g_Language)->GetW(clilocID);

	//������� �������� ������
	FontManager->GenerateW(1, m_Texture, wtext.c_str(), 0, 30, 150);

	//��������� ��������� HTML-�����
	FontManager->SetUseHTML(false);
}
//---------------------------------------------------------------------------
//-----------------------------------TCityList-------------------------------
//---------------------------------------------------------------------------
TCityList::TCityList()
: TBaseQueue()
{
}
//---------------------------------------------------------------------------
TCityList::~TCityList()
{
}
//---------------------------------------------------------------------------
TCityItem *TCityList::GetCity(int index)
{
	//��������� �� ������ �������
	TCityItem *city = (TCityItem*)m_Items;

	//��������� �� ������
	while (city != NULL)
	{
		//���� ��� ����� � ������ �������� ������� - ���������
		if (city->LocationIndex == index)
			break;

		//��� ��������� � ���������� ������
		city = (TCityItem*)city->m_Next;
	}

	//��� ������� (��� �� �������)
	return city;
}
//---------------------------------------------------------------------------