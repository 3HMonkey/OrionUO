/***********************************************************************************
**
** MulReader.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "MulReader.h"
#include "ColorManager.h"
#include "../GLEngine/GLEngine.h"

CMulReader *g_MulReader = NULL;
//---------------------------------------------------------------------------
//----------------------------------CMulReader-------------------------------
//---------------------------------------------------------------------------
/*!
�������� ������ �������� �����
@param [__in] io ������ �� ������ � �����
@return ������ �������� ��� NULL
*/
USHORT_LIST CMulReader::GetGumpPixels(CIndexObject &io)
{
	int dataStart = io.Address;
	puint lookupList = (puint)dataStart;

	int blocksize = io.Width * io.Height;

	USHORT_LIST pixels(blocksize);

#if UO_ENABLE_TEXTURE_DATA_SAVING == 1
	USHORT_LIST &data = io.Texture.PixelsData;
	data.resize(blocksize);
#endif

	ushort color = io.Color;

	IFOR(y, 0, io.Height)
	{
		int gSize = 0;

		if (y < io.Height - 1)
			gSize = lookupList[y + 1] - lookupList[y];
		else
			gSize = (io.DataSize / 4) - lookupList[y];

		PGUMP_BLOCK gmul = (PGUMP_BLOCK)(dataStart + lookupList[y] * 4);
		int pos = y * io.Width;

		IFOR(i, 0, gSize)
		{
			ushort val = gmul[i].Value;

			if (color)
				val = g_ColorManager.GetColor16(val, color);

			ushort a = (val ? 0x8000 : 0) | val;

			int count = gmul[i].Run;

			IFOR(j, 0, count)
			{
				pixels[pos] = a;

#if UO_ENABLE_TEXTURE_DATA_SAVING == 1
				data[pos] = a;
#endif

				pos++;
			}
		}
	}

	return pixels;
}
//---------------------------------------------------------------------------
/*!
��������� ���� � ������������� ��������
@param [__in] io ������ �� ������ � �����
@return ������ �� ������ � ��������
*/
CGLTexture *CMulReader::ReadGump(CIndexObject &io)
{
	CGLTexture *th = new CGLTexture();
	th->Width = io.Width;
	th->Height = io.Height;
	th->Texture = 0;

	USHORT_LIST pixels = GetGumpPixels(io);

	if (pixels.size())
		g_GL.BindTexture16(th->Texture, io.Width, io.Height, &pixels[0]);

	return th;
}
//---------------------------------------------------------------------------
/*!
��������� ���������� ������� ����� � ��������� �����������
@param [__in] io ������ �� ������ � �����
@param [__in] checkX ���������� X
@param [__in] checkY ���������� Y
@return true � ������ ��������� �����
*/
bool CMulReader::GumpPixelsInXY(CIndexObject &io, const int &checkX, const int &checkY)
{
	CGLTexture *th = io.Texture;

	//if (th == NULL)
	//	return false;

	int width = th->Width;
	int height = th->Height;

	if (checkX < 0 || checkY < 0 || checkX >= width || checkY >= height)
		return false;

	int dataStart = io.Address;
	puint lookupList = (puint)dataStart;

	int gSize = 0;
	if (checkY < height - 1)
		gSize = lookupList[checkY + 1] - lookupList[checkY];
	else
		gSize = (io.DataSize / 4) - lookupList[checkY];

	PGUMP_BLOCK gmul = (PGUMP_BLOCK)(dataStart + lookupList[checkY] * 4);
	
	int x = 0;
	IFOR(i, 0, gSize)
	{
		x += gmul[i].Run;

		if (x >= checkX)
			return (gmul[i].Value != 0);
	}

	return false;
}
//---------------------------------------------------------------------------
/*!
��������� ��� � ������������� ��������
@param [__in] ID ������ ����
@param [__in] io ������ �� ������ � ����
@return ������ �� ������ � ��������
*/
CGLTexture *CMulReader::ReadArt(const WORD &id, CIndexObject &io)
{
	CGLTexture *th = new CGLTexture();
	th->Texture = 0;

	uint flag = *(puint)io.Address;
	ushort h = 44;
	ushort w = 44;
	pushort P = (pushort)io.Address;
	ushort color = io.Color;

	//if (!flag || flag > 0xFFFF) //raw tile
	if (id < 0x4000) //raw tile
	{
		const int blocksize = 44 * 44;

		ushort pixels[blocksize] = { 0 };
		
#if UO_ENABLE_TEXTURE_DATA_SAVING == 1
		PUSHORT_LIST &data = th->PixelsData;
		data.resize(blocksize, 0);
#endif
		IFOR(i, 0, 22)
		{
			int pos = i * 44;
			int end = (22 - (i + 1)) + (i + 1) * 2;

			IFOR(j, 22 - (i + 1), end)
			{
				ushort val = *P++;

				if (color)
					val = g_ColorManager.GetColor16(val, color);

				val = (val ? 0x8000 : 0) | val;
				int block = pos + j;
				pixels[block] = val;
#if UO_ENABLE_TEXTURE_DATA_SAVING == 1
				data[block] = val;
#endif
			}
		}

		IFOR(i, 0, 22)
		{
			int pos = (i + 22) * 44;
			int end = i + (22 - i) * 2;

			IFOR(j, i, end)
			{
				ushort val = *P++;

				if (color)
					val = g_ColorManager.GetColor16(val, color);

				val = (val ? 0x8000 : 0) | val;
				int block = pos + j;
				pixels[block] = val;
#if UO_ENABLE_TEXTURE_DATA_SAVING == 1
				data[block] = val;
#endif
			}
		}

		g_GL.BindTexture16(th->Texture, 44, 44, &pixels[0]);
	}
	else //run tile
	{
		pushort ptr = (pushort)(io.Address + 4);

		w = *ptr;
		if (!w || w >= 1024)
		{
			delete th;
			return NULL;
		}

		ptr++;

		h = *ptr;

		if (!h || (h * 2) > 5120)
		{
			delete th;
			return NULL;
		}

		ptr++;

		pushort LineOffsets = ptr;
		PVOID DataStart = (PVOID)((uint)ptr + (h * 2));

		int X = 0;
		int Y = 0;
		ushort XOffs = 0;
		ushort Run = 0;

		int blocksize = w * h;

		USHORT_LIST pixels(blocksize, 0);
		
#if UO_ENABLE_TEXTURE_DATA_SAVING == 1
		USHORT_LIST &data = th->PixelsData;
		data.resize(blocksize, 0);
#endif

		ptr = (pushort)((uint)DataStart + (*LineOffsets));

		while (Y < h)
		{
			XOffs = *ptr;
			ptr++;
			Run = *ptr;
			ptr++;
			if (XOffs + Run >= 2048)
			{
				delete th;
				return NULL;
			}
			else if (XOffs + Run != 0)
			{
				X += XOffs;
				int pos = Y * w + X;

				IFOR(j, 0, Run)
				{
					ushort val = *ptr;

					if (color)
						val = g_ColorManager.GetColor16(val, color);

					val = (val ? 0x8000 : 0) | val;
					int block = pos + j;
					pixels[block] = val;
#if UO_ENABLE_TEXTURE_DATA_SAVING == 1
					data[block] = val;
#endif
					ptr++;
				}

				X += Run;
			}
			else
			{
				X = 0;
				Y++;
				ptr = (pushort)((uint)DataStart + (LineOffsets[Y] * 2));
			}
		}

		if ((id >= 0x6053 && id <= 0x6062) || (id >= 0x606A && id <= 0x6079)) //������� ����� (���� ��� ������ �����)
		{
			IFOR(i, 0, w)
			{
				pixels[i] = 0;
				pixels[(h - 1) * w + i] = 0;
			}

			IFOR(i, 0, h)
			{
				pixels[i * w] = 0;
				pixels[i * w + w - 1] = 0;
			}
		}

		g_GL.BindTexture16(th->Texture, w, h, &pixels[0]);
	}

	th->Width = w;
	th->Height = h;

	return th;
}
//---------------------------------------------------------------------------
/*!
��������� ��� � ��������� �������� ����������� ������� ��������
@param [__in] io ������ �� ������ � ����
@param [__out] r ��������� � ���������� �� ������
@return ������ �� ������ � ��������
*/
WISP_GEOMETRY::CRect CMulReader::ReadStaticArtPixelDimension(CIndexObject &io)
{
	WISP_GEOMETRY::CRect r;

	uint flag = *(PDWORD)io.Address;
	ushort h = 44;
	ushort w = 44;
	pushort P = (pushort)io.Address;

	pushort ptr = (pushort)(io.Address + 4);

	w = *ptr;
	if (!w || w >= 1024)
		return r;

	ptr++;

	h = *ptr;

	if (!h || (h * 2) > 5120)
		return r;

	ptr++;

	pushort LineOffsets = ptr;
	PVOID DataStart = (PVOID)((uint)ptr + (h * 2));

	int X = 0;
	int Y = 0;
	ushort XOffs = 0;
	ushort Run = 0;

	ptr = (pushort)((uint)DataStart + (*LineOffsets));

	int minX = w;
	int minY = h;
	int maxX = 0;
	int maxY = 0;

	while (Y < h)
	{
		XOffs = *ptr;
		ptr++;
		Run = *ptr;
		ptr++;
		if (XOffs + Run >= 2048)
			return r;
		else if (XOffs + Run != 0)
		{
			X += XOffs;

			IFOR(j, 0, Run)
			{
				if (*ptr)
				{
					int testX = X + j;

					if (testX < minX)
						minX = testX;

					if (testX > maxX)
						maxX = testX;

					if (Y < minY)
						minY = Y;

					if (Y > maxY)
						maxY = Y;
				}

				ptr++;
			}

			X += Run;
		}
		else
		{
			X = 0;
			Y++;
			ptr = (pushort)((uint)DataStart + (LineOffsets[Y] * 2));
		}
	}

	r.Position.X = minX;
	r.Size.Width = maxX - minX;
	r.Position.Y = minY;
	r.Size.Height = maxY - minY;

	return r;
}
//---------------------------------------------------------------------------
/*!
��������� ���������� ������� ���� � ��������� �����������
@param [__in] land �������� ��� �������
@param [__in] io ������ �� ������ � ����
@param [__in] checkX ���������� X
@param [__in] checkY ���������� Y
@return true � ������ ��������� �����
*/
bool CMulReader::ArtPixelsInXY(const bool &land, CIndexObject &io, const int &checkX, const int &checkY)
{
	CGLTexture *th = io.Texture;

	//if (th == NULL)
	//	return false;

	int width = th->Width;
	int height = th->Height;

	if (checkX < 0 || checkY < 0 || checkX >= width || checkY >= height)
		return false;

	uint flag = *(PDWORD)io.Address;
	ushort h = 44;
	ushort w = 44;
	pushort P = (pushort)io.Address;

	if (land) //raw tile
	{
		IFOR(i, 0, 22)
		{
			int start = 22 - (i + 1);
			int end = (22 - (i + 1)) + (i + 1) * 2;

			if (i == checkY && checkX >= start && checkX < end)
			{
				P += checkX - start;
				return ((*P) != 0);

				/*IFOR(j, start, end)
				{
					if (j == checkX)
						return ((*P) != 0);

					P++;
				}*/
			}

			P += end - start;
		}

		IFOR(i, 0, 22)
		{
			int end = i + (22 - i) * 2;

			if ((i + 22) == checkY && checkX >= i && checkX < end)
			{
				P += checkX - i;
				return ((*P) != 0);

				/*IFOR(j, i, end)
				{
					if ((i + 22) == checkY && j == checkX)
						return ((*P) != 0);

					P++;
				}*/
			}

			P += end - i;
		}
	}
	else //run tile
	{
		pushort ptr = (pushort)(io.Address + 4);

		w = *ptr;
		if (!w || w >= 1024)
		{
			return false;
		}

		ptr++;

		h = *ptr;

		if (!h || (h * 2) > 5120)
		{
			return false;
		}

		ptr++;

		pushort lineOffsets = ptr;
		PVOID dataStart = (PVOID)((uint)ptr + (h * 2));

		int x = 0;
		int y = 0;
		ushort xOffs = 0;
		ushort run = 0;

		ptr = (pushort)((uint)dataStart + (*lineOffsets));

		while (y < h)
		{
			xOffs = *ptr++;
			run = *ptr++;

			if (xOffs + run >= 2048)
				return false;
			else if (xOffs + run != 0)
			{
				x += xOffs;

				if (y == checkY && checkX >= x && checkX < (x + run))
				{
					ptr += checkX - x;
					return ((*ptr) != 0);

					/*IFOR(j, 0, run)
					{
						if (y == checkY && (x + j) == checkX)
							return ((*ptr) != 0);
						ptr++;
					}*/
				}

				ptr += run;
				x += run;
			}
			else
			{
				x = 0;
				y++;
				ptr = (pushort)((uint)dataStart + (lineOffsets[y] * 2));
			}
		}
	}

	return false;
}
//---------------------------------------------------------------------------
/*!
��������� �������� ��������� � ������������� ��������
@param [__in] io ������ �� ������ � �������� ���������
@return ������ �� ������ � ��������
*/
CGLTexture *CMulReader::ReadTexture(CIndexObject &io)
{
	CGLTexture *th = new CGLTexture();
	th->Texture = 0;
	ushort color = io.Color;

	ushort w = 64;
	ushort h = 64;

	if (io.DataSize == 0x2000)
	{
		w = 64;
		h = 64;
	}
	else if (io.DataSize == 0x8000)
	{
		w = 128;
		h = 128;
	}
	else
	{
		delete th;
		return NULL;
	}

	USHORT_LIST pixels(w * h);

	pushort P = (pushort)io.Address;

	IFOR(i, 0, h)
	{
		int pos = i * w;

		IFOR(j, 0, w)
		{
			ushort val = *P++;

			if (color)
				val = g_ColorManager.GetColor16(val, color);

			pixels[pos + j] = (val ? 0x8000 : 0) | val;
		}
	}

	th->Width = w;
	th->Height = h;

	g_GL.BindTexture16(th->Texture, w, h, &pixels[0]);

	return th;
}
//---------------------------------------------------------------------------
/*!
��������� ��������� � ������������� ��������
@param [__in] io ������ �� ������ � ���������
@return ������ �� ������ � ��������
*/
CGLTexture *CMulReader::ReadLight(CIndexObject &io)
{
	CGLTexture *th = new CGLTexture();
	th->Texture = NULL;

	USHORT_LIST pixels(io.Width * io.Height);

	puchar p = (puchar)io.Address;

	IFOR(i, 0, io.Height)
	{
		int pos = i * io.Width;

		IFOR(j, 0, io.Width)
		{
			ushort val = (*p << 10) | (*p << 5) | *p;
			p++;
			pixels[pos + j] = (val ? 0x8000 : 0) | val;
		}
	}

	th->Width = io.Width;
	th->Height = io.Height;

	g_GL.BindTexture16(th->Texture, io.Width, io.Height, &pixels[0]);

	return th;
}
//---------------------------------------------------------------------------
//----------------------------------CUopReader-------------------------------
//---------------------------------------------------------------------------
/*!
�������� ������ �������� �����
@param [__in] io ������ �� ������ � �����
@return ������ �������� ��� NULL
*/
USHORT_LIST CUopReader::GetGumpPixels(CIndexObject &io)
{
	USHORT_LIST result;

	return result;
}
//---------------------------------------------------------------------------
/*!
��������� ���� � ������������� ��������
@param [__in] io ������ �� ������ � �����
@return ������ �� ������ � ��������
*/
CGLTexture *CUopReader::ReadGump(CIndexObject &io)
{
	return NULL;
}
//---------------------------------------------------------------------------
/*!
��������� ���������� ������� ����� � ��������� �����������
@param [__in] io ������ �� ������ � �����
@param [__in] checkX ���������� X
@param [__in] checkY ���������� Y
@return true � ������ ��������� �����
*/
bool CUopReader::GumpPixelsInXY(CIndexObject &io, const int &checkX, const int &checkY)
{
	return false;
}
//---------------------------------------------------------------------------
/*!
��������� ��� � ������������� ��������
@param [__in] ID ������ ����
@param [__in] io ������ �� ������ � ����
@return ������ �� ������ � ��������
*/
CGLTexture *CUopReader::ReadArt(const WORD &id, CIndexObject &io)
{
	return NULL;
}
//---------------------------------------------------------------------------
/*!
��������� ��� � ��������� �������� ����������� ������� ��������
@param [__in] io ������ �� ������ � ����
@param [__out] r ��������� � ���������� �� ������
@return ������ �� ������ � ��������
*/
WISP_GEOMETRY::CRect CUopReader::ReadStaticArtPixelDimension(CIndexObject &io)
{
	WISP_GEOMETRY::CRect r;

	return r;
}
//---------------------------------------------------------------------------
/*!
��������� ���������� ������� ���� � ��������� �����������
@param [__in] land �������� ��� �������
@param [__in] io ������ �� ������ � ����
@param [__in] checkX ���������� X
@param [__in] checkY ���������� Y
@return true � ������ ��������� �����
*/
bool CUopReader::ArtPixelsInXY(const bool &land, CIndexObject &io, const int &checkX, const int &checkY)
{
	return false;
}
//---------------------------------------------------------------------------
/*!
��������� �������� ��������� � ������������� ��������
@param [__in] io ������ �� ������ � �������� ���������
@return ������ �� ������ � ��������
*/
CGLTexture *CUopReader::ReadTexture(CIndexObject &io)
{
	return NULL;
}
//---------------------------------------------------------------------------