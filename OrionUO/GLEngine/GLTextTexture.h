/***********************************************************************************
**
** GLTextTexture.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GLTEXTTEXTURE_H
#define GLTEXTTEXTURE_H
//----------------------------------------------------------------------------------
#include "GLTexture.h"
//----------------------------------------------------------------------------------
//��������� ������ ��� �������� ���������� � ���-������
struct WEB_LINK_RECT
{
	//������ ������
	ushort LinkID;

	//������ ������ ������������ ��������� ��������� ������
	int StartX;
	int StartY;

	//����� ������ ������������ ��������� ��������� ������
	int EndX;
	int EndY;
};
//----------------------------------------------------------------------------------
class CGLTextTexture : public CGLTexture
{
	SETGETEX(int, LinesCount);

public:
	CGLTextTexture();
	virtual ~CGLTextTexture();

	//���� �� ���� ��������� � �������-���������
#if UO_ENABLE_TEXTURE_DATA_SAVING == 0
	vector<ushort> PixelsData;
#endif

	bool Empty() { return (Texture == 0); }

	virtual void Clear();

	//���������� ��������
	virtual void Draw(const int &x, const int &y, const bool &checktrans = false);

	//�������� �� ������� �������� ��� ������
	bool UnderMouse(int x, int y);

	//������� ���-������
	virtual void ClearWebLink() {}

	//����������� ���-������
	virtual void AddWebLink(WEB_LINK_RECT &wl) {}

	//�������� ���-������ ��� ������
	virtual ushort WebLinkUnderMouse(int x, int y) { return 0; }
};
//----------------------------------------------------------------------------------
#endif