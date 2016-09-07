/***********************************************************************************
**
** MapManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef MAPMANAGER_H
#define MAPMANAGER_H
//----------------------------------------------------------------------------------
//������������ ������ ������ ��� �������
#define USE_BLOCK_MAP 1
//----------------------------------------------------------------------------------
#include "../BaseQueue.h"
#include "../Game objects/MapBlock.h"
#include "../MulStruct.h"
//----------------------------------------------------------------------------------
//!����� ��������� ����
class CMapManager : public CBaseQueue
{
private:
#if USE_BLOCK_MAP == 1
	//!������ ������ �� ����� �����
	CMapBlock **m_Blocks;
#endif

	//!������������ ������ ����� ��� ������� �����
	uint m_MaxBlockIndex;

public:
	CMapManager();
	virtual ~CMapManager();

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
	virtual void LoadBlock(CMapBlock *block);

	/*!
	�������� ���� ��� ������ �� ������
	@param [__in] blockX ���������� X �����
	@param [__in] blockY ���������� Y �����
	@param [__out] mb ������ �� ����
	@return 
	*/
	virtual void GetRadarMapBlock(const int &blockX, const int &blockY, MAP_BLOCK &mb);

	/*!
	�������� ���� ����� �������� �� �����
	@param [__in] map ������ �����
	@param [__in] blockX ���������� X �����
	@param [__in] blockY ���������� Y �����
	@param [__out] mb ������ �� ����
	@return ��� ������ (0 - �������)
	*/
	virtual int GetWorldMapBlock(const int &map, const int &blockX, const int &blockY, MAP_BLOCK &mb);

	/*!
	�������� �������� Z ���������� ��� ��������� ����� � ����
	@param [__in] x ���������� X
	@param [__in] y ���������� Y
	@param [__out] groundZ �������� Z ���������� �����
	@param [__out] staticZ �������� Z ���������� �������
	@return 
	*/
	void GetMapZ(const int &x, const int &y, int &groundZ, int &staticZ);

	/*!
	�������������
	@param [__in_opt] delayed �� ��������� ������� �� �������� �������� �� �����
	@return 
	*/
	void Init(const bool &delayed = false);

	/*!
	�������� ������ �� ����
	@param [__in] index ������ �����
	@return ������ �� ���� ��� NULL
	*/
	CMapBlock *GetBlock(const uint &index);

	/*!
	�������� ����
	@param [__in] index ������ �����
	@return ������ �� ���� ��� NULL
	*/
	CMapBlock *AddBlock(const uint &index);

	/*!
	������� ����
	@param [__in] index ������ �����
	@return 
	*/
	void DeleteBlock(const uint &index);

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
	void AddRender(CRenderWorldObject *item);

};
//----------------------------------------------------------------------------------
//!����� ��������� ����
class CUopMapManager : public CMapManager
{
public:
	CUopMapManager();
	virtual ~CUopMapManager();

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
	virtual void LoadBlock(CMapBlock *block);

	/*!
	�������� ���� ����� �������� �� �����
	@param [__in] map ������ �����
	@param [__in] blockX ���������� X �����
	@param [__in] blockY ���������� Y �����
	@param [__out] mb ������ �� ����
	@return ��� ������ (0 - �������)
	*/
	virtual int GetWorldMapBlock(const int &map, const int &blockX, const int &blockY, MAP_BLOCK &mb);

	/*!
	�������� ���� ��� ������ �� ������
	@param [__in] blockX ���������� X �����
	@param [__in] blockY ���������� Y �����
	@param [__out] mb ������ �� ����
	@return
	*/
	virtual void GetRadarMapBlock(const int &blockX, const int &blockY, MAP_BLOCK &mb);
};
//----------------------------------------------------------------------------------
extern CMapManager *g_MapManager;
//----------------------------------------------------------------------------------
#endif
