/***********************************************************************************
**
** GamePlayer.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H
//----------------------------------------------------------------------------------
#include "GameCharacter.h"
#include "../Skills.h"
//----------------------------------------------------------------------------------
//!����� ������
class CPlayer: public CGameCharacter
{
	SETGET(short, Str);
	SETGET(short, Int);
	SETGET(short, Dex);
	SETGET(uchar, LockStr);
	SETGET(uchar, LockInt);
	SETGET(uchar, LockDex);
	SETGET(ushort, MaxWeight);
	SETGET(ushort, Weight);
	SETGET(short, Armor);
	SETGET(uint, Gold);
	SETGET(bool, Warmode);
	SETGET(WORD, StatsCap);
	SETGET(uchar, Followers);
	SETGET(uchar, MaxFollowers);
	SETGET(short, FireResistance);
	SETGET(short, ColdResistance);
	SETGET(short, PoisonResistance);
	SETGET(short, EnergyResistance);
	SETGET(short, Luck);
	SETGET(short, MinDamage);
	SETGET(short, MaxDamage);
	SETGET(uint, TithingPoints);
	//SETGET(CHARACTER_RACE_TYPE, Race);

	//!��������� �� ������ ������
	CSkill *m_Skills;

public:
	CPlayer(const uint &serial);
	virtual ~CPlayer();

	/*!
	���������� ������� �������� ������
	@param [__in] index ������ ������
	@param [__in] val ����� ��������
	@return 
	*/
	void SetSkillBaseValue(const int &index, const float &val);

	/*!
	���������� �������� ������
	@param [__in] index ������ ������
	@param [__in] val ����� ��������
	@return 
	*/
	void SetSkillValue(const int &index, const float &val);

	/*!
	���������� ������������ �������� ������
	@param [__in] index ������ ������
	@param [__in] val ����� ��������
	@return 
	*/
	void SetSkillCap(const int &index, const float &val);

	/*!
	���������� ������ ������
	@param [__in] index ������ ������
	@param [__in] val ����� ���������
	@return 
	*/
	void SetSkillStatus(const int &index, const uchar &val);

	/*!
	�������� ������� �������� ������
	@param [__in] index ������ ������
	@return ������� ��������
	*/
	float GetSkillBaseValue(const int &index) const;

	/*!
	�������� �������� ������
	@param [__in] index ������ ������
	@return ������� ��������
	*/
	float GetSkillValue(const int &index) const;

	/*!
	�������� ������������ �������� ������
	@param [__in] index ������ ������
	@return ������� ��������
	*/
	float GetSkillCap(const int &index) const;

	/*!
	�������� ������ ������
	@param [__in] index ������ ������
	@return ������� ���������
	*/
	uchar GetSkillStatus(const int &index) const;

	/*!
	����� ������ � ����� (� ���������)
	@return ������ �� ���� ��� NULL
	*/
	class CGameItem *FindBandage();

	/*!
	�������� �� ������ (�������� - ����� �������� �� �����������)
	@return ����� ��� ���
	*/
	bool IsPlayer() {return true;}
};
//----------------------------------------------------------------------------------
//!������ �� ������
extern CPlayer *g_Player;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
