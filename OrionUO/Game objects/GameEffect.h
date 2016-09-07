/***********************************************************************************
**
** GameEffect.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GAMEEFFECT_H
#define GAMEEFFECT_H
//----------------------------------------------------------------------------------
#include "../RenderWorldObject.h"
//----------------------------------------------------------------------------------
//!������� ������
class CGameEffect : public CRenderWorldObject
{
	//!��� �������
	SETGET(EFFECT_TYPE, EffectType);
	//!�������� ����������
	SETGET(uint, DestSerial);
	//!���������� ���������� �� ��� X
	SETGET(ushort, DestX);
	//!���������� ���������� �� ��� Y
	SETGET(ushort, DestY);
	//!���������� ���������� �� ��� Z
	SETGET(char, DestZ);
	//!��������
	SETGET(uchar, Speed);
	//!����� �����
	SETGET(uint, Duration);
	//!�������� ����������� �������� ��� ������ �������?
	SETGET(bool, FixedDirection);
	//!�������� �� ���������� ����?
	SETGET(bool, Explode);
	//!����� ����������� �������
	SETGET(uint, RenderMode);

	//!������ ��������
	SETGET(int, AnimIndex);
	//!�������� �� �������� �������
	SETGET(int, Increment);
	//!��������� ����� ��������� ��������
	SETGET(uint, LastChangeFrameTime);

public:
	CGameEffect();
	virtual ~CGameEffect();

	/*!
	���������� ������
	@param [__in] mode ����� ���������. true - ���������, false - ����� ��������
	@param [__in] drawX �������� ���������� X �������
	@param [__in] drawY �������� ���������� Y �������
	@param [__in] ticks ������ �������
	@return ��� ������ �������� ���������� ��������� �������
	*/
	virtual void Draw(const int &x, const int &y);

	/*!
	�������� ������� ������ ��������
	@return ������ ��������
	*/
	ushort GetCurrentGraphic();

	/*!
	��������� ������� ������ ��������
	@return ������ ��������
	*/
	ushort CalculateCurrentGraphic();

	/*!
	���������� ������ �����������
	@return 
	*/
	void ApplyRenderMode();

	/*!
	������ ������ �����������
	@return 
	*/
	void RemoveRenderMode();

	/*!
	��������, ������ �� ���
	@return ������ ��� ���
	*/
	bool IsEffectObject() {return true;}

	/*!
	�������� ������
	@return 
	*/
	virtual void Update() {}
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
