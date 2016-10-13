/***********************************************************************************
**
** GLTextureCircleOfTransparency.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GLTEXTURECIRCLEOFTRANSPARENCY_H
#define GLTEXTURECIRCLEOFTRANSPARENCY_H
//----------------------------------------------------------------------------------
#include "GLTexture.h"
//----------------------------------------------------------------------------------
class CGLTextureCircleOfTransparency : public CGLTexture
{
	SETGET(int, Radius);
	SETGET(int, X);
	SETGET(int, Y);

public:
	CGLTextureCircleOfTransparency();
	virtual ~CGLTextureCircleOfTransparency();

	//������� ��������
	static void CreatePixels(const int &radius, int &width, int &height, UINT_LIST &pixels);

	//������� ��������
	bool Create(int radius);

	//���������� ��������
	virtual void Draw(const int &x, const int &y, const bool &checktrans = false);

	//���������� ��������
	void Redraw();

#if UO_ENABLE_TEXTURE_DATA_SAVING == 0
	vector<ushort> PixelsData;
#endif
};
//----------------------------------------------------------------------------------
extern CGLTextureCircleOfTransparency g_CircleOfTransparency;
//----------------------------------------------------------------------------------
#endif
