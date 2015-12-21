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
TBaseQueueItem *TBaseQueue::Add(TBaseQueueItem *item)
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
void TBaseQueue::Delete(TBaseQueueItem *item)
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
void TBaseQueue::Delete(int index)
{
	//������� ������� � ��������� �������� � ������ ��� (���� ����)
	Delete(Get(index));
}
//---------------------------------------------------------------------------
int TBaseQueue::GetItemIndex(TBaseQueueItem *item)
{
	int index = 0;

	//��������� �� �������
	for (TBaseQueueItem *current = m_Items; current != NULL; current = current->m_Next, index++)
	{
		//���� ������� ������� - ���������� ����������� ������
		if (current == item)
			return index;
	}

	//� ������ �� �������� ������ - ������ -1 (�� �������)
	return -1;
}
//---------------------------------------------------------------------------
int TBaseQueue::GetItemsCount()
{
	int count = 0;

	//��������� �� ���� ��������� ������� � �������� ����� ����������
	//��� �������� ������ �� ������� ��� �������� � ��������� ����������
	for (TBaseQueueItem *current = m_Items; current != NULL; current = current->m_Next, count++);

	return count;
}
//---------------------------------------------------------------------------
TBaseQueueItem *TBaseQueue::Get(int index)
{
	TBaseQueueItem *item = m_Items;

	//��������� �� ���� ��������� ������� �� ���������� ������� ��� ��������� ������
	for (; item != NULL && index; item = item->m_Next, index--);

	return item;
}
//---------------------------------------------------------------------------
void TBaseQueue::Insert(TBaseQueueItem *first, TBaseQueueItem *item)
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
void TBaseQueue::Unlink(TBaseQueueItem *item)
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
void TBaseQueue::MoveToFront(TBaseQueueItem *item)
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
void TBaseQueue::MoveToBack(TBaseQueueItem *item)
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
bool TBaseQueue::Move(TBaseQueueItem *item, bool up)
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