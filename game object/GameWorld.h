/****************************************************************************
**
** GameWorld.h
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
#ifndef GameWorldH
#define GameWorldH
//---------------------------------------------------------------------------
typedef std::map<DWORD, TGameObject*> WORLD_MAP;
//---------------------------------------------------------------------------
//!����� �������� ����
class TGameWorld
{
private:
	/*!
	������� ������
	@param [__in] serial �������� ������
	@return 
	*/
	void CreatePlayer(__in DWORD serial);

	/*!
	������� ������
	@return 
	*/
	void RemovePlayer();

public:
	TGameWorld(DWORD serial);
	~TGameWorld();

	//!�������� � ������
	WORLD_MAP m_Map;

	//!�������� � ����
	TGameObject *m_Items;

	/*!
	��������� �������� ���� ����������
	@return 
	*/
	void ProcessAnimation();

	/*!
	���������� �������� ���� � ��������� ���������� ��� ���������
	@param [__in] serial �������� ������ ������
	@return 
	*/
	void SetPlayer(__in DWORD serial);

	/*!
	������� (��� �����, ���� ��� ����������) ������� �������
	@param [__in] serial �������� ��������
	@return ������ �� �������
	*/
	TGameItem *GetWorldItem(__in DWORD serial);

	/*!
	������� (��� �����, ���� ��� ����������) �������� ���������
	@param [__in] serial �������� ���������
	@return ������ �� ���������
	*/
	TGameCharacter *GetWorldCharacter(__in DWORD serial);

	/*!
	����� ������� ������ � ������
	@param [__in] serial �������� �������
	@return ������ �� ������ ��� NULL
	*/
	TGameObject *FindWorldObject(__in DWORD serial);

	/*!
	����� ������� ������� � ������
	@param [__in] serial �������� ��������
	@return ������ �� ������� ��� NULL
	*/
	TGameItem *FindWorldItem(__in DWORD serial);

	/*!
	����� �������� ��������� � ������
	@param [__in] serial �������� ���������
	@return ������ � ��������� ��� NULL
	*/
	TGameCharacter *FindWorldCharacter(__in DWORD serial);

	/*!
	������� ������ �� ������
	@param [__in] obj ������ �� ������
	@return 
	*/
	void RemoveObject(__in TGameObject *obj);

	/*!
	������ ������ �� ����������
	@param [__in] obj ������ �� ������
	@return 
	*/
	void RemoveFromContainer(__in TGameObject *obj);

	/*!
	�������� ��������� ���������
	@param [__in] obj ������ �� ������ (���������)
	@return 
	*/
	void ClearContainer(__in TGameObject *obj);

	/*!
	�������� � ���������
	@param [__in] obj ������ �� ������
	@param [__in] containerSerial �������� ����������
	@return 
	*/
	void PutContainer( __in TGameObject *obj, __in DWORD containerSerial)
	{
		TGameObject *cnt = FindWorldObject(containerSerial);
		if (cnt != NULL)
			PutContainer(obj, cnt);
	}

	/*!
	�������� � ���������
	@param [__in] obj ������ �� ������
	@param [__in] container ������ �� ���������
	@return 
	*/
	void PutContainer(__in TGameObject *obj, __in TGameObject *container);

	/*!
	����� �������
	@param [__in] obj ������ �� �������
	@param [__in] containerSerial �������� ����������
	@param [__in] layer ����, � ������� ����� �������
	@return 
	*/
	void PutEquipment( __in TGameItem *obj, __in DWORD containerSerial, __in int layer)
	{
		TGameObject *cnt = FindWorldObject(containerSerial);
		if (cnt != NULL)
			PutEquipment(obj, cnt, layer);
	}

	/*!
	����� �������
	@param [__in] obj ������ �� ������
	@param [__in] container ������ �� ���������
	@param [__in] layer ����, � ������� ����� �������
	@return 
	*/
	void PutEquipment( __in TGameItem *obj, __in TGameObject *container, __in int layer)
	{
		PutContainer(obj, container);
		obj->Layer = layer;
	}

	/*!
	������� ������ ����� � �������
	@param [__in] obj ������ �� ������
	@return 
	*/
	void MoveToTop(__in TGameObject *obj);

	/*!
	���� ���������, ���������� � ������
	@param [__in] nCount ���������� ��������
	@param [__in_opt] serial �������� ��������
	@return 
	*/
	void Dump(__in BYTE nCount = 0, __in_opt DWORD serial = 0xFFFFFFFF);

	/*!
	����� �������
	@param [__in] serialStart ��������� �������� ��� ������
	@param [__in] scanDistance ��������� ������
	@param [__in] scanType ��� �������� ������
	@param [__in] scanMode ����� ������
	@return ������ �� ��������� ������ ��� NULL
	*/
	TGameObject *SearchWorldObject(__in DWORD serialStart, __in int scanDistance, __in SCAN_TYPE_OBJECT scanType, __in SCAN_MODE_OBJECT scanMode);
 };
//---------------------------------------------------------------------------
//!��������� �� ���
extern TGameWorld *World;
//---------------------------------------------------------------------------
#endif