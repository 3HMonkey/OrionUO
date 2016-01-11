/****************************************************************************
**
** RenderObject.cpp
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
//---------------------------------------------------------------------------
TMapBlock::TMapBlock(DWORD index)
: TBaseQueueItem(), m_Index(index), m_LastAccessTime(GetTickCount()), m_X(0), m_Y(0)
{
	//�������� ����
	IFOR(i, 0, 8)
	{
		IFOR(j, 0, 8)
		{
			Block[i][j] = NULL;
		}
	}
}
//---------------------------------------------------------------------------
TMapBlock::~TMapBlock()
{
	//��� �������� ����� ������� ������ ��������� ����� � ������� ��������
	IFOR(i, 0, 8)
	{
		IFOR(j, 0, 8)
		{
			TMapObject *obj = Block[i][j];
			if (obj != NULL)
			{
				TRenderWorldObject *render = GetRender(i, j);

				while (render != NULL)
				{
					TRenderWorldObject *next = render->m_NextXY;
					render->m_PrevXY = NULL;
					render->m_NextXY = NULL;
					render = next;
				}

				delete obj;
				Block[i][j] = NULL;
			}
		}
	}

	m_Items = NULL;
}
//---------------------------------------------------------------------------
WORD TMapBlock::GetRadarColor(int x, int y)
{
	WORD color = 0;
	TRenderWorldObject *obj = Block[x][y];

	//�������� ��������� �� ������ ������� ������
	while (obj != NULL && obj->m_PrevXY != NULL)
		obj = obj->m_PrevXY;

	//��������� �� ����� ������ � �������� ��������� ������������� �� ��������
	while (obj != NULL)
	{
		switch (obj->RenderType)
		{
			case ROT_LAND_OBJECT:
			case ROT_STATIC_OBJECT:
			case ROT_MULTI_OBJECT:
			{
				color = obj->Graphic;

				break;
			}
			default:
				break;
		}

		obj = obj->m_NextXY;
	}

	//������ ��������� ���������
	return color;
}
//---------------------------------------------------------------------------
void TMapBlock::CreateLandTextureRect()
{
	//��������������� ������ �����
	int map = MapManager->GetActualMap();

	//� ��������� �� ���� �������� ��������� �����
	IFOR(x, 0, 8)
	{
		IFOR(y, 0, 8)
		{
			//��������� �� �����
			TLandObject *obj = GetLand(x, y);

			if (obj != NULL)
			{
				//��������� ������� � �������� Z-����������
				char tileZ1 = obj->Z;
				char tileZ2 = GetLandZ(obj->X, obj->Y + 1, map);
				char tileZ3 = GetLandZ(obj->X + 1, obj->Y + 1, map);
				char tileZ4 = GetLandZ(obj->X + 1, obj->Y, map);

				//��������������� �������� Z-����������
				char drawZ = (char)((tileZ1 + tileZ2 + tileZ3 + tileZ4) / 4);

				//���� ��� Z-���������� ����� - ������ ��� ��� ���� �� �����
				if (tileZ1 == tileZ2 && tileZ1 == tileZ3 && tileZ1 == tileZ4)
					obj->Color = 1;
				else //��� �� - ��������
				{
					obj->Color = 2;
					obj->Serial = drawZ;

					//�������� ��� �������
					RECT r =
					{
						(tileZ1 * 4),
						((tileZ1 - tileZ2) * 4),
						((tileZ1 - tileZ3) * 4),
						((tileZ1 - tileZ4) * 4)
					};

					obj->Rect = r;

					TVector vec[3][3][4];

					IFOR(i, -1, 2)
					{
						int curX = obj->X + i;

						IFOR(j, -1, 2)
						{
							int curY = obj->Y + j;

							char currentZ = GetLandZ(curX, curY, map);
							char leftZ = GetLandZ(curX, curY + 1, map);
							char rightZ = GetLandZ(curX + 1, curY + 1, map);
							char bottomZ = GetLandZ(curX + 1, curY, map);

							if (currentZ == leftZ && currentZ == rightZ && currentZ == bottomZ)
							{
								IFOR(k, 0, 4)
									vec[i + 1][j + 1][k].Link(0.0, 0.0, 1.0);
							}
							else
							{
								int curI = i + 1;
								int curJ = j + 1;

								vec[curI][curJ][0].Link(-22.0, 22.0, (currentZ - bottomZ) * 4);
								TVector v(-22.0, -22.0, (leftZ - currentZ) * 4);
								vec[curI][curJ][0].Merge(v);
								vec[curI][curJ][0].Normalize();
								
								vec[curI][curJ][1].Link(22.0, 22.0, (bottomZ - rightZ) * 4);
								v.Link(-22.0, 22.0, (currentZ - bottomZ) * 4);
								vec[curI][curJ][1].Merge(v);
								vec[curI][curJ][1].Normalize();
								
								vec[curI][curJ][2].Link(22.0, -22.0, (rightZ - leftZ) * 4);
								v.Link(22.0, 22.0, (bottomZ - rightZ) * 4);
								vec[curI][curJ][2].Merge(v);
								vec[curI][curJ][2].Normalize();
								
								vec[curI][curJ][3].Link(-22.0, -22.0, (leftZ - currentZ) * 4);
								v.Link(22.0, -22.0, (rightZ - leftZ) * 4);
								vec[curI][curJ][3].Merge(v);
								vec[curI][curJ][3].Normalize();

								/*vec[curI][curJ][0].Link(-22.0, 22.0, (currentZ - rightZ) * 4);
								TVector v(-22.0, -22.0, (leftZ - currentZ) * 4);
								vec[curI][curJ][0].Merge(v);
								vec[curI][curJ][0].Normalize();
								
								vec[curI][curJ][1].Link(22.0, 22.0, (rightZ - bottomZ) * 4);
								v.Link(-22.0, 22.0, (currentZ - rightZ) * 4);
								vec[curI][curJ][1].Merge(v);
								vec[curI][curJ][1].Normalize();
								
								vec[curI][curJ][2].Link(22.0, -22.0, (bottomZ - leftZ) * 4);
								v.Link(22.0, 22.0, (rightZ - bottomZ) * 4);
								vec[curI][curJ][2].Merge(v);
								vec[curI][curJ][2].Normalize();
								
								vec[curI][curJ][3].Link(-22.0, -22.0, (leftZ - currentZ) * 4);
								v.Link(22.0, -22.0, (bottomZ - leftZ) * 4);
								vec[curI][curJ][3].Merge(v);
								vec[curI][curJ][3].Normalize();*/
							}
						}
					}

					int i = 1;
					int j = 1;

					obj->m_Normals[0].Link(vec[i - 1][j - 1][2]);
					obj->m_Normals[0].Add(vec[i - 1][j][1]);
					obj->m_Normals[0].Add(vec[i][j - 1][3]);
					obj->m_Normals[0].Add(vec[i][j][0]);
					obj->m_Normals[0].Normalize();

					obj->m_Normals[1].Link(vec[i][j - 1][2]);
					obj->m_Normals[1].Add(vec[i][j][1]);
					obj->m_Normals[1].Add(vec[i + 1][j - 1][3]);
					obj->m_Normals[1].Add(vec[i + 1][j][0]);
					obj->m_Normals[1].Normalize();

					obj->m_Normals[2].Link(vec[i][j][2]);
					obj->m_Normals[2].Add(vec[i][j + 1][1]);
					obj->m_Normals[2].Add(vec[i + 1][j][3]);
					obj->m_Normals[2].Add(vec[i + 1][j + 1][0]);
					obj->m_Normals[2].Normalize();

					obj->m_Normals[1].Link(vec[i - 1][j][2]);
					obj->m_Normals[1].Add(vec[i - 1][j + 1][1]);
					obj->m_Normals[1].Add(vec[i][j][3]);
					obj->m_Normals[1].Add(vec[i][j + 1][0]);
					obj->m_Normals[1].Normalize();
				}

				//����������� Z-���������� �� ����
				char minZ = tileZ1;

				//if (tileZ2 > drawZ)
					//drawZ = tileZ2;
				if (tileZ2 < minZ)
					minZ = tileZ2;

				//if (tileZ3 > drawZ)
					//drawZ = tileZ3;
				if (tileZ3 < minZ)
					minZ = tileZ3;

				//if (tileZ4 > drawZ)
					//drawZ = tileZ4;
				if (tileZ4 < minZ)
					minZ = tileZ4;

				TMapObject *next = (TMapObject*)obj->m_Next;

				//��������� ��� ����� ����, ��� ��� �� ����� ������������ ����������� ����� ���������
				//if (next != NULL && next->IsWet() && !::IsWet(UO->GetLandFlags(obj->Graphic)))
					//next->RenderQueueIndex = 5;
					//drawZ = next->Z + 4;

				//� Z-����������� ���������, ���� �� ������������� ��� ������� �� ��������
				obj->DrawZ = drawZ - 3;
				obj->MinZ = minZ;
			}
		}
	}
}
//---------------------------------------------------------------------------
char TMapBlock::GetLandZ(int x, int y, int &map)
{
	//�������� ������������ ������
	if (!FileManager.MapMul[map].Address || !FileManager.StaticIdx[map].Address || !FileManager.StaticMul[map].Address)
		return 0;
	else if (x < 0 || y < 0 || x >= g_MapSizeX[map] || y >= g_MapSizeY[map])
		return 0;

	//������� �����
	WORD BlockX = x / 8;
	WORD BlockY = y /8;

	int Block = (BlockX * 512) + BlockY;

	//����
	PMAP_BLOCK mb = (PMAP_BLOCK)((DWORD)FileManager.MapMul[map].Address + (Block * sizeof(MAP_BLOCK)));

	BYTE mX = x % 8;
	BYTE mY = y % 8;

	return mb->Cells[mY * 8 + mX].Z;
}
//---------------------------------------------------------------------------
TLandObject *TMapBlock::GetLand(int &x, int &y)
{
	TMapObject *obj = Block[x][y];

	//��������� �� MapObject'�� �����
	while (obj != NULL)
	{
		//���� ����� - ����� �������� �����
		if (obj->IsLandObject())
			break;

		obj = (TMapObject*)obj->m_Next;
	}

	return (TLandObject*)obj;
}
//---------------------------------------------------------------------------
char TMapBlock::GetRenderZ(TRenderWorldObject *item)
{
	//�������� Z-���������� ��� �������
	char z = item->Z;

	//���������� ��� �����
	if (item->IsLandObject())
	{
		TMapObject *mo = (TMapObject*)item;

		//���� ��� ���� ��������
		if (mo->Color != 1)
			z = (char)mo->Serial;
	}

	return z;
}
//---------------------------------------------------------------------------
void TMapBlock::AddRender(TRenderWorldObject *item, int &x, int &y)
{
	item->RemoveRender();

	TRenderWorldObject *obj = Block[x][y];

	while (obj != NULL && obj->m_PrevXY != NULL)
		obj = obj->m_PrevXY;

	char inZ = GetRenderZ(item);
	BYTE inRQI = item->RenderQueueIndex;
	int inSumZ = inZ + inRQI;

	while (obj != NULL /*&& obj->m_NextDraw != NULL*/)
	{
		char objZ = GetRenderZ(obj);
		BYTE objRQI = obj->RenderQueueIndex;
		int objSumZ = objZ + objRQI;

		bool condition = false;

		if (inSumZ < objSumZ)
			condition = true;
		else if (inSumZ == objSumZ)
		{
			if (!inRQI && objRQI)
				condition = true;
			else if (inRQI < objRQI)
				condition = true;
		}

		if (condition)
		{
			if (obj->m_PrevXY != NULL)
			{
				obj = obj->m_PrevXY;
				break;
			}
			else
			{
				obj->m_PrevXY = item;
				item->m_NextXY = obj;
				item->m_PrevXY = NULL;

				return;
			}
		}

		if (obj->m_NextXY == NULL)
			break;

		obj = obj->m_NextXY;
	}

	TRenderWorldObject *next = obj->m_NextXY;
	
	obj->m_NextXY = item;
	item->m_PrevXY = obj;
	item->m_NextXY = next;

	if (next != NULL)
		next->m_PrevXY = item;
}
//---------------------------------------------------------------------------
TRenderWorldObject *TMapBlock::GetRender(int &x, int &y)
{
	TRenderWorldObject *obj = Block[x][y];

	//������ ��������� �� ������ ������� ������ �������
	while (obj != NULL && obj->m_PrevXY != NULL)
		obj = obj->m_PrevXY;

	return obj;
}
//---------------------------------------------------------------------------
TMapObject *TMapBlock::AddObject(TMapObject *obj, int x, int y)
{
	if (Block[x][y] != NULL)
	{
		TMapObject *item = Block[x][y];

		while (item != NULL)
		{
			if (!item->IsLandObject() && item->Z > obj->Z)
			{
				if (item->m_Prev != NULL)
				{
					item = (TMapObject*)item->m_Prev;
					break;
				}

				m_Items = obj;
				obj->m_Prev = NULL;
				obj->m_Next = item;
				item->m_Prev = obj;

				AddRender(obj, x, y);

				return obj;
			}
			else if (item->m_Next == NULL)
				break;

			item = (TMapObject*)item->m_Next;
		}
		
		TMapObject *next = (TMapObject*)item->m_Next;
		
		item->m_Next = obj;
		obj->m_Next = next;
		obj->m_Prev = item;
		
		if (next != NULL)
			next->m_Prev = obj;

		AddRender(obj, x, y);
	}
	else
	{
		Block[x][y] = obj;
		obj->m_Next = NULL;
		obj->m_Prev = NULL;
		obj->m_NextXY = NULL;
		obj->m_PrevXY = NULL;
	}

	return obj;
}
//---------------------------------------------------------------------------