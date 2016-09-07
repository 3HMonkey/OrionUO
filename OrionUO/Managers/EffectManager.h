/***********************************************************************************
**
** EffectManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef EFFECTMANAGER_H
#define EFFECTMANAGER_H
//----------------------------------------------------------------------------------
#include "../Game objects/GameEffect.h"
//----------------------------------------------------------------------------------
//!����� ��������� ��������
class CEffectManager : public CBaseQueue
{
public:
	CEffectManager();
	virtual ~CEffectManager() {}

	/*!
	�������� ������
	@param [__in] effect ������ �� ������
	@return 
	*/
	void AddEffect(CGameEffect *effect);

	/*!
	������� ������
	@param [__in] effect ������ �� ������
	@return 
	*/
	void RemoveEffect(CGameEffect *effect);

	/*!
	������� ������ ������
	@param [__in] effect ������ �� ������
	@return 
	*/
	void CreateExplodeEffect(CGameEffect *effect);

	/*!
	���������� ��������
	@return 
	*/
	void UpdateEffects();

	/*!
	�������� ��������, �������� �� ������� ������
	@return 
	*/
	void RemoveRangedEffects();
};
//----------------------------------------------------------------------------------
//!������ �� �������� ��������
extern CEffectManager g_EffectManager;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
