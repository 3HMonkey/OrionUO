/****************************************************************************
**
** EffectManager.h
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
//--------------------------------------------------------------------------
#ifndef EffectManagerH
#define EffectManagerH
//--------------------------------------------------------------------------
//!����� ��������� ��������
class TEffectManager : public TBaseQueue
{
public:
	TEffectManager() : TBaseQueue() {}
	virtual ~TEffectManager() {}

	/*!
	�������� ������
	@param [__in] effect ������ �� ������
	@return 
	*/
	void AddEffect(__in TGameEffect *effect);

	/*!
	������� ������
	@param [__in] effect ������ �� ������
	@return 
	*/
	void RemoveEffect(__in TGameEffect *effect);

	/*!
	������� ������ ������
	@param [__in] effect ������ �� ������
	@return 
	*/
	void CreateExplodeEffect(__in TGameEffect *effect);

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
//--------------------------------------------------------------------------
//!������ �� �������� ��������
extern TEffectManager *EffectManager;
//--------------------------------------------------------------------------
#endif