/***********************************************************************************
**
** Target.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef TARGET_H
#define TARGET_H
//----------------------------------------------------------------------------------
#include "Multi.h"
#include "Game objects/MultiObject.h"
#include "Wisp/WispDataStream.h"
//----------------------------------------------------------------------------------
//����� ��� ������ � ��������
class CTarget
{
	//��� ������� �������
	SETGET(uchar, Type);
	//��� �������
	SETGET(uchar, CursorType);
	//������ �� �������
	SETGET(ushort, MultiGraphic);

private:
	//�������� �������, � �������� �������� ������
	uint m_CursorID;

	//���� ��������� �������
	bool m_Targeting;

	//������� � ��������� ������ �������
	uchar m_Data[19];
	uchar m_LastData[19];

	//������ �������� ������ �� �������
	CMulti *m_Multi;

	//�������� ������-������
	void AddMultiObject(CMultiObject *obj);

public:
	CTarget();
	~CTarget() {}

	//���������� ������ �������
	void SetData(WISP_DATASTREAM::CDataReader &reader);

	//���������� ������ ������-�������
	void SetMultiData(WISP_DATASTREAM::CDataReader &reader);

	bool IsTargeting() const { return m_Targeting; }

	//�������� ������
	void Reset();

	//������� ������ �� ������
	void SendTargetObject(const uint &Serial);

	//������� ������ �� ����
	void SendTargetTile(const ushort &tileID, const short &x, const short &Y, char z);

	//������� ������ �������
	void SendCancelTarget();

	//������� ������ �� ��������� ����
	void SendLastTarget();

	//������� ������
	void SendTarget();

	//��������� ������-������
	void LoadMulti(const int &x, const int &y, const char &z);

	//��������� ������-������
	void UnloadMulti();

	//�������� ������ ������ � �����������
	CMulti *GetMultiAtXY(const short &x, const short &y);
};
//----------------------------------------------------------------------------------
extern CTarget g_Target;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
