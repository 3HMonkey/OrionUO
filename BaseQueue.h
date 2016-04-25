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
//!��������� ��� ���������
class TBaseQueue
{
public:
	TBaseQueue();
	virtual ~TBaseQueue();

	//!������ ������� �� ������
	TBaseQueueItem *m_Items;

	/*!
	������� ������
	@return 
	*/
	virtual void Clear();

	/*!
	���������� �������� � ������
	@param [__in] item ������ �� ����� �������
	@return ������ �� ����� �������
	*/
	virtual TBaseQueueItem *Add(__in TBaseQueueItem *item);

	/*!
	�������� ���������� �������� �� ������
	@param [__in] item ������ �� �������
	@return 
	*/
	void Delete(__in TBaseQueueItem *item);

	/*!
	�������� �������� � ��������� ��������
	@param [__in] index ������ ��������
	@return 
	*/
	void Delete(__in const int &index);

	/*!
	�������� ������� � ��������� ��������
	@param [__in] index ������ ��������
	@return ������ �� ������� ��� NULL
	*/
	TBaseQueueItem *Get(__in int index);

	/*!
	�������� ������ ���������� ��������
	@param [__in] item ������ �� �������
	@return ������ �������� � �������
	*/
	int GetItemIndex(__in TBaseQueueItem *item);

	/*!
	�������� ����� ���������� ��������� � ������
	@return ���������� �������� � �������
	*/
	int GetItemsCount();

	/*!
	������������ ������� ���������� �������� �� �������
	@param [__in] item ������ �� �������
	@return 
	*/
	void Unlink(__in TBaseQueueItem *item);

	/*!
	������������ ������� �������� � �������
	@param [__in] first ������ �� �������������� �������
	@param [__out] item ������ �� �������
	@return 
	*/
	void Insert(__in TBaseQueueItem *first, __out TBaseQueueItem *item);

	/*!
	��������� ������� � ������ �������
	@param [__in] item ������ �� �������
	@return 
	*/
	void MoveToFront(__in TBaseQueueItem *item);

	/*!
	��������� ������� � ����� �������
	@param [__in] item ������ �� �������
	@return 
	*/
	void MoveToBack(__in TBaseQueueItem *item);

	/*!
	����������� ������� �����/���� �� �������
	@param [__in] item ������ �� �������
	@param [__in] up ����� ��� ���� �� �������
	@return true � ������ ��������� �����������
	*/
	bool Move(__in TBaseQueueItem *item, __in const bool &up);

	/*!
	������ ������ ��� ���
	@return true � ������ ��������� �����������
	*/
	bool Empty() const {return (m_Items == NULL);}

	/*!
	�������� ��������� �� ��������� �������
	@return ������ �� �������
	*/
	TBaseQueueItem *Last();
};
//---------------------------------------------------------------------------
//!������� �������
class TBaseQueueItem : public TBaseQueue
{
public:
	TBaseQueueItem();
	virtual ~TBaseQueueItem();

	//!��������� �������
	TBaseQueueItem *m_Next;

	//!���������� �������
	TBaseQueueItem *m_Prev;
};
//---------------------------------------------------------------------------
#endif