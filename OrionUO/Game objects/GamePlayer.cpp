/***********************************************************************************
**
** GamePlayer.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "GamePlayer.h"
#include "GameItem.h"
//----------------------------------------------------------------------------------
CPlayer *g_Player = NULL;
//----------------------------------------------------------------------------------
CPlayer::CPlayer(const uint &serial)
: CGameCharacter(serial), m_Str(0), m_Int(0), m_Dex(0), m_MaxWeight(0),
m_Weight(0), m_Armor(0), m_Gold(0), m_Warmode(false), m_StatsCap(0), m_Followers(0),
m_MaxFollowers(5), m_FireResistance(0), m_ColdResistance(0), m_PoisonResistance(0),
m_EnergyResistance(0), m_Luck(0), m_MinDamage(0), m_MaxDamage(0), m_TithingPoints(0),
m_LockStr(0), m_LockInt(0), m_LockDex(0)
//, m_Race(CRT_HUMAN)
{
	m_Skills = new CSkill[g_SkillsCount];
}
//---------------------------------------------------------------------------
CPlayer::~CPlayer()
{
	if (m_Skills != NULL)
	{
		delete []m_Skills;
		m_Skills = NULL;
	}
}
//---------------------------------------------------------------------------
/*!
���������� ������� �������� ������
@param [__in] index ������ ������
@param [__in] val ����� ��������
@return 
*/
void CPlayer::SetSkillBaseValue(const int &index, const float &val)
{
	if (index < 0 || index >= g_SkillsCount)
		return;

	m_Skills[index].SetBaseValue(val);
}
//---------------------------------------------------------------------------
/*!
���������� �������� ������
@param [__in] index ������ ������
@param [__in] val ����� ��������
@return 
*/
void CPlayer::SetSkillValue(const int &index, const float &val)
{
	if (index < 0 || index >= g_SkillsCount)
		return;

	m_Skills[index].SetValue(val);
}
//---------------------------------------------------------------------------
/*!
���������� ������������ �������� ������
@param [__in] index ������ ������
@param [__in] val ����� ��������
@return 
*/
void CPlayer::SetSkillCap(const int &index, const float &val)
{
	if (index < 0 || index >= g_SkillsCount)
		return;

	m_Skills[index].SetCap(val);
}
//---------------------------------------------------------------------------
/*!
���������� ������ ������
@param [__in] index ������ ������
@param [__in] val ����� ���������
@return 
*/
void CPlayer::SetSkillStatus(const int &index, const uchar &val)
{
	if (index < 0 || index >= g_SkillsCount)
		return;

	m_Skills[index].SetStatus(val);
}
//---------------------------------------------------------------------------
/*!
�������� ������� �������� ������
@param [__in] index ������ ������
@return ������� ��������
*/
float CPlayer::GetSkillBaseValue(const int &index) const
{
	if (index < 0 || index >= g_SkillsCount)
		return 0.0f;

	return m_Skills[index].GetBaseValue();
}
//---------------------------------------------------------------------------
/*!
�������� �������� ������
@param [__in] index ������ ������
@return ������� ��������
*/
float CPlayer::GetSkillValue(const int &index) const
{
	if (index < 0 || index >= g_SkillsCount)
		return 0.0f;

	return m_Skills[index].GetValue();
}
//---------------------------------------------------------------------------
/*!
�������� ������������ �������� ������
@param [__in] index ������ ������
@return ������� ��������
*/
float CPlayer::GetSkillCap(const int &index) const
{
	if (index < 0 || index >= g_SkillsCount)
		return 0.0f;

	return m_Skills[index].GetCap();
}
//---------------------------------------------------------------------------
/*!
�������� ������ ������
@param [__in] index ������ ������
@return ������� ���������
*/
uchar CPlayer::GetSkillStatus(const int &index) const
{
	if (index < 0 || index >= g_SkillsCount)
		return 0;

	return m_Skills[index].GetStatus();
}
//---------------------------------------------------------------------------
/*!
����� ������ � ����� (� ���������)
@return ������ �� ���� ��� NULL
*/
CGameItem *CPlayer::FindBandage()
{
	CGameItem *item = FindLayer(OL_BACKPACK);

	if (item != NULL)
		item = item->FindItem(0x0E21);

	return item;
}
//---------------------------------------------------------------------------