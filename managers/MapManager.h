/****************************************************************************
**
** MapManager.h
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
#ifndef MapManagerH
#define MapManagerH

//������������ ������ ������ ��� �������
#define USE_BLOCK_MAP 1
//--------------------------------------------------------------------------
//!����� ��������� ����
class TMapManager : public TBaseQueue
{
private:
#if USE_BLOCK_MAP == 1
	//!������ ������ �� ����� �����
	TMapBlock **m_Blocks;
#endif

	//!������������ ������ ����� ��� ������� �����
	DWORD m_MaxBlockIndex;

public:
	TMapManager();
	virtual ~TMapManager();

	/*!
	�������� ������ ������� �����
	@return 
	*/
	virtual int GetActualMap();

	/*!
	��������� ����
	@param [__inout] block ������ �� ���� ��� ��������
	@return 
	*/
	virtual void LoadBlock(__inout TMapBlock *block);

	/*!
	�������� ���� ��� ������ �� ������
	@param [__in] blockX ���������� X �����
	@param [__in] blockY ���������� Y �����
	@param [__out] mb ������ �� ����
	@return 
	*/
	virtual void GetRadarMapBlock(__in int blockX, __in int blockY, __out MAP_BLOCK &mb);

	/*!
	�������� ���� ����� �������� �� �����
	@param [__in] map ������ �����
	@param [__in] blockX ���������� X �����
	@param [__in] blockY ���������� Y �����
	@param [__out] mb ������ �� ����
	@return ��� ������ (0 - �������)
	*/
	virtual int GetWorldMapBlock(__in int &map, __in int &blockX, __in int &blockY, __out MAP_BLOCK &mb);

	/*!
	�������� �������� Z ���������� ��� ��������� ����� � ����
	@param [__in] x ���������� X
	@param [__in] y ���������� Y
	@param [__out] groundZ �������� Z ���������� �����
	@param [__out] staticZ �������� Z ���������� �������
	@return 
	*/
	void GetMapZ(__in int x, __in int y, __out int &groundZ, __out int &staticZ);

	/*!
	�������������
	@param [__in_opt] delayed �� ��������� ������� �� �������� �������� �� �����
	@return 
	*/
	void Init(__in_opt bool delayed = false);

	/*!
	�������� ������ �� ����
	@param [__in] index ������ �����
	@return ������ �� ���� ��� NULL
	*/
	TMapBlock *GetBlock(__in DWORD index);

	/*!
	�������� ����
	@param [__in] index ������ �����
	@return ������ �� ���� ��� NULL
	*/
	TMapBlock *AddBlock(__in DWORD index);

	/*!
	������� ����
	@param [__in] index ������ �����
	@return 
	*/
	void DeleteBlock(__in DWORD index);

	/*!
	������� �������������� �����
	@return 
	*/
	void ClearUnusedBlocks();

	/*!
	�������� ������ �������
	@param [__in] item ������ �� ������
	@return 
	*/
	void AddRender(__in TRenderWorldObject *item);

};
//--------------------------------------------------------------------------
//!����� ��������� ����
class TUopMapManager : public TMapManager
{
public:
	TUopMapManager();
	virtual ~TUopMapManager();

	/*!
	�������� ������ ������� �����
	@return
	*/
	virtual int GetActualMap();

	/*!
	��������� ����
	@param [__inout] block ������ �� ���� ��� ��������
	@return
	*/
	virtual void LoadBlock(__inout TMapBlock *block);

	/*!
	�������� ���� ����� �������� �� �����
	@param [__in] map ������ �����
	@param [__in] blockX ���������� X �����
	@param [__in] blockY ���������� Y �����
	@param [__out] mb ������ �� ����
	@return ��� ������ (0 - �������)
	*/
	virtual int GetWorldMapBlock(__in int &map, __in int &blockX, __in int &blockY, __out MAP_BLOCK &mb);

	/*!
	�������� ���� ��� ������ �� ������
	@param [__in] blockX ���������� X �����
	@param [__in] blockY ���������� Y �����
	@param [__out] mb ������ �� ����
	@return
	*/
	virtual void GetRadarMapBlock(__in int blockX, __in int blockY, __out MAP_BLOCK &mb);
};
//--------------------------------------------------------------------------
extern TMapManager *MapManager;
//--------------------------------------------------------------------------
#endif