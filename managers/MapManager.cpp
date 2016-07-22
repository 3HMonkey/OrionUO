/****************************************************************************
**
** MouseManager.cpp
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
#include "stdafx.h"

TMapManager *MapManager = NULL;
//---------------------------------------------------------------------------
TMapManager::TMapManager()
: TBaseQueue()
#if USE_BLOCK_MAP == 1
, m_Blocks(NULL), m_MaxBlockIndex(0)
#endif
{
}
//---------------------------------------------------------------------------
TMapManager::~TMapManager()
{
#if USE_BLOCK_MAP == 1
	if (m_Blocks != NULL)
	{
		delete[] m_Blocks;
		m_Blocks = NULL;
	}

	m_MaxBlockIndex = 0;
#endif
}
//---------------------------------------------------------------------------
/*!
�������� ���� ����� �������� �� �����
@param [__in] map ������ �����
@param [__in] blockX ���������� X �����
@param [__in] blockY ���������� Y �����
@param [__out] mb ������ �� ����
@return ��� ������ (0 - �������)
*/
int TMapManager::GetWorldMapBlock( __in int &map, __in int &blockX, __in int &blockY, __out MAP_BLOCK &mb)
{
	if (!FileManager.MapMul[map].Address || !FileManager.StaticIdx[map].Address || !FileManager.StaticMul[map].Address)
		return 1;
	else if (blockX < 0 || blockX >= g_MapBlockX[map])
		return 2;
	else if ( blockY < 0 || blockY >= g_MapBlockY[map])
		return 3;

	int block = (blockX * g_MapBlockY[map]) + blockY;
	PMAP_BLOCK pmb = (PMAP_BLOCK)((DWORD)FileManager.MapMul[map].Address + (block * sizeof(MAP_BLOCK)));
	
	if ((DWORD)pmb  > (DWORD)FileManager.MapMul[map].Address + FileManager.MapMul[map].Size)
		return 4;

	IFOR(x, 0, 8)
	{
		IFOR(y, 0, 8)
		{
			int pos = (y * 8) + x;
			mb.Cells[pos].TileID = pmb->Cells[pos].TileID;
			mb.Cells[pos].Z = pmb->Cells[pos].Z;
		}
	}

	PSTAIDX_BLOCK sidx = (PSTAIDX_BLOCK)((DWORD)FileManager.StaticIdx[map].Address + (block * sizeof(STAIDX_BLOCK)));
	if (sidx->Size > 0 && sidx->Position != 0xFFFFFFFF && (DWORD)sidx < (DWORD)FileManager.StaticIdx[map].Address + FileManager.StaticIdx[map].Size)
	{
		PSTATICS_BLOCK sb = (PSTATICS_BLOCK)((DWORD)FileManager.StaticMul[map].Address + sidx->Position);

		int scnt = sidx->Size / sizeof(STATICS_BLOCK);

		if (scnt > 0)
		{
			if (scnt > 1024)
				scnt = 1024;

			IFOR(c, 0, scnt)
			{
				if (sb->Color && sb->Color != 0xFFFF)
				{
					int pos = (sb->Y * 8) + sb->X;
					//if (pos > 64) continue;

					if (mb.Cells[pos].Z <= sb->Z)
					{
						mb.Cells[pos].TileID = sb->Color + 0x4000;
						mb.Cells[pos].Z = sb->Z;
					}
				}

				sb++;
			}
		}
	}

	return 0;
}
//---------------------------------------------------------------------------
/*!
�������� ���� ��� ������ �� ������
@param [__in] blockX ���������� X �����
@param [__in] blockY ���������� Y �����
@param [__out] mb ������ �� ����
@return 
*/
void TMapManager::GetRadarMapBlock( __in int blockX, __in int blockY, __out MAP_BLOCK &mb)
{
	int map = GetActualMap();
	
	if (!FileManager.MapMul[map].Address || !FileManager.StaticIdx[map].Address || !FileManager.StaticMul[map].Address)
		return;

	if (blockX < 0 || blockY < 0 || blockX >= g_MapBlockX[map] || blockY >= g_MapBlockY[map])
		return;

	int block = (blockX * g_MapBlockY[map]) + blockY;
	PMAP_BLOCK pmb = (PMAP_BLOCK)((DWORD)FileManager.MapMul[map].Address + (block * sizeof(MAP_BLOCK)));
	
	if ((DWORD)pmb  > (DWORD)FileManager.MapMul[map].Address + FileManager.MapMul[map].Size)
		return;

	IFOR(x, 0, 8)
	{
		IFOR(y, 0, 8)
		{
			int pos = (y * 8) + x;
			mb.Cells[pos].TileID = pmb->Cells[pos].TileID;
			mb.Cells[pos].Z = pmb->Cells[pos].Z;
		}
	}

	PSTAIDX_BLOCK sidx = (PSTAIDX_BLOCK)((DWORD)FileManager.StaticIdx[map].Address + (block * sizeof(STAIDX_BLOCK)));
	if (sidx->Size > 0 && sidx->Position != 0xFFFFFFFF && (DWORD)sidx < (DWORD)FileManager.StaticIdx[map].Address + FileManager.StaticIdx[map].Size)
	{
		PSTATICS_BLOCK sb = (PSTATICS_BLOCK)((DWORD)FileManager.StaticMul[map].Address + sidx->Position);

		int scnt = sidx->Size / sizeof(STATICS_BLOCK);
		if (scnt < 1)
			return;

		if (scnt > 1024)
			scnt = 1024;

		IFOR(c, 0, scnt)
		{
			if (sb->Color && sb->Color != 0xFFFF)
			{
				int pos = (sb->Y * 8) + sb->X;
				//if (pos > 64) continue;

				if (mb.Cells[pos].Z <= sb->Z)
				{
					mb.Cells[pos].TileID = sb->Color + 0x4000;
					mb.Cells[pos].Z = sb->Z;
				}
			}

			sb++;
		}
	}
}
//---------------------------------------------------------------------------
/*!
�������� �������� Z ���������� ��� ��������� ����� � ����
@param [__in] x ���������� X
@param [__in] y ���������� Y
@param [__out] groundZ �������� Z ���������� �����
@param [__out] staticZ �������� Z ���������� �������
@return 
*/
void TMapManager::GetMapZ( __in int x, __in int y, __out int &groundZ, __out int &staticZ)
{
	int blockX = x / 8;
	int blockY = y / 8;
	int index = (blockX * g_MapBlockY[g_CurrentMap]) + blockY;

	TMapBlock *block = GetBlock(index);

	if (block == NULL)
	{
		block = AddBlock(index);
		block->X = blockX;
		block->Y = blockY;
		LoadBlock(block);
	}
	
	x = x % 8;
	y = y % 8;

	TMapObject *item = block->Block[x][y];

	while (item != NULL)
	{
		if (item->IsLandObject())
			groundZ = item->Z;
		else if (staticZ < item->Z)
			staticZ = item->Z;

		item = (TMapObject*)item->m_Next;
	}
}
//---------------------------------------------------------------------------
/*!
������� �������������� �����
@return 
*/
void TMapManager::ClearUnusedBlocks()
{
	TMapBlock *block = (TMapBlock*)m_Items;
	DWORD ticks = g_Ticks - CLEAR_TEXTURES_DELAY;

	while (block != NULL)
	{
		TMapBlock *next = (TMapBlock*)block->m_Next;

		if (block->LastAccessTime < ticks && block->HasNoExternalData())
		{
			DWORD index = block->Index;
			Delete(block);

#if USE_BLOCK_MAP == 1
			m_Blocks[index] = NULL;
#endif
		}

		block = next;
	}
}
//---------------------------------------------------------------------------
/*!
�������������
@param [__in_opt] delayed �� ��������� ������� �� �������� �������� �� �����
@return 
*/
void TMapManager::Init( __in_opt bool delayed)
{
	if (g_Player == NULL)
		return;

	int map = GetActualMap();

#if USE_BLOCK_MAP == 1
	if (!delayed)
	{
		if (m_Blocks != NULL)
		{
			delete[] m_Blocks;
			m_Blocks = NULL;
		}

		m_MaxBlockIndex = g_MapBlockX[map] * g_MapBlockY[map];
		m_Blocks = new TMapBlock*[m_MaxBlockIndex];
		memset(&m_Blocks[0], 0, sizeof(TMapBlock*) * m_MaxBlockIndex);
	}
#endif
	
	const int XY_Offset = 30; //70;

	int minBlockX = (g_Player->X - XY_Offset) / 8 - 1;
	int minBlockY = (g_Player->Y - XY_Offset) / 8 - 1;
	int maxBlockX = ((g_Player->X + XY_Offset) / 8) + 1;
	int maxBlockY = ((g_Player->Y + XY_Offset) / 8) + 1;

	DWORD ticks = g_Ticks;
	DWORD maxDelay = g_FrameDelay[1] / 2;

	for (int i = minBlockX; i <= maxBlockX; i++)
	{
		if (i < 0 || i >= g_MapBlockX[map])
			continue;

		for (int j = minBlockY; j <= maxBlockY; j++)
		{
			if (j < 0 || j >= g_MapBlockY[map])
				continue;

			int index = (i * g_MapBlockY[map]) + j;
			TMapBlock *block = GetBlock(index);

			if (block == NULL)
			{
				if (delayed && g_Ticks - ticks >= maxDelay)
					return;

				block = AddBlock(index);
				block->X = i;
				block->Y = j;
				LoadBlock(block);
			}
		}
	}
}
//---------------------------------------------------------------------------
/*!
��������� ����
@param [__inout] block ������ �� ���� ��� ��������
@return 
*/
void TMapManager::LoadBlock( __inout TMapBlock *block)
{
	int Map = GetActualMap();
	
	if (!FileManager.MapMul[Map].Address || !FileManager.StaticIdx[Map].Address || !FileManager.StaticMul[Map].Address)
		return;

	int index = block->Index;
	PMAP_BLOCK pmb = (PMAP_BLOCK)((DWORD)FileManager.MapMul[Map].Address + (index * sizeof(MAP_BLOCK)));
	
	int bx = block->X * 8;
	int by = block->Y * 8;

	IFOR(x, 0, 8)
	{
		IFOR(y, 0, 8)
		{
			int pos = y * 8 + x;
			TMapObject *obj = new TLandObject(pos, pmb->Cells[pos].TileID, 0, bx + x, by + y, pmb->Cells[pos].Z);
			block->AddObject(obj, x, y);
		}
	}

	PSTAIDX_BLOCK sidx = (PSTAIDX_BLOCK)((DWORD)FileManager.StaticIdx[Map].Address + (index * sizeof(STAIDX_BLOCK)));
	if (sidx->Size > 0 && sidx->Position != 0xFFFFFFFF && (DWORD)sidx < (DWORD)FileManager.StaticIdx[Map].Address + FileManager.StaticIdx[Map].Size)
	{
		PSTATICS_BLOCK sb = (PSTATICS_BLOCK)((DWORD)FileManager.StaticMul[Map].Address + sidx->Position);

		int scnt = sidx->Size / sizeof(STATICS_BLOCK);

		if (scnt > 1024)
			scnt = 1024;

		for (int c = 0; c < scnt; c++, sb++)
		{
			if (sb->Color && sb->Color != 0xFFFF)
			{
				int x = sb->X;
				int y = sb->Y;

				int pos = (y * 8) + x;
				if (pos >= 64)
					continue;

				TRenderStaticObject *obj = new TStaticObject(pos, sb->Color, sb->Hue, bx + x, by + y, sb->Z);

				if (ToLowerA(obj->GetStaticData()->Name) == "nodraw")
					delete obj;
				else
					block->AddObject(obj, x, y);
			}
		}
	}

	block->CreateLandTextureRect();
}
//---------------------------------------------------------------------------
/*!
�������� ������ ������� �����
@return
*/
int TMapManager::GetActualMap()
{
	if (g_CurrentMap == 1 && (!FileManager.MapMul[1].Address || !FileManager.StaticIdx[1].Address || !FileManager.StaticMul[1].Address))
		return 0;

	return g_CurrentMap;
}
//---------------------------------------------------------------------------
/*!
�������� ������ �������
@param [__in] item ������ �� ������
@return 
*/
void TMapManager::AddRender( __in TRenderWorldObject *item)
{
	int itemX = item->X;
	int itemY = item->Y;

	int x = itemX / 8;
	int y = itemY / 8;
	
	int index = (x * g_MapBlockY[g_CurrentMap]) + y;
	
	TMapBlock *block = MapManager->GetBlock(index);
	
	if (block == NULL)
	{
		block = AddBlock(index);
		block->X = x;
		block->Y = y;
		LoadBlock(block);
	}

	x = itemX % 8;
	y = itemY % 8;
		
	block->AddRender(item, x, y);
}
//---------------------------------------------------------------------------
/*!
�������� ������ �� ����
@param [__in] index ������ �����
@return ������ �� ���� ��� NULL
*/
TMapBlock *TMapManager::GetBlock(__in DWORD index)
{
#if USE_BLOCK_MAP == 0
	TMapBlock *block = (TMapBlock*)m_Items;

	while (block != NULL)
	{
		if (block->Index == index)
		{
			block->LastAccessTime = g_Ticks;

			break;
		}

		block = (TMapBlock*)block->m_Next;
	}
#else
	TMapBlock *block = NULL;

	if (index < m_MaxBlockIndex)
		block = m_Blocks[index];

	if (block != NULL)
		block->LastAccessTime = g_Ticks;
#endif

	return block;
}
//---------------------------------------------------------------------------
/*!
�������� ����
@param [__in] index ������ �����
@return ������ �� ���� ��� NULL
*/
TMapBlock *TMapManager::AddBlock(__in DWORD index)
{
	TMapBlock *block = (TMapBlock*)Add(new TMapBlock(index));

#if USE_BLOCK_MAP == 1
	m_Blocks[index] = block;
#endif

	return block;
}
//---------------------------------------------------------------------------
/*!
������� ����
@param [__in] index ������ �����
@return 
*/
void TMapManager::DeleteBlock( __in DWORD index)
{
	TMapBlock *block = (TMapBlock*)m_Items;

	while (block != NULL)
	{
		if (block->Index == index)
		{
			Delete(block);
#if USE_BLOCK_MAP == 1
			m_Blocks[index] = NULL;
#endif

			break;
		}

		block = (TMapBlock*)block->m_Next;
	}
}
//---------------------------------------------------------------------------
TUopMapManager::TUopMapManager()
: TMapManager()
{
}
//---------------------------------------------------------------------------
TUopMapManager::~TUopMapManager()
{
}
//---------------------------------------------------------------------------
/*!
�������� ������ ������� �����
@return
*/
int TUopMapManager::GetActualMap()
{
	//if (g_CurrentMap == 1 && (!FileManager.MapMul[1].Address || !FileManager.StaticIdx[1].Address || !FileManager.StaticMul[1].Address))
	//	return 0;

	return g_CurrentMap;
}
//---------------------------------------------------------------------------
/*!
��������� ����
@param [__inout] block ������ �� ���� ��� ��������
@return
*/
void TUopMapManager::LoadBlock(__inout TMapBlock *block)
{
}
//---------------------------------------------------------------------------
/*!
�������� ���� ����� �������� �� �����
@param [__in] map ������ �����
@param [__in] blockX ���������� X �����
@param [__in] blockY ���������� Y �����
@param [__out] mb ������ �� ����
@return ��� ������ (0 - �������)
*/
int TUopMapManager::GetWorldMapBlock(__in int &map, __in int &blockX, __in int &blockY, __out MAP_BLOCK &mb)
{
	return 0;
}
//---------------------------------------------------------------------------
/*!
�������� ���� ��� ������ �� ������
@param [__in] blockX ���������� X �����
@param [__in] blockY ���������� Y �����
@param [__out] mb ������ �� ����
@return
*/
void TUopMapManager::GetRadarMapBlock(__in int blockX, __in int blockY, __out MAP_BLOCK &mb)
{
}
//---------------------------------------------------------------------------