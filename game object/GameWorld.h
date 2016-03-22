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
class TGameWorld
{
private:
	//������� ������
	void CreatePlayer(DWORD serial);
	//������� ������
	void RemovePlayer();
public:
	TGameWorld(DWORD serial);
	~TGameWorld();

	//�������� � ������
	WORLD_MAP m_Map;

	//�������� � ����
	TGameObject *m_Items;

	//��������� �������� ���� ����������
	void ProcessAnimation();

	//���������� �������� ���� � ��������� ���������� ��� ���������
	void SetPlayer(DWORD serial);

	//������� (��� �����, ���� ��� ����������) ������� �������
	TGameItem *GetWorldItem(DWORD serial);
	//������� (��� �����, ���� ��� ����������) �������� ���������
	TGameCharacter *GetWorldCharacter(DWORD serial);
	//����� ������� ������ � ������ (NULL ���� ���)
	TGameObject *FindWorldObject(DWORD serial);
	//����� ������� ������� � ������ (NULL ���� ���)
	TGameItem *FindWorldItem(DWORD serial);
	//����� �������� ��������� � ������ (NULL ���� ���)
	TGameCharacter *FindWorldCharacter(DWORD serial);
	//����� �������� ��������� (��������� �����) � ������ (NULL ���� ���)
	TGameCharacter *FindWorldCorpseOwner(DWORD serial);

	//������� ������ �� ������
	void RemoveObject(TGameObject *obj);
	//������ ������ �� ����������
	void RemoveFromContainer(TGameObject *obj);
	//�������� ��������� ���������
	void ClearContainer(TGameObject *obj);
	//�������� � ���������
	void PutContainer(TGameObject *obj, DWORD container_serial)
	{
		TGameObject *cnt = FindWorldObject(container_serial);
		if (cnt != NULL)
			PutContainer(obj, cnt);
	}
	//�������� � ���������
	void PutContainer(TGameObject *obj, TGameObject *container);
	//����� �������
	void PutEquipment(TGameItem *obj, DWORD container_serial, int layer)
	{
		TGameObject *cnt = FindWorldObject(container_serial);
		if (cnt != NULL)
			PutEquipment(obj, cnt, layer);
	}
	//����� �������
	void PutEquipment(TGameItem *obj, TGameObject *container, int layer)
	{
		PutContainer(obj, container);
		obj->Layer = layer;
	}

	//������� ������� ����� � �������
	void MoveToTop(TGameObject *obj);

	//���� ���������, ���������� � ������
	void Dump(BYTE nCount = 0, DWORD serial = 0xFFFFFFFF);

	//����� �������
	TGameObject *SearchWorldObject(DWORD serialStart, int scanDistance, SCAN_TYPE_OBJECT scanType, SCAN_MODE_OBJECT scanMode);
};
//---------------------------------------------------------------------------
extern TGameWorld *World; //��������� �� ���
//---------------------------------------------------------------------------
#endif