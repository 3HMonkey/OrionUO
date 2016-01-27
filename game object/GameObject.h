/****************************************************************************
**
** GameObject.h
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
#ifndef GameObjectH
#define GameObjectH
//--------------------------------------------------------------------------
class TGameObject : public TRenderWorldObject
{
//private:
protected:
	DWORD m_Container; //�������� ����������, ����������� ������ (0xFFFFFFFF - ������ ����� � ����)
	BYTE m_MapIndex; //����� �������
	WORD m_Count; //����������
	BYTE m_Flags; //����� �� �������
	string m_Name; //���
	bool m_NPC; //��� ��� �������
	bool m_Clicked; //�� ������� ��������
	char m_AnimIndex; //������� ������ ��������
	DWORD m_LastAnimationChangeTime; //����� ���������� ��������� ��������

	TGameEffect *m_Effects; //������ �� ������ �������� ���������
public:
	TGameObject(DWORD serial = 0);
	virtual ~TGameObject();
	
	//�������� ����� � ���������
	void AddText(TTextData *td);

	SETGET(DWORD, Container);
	SETGET(BYTE, MapIndex);
	SETGET(WORD, Count);
	SETGET(BYTE, Flags);
	virtual SETGET(string, Name);
	SETGET(bool, NPC);
	SETGET(bool, Clicked);
	SETGETEX(char, AnimIndex);
	SETGET(DWORD, LastAnimationChangeTime);

	virtual WORD GetMountAnimation() {return Graphic;}

	//���������� ���������
	void DrawEffects(int &drawX, int &drawY, DWORD &ticks);
	void AddEffect(TGameEffect *effect); //�������� ������
	void RemoveEffect(TGameEffect *effect); //������� ������

	//���������� ��������� ������ �������� �������
	void AddObject(TGameObject *obj); //�������� ������ � ������ �������� �������� ����������
	void AddItem(TGameObject *obj); //�������� ������ � ��������� (this - ���������)
	void Reject(TGameObject *obj); //������ ������ �� ����������
	//void MoveToTop(TGameObject *obj); //������ ��������� (� ����� ������)

	void Clear(); //�������� ���������

	//��������� �������� ��������� � ����������� �� ������
	bool Poisoned() {return (m_Flags & 0x04);}
	bool YellowHits() {return (m_Flags & 0x08);}
	bool Locked() {return !(m_Flags & 0x20);}
	bool InWarMode() {return (m_Flags & 0x40);}
	bool Hidden() {return (m_Flags & 0x80);}

	//����������� ���������
	virtual bool IsHuman() {return false;}
	virtual bool IsPlayer() {return false;}

	bool IsGameObject() {return true;}
	bool IsCorpse() {return (Graphic == 0x2006);}

	//����� ������ � ����, � ������� ���������� ���������
	TGameObject *GetTopObject();
};
//---------------------------------------------------------------------------
//������� ��� ���������� ���������
int GetDistance(TGameObject *current, TGameObject *target);
int GetDistance(TGameObject *current, POINT target);
int GetDistance(POINT current, TGameObject *target);
int GetDistance(POINT current, POINT target);
int GetTopObjDistance(TGameObject *current, TGameObject *target);
//---------------------------------------------------------------------------
#endif