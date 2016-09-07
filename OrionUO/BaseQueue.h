/***********************************************************************************
**
** BaseQueue.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef BASEQUEUE_H
#define BASEQUEUE_H
//----------------------------------------------------------------------------------
#include <windows.h>
//----------------------------------------------------------------------------------
//!TBaseQueue for [extended]
#define QFOR(var, start, type) for (type var = (type)start; var != NULL; var = (type)var->m_Next)
//!TBaseQueue for
#define BQFOR(var, start) QFOR(var, start, CBaseQueueItem*)
//----------------------------------------------------------------------------------
class CBaseQueueItem;
//----------------------------------------------------------------------------------
//!��������� ��� ���������
class CBaseQueue
{
public:
	CBaseQueue();
	virtual ~CBaseQueue();

	//!������ ������� �� ������
	CBaseQueueItem *m_Items;

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
	virtual CBaseQueueItem *Add(CBaseQueueItem *item);

	/*!
	�������� ���������� �������� �� ������
	@param [__in] item ������ �� �������
	@return 
	*/
	void Delete(CBaseQueueItem *item);

	/*!
	�������� �������� � ��������� ��������
	@param [__in] index ������ ��������
	@return 
	*/
	void Delete(const int &index);

	/*!
	�������� ������� � ��������� ��������
	@param [__in] index ������ ��������
	@return ������ �� ������� ��� NULL
	*/
	CBaseQueueItem *Get(int index);

	/*!
	�������� ������ ���������� ��������
	@param [__in] item ������ �� �������
	@return ������ �������� � �������
	*/
	int GetItemIndex(CBaseQueueItem *item);

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
	void Unlink(CBaseQueueItem *item);

	/*!
	������������ ������� �������� � �������
	@param [__in] first ������ �� �������������� �������
	@param [__out] item ������ �� �������
	@return 
	*/
	void Insert(CBaseQueueItem *first, CBaseQueueItem *item);

	/*!
	��������� ������� � ������ �������
	@param [__in] item ������ �� �������
	@return 
	*/
	virtual void MoveToFront(CBaseQueueItem *item);

	/*!
	��������� ������� � ����� �������
	@param [__in] item ������ �� �������
	@return 
	*/
	void MoveToBack(CBaseQueueItem *item);

	/*!
	����������� ������� �����/���� �� �������
	@param [__in] item ������ �� �������
	@param [__in] up ����� ��� ���� �� �������
	@return true � ������ ��������� �����������
	*/
	bool Move(CBaseQueueItem *item, const bool &up);

	/*!
	������ ������ ��� ���
	@return true � ������ ��������� �����������
	*/
	bool Empty() const {return (m_Items == NULL);}

	/*!
	�������� ��������� �� ��������� �������
	@return ������ �� �������
	*/
	CBaseQueueItem *Last();
};
//----------------------------------------------------------------------------------
//!������� �������
class CBaseQueueItem : public CBaseQueue
{
public:
	CBaseQueueItem();
	virtual ~CBaseQueueItem();

	//!��������� �������
	CBaseQueueItem *m_Next;

	//!���������� �������
	CBaseQueueItem *m_Prev;
};
//----------------------------------------------------------------------------------
#endif
