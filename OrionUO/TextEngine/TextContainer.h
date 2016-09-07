/***********************************************************************************
**
** TextContainer.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef TEXTCONTAINER_H
#define TEXTCONTAINER_H
//----------------------------------------------------------------------------------
#include "TextData.h"
#include "TextData.h"
//----------------------------------------------------------------------------------
//��������� ��� ������
class CTextContainer : public CBaseQueue
{
	SETGET(int, MaxSize);
	SETGET(int, Size);

public:
	CTextContainer(const int &maxSize);
	~CTextContainer();

	//�������� �����
	void Add(CTextData *obj);

	//������� �����
	void Delete(CTextData *obj);

	//�������� ���������
	virtual void Clear();

	//���������� ��������� ���
	void DrawSystemChat(const int &x, const int &y, const int &height);
};
//----------------------------------------------------------------------------------
extern CTextContainer g_SystemChat;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
