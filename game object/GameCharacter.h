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
#ifndef GameCharacterH
#define GameCharacterH
//--------------------------------------------------------------------------
class TGameCharacter: public TGameObject
{
//private:
protected:
	short m_Hits; //������� �������� ��
	short m_MaxHits; //������������ �������� ��
	short m_Mana; //������� �������� ����
	short m_MaxMana; //������������ �������� ����
	short m_Stam; //������� �������� �������
	short m_MaxStam; //������������ �������� �������
	bool m_Sex; //���
	BYTE m_Race; //�����
	BYTE m_Direction; //�����������
	BYTE m_Notoriety; //���������
	bool m_CanChangeName; //����������� �������� ��� � ������ ����
	BYTE m_AnimationGroup; //������ ��������
	BYTE m_AnimationInterval; //�������� ����� ������
	BYTE m_AnimationFrameCount; //���������� ������
	BYTE m_AnimationRepeatMode; //����� ��������������� ��������
	bool m_AnimationRepeat; //��������� ��������?
	bool m_AnimationDirection; //����������� ������������ ��������
	bool m_AnimationFromServer; //���� �������� ������ � �������
	DWORD m_LastStepSoundTime; //����� ���������� ������������ ����� ��� ������
	DWORD m_TimeToRandomFidget; //����� ��� ��������� ��������� ��������
	DWORD m_CorpseLink; //������ �� ���� (��� �������� �����)
	
	char m_OffsetX; //�������� �������� �� ��� X
	char m_OffsetY; //�������� �������� �� ��� Y
	char m_OffsetZ; //�������� �������� �� ��� Z
	DWORD m_LastStepTime; //����� ���������� ����
	short m_AfterStepDelay; //�������� ����� ���� (��� ����������� ����������� �������� ������)
	BYTE m_StepSoundOffset; //�������� ��� ����� ����

	string m_PaperdollText; //����� ������ � ����������

	bool IsCorrectStep(WORD cx, WORD cy, WORD &x, WORD &y, BYTE &dir);
public:
	TGameCharacter(DWORD serial = 0);
	virtual ~TGameCharacter();
	
	TWalkStack m_WalkStack; //������ �� ������� �����
	
	SETGETEX(short, Hits);
	SETGETEX(short, MaxHits);
	SETGETEX(short, MaxMana);
	SETGETEX(short, MaxStam);
	SETGETEX(short, Mana);
	SETGETEX(short, Stam);
	SETGET(bool, Sex);
	SETGET(BYTE, Race);
	SETGET(BYTE, Direction);
	SETGET(BYTE, Notoriety);
	SETGET(bool, CanChangeName);
	SETGET(short, AfterStepDelay);
	SETGET(BYTE, AnimationInterval);
	SETGET(BYTE, AnimationFrameCount);
	SETGET(BYTE, AnimationRepeatMode);
	SETGET(bool, AnimationRepeat);
	SETGET(bool, AnimationDirection);
	SETGET(bool, AnimationFromServer);
	SETGET(DWORD, LastStepSoundTime);
	SETGET(DWORD, TimeToRandomFidget);
	SETGET(BYTE, StepSoundOffset);
	SETGET(DWORD, CorpseLink);

	SETGETEX(char, OffsetX);
	SETGETEX(char, OffsetY);
	SETGETEX(char, OffsetZ);
	SETGET(DWORD, LastStepTime);

	virtual int Draw(bool &mode, int &drawX, int &drawY, DWORD &ticks);

	void OnGraphicChange(int direction = 0); //�������� ���������� � ���� ���������

	void SetPaperdollText(string val); //������������� �������� ������ ����������
	void SetAnimationGroup(BYTE val); //��������� ������ ��������
	void SetRandomFidgetAnimation(); //��������� ��������� �������� (��� ���������� �������)
	//��������� ��������
	void SetAnimation(BYTE id, BYTE interval = 0, BYTE frameCount = 0, BYTE repeatCount = 0, bool repeat = false, bool frameDirection = false);

	WORD GetMountAnimation(); //�������� ������ �������� ��� ���������� �������� ��������

	TTextTexture m_PaperdollTextTexture; //�������� ������ ����������

	string GetPaperdollText() const {return m_PaperdollText;}
	BYTE GetAnimationGroup(WORD graphic = 0); //�������� ������� ������ ��������
	void GetAnimationGroup(ANIMATION_GROUPS group, BYTE &animation); //��������������� ��������� ��������
	bool Staying() {return m_AnimationGroup == 0xFF && m_WalkStack.Empty();} //���� �������� �� ��������
	bool Walking() {return (m_LastStepTime > (DWORD)(GetTickCount() - m_AfterStepDelay));} //���� �������� ���� (��� ������ ��� �������� �������������)
	void UpdateAnimationInfo(BYTE &dir, bool canChange = false); //�������� �������������� �������� ���������
	bool IsTeleportAction(WORD &x, WORD &y, BYTE &dir);

	//������� �� ���
	bool IsHuman() {return (((Graphic >= 0x0190) && (Graphic <= 0x0193)) || (Graphic == 0x03DB));}
	bool Dead() {return ((Graphic == 0x0192) || (Graphic == 0x0193));} //������ �����
	
	TGameItem *FindLayer(int layer); //����� ������ � ���������� �� ��������� ����
};
//---------------------------------------------------------------------------
#endif