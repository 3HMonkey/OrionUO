/***********************************************************************************
**
** GameObject.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
//----------------------------------------------------------------------------------
#include "RenderStaticObject.h"
#include "../GLEngine/GLEngine.h"
//----------------------------------------------------------------------------------
struct DRAW_FRAME_INFORMATION
{
	int OffsetX;
	int OffsetY;
	int Width;
	int Height;
};
//----------------------------------------------------------------------------------
//!����� �������� �������
class CGameObject : public CRenderStaticObject
{
	//!�������� ����������, ����������� ������ (0xFFFFFFFF - ������ ����� � ����)
	SETGET(uint, Container);
	//!����� �������
	SETGET(uchar, MapIndex);
	//!����������
	SETGET(uint, Count);
	//!����� �� �������
	SETGETE(uchar, Flags, OnChangedFlags);
	//!���
	SETGETE(string, Name, OnChangeName);
	//!��� ��� �������
	SETGET(bool, NPC);
	//!�� ������� ��������
	SETGET(bool, Clicked);
	//!������� ������ ��������
	SETGETEX(char, AnimIndex);
	//!������� You see: � �������
	SETGET(bool, YouSeeJournalPrefix);
	//!����� ���������� ��������� ��������
	SETGET(uint, LastAnimationChangeTime);
	SETGET(wstring, ClilocMessage);

protected:
	//!������ �� ������ �������� ���������
	class CGameEffect *m_Effects;

	//!��������� �� �������� ��� ����� Object Handles
	CGLTexture m_TextureObjectHalndes;

	/*!
	������� �������� ��� ����� Object Handles
	@param [__in] text ����� �������� �������
	@return
	*/
	void GenerateObjectHandlesTexture(wstring text);

public:
	CGameObject(const uint &serial = 0);
	virtual ~CGameObject();

	//!���������� � �� ������� (��� Animation Manager)
	DRAW_FRAME_INFORMATION m_FrameInfo;

	/*!
	�������� ����� � ���������
	@param [__in] td ������ �� ������ ������
	@return
	*/
	virtual void AddText(CTextData *td);

	/*!
	���������� �������� ����� Object Handles (������������� ������� ��������, ���� ��� �� ���� �������)
	@param [__in] mode ����� �����������
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@return
	*/
	void DrawObjectHandlesTexture(const int &x, const int &y);

	void SelectObjectHandlesTexture(const int &x, const int &y);

	/*!
	�������� ������ ��������
	@return ������ ��������
	*/
	virtual ushort GetMountAnimation();

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
	void DrawEffects(int x, int y);

	void UpdateEffects();

	/*!
	�������� ������
	@param [__in] effect ������ �� ������
	@return
	*/
	void AddEffect(class CGameEffect *effect);

	/*!
	������� ������
	@param [__in] effect ������ �� ������
	@return
	*/
	void RemoveEffect(class CGameEffect *effect);

	/*!
	�������� ������ � ������ �������� �������� ����������
	@param [__in] obj ������ �� ������
	@return
	*/
	void AddObject(CGameObject *obj);

	/*!
	�������� ������ � ��������� (this - ���������)
	@param [__in] obj ������ �� ������
	@return
	*/
	void AddItem(CGameObject *obj);

	/*!
	������ ������ �� ����������
	@param [__in] obj ������ �� ������
	@return
	*/
	void Reject(CGameObject *obj);

	/*!
	�������� ���������
	@return
	*/
	void Clear();

	/*!
	��������� �� ������
	@return
	*/
	bool Frozen() { return (m_Flags & 0x01); }

	/*!
	�������� �� ������
	@return
	*/
	bool Poisoned();

	/*!
	����� �� ������
	@return
	*/
	bool Flying();

	/*!
	������ ����� ������ ������� ������
	@return
	*/
	bool YellowHits() { return (m_Flags & 0x08); }

	/*!
	������ ���������� ���������� ��� �����������
	@return
	*/
	bool IgnoreCharacters() { return (m_Flags & 0x10); }

	/*!
	����� �� ����� ������ � ����
	@return
	*/
	bool Locked() { return !(m_Flags & 0x20); }

	/*!
	������ � ������ ���
	@return
	*/
	bool InWarMode() { return (m_Flags & 0x40); }

	/*!
	������ �������
	@return
	*/
	bool Hidden() { return (m_Flags & 0x80); }

	/*!
	�������� �� ����������������� ���������
	@return ���������������� ��� ���
	*/
	virtual bool IsHuman() { return false; }

	/*!
	�������� �� ������ (�������� - ����� �������� �� �����������)
	@return ����� ��� ���
	*/
	virtual bool IsPlayer() { return false; }

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
	ushort GetDrawGraphic(bool &doubleDraw);

	/*!
	��� ������� ������
	@return
	*/
	bool IsGameObject() { return true; }

	/*!
	��� ����
	@return
	*/
	bool IsCorpse() { return (m_Graphic == 0x2006); }

	/*!
	����� ������ � ����, � ������� ���������� ���������
	@return ������ �� ������ � ����
	*/
	CGameObject *GetTopObject();
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
