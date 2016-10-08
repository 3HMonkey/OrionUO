/***********************************************************************************
**
** BaseQueue.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "BaseQueue.h"
//---------------------------------------------------------------------------
//--------------------------------CBaseQueueItem-----------------------------
//---------------------------------------------------------------------------
CBaseQueueItem::CBaseQueueItem()
: CBaseQueue(), m_Next(NULL), m_Prev(NULL)
{
}
//---------------------------------------------------------------------------
CBaseQueueItem::~CBaseQueueItem()
{
	//�������������� ������� ��� ��������
	Clear();

	CBaseQueueItem *item = m_Next;
	//while (item != NULL && item->m_Next != NULL)
	//	item = item->m_Next;

	while (item != NULL && item != this)
	{
		CBaseQueueItem *next = item->m_Next;
		item->m_Next = NULL;
		delete item;
		item = next;
	}

	//���� ���� ��������� ������� - ������� ��� (��������� ���������/���������)
	/*if (m_Next != NULL)
	{
		delete m_Next;
		m_Next = NULL;
	}*/
}
//---------------------------------------------------------------------------
//----------------------------------CBaseQueue-------------------------------
//---------------------------------------------------------------------------
CBaseQueue::CBaseQueue()
: m_Items(NULL)
{
}
//---------------------------------------------------------------------------
CBaseQueue::~CBaseQueue()
{
	//�������������� ������� ��� ��������
	Clear();
}
//---------------------------------------------------------------------------
/*!
������� ������
@return 
*/
void CBaseQueue::Clear()
{
	//���� � ���������� ���� �������� - ���������� ������ ������� ������, ��������� �������� ������ � ���
	if (m_Items != NULL)
	{
		CBaseQueueItem *item = m_Items;
		m_Items = NULL;

		while (item != NULL)
		{
			CBaseQueueItem *next = item->m_Next;
			item->m_Next = NULL;
			delete item;
			item = next;
		}
	}
}
//---------------------------------------------------------------------------
/*!
���������� �������� � ������
@param [__in] item ������ �� ����� �������
@return ������ �� ����� �������
*/
CBaseQueueItem *CBaseQueue::Add(CBaseQueueItem *item)
{
	//���� ����������� ������� �� ����� ����
	if (item != NULL)
	{
		//���� ������� ����� -  ������� ������� � ����� ������ �������
		if (m_Items == NULL)
			m_Items = item;
		else //���, ������ ��������� ������� � �������� ��� � ���
		{
			CBaseQueueItem *current = m_Items;

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
void CBaseQueue::Delete(CBaseQueueItem *item)
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
void CBaseQueue::Delete(const int &index)
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
int CBaseQueue::GetItemIndex(CBaseQueueItem *item)
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
int CBaseQueue::GetItemsCount()
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
CBaseQueueItem *CBaseQueue::Get(int index)
{
	CBaseQueueItem *item = m_Items;

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
void CBaseQueue::Insert(CBaseQueueItem *first, CBaseQueueItem *item)
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
		CBaseQueueItem *next = first->m_Next;
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
void CBaseQueue::Unlink(CBaseQueueItem *item)
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
void CBaseQueue::MoveToFront(CBaseQueueItem *item)
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
void CBaseQueue::MoveToBack(CBaseQueueItem *item)
{
	//���� ������� �� ����� ����
	if (item != NULL)
	{
		//����������
		Unlink(item);

		//������� ��������� �� ����� �������
		CBaseQueueItem *last = Last();

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
bool CBaseQueue::Move(CBaseQueueItem *item, const bool &up)
{
	//���������� ������� ��������� (� �������� ������ ��� ������ ��������) � ����������
	bool result = (item != NULL);

	//���� ������� �� ����� ����
	if (result)
	{
		//����������� "�����"
		if (up)
		{
			CBaseQueueItem *prev = item->m_Prev;

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
					CBaseQueueItem *prevprev = prev->m_Prev;
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
			CBaseQueueItem *next = item->m_Next;

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
					CBaseQueueItem *prev = item->m_Prev;
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
CBaseQueueItem *CBaseQueue::Last()
{
	//�������� ����� � ������ �������
	CBaseQueueItem *last = m_Items;

	//��������� �� ���� ��������� ������� �� ����� (���� ������� �� �����)
	while (last != NULL && last->m_Next != NULL)
		last = last->m_Next;

	//������ ��� ���������� � ���������� ������
	return last;
}
//---------------------------------------------------------------------------