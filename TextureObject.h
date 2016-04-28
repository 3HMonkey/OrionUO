/****************************************************************************
**
** TextureObject.h
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
#ifndef TextureObjectH
#define TextureObjectH
//---------------------------------------------------------------------------
//���������/���������� ���������� ������ � �������� (������� �������� ��������� � ����� ���������� ����������� ������ ��� ��������)
#define UO_ENABLE_TEXTURE_DATA_SAVING 0
//---------------------------------------------------------------------------
//����� ��� ������ � ���������
class TTextureObject
{
protected:
	//�������� ��������
	int m_Width;
	int m_Height;
public:
	TTextureObject();
	virtual ~TTextureObject();

	SETGET(int, Width);
	SETGET(int, Height);

	//������ ��������
	GLuint Texture;

#if UO_ENABLE_TEXTURE_DATA_SAVING == 1
	//������ �������� (0/1)
	PBYTE Data;
#endif
};
//---------------------------------------------------------------------------
//����� ��� ������ � ��������� ����� ������������
class TCircleOfTransparencyTexture : public TTextureObject
{
protected:
	//������ �����
	int m_Radius;

	//���������� ��������� �����
	int m_X;
	int m_Y;
public:
	TCircleOfTransparencyTexture();
	virtual ~TCircleOfTransparencyTexture();
	
	SETGET(int, Radius);
	SETGET(int, X);
	SETGET(int, Y);

	//������� ��������
	bool Create(int radius);

	//���������� ��������
	void Draw(int x, int y);

	//���������� ��������
	void Redraw();

	//������ ��������
	PBYTE PixelData;
};
//---------------------------------------------------------------------------
//����� ��� ������ � ��������� ����� ��������
class TTextureAnimationFrame : public TBaseQueueItem
{
private:
	//������ �����
	BYTE m_Frame;

	//�������� ��������
	short m_Width;
	short m_Height;

	//���������� ������ �������� ������������ ������ ��������
	short m_CenterX;
	short m_CenterY;
public:
	TTextureAnimationFrame(const int &frame);
	virtual ~TTextureAnimationFrame();

	SETGET(BYTE, Frame);
	SETGET(short, Width);
	SETGET(short, Height);
	SETGET(short, CenterX);
	SETGET(short, CenterY);

	//������ ��������
	GLuint Texture;
};
//---------------------------------------------------------------------------
//����� ��� ������ � ������������ ��������
class TTextureAnimationDirection : public TBaseQueueItem
{
private:
	//�����������
	BYTE m_Direction;

	//���������� ������
	BYTE m_FrameCount;

	//����� � ������
	DWORD m_Address;

	//����� ���������� �������
	DWORD m_LastAccessTime;
public:
	TTextureAnimationDirection(int direction);
	virtual ~TTextureAnimationDirection();

	SETGET(BYTE, Direction);
	SETGET(BYTE, FrameCount);
	SETGET(DWORD, Address);
	SETGET(DWORD, LastAccessTime);

	//�������� ������ �� �����
	TTextureAnimationFrame *GetFrame(const BYTE &frame);

	//����� ������ �� �����
	TTextureAnimationFrame *FindFrame(const BYTE &frame);
};
//---------------------------------------------------------------------------
//����� ��� ������ � ������� ��������
class TTextureAnimationGroup : public TBaseQueueItem
{
private:
	//������ ������
	BYTE m_Index;
public:
	TTextureAnimationGroup(int index);
	virtual ~TTextureAnimationGroup();

	SETGET(BYTE, Index);

	//�������� ������ �� �����������
	TTextureAnimationDirection *GetDirection(const BYTE &direction);
};
//---------------------------------------------------------------------------
//����� ��� ������ � �������� ������� ��������
class TTextureAnimation : public TBaseQueue
{
private:
public:
	TTextureAnimation();
	virtual ~TTextureAnimation();

	//�������� ������ �� ������
	TTextureAnimationGroup *GetGroup(const BYTE &index);
};
//---------------------------------------------------------------------------
//��������� ������ ��� �������� ���������� � ���-������
struct WEB_LINK_RECT
{
	//������ ������
	WORD LinkID;

	//������ ������ ������������ ��������� ��������� ������
	int StartX;
	int StartY;

	//����� ������ ������������ ��������� ��������� ������
	int EndX;
	int EndY;
};
//---------------------------------------------------------------------------
//����� ��� ������ � ���������� ������
class TTextTexture
{
private:
	//��������
	int m_Width;
	int m_Height;

	//���������� �����
	int m_Lines;
public:
	TTextTexture();
	virtual ~TTextTexture();

	//������ �������� (0/1)
	PBYTE Data;

	SETGET(int, Width);
	SETGET(int, Height);
	SETGETEX(int, Lines);

	//�������� ������
	GLuint Texture;

	//������� �� ��������
	bool Empty() {return (Texture == 0);}

	//�������������
	void Init();

	//������� ��������
	void Clear();

	//���������� ��������
	void Draw(const int &x, const int &y);

	//�������� �� ������� �������� ��� ������
	bool UnderMouse(int x, int y);

	//������� ���-������
	virtual void ClearWebLink() {}

	//����������� ���-������
	virtual void AddWebLink(WEB_LINK_RECT &wl) {}

	//�������� ���-������ ��� ������
	virtual WORD WebLinkUnderMouse(int x, int y) {return 0;}
};
//---------------------------------------------------------------------------
//����� ��� ������ HTML ���������� ������
class THTMLTextTexture : public TTextTexture
{
private:
public:
	THTMLTextTexture();
	virtual ~THTMLTextTexture();

	//������ ������
	std::deque<WEB_LINK_RECT> WebLinkRect;

	//������� ���-������
	void ClearWebLink() {WebLinkRect.clear();}

	//����������� ���-������
	void AddWebLink(WEB_LINK_RECT &wl) {WebLinkRect.push_back(wl);}

	//�������� ���-������ ��� ������
	WORD WebLinkUnderMouse(int x, int y);
};
//---------------------------------------------------------------------------
extern TCircleOfTransparencyTexture g_CircleOfTransparency;
//---------------------------------------------------------------------------
#endif