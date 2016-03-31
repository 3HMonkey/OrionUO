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
//!����� �������� �������
class TGameObject : public TRenderStaticObject
{
protected:
	//!�������� ����������, ����������� ������ (0xFFFFFFFF - ������ ����� � ����)
	DWORD m_Container;

	//!����� �������
	BYTE m_MapIndex;

	//!����������
	DWORD m_Count;

	//!����� �� �������
	BYTE m_Flags;

	//!���
	string m_Name;

	//!��� ��� �������
	bool m_NPC;

	//!�� ������� ��������
	bool m_Clicked;

	//!������� ������ ��������
	char m_AnimIndex;

	//!����� ���������� ��������� ��������
	DWORD m_LastAnimationChangeTime;

	//!������ �� ������ �������� ���������
	TGameEffect *m_Effects;

	//!��������� �� �������� �� ������ Object Handles
	TTextureObject m_TextureObjectHalndes;

	/*!
	������� �������� ��� ����� Object Handles
	@param [__in] text ����� �������� �������
	@return 
	*/
	void GenerateObjectHandlesTexture(__in wstring text);

public:
	TGameObject(DWORD serial = 0);
	virtual ~TGameObject();

	SETGET(DWORD, Container);
	SETGET(BYTE, MapIndex);
	SETGET(DWORD, Count);
	SETGET(BYTE, Flags);
	virtual SETGET(string, Name);
	SETGET(bool, NPC);
	SETGET(bool, Clicked);
	SETGETEX(char, AnimIndex);
	SETGET(DWORD, LastAnimationChangeTime);

	/*!
	�������� ����� � ���������
	@param [__in] td ������ �� ������ ������
	@return 
	*/
	void AddText(__in TTextData *td);

	/*!
	���������� �������� ����� Object Handles (������������� ������� ��������, ���� ��� �� ���� �������)
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@return 
	*/
	void DrawObjectHandlesTexture(__in int &x, __in int &y);

	/*!
	�������� ������ ��������
	@return ������ ��������
	*/
	virtual WORD GetMountAnimation();
	
	/*!
	�������, ���������� ��� ��������� ������� ��������
	@param [__in_opt] direction ����������� �������
	@return
	*/
	virtual void OnGraphicChange(int direction = 0) {}

	/*!
	�������� ������������ (��� ����� ������������)
	@param [__in] playerZ ���������� Z ������
	@return ����� �� ���� ����������
	*/
	virtual bool TranparentTest(int &playerZ) { return false; }

	/*!
	���������� ������
	@param [__in] drawX �������� ���������� X
	@param [__in] drawY �������� ���������� Y
	@param [__in] ticks ������ �������
	@return 
	*/
	void DrawEffects(__in int &drawX, __in int &drawY, __in DWORD &ticks);

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
	�������� ������ � ������ �������� �������� ����������
	@param [__in] obj ������ �� ������
	@return 
	*/
	void AddObject(__in TGameObject *obj); 

	/*!
	�������� ������ � ��������� (this - ���������)
	@param [__in] obj ������ �� ������
	@return 
	*/
	void AddItem(__in TGameObject *obj);

	/*!
	������ ������ �� ����������
	@param [__in] obj ������ �� ������
	@return 
	*/
	void Reject(__in TGameObject *obj);

	/*!
	�������� ���������
	@return 
	*/
	void Clear();

	/*!
	�������� �� ������
	@return
	*/
	bool Poisoned() {return (m_Flags & 0x04);}

	/*!
	������ ����� ������ ������� ������
	@return
	*/
	bool YellowHits() {return (m_Flags & 0x08);}

	/*!
	����� �� ����� ������ � ����
	@return
	*/
	bool Locked() {return !(m_Flags & 0x20);}

	/*!
	������ � ������ ���
	@return
	*/
	bool InWarMode() {return (m_Flags & 0x40);}

	/*!
	������ �������
	@return
	*/
	bool Hidden() {return (m_Flags & 0x80);}

	/*!
	�������� �� ����������������� ���������
	@return ���������������� ��� ���
	*/
	virtual bool IsHuman() {return false;}

	/*!
	�������� �� ������ (�������� - ����� �������� �� �����������)
	@return ����� ��� ���
	*/
	virtual bool IsPlayer() {return false;}

	/*!
	������ �� ���
	@return ������ � ������� ������
	*/
	int IsGold();

	/*!
	�������� ������ �������� ��� ���������
	@param [__out] doubleDraw ������� ��������� �������
	@return ������ ��������
	*/
	WORD GetDrawGraphic(__out bool &doubleDraw);

	/*!
	��� ������� ������
	@return 
	*/
	bool IsGameObject() {return true;}

	/*!
	��� ����
	@return
	*/
	bool IsCorpse() {return (m_Graphic == 0x2006);}

	/*!
	����� ������ � ����, � ������� ���������� ���������
	@return ������ �� ������ � ����
	*/
	TGameObject *GetTopObject();
};
//---------------------------------------------------------------------------
#endif