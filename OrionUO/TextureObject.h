/***********************************************************************************
**
** TextureObject.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef TEXTUREOBJECT_H
#define TEXTUREOBJECT_H
//----------------------------------------------------------------------------------
#include "BaseQueue.h"
#include "Globals.h"
//----------------------------------------------------------------------------------
//����� ��� ������ � ��������� ����� ��������
class CTextureAnimationFrame : public CBaseQueueItem
{
	//������ �����
	SETGET(uchar, Frame);
	//�������� ��������
	SETGET(short, Width);
	SETGET(short, Height);
	//���������� ������ �������� ������������ ������ ��������
	SETGET(short, CenterX);
	SETGET(short, CenterY);

public:
	CTextureAnimationFrame(const int &frame);
	virtual ~CTextureAnimationFrame();

	//������ ��������
	GLuint Texture;
};
//----------------------------------------------------------------------------------
//����� ��� ������ � ������������ ��������
class CTextureAnimationDirection : public CBaseQueueItem
{
	//�����������
	SETGET(uchar, Direction);
	//���������� ������
	SETGET(uchar, FrameCount);
	//����� � ������
	SETGET(uint, Address);
	//������ ������ � ������
	SETGET(uint, Size);
	//����� ���������� �������
	SETGET(uint, LastAccessTime);

public:
	CTextureAnimationDirection(int direction);
	virtual ~CTextureAnimationDirection();

	//�������� ������ �� �����
	CTextureAnimationFrame *GetFrame(const uchar &frame);

	//����� ������ �� �����
	CTextureAnimationFrame *FindFrame(const uchar &frame);
};
//----------------------------------------------------------------------------------
//����� ��� ������ � ������� ��������
class CTextureAnimationGroup : public CBaseQueueItem
{
	//������ ������
	SETGET(uchar, Index);

public:
	CTextureAnimationGroup(int index);
	virtual ~CTextureAnimationGroup();

	//�������� ������ �� �����������
	CTextureAnimationDirection *GetDirection(const uchar &direction);
};
//----------------------------------------------------------------------------------
//����� ��� ������ � �������� ������� ��������
class CTextureAnimation : public CBaseQueue
{
public:
	CTextureAnimation();
	virtual ~CTextureAnimation();

	//�������� ������ �� ������
	CTextureAnimationGroup *GetGroup(const uchar &index);
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
