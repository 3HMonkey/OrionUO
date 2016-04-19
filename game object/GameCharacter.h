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
//!������� ��������
class TGameCharacter: public TGameObject
{
protected:
	//!������� �������� ��
	short m_Hits;

	//!������������ �������� ��
	short m_MaxHits;

	//!������� �������� ����
	short m_Mana;

	//!������������ �������� ����
	short m_MaxMana;

	//!������� �������� �������
	short m_Stam;

	//!������������ �������� �������
	short m_MaxStam;

	//!���
	bool m_Sex;

	//!�����
	BYTE m_Race;

	//!�����������
	BYTE m_Direction;

	//!���������
	BYTE m_Notoriety;

	//!����������� �������� ��� � ������ ����
	bool m_CanChangeName;

	//!������ ��������
	BYTE m_AnimationGroup;

	//!�������� ����� ������
	BYTE m_AnimationInterval;

	//!���������� ������
	BYTE m_AnimationFrameCount;

	//!����� ��������������� ��������
	BYTE m_AnimationRepeatMode;

	//!��������� ��������?
	bool m_AnimationRepeat;

	//!����������� ������������ ��������
	bool m_AnimationDirection;

	//!���� �������� ������ � �������
	bool m_AnimationFromServer;

	//!����� ���������� ������������ ����� ��� ������
	DWORD m_LastStepSoundTime;

	//!����� ��� ��������� ��������� ��������
	DWORD m_TimeToRandomFidget;

	//!�������� �������� �� ��� X
	int m_OffsetX;

	//!�������� �������� �� ��� Y
	int m_OffsetY;

	//!�������� �������� �� ��� Z
	int m_OffsetZ;

	//!����� ���������� ����
	DWORD m_LastStepTime;

	//!�������� ����� ���� (��� ����������� ����������� �������� ������)
	short m_AfterStepDelay;

	//!�������� ��� ����� ����
	BYTE m_StepSoundOffset;
	
	/*!
	��������, ��� �� ��� ��� �������� (���������� �������� �� 1 ���� �� ����������� �������� ��� ���)
	@param [__inout] cx ������� ���������� X
	@param [__inout] cy ������� ���������� Y
	@param [__in] x ����� ���������� X
	@param [__in] y ����� ���������� Y
	@param [__in] dir ����������� ���������
	@return ��������� ���������� ���/��������
	*/
	bool IsCorrectStep(__inout WORD &cx, __inout WORD &cy, __in WORD &x, __in WORD &y, __in BYTE &dir);

	/*!
	��������������� ��������� �������� ����� ��������
	@param [__in] graphic ������ ��������
	@param [__in] group ������ ��������
	@param [__inout] animation ������ �������� � ������
	@return 
	*/
	void CorrectAnimationGroup(__in WORD &graphic, __in ANIMATION_GROUPS &group, __inout BYTE &animation);

public:
	TGameCharacter(DWORD serial = 0);
	virtual ~TGameCharacter();

	//������ �� ��������� ��� ������ �����
	TTextContainer *m_DamageTextControl;

	//!������ �� ������� �����
	TWalkStack m_WalkStack;

	//!�������� ������ ����������
	TTextTexture m_PaperdollTextTexture;

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

	SETGETEX(int, OffsetX);
	SETGETEX(int, OffsetY);
	SETGETEX(int, OffsetZ);
	SETGET(DWORD, LastStepTime);

	/*!
	����� �� ��������
	@return ������ ������� �� �������, �� ������� �� ���������
	*/
	int IsSitting();

	/*!
	���������� ���������
	@param [__in] mode ����� ���������. true - ���������, false - ����� ��������
	@param [__in] drawX �������� ���������� X �������
	@param [__in] drawY �������� ���������� Y �������
	@param [__in] ticks ������ �������
	@return ��� ������ �������� ���������� ��������� �������
	*/
	virtual int Draw(__in bool &mode, __out int &drawX, __in int &drawY, __in DWORD &ticks);

