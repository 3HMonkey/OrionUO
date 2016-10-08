/***********************************************************************************
**
** GameItem.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GAMEITEM_H
#define GAMEITEM_H
//----------------------------------------------------------------------------------
#include "GameObject.h"
#include "MultiObject.h"
#include "ShopItem.h"
#include "../Multi.h"
//----------------------------------------------------------------------------------
//!����� �������� �������� (��� �����)
class CGameItem : public CGameObject
{
	//!����, � ������� ���������� ������
	SETGET(uchar, Layer);
	//!������ �������� ��������
	SETGET(ushort, AnimID);
	//!������ �������� ����� ��� ����������
	SETGET(ushort, ImageID);
	//!������������ ��������� ���� (�� tiledata.mul/verdata)
	SETGET(uchar, UsedLayer);
	//!������ �� ���������/��������
	SETGET(bool, Opened);
	//!������� �� ���� ���������� ����������?
	SETGET(bool, Dragged);
	//!��� ������-������ ������
	SETGET(bool, MultiBody);

protected:
	/*!
	�������� �������-������
	@param [__in] obj ������ �� ������-������
	@return 
	*/
	void AddMultiObject(CMultiObject *obj);

public:
	CGameItem(const uint &serial = 0);
	virtual ~CGameItem();

	//!��������� �� ������� ����� �������
	CShopItem *ShopItem;

	/*!
	������� ������ �� ������� � ���� (�� �������)
	@param [__in] obj ������ �� ������ �� �������
	@return 
	*/
	void Paste(class CObjectOnCursor *obj);

	virtual void Draw(const int &x, const int &y);

	virtual void Select(const int &x, const int &y);

	/*!
	������� ��������� �������� �������
	@param [__in_opt] direction ����������� �������� (��� ������)
	@return
	*/
	void OnGraphicChange(int direction = 0);

	/*!
	�������� ������ �������� (��� ��������)
	@return ������ ��������
	*/
	ushort GetMountAnimation();

	/*!
	���������� �� ��� ������, �������� �����
	@return 
	*/
	virtual bool IsInternal() { return ((m_TiledataPtr->Flags & 0x00010000) && !IsCorpse()); }

	/*!
	���������������� ���� �� ���?
	@return 
	*/
	bool IsHuman() { return (IsCorpse() && (m_Count >= 0x0190) && (m_Count <= 0x0193)); }

	/*!
	�������� ������ � ������� ������
	@return 
	*/
	void LoadMulti();

	/*!
	��������� ������� ������ � �������� �����������
	@param [__in] x ���������� X
	@param [__in] y ���������� Y
	@return ������ �� ������ ��� NULL
	*/
	CMulti *GetMultiAtXY(const short &x, const short &y);

	/*!
	����� ������ ������ (����������) �� ���� � ������ (� ���) �����
	@param [__in] graphic ������ ��������
	@param [__in_opt] color ���� ��������
	@return ������ �� ��������� ������ ��� NULL
	*/
	CGameItem *FindItem(const ushort &graphic, const ushort &color = 0xFFFF);
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
