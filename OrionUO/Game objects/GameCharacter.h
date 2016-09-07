/***********************************************************************************
**
** GameCharacter.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H
//----------------------------------------------------------------------------------
#include "GameObject.h"
#include "../Walker/WalkStack.h"
//----------------------------------------------------------------------------------
//!������� ��������
class CGameCharacter: public CGameObject
{
	SETGETEX(short, Hits);
	SETGETEX(short, MaxHits);
	SETGETEX(short, MaxMana);
	SETGETEX(short, MaxStam);
	SETGETEX(short, Mana);
	SETGETEX(short, Stam);
	SETGET(bool, Sex);
	SETGET(uchar, Race);
	SETGET(uchar, Direction);
	SETGET(uchar, Notoriety);
	SETGET(bool, CanChangeName);
	SETGET(uchar, AnimationInterval);
	SETGET(uchar, AnimationFrameCount);
	SETGET(uchar, AnimationRepeatMode);
	SETGET(uchar, AnimationGroup);
	SETGET(bool, AnimationRepeat);
	SETGET(bool, AnimationDirection);
	SETGET(bool, AnimationFromServer);
	SETGET(uint, LastStepSoundTime);
	SETGET(uint, TimeToRandomFidget);
	SETGET(uchar, StepSoundOffset);

	SETGETEX(int, OffsetX);
	SETGETEX(int, OffsetY);
	SETGETEX(int, OffsetZ);
	SETGET(uint, LastStepTime);
	SETGET(string, PaperdollText);

protected:
	/*!
	��������, ��� �� ��� ��� �������� (���������� �������� �� 1 ���� �� ����������� �������� ��� ���)
	@param [__inout] cx ������� ���������� X
	@param [__inout] cy ������� ���������� Y
	@param [__in] x ����� ���������� X
	@param [__in] y ����� ���������� Y
	@param [__in] dir ����������� ���������
	@return ��������� ���������� ���/��������
	*/
	bool IsCorrectStep(short &cx, short &cy, short &x, short &y, const uchar &dir);

	/*!
	��������������� ��������� �������� ����� ��������
	@param [__in] graphic ������ ��������
	@param [__in] group ������ ��������
	@param [__inout] animation ������ �������� � ������
	@return 
	*/
	void CorrectAnimationGroup(const ushort &graphic, const ANIMATION_GROUPS &group, uchar &animation);

public:
	CGameCharacter(const uint &serial = 0);
	virtual ~CGameCharacter();

	//������ �� ��������� ��� ������ �����
	CTextContainer *m_DamageTextControl;

	//!������ �� ������� �����
	CWalkStack m_WalkStack;

	/*!
	����� �� ��������
	@return ������ ������� �� �������, �� ������� �� ���������
	*/
	int IsSitting();

	virtual void Draw(const int &x, const int &y);
	virtual void Select(const int &x, const int &y);

	/*!
	�������� ���������� � ���� ���������, ���������� ������
	@param [__in_opt] direction ����������� ���������
	@return 
	*/
	void OnGraphicChange(int direction = 0);

	/*!
	��������� ������ ��������
	@param [__in] val ����� �������� ������ ��������
	@return 
	*/
	void ResetAnimationGroup(const uchar &val);

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
	void SetAnimation(const uchar &id, const uchar &interval = 0, const uchar &frameCount = 0, const uchar &repeatCount = 0, const bool &repeat = false, const bool &frameDirection = false);

	/*!
	�������� ������ �������� ��� ���������� �������� ��������
	@return ������ �������� ���������
	*/
	ushort GetMountAnimation();

	/*!
	�������� ������� ������ ��������
	@param [__in_opt] graphic ������ �������� ���������
	@return ������ ������ ��������
	*/
	uchar GetAnimationGroup(ushort graphic = 0);

	/*!
	��������������� ��������� ��������
	@param [__in] group ������ ��������
	@param [__inout] animation ������ ������ ��������
	@return 
	*/
	void GetAnimationGroup(const ANIMATION_GROUPS &group, uchar &animation);

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
	bool TestStepNoChangeDirection(const uchar &group);

	/*!
	���� �������� ���� (��� ������ ��� �������� �������������)
	@return true - � ��������, false - ���
	*/
	bool Walking() { return (m_LastStepTime > (uint)(g_Ticks - WALKING_DELAY));	}

	/*!
	�� ����������� �������
	@param [__inout] dir �� ����������� ��������
	@param [__in] canChange ����� �� �������� ��������� ����� ������ ��� ���
	@return 
	*/
	void UpdateAnimationInfo(uchar &dir, const bool &canChange = false);

	/*!
	�������� ��������� ���������, �������� �� ���
	@param [__in] x ����� ���������� X
	@param [__in] y ����� ���������� Y
	@param [__in] dir ����� ����������� ���������
	@return true - ��������, false - ���
	*/
	bool IsTeleportAction(short &x, short &y, const uchar &dir);

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
	class CGameItem *FindLayer(const int &layer);

	virtual CGameCharacter *GameCharacterPtr() { return this; }
 };
 //----------------------------------------------------------------------------------
#endif
 //----------------------------------------------------------------------------------