	/*!
	�������� ���������� � ���� ���������, ���������� ������
	@param [__in_opt] direction ����������� ���������
	@return 
	*/
	void OnGraphicChange(__in_opt int direction = 0);

	/*!
	������������� �������� ������ ����������
	@param [__in] val ����� ����������
	@return 
	*/
	void GeneratePaperdollText(__in string val);

	/*!
	��������� ������ ��������
	@param [__in] val ����� �������� ������ ��������
	@return 
	*/
	void SetAnimationGroup(__in BYTE val);

	/*!
	��������� ��������� �������� (��� ���������� �������)
	@return 
	*/
	void SetRandomFidgetAnimation();

	/*!
	��������� �������� �� �������
	@param [__in] id ������ �������
	@param [__in_opt] interval �������� ����� �������
	@param [__in_opt] frameCount ���������� ������ ��������
	@param [__in_opt] repeatCount ���������� �������� ��������
	@param [__in_opt] repeat ��������� ��� ���
	@param [__out_opt] frameDirection ����������� ��������� ������ (������/�����)
	@return 
	*/
	void SetAnimation(__in BYTE id, __in_opt BYTE interval = 0, __in_opt BYTE frameCount = 0, __in_opt BYTE repeatCount = 0, __in_opt bool repeat = false, __out_opt bool frameDirection = false);

	/*!
	�������� ������ �������� ��� ���������� �������� ��������
	@return ������ �������� ���������
	*/
	WORD GetMountAnimation();

	/*!
	�������� ������� ������ ��������
	@param [__in_opt] graphic ������ �������� ���������
	@return ������ ������ ��������
	*/
	BYTE GetAnimationGroup(__in_opt WORD graphic = 0);

	/*!
	��������������� ��������� ��������
	@param [__in] group ������ ��������
	@param [__inout] animation ������ ������ ��������
	@return 
	*/
	void GetAnimationGroup(__in ANIMATION_GROUPS group, __inout BYTE &animation);

	/*!
	���������, ���� �������� �� ��������
	@return true - �����, false - � ��������
	*/
	bool Staying() { return m_AnimationGroup == 0xFF && m_WalkStack.Empty(); }

	/*!
	�������� �� ����������� ��������� ����������� ��������� ��� �������� � ������� ���������
	@param [__in] group ������ ������ ��������
	@return ����� �������� ����������� ��� ���
	*/
	bool TestStepNoChangeDirection(__in BYTE group);

	/*!
	���� �������� ���� (��� ������ ��� �������� �������������)
	@return true - � ��������, false - ���
	*/
	bool Walking() {
		return (m_LastStepTime > (DWORD)(GetTickCount() - m_AfterStepDelay));
	}

	/*!
	�� ����������� �������
	@param [__inout] dir �� ����������� ��������
	@param [__in] canChange ����� �� �������� ��������� ����� ������ ��� ���
	@return 
	*/
	void UpdateAnimationInfo(__inout BYTE &dir, __in bool canChange = false);

	/*!
	�������� ��������� ���������, �������� �� ���
	@param [__in] x ����� ���������� X
	@param [__in] y ����� ���������� Y
	@param [__in] dir ����� ����������� ���������
	@return true - ��������, false - ���
	*/
	bool IsTeleportAction(__in WORD &x, __in WORD &y, __in BYTE &dir);

	/*!
	�������� �� ����������������� ���������
	@return ���������������� ��� ���
	*/
	bool IsHuman() { return (((m_Graphic >= 0x0190) && (m_Graphic <= 0x0193)) || (m_Graphic == 0x03DB) || (m_Graphic == 0x03DF) || (m_Graphic == 0x03E2)); }

	/*!
	��� ��� ����� ������
	@return ����� ��� ���
	*/
	bool Dead() { return ((m_Graphic == 0x0192) || (m_Graphic == 0x0193)); }

	/*!
	����� ������ �� ��������� ����
	@param [__in] layer ����� ����
	@return ������ �� ��������� ������ ��� NULL
	*/
	TGameItem *FindLayer(__in int layer);
 };
//---------------------------------------------------------------------------
#endif