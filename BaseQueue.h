/****************************************************************************
**
** BaseQueue.h
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
#ifndef BaseQueueH
#define BaseQueueH

class TBaseQueueItem;
//---------------------------------------------------------------------------
//��������� ��� ���������
class TBaseQueue
{
private:
public:
	TBaseQueue();
	virtual ~TBaseQueue();

	//������ ������� �� ������
	TBaseQueueItem *m_Items;

	//������� ������
	virtual void Clear();

	//���������� �������� � ������
	virtual TBaseQueueItem *Add(TBaseQueueItem *item);

	//�������� ���������� �������� �� ������
	void Delete(TBaseQueueItem *item);
	//�������� �������� � ��������� ��������
	void Delete(int index);

	//�������� ������� � ��������� ��������
	TBaseQueueItem *Get(int index);
	//�������� ������ ���������� ��������
	int GetItemIndex(TBaseQueueItem *item);
	//�������� ����� ���������� ��������� � ������
	int GetItemsCount();

	//������������ ������� ���������� �������� �� �������
	void Unlink(TBaseQueueItem *item);
	
	//������������ ������� �������� � �������
	void Insert(TBaseQueueItem *first, TBaseQueueItem *item);

	//��������� ������� � ������ �������
	void MoveToFront(TBaseQueueItem *item);
	//��������� ������� � ����� �������
	void MoveToBack(TBaseQueueItem *item);
	//����������� ������� �����/���� �� �������
	bool Move(TBaseQueueItem *item, bool up);

	//������ ������ ��� ���
	bool Empty() const {return (m_Items == NULL);}

	//��������� �� ��������� �������
	TBaseQueueItem *Last();
};
//---------------------------------------------------------------------------
//������� �������
class TBaseQueueItem : public TBaseQueue
{
private:
public:
	TBaseQueueItem();
	virtual ~TBaseQueueItem();

	//��������� �������
	TBaseQueueItem *m_Next;
	//���������� �������
	TBaseQueueItem *m_Prev;
};
//---------------------------------------------------------------------------
#endif