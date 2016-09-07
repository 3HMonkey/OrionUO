/***********************************************************************************
**
** GameWorld.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GAMEWORLD_H
#define GAMEWORLD_H
//----------------------------------------------------------------------------------
#include "GameObject.h"
#include "GameItem.h"
#include "GameCharacter.h"
//----------------------------------------------------------------------------------
typedef map<uint, CGameObject*> WORLD_MAP;
//----------------------------------------------------------------------------------
//!����� �������� ����
class CGameWorld
{
private:
	/*!
	������� ������
	@param [__in] serial �������� ������
	@return 
	*/
	void CreatePlayer(const uint &serial);

	/*!
	������� ������
	@return 
	*/
	void RemovePlayer();

public:
	CGameWorld(const uint &serial);
	~CGameWorld();

	//!�������� � ������
	WORLD_MAP m_Map;

	//!�������� � ����
	CGameObject *m_Items;

	/*!
	��������� �������� ���� ����������
	@return 
	*/
	void ProcessAnimation();
	/*!
	��������� ������ �����������
	@return
	*/
	void ProcessSound(const uint &ticks, CGameCharacter *gc);

	/*!
	���������� �������� ���� � ��������� ���������� ��� ���������
	@param [__in] serial �������� ������ ������
	@return 
	*/
	void SetPlayer(const uint &serial);

	/*!
	������� (��� �����, ���� ��� ����������) ������� �������
	@param [__in] serial �������� ��������
	@return ������ �� �������
	*/
	CGameItem *GetWorldItem(const uint &serial);

	/*!
	������� (��� �����, ���� ��� ����������) �������� ���������
	@param [__in] serial �������� ���������
	@return ������ �� ���������
	*/
	CGameCharacter *GetWorldCharacter(const uint &serial);

	/*!
	����� ������� ������ � ������
	@param [__in] serial �������� �������
	@return ������ �� ������ ��� NULL
	*/
	CGameObject *FindWorldObject(const uint &serial);

	/*!
	����� ������� ������� � ������
	@param [__in] serial �������� ��������
	@return ������ �� ������� ��� NULL
	*/
	CGameItem *FindWorldItem(const uint &serial);

	/*!
	����� �������� ��������� � ������
	@param [__in] serial �������� ���������
	@return ������ � ��������� ��� NULL
	*/
	CGameCharacter *FindWorldCharacter(const uint &serial);

	/*!
	������� ������ �� ������
	@param [__in] obj ������ �� ������
	@return 
	*/
	void RemoveObject(CGameObject *obj);

	/*!
	������ ������ �� ����������
	@param [__in] obj ������ �� ������
	@return 
	*/
	void RemoveFromContainer(CGameObject *obj);

	/*!
	�������� ��������� ���������
	@param [__in] obj ������ �� ������ (���������)
	@return 
	*/
	void ClearContainer(CGameObject *obj);

	/*!
	�������� � ���������
	@param [__in] obj ������ �� ������
	@param [__in] containerSerial �������� ����������
	@return 
	*/
	void PutContainer(CGameObject *obj, const uint &containerSerial)
	{
		CGameObject *cnt = FindWorldObject(containerSerial);
		if (cnt != NULL)
			PutContainer(obj, cnt);
	}

	/*!
	�������� � ���������
	@param [__in] obj ������ �� ������
	@param [__in] container ������ �� ���������
	@return 
	*/
	void PutContainer(CGameObject *obj, CGameObject *container);

	/*!
	����� �������
	@param [__in] obj ������ �� �������
	@param [__in] containerSerial �������� ����������
	@param [__in] layer ����, � ������� ����� �������
	@return 
	*/
	void PutEquipment(CGameItem *obj, const uint &containerSerial, const int &layer)
	{
		CGameObject *cnt = FindWorldObject(containerSerial);
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
	void PutEquipment(CGameItem *obj, CGameObject *container, const int &layer)
	{
		PutContainer(obj, container);
		obj->Layer = layer;
	}

	/*!
	������� ������ ����� � �������
	@param [__in] obj ������ �� ������
	@return 
	*/
	void MoveToTop(CGameObject *obj);

	/*!
	���� ���������, ���������� � ������
	@param [__in] nCount ���������� ��������
	@param [__in_opt] serial �������� ��������
	@return 
	*/
	void Dump(uchar nCount = 0, uint serial = 0xFFFFFFFF);

	/*!
	����� �������
	@param [__in] serialStart ��������� �������� ��� ������
	@param [__in] scanDistance ��������� ������
	@param [__in] scanType ��� �������� ������
	@param [__in] scanMode ����� ������
	@return ������ �� ��������� ������ ��� NULL
	*/
	CGameObject *SearchWorldObject(const uint &serialStart, const int &scanDistance, const SCAN_TYPE_OBJECT &scanType, const SCAN_MODE_OBJECT &scanMode);
 };
//---------------------------------------------------------------------------
//!��������� �� ���
extern CGameWorld *g_World;
//---------------------------------------------------------------------------
#endif