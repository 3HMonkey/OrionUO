/****************************************************************************
**
** GameEffect.h
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
#ifndef GameEffectH
#define GameEffectH
//--------------------------------------------------------------------------
//!������� ������
class TGameEffect : public TRenderWorldObject
{
protected:
	//!��� �������
	EFFECT_TYPE m_EffectType;

	//!�������� ����������
	DWORD m_DestSerial;

	//!���������� ���������� �� ��� X
	WORD m_DestX;

	//!���������� ���������� �� ��� Y
	WORD m_DestY;

	//!���������� ���������� �� ��� Z
	char m_DestZ;

	//!��������
	BYTE m_Speed;

	//!����� �����
	DWORD m_Duration;

	//!�������� ����������� �������� ��� ������ �������?
	bool m_FixedDirection;

	//!�������� �� ���������� ����?
	bool m_Explode;

	//!����� ����������� �������
	DWORD m_RenderMode;

	//!������ ��������
	int m_AnimIndex;

	//!�������� �� �������� �������
	int m_Increment;

	//!��������� ����� ��������� ��������
	DWORD m_LastChangeFrameTime;
public:
	TGameEffect();
	virtual ~TGameEffect();

	SETGET(EFFECT_TYPE, EffectType);
	SETGET(DWORD, DestSerial);
	SETGET(WORD, DestX);
	SETGET(WORD, DestY);
	SETGET(char, DestZ);
	SETGET(BYTE, Speed);
	SETGET(DWORD, Duration);
	SETGET(bool, FixedDirection);
	SETGET(bool, Explode);
	SETGET(DWORD, RenderMode);
	
	SETGET(int, AnimIndex);
	SETGET(int, Increment);
	SETGET(DWORD, LastChangeFrameTime);

	/*!
	���������� ������
	@param [__in] mode ����� ���������. true - ���������, false - ����� ��������
	@param [__in] drawX �������� ���������� X �������
	@param [__in] drawY �������� ���������� Y �������
	@param [__in] ticks ������ �������
	@return ��� ������ �������� ���������� ��������� �������
	*/
	virtual int Draw(__in bool &mode, __in int &drawX, __in int &drawY, __in DWORD &ticks);

	/*!
	�������� ������� ������ ��������
	@return ������ ��������
	*/
	WORD GetCurrentGraphic();

	/*!
	��������� ������� ������ ��������
	@return ������ ��������
	*/
	WORD CalculateCurrentGraphic();

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
//--------------------------------------------------------------------------
//������ ����������� ��������
class TGameEffectDrag : public TGameEffect
{
protected:
	//!�������� �� ��� X
	int m_OffsetX;

	//!�������� �� ��� Y
	int m_OffsetY;
public:
	TGameEffectDrag();
	virtual ~TGameEffectDrag();

	SETGET(int, OffsetX);
	SETGET(int, OffsetY);

	/*!
	�������� ������
	@return
	*/
	virtual void Update();
};
//--------------------------------------------------------------------------
//���������� ������
class TGameEffectMoving : public TGameEffectDrag
{
protected:
	//!���� �������� �������
	float m_Angle;

	//!�������� �� ��� Z
	int m_OffsetZ;
public:
	TGameEffectMoving();
	virtual ~TGameEffectMoving();

	SETGET(float, Angle);
	SETGET(int, OffsetZ);

	/*!
	�������� ������
	@return
	*/
	virtual void Update();
};
//---------------------------------------------------------------------------
#endif