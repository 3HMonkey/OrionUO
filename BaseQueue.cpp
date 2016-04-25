/****************************************************************************
**
** BaseQueue.cpp
**
** Copyright (C) May 2015 Hotride
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
//---------------------------------------------------------------------------
//--------------------------------TBaseQueueItem-----------------------------
//---------------------------------------------------------------------------
TBaseQueueItem::TBaseQueueItem()
: TBaseQueue(), m_Next(NULL), m_Prev(NULL)
{
}
//---------------------------------------------------------------------------
TBaseQueueItem::~TBaseQueueItem()
{
	//�������������� ������� ��� ��������
	Clear();

	//���� ���� ��������� ������� - ������� ��� (��������� ���������/���������)
	if (m_Next != NULL)
	{
		delete m_Next;
		m_Next = NULL;
	}
}
//---------------------------------------------------------------------------
//----------------------------------TBaseQueue-------------------------------
//---------------------------------------------------------------------------
TBaseQueue::TBaseQueue()
: m_Items(NULL)
{
}
//---------------------------------------------------------------------------
TBaseQueue::~TBaseQueue()
{
	//�������������� ������� ��� ��������
	Clear();
}
//---------------------------------------------------------------------------
/*!
������� ������
@return 
*/
void TBaseQueue::Clear()
{
	//���� � ���������� ���� �������� - ���������� ������ ������� ������, ��������� �������� ������ � ���
	if (m_Items != NULL)
	{
		delete m_Items;
		m_Items = NULL;
	}
}
//---------------------------------------------------------------------------
/*!
���������� �������� � ������
@param [__in] item ������ �� ����� �������
@return ������ �� ����� �������
*/
TBaseQueueItem *TBaseQueue::Add(__in TBaseQueueItem *item)
{
	//���� ����������� ������� �� ����� ����
	if (item != NULL)
	{
		//���� ������� ����� -  ������� ������� � ����� ������ �������
		if (m_Items == NULL)
			m_Items = item;
		else //���, ������ ��������� ������� � �������� ��� � ���
		{
			TBaseQueueItem *current = m_Items;

			while (current->m_Next != NULL)
				current = current->m_Next;

			current->m_Next = item;
			item->m_Prev = current;
		}
	}

	//������ ����������� ������� (��� ������������ ����������� ����: item = Container->Add(new TItem());)
	return item;
}
//---------------------------------------------------------------------------
/*!
�������� ���������� �������� �� ������
@param [__in] item ������ �� �������
@return 
*/
void TBaseQueue::Delete( __in TBaseQueueItem *item)
{
	//���� ������� �� ����� ����
	if (item != NULL)
	{
		//���������� �������
		Unlink(item);

		//����� �������� ������� ���
		item->m_Next = NULL;
		item->m_Prev = NULL;
		delete item;
	}
}
//---------------------------------------------------------------------------
/*!
�������� �������� � ��������� ��������
@param [__in] index ������ ��������
@return
*/
void TBaseQueue::Delete(__in const int &index)
{
	//������� ������� � ��������� �������� � ������ ��� (���� ����)
	Delete(Get(index));
}
//---------------------------------------------------------------------------
/*!
�������� ������ ���������� ��������
@param [__in] item ������ �� �������
@return ������ �������� � �������
*/
int TBaseQueue::GetItemIndex( __in TBaseQueueItem *item)
{
	int index = 0;

	//��������� �� �������
	BQFOR(current, m_Items)
	{
		//���� ������� ������� - ���������� ����������� ������
		if (current == item)
			return index;

		index++;
	}

	//� ������ �� �������� ������ - ������ -1 (�� �������)
	return -1;
}
//---------------------------------------------------------------------------
/*!
�������� ����� ���������� ��������� � ������
@return ���������� �������� � �������
*/
int TBaseQueue::GetItemsCount()
{
	int count = 0;

	//��������� �� ���� ��������� ������� � �������� ����� ����������
	//��� �������� ������ �� ������� ��� �������� � ��������� ����������
	BQFOR(current, m_Items)
		count++;

	return count;
}
//---------------------------------------------------------------------------
/*!
�������� ������� � ��������� ��������
@param [__in] index ������ ��������
@return ������ �� ������� ��� NULL
*/
TBaseQueueItem *TBaseQueue::Get(__in int index)
{
	TBaseQueueItem *item = m_Items;

	//��������� �� ���� ��������� ������� �� ���������� ������� ��� ��������� ������
	for (; item != NULL && index; item = item->m_Next, index--);

	return item;
}
//---------------------------------------------------------------------------
/*!
������������ ������� �������� � �������
@param [__in] first ������ �� �������������� �������
@param [__out] item ������ �� �������
@return 
*/
void TBaseQueue::Insert( __in TBaseQueueItem *first, __out TBaseQueueItem *item)
{
	if (first == NULL)
	{
		item->m_Next = m_Items;
		item->m_Prev = NULL;
		
		if (m_Items != NULL)
			m_Items->m_Prev = item;

		m_Items = item;
	}
	else
	{
		TBaseQueueItem *next = first->m_Next;
		item->m_Next = next;
		item->m_Prev = first;
		
		first->m_Next = item;

		if (next != NULL)
			next->m_Prev = item;
	}
}
//---------------------------------------------------------------------------
/*!
������������ ������� ���������� �������� �� �������
@param [__in] item ������ �� �������
@return 
*/
void TBaseQueue::Unlink( __in TBaseQueueItem *item)
{
	//���� ������� �� ����� ����
	if (item != NULL)
	{
		//���� ������� - ������ ������
		if (item == m_Items)
		{
			//������������� ���
			m_Items = m_Items->m_Next;

			if (m_Items != NULL)
				m_Items->m_Prev = NULL;
		}
		else
		{
			//��� �������� ��������� ����������� � ���������� (��� ��� �������) ��������� ���� �� �����
			item->m_Prev->m_Next = item->m_Next;

			if (item->m_Next != NULL)
				item->m_Next->m_Prev = item->m_Prev;
		}
	}
}
//---------------------------------------------------------------------------
/*!
��������� ������� � ������ �������
@param [__in] item ������ �� �������
@return 
*/
void TBaseQueue::MoveToFront( __in TBaseQueueItem *item)
{
	//���� ������� �� ����� ���� � �� ����� ������ �������
	if (item != NULL && item != m_Items)
	{
		//����������
		Unlink(item);

		//����������� � ������� �������
		if (m_Items != NULL)
			m_Items->m_Prev = item;

		item->m_Next = m_Items;
		item->m_Prev = NULL;

		//������� � ������ �������
		m_Items = item;
	}
}
//---------------------------------------------------------------------------
/*!
��������� ������� � ����� �������
@param [__in] item ������ �� �������
@return 
*/
void TBaseQueue::MoveToBack( __in TBaseQueueItem *item)
{
	//���� ������� �� ����� ����
	if (item != NULL)
	{
		//����������
		Unlink(item);

		//������� ��������� �� ����� �������
		TBaseQueueItem *last = Last();

		//����������� ������� � ��������� ��������� (��� � ������� ������� ��� ������ �������)
		if (last == NULL)
			m_Items = item;
		else
			last->m_Next = item;

		item->m_Prev = last;
		item->m_Next = NULL;
	}
}
//---------------------------------------------------------------------------
/*!
����������� ������� �����/���� �� �������
@param [__in] item ������ �� �������
@param [__in] up ����� ��� ���� �� �������
@return true � ������ ��������� �����������
*/
bool TBaseQueue::Move(__in TBaseQueueItem *item, __in const bool &up)
{
	//���������� ������� ��������� (� �������� ������ ��� ������ ��������) � ����������
	bool result = (item != NULL);

	//���� ������� �� ����� ����
	if (result)
	{
		//����������� "�����"
		if (up)
		{
			TBaseQueueItem *prev = item->m_Prev;

			//���� ���������� ������� �� ����� ���� (���� ���� ���������)
			result = (prev != NULL);

			if (result)
			{
				//���������� ������� - ������ �������
				if (prev == m_Items)
				{
					prev->m_Prev = item;
					prev->m_Next = item->m_Next;
					m_Items = item;
					item->m_Prev = NULL;
					item->m_Next = prev;
				}
				else //���-�� � ���� �������
				{
					TBaseQueueItem *prevprev = prev->m_Prev;
					prev->m_Prev = item;
					prev->m_Next = item->m_Next;
					prevprev->m_Next = item;
					item->m_Prev = prevprev;
					item->m_Next = prev;
				}
			}
		}
		else
		{
			TBaseQueueItem *next = item->m_Next;

			//���� ��������� ������� �� ����� ���� (���� ���� ���������)
			result = (next != NULL);

			if (result)
			{
				//������� ������� - ������ �������
				if (item == m_Items)
				{
					item->m_Next = next->m_Next;
					item->m_Prev = next;
					m_Items = item;
					m_Items->m_Prev = NULL;
					m_Items->m_Next = item;
				}
				else //���-�� � ���� �������
				{
					TBaseQueueItem *prev = item->m_Prev;
					prev->m_Next = next;
					item->m_Next = next->m_Next;
					item->m_Prev = next;
					next->m_Prev = prev;
					next->m_Next = item;
				}
			}
		}
	}

	//���� ��� �������� ������ ������� - ������� ���������
	return result;
}
//---------------------------------------------------------------------------
/*!
�������� ��������� �� ��������� �������
@return ������ �� �������
*/
TBaseQueueItem *TBaseQueue::Last()
{
	//�������� ����� � ������ �������
	TBaseQueueItem *last = m_Items;

	//��������� �� ���� ��������� ������� �� ����� (���� ������� �� �����)
	while (last != NULL && last->m_Next != NULL)
		last = last->m_Next;

	//������ ��� ���������� � ���������� ������
	return last;
}
//---------------------------------------------------------------------------