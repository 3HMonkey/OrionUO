/****************************************************************************
**
** AnimationManager.h
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
#ifndef AnimationManagerH
#define AnimationManagerH
//---------------------------------------------------------------------------
struct FRAME_OUTPUT_INFO
{
	int StartX;
	int StartY;
	int EndX;
	int EndY;
};
//---------------------------------------------------------------------------
struct ANIMATION_DIMENSIONS
{
	int Width;
	int Height;
	int CenterX;
	int CenterY;
};
//---------------------------------------------------------------------------
//!��������� � ����������� � ����
struct SHADOW_DATA
{
	//!������ ��������
	GLuint Texture;

	//!�������� ���������� �������
	int DrawX;
	int DrawY;

	//!�������� Z-buffer'�
	int ZBuffer;

	//!�������� �����������
	int Width;
	int Height;

	//!������������ �������� ��� ���
	bool Mirror;
};
//---------------------------------------------------------------------------
//!����� ��������� ��������
class TAnimationManager
{
private:
	//!������ ������ � ������
	DWORD m_AddressIdx[6];
	DWORD m_AddressMul[6];
	DWORD m_SizeIdx[6];

	//!���� �������� �����
	WORD m_Color;

	const float UPPER_BODY_RATIO = 0.35f;
	const float MID_BODY_RATIO = 0.60f;
	const float LOWER_BODY_RATIO = 0.94f;

	//!������ �������� ���������.
	int m_CharacterFrameHeight;

	//!������ �������� ��������� ( �������� ���������� )
	int m_CharacterFrameStartY;

	//!������ ����� � �������� ��������� ( ������-���� )
	int m_StartCharacterWaistY;

	//!������ ����� � �������� ��������� ( ������-���� )
	int m_StartCharacterKneesY;

	//!������ ���� � �������� ��������� ( ������-���� )
	int m_StartCharacterFeetY;

	//!������ �������� �������� �����
	int m_AnimGroup;

	//!����������� �������� �����
	BYTE m_Direction;

	//!������� ���� �����
	int m_Sitting;

	//!������ �����
	SHADOW_DATA m_ShadowList[MAX_SHADOWS_COUNT];

	//!���������� �����
	int m_ShadowCount;

	//!������������� ������ ����� ��� ����������� ������� ���������� ��� ���� ����������� ���������
	static const int USED_LAYER_COUNT = 19;
	static int m_UsedLayers[8][USED_LAYER_COUNT];

	//!������ ��������
	TIndexAnimation m_DataIndex[MAX_ANIMATIONS_DATA_INDEX_COUNT];

	//!������ ����� ��� ������
	WORD m_CorpseReplaces[MAX_ANIMATIONS_DATA_INDEX_COUNT];

	//!������ ������������ ��������
	TLinkedList *m_UsedAnimList;

	//���������� ���� � ������
	void AddShadow(GLuint texture, int drawX, int drawY, int zBuffer, int width, int height, bool mirror);

	//�������� �������� �������� � ��������� �����������
	bool TestImagePixels(TTextureAnimationDirection *direction, BYTE &frame, WORD &id, int &checkX, int &checkY);
	bool TestPixels(TGameObject *obj, int x, int y, bool &mirror, BYTE &frameIndex, WORD id = 0x0000);

	//������������� ����������� �������� ���������, �������� ����. �� ��� �� �����
	void FixSittingDirection(BYTE &layerDirection, bool &mirror, int &x, int &y);

	//���������� ������� ���������
	void Draw(TGameObject *obj, int x, int y, bool &mirror, BYTE &frameIndex, int id = 0);

	void DrawIntoFrameBuffer(__in TGameCharacter *obj, __in int x, __in int y);

	//!������ ���� ������ ������ �� ����, ��������� ����������� ����-����� ����.
	void DrawEquippedLayers(TGameCharacter* obj, int drawX, int drawY, bool mirror, BYTE layerDir, BYTE animIndex, int lightOffset);

	//!���������-�� ������ ���� ��� �����
	bool IsUnderRobe(int layer);

	bool m_Transform;

public:
	TAnimationManager();
	~TAnimationManager();

	SETGET(WORD, Color);
	SETGET(int, AnimGroup);
	SETGET(BYTE, Direction);
	SETGET(int, ShadowCount);

	/*!
	������������� �������
	@param [__in] idx ������ �����
	@param [__in] AddressIdx ����� ����� � �������� �������
	@param [__in] AddressMul ����� ����� � �������
	@param [__in] SizeIdx ������ ����� � �������� �������
	@return 
	*/
	void Init( __in int idx, __in DWORD AddressIdx, __in DWORD AddressMul, __in DWORD SizeIdx)
	{
		m_AddressIdx[idx] = AddressIdx;
		m_AddressMul[idx] = AddressMul;
		m_SizeIdx[idx] = SizeIdx;
	}

	/*!
	�������� ����� ���������� �������� �������� ��������
	@param [__in] verdata ������ �� ����� � ������ ����� ������ (verdata.mul)
	@return
	*/
	void InitIndexReplaces(__in PDWORD verdata);

	/*!
	�������� ������
	@param [__in] verdata ������ �� ����� � ������ ����� ������ (verdata.mul)
	@return 
	*/
	void Load(__in PDWORD verdata);

	/*!
	��������� ������ �� ��������� �����
	@param [__in] obj ������� ������
	@param [__inout] frameIndex ������ �����
	@param [__in_opt] id ������ ��������
	@return ������ �� ���� ��������
	*/
	TTextureAnimationFrame *GetFrame(__in TGameObject *obj, __inout BYTE &frameIndex, __in_opt WORD id = 0x0000);

	/*!
	������� �������������� �������
	@param [__in] ticks ������ ��������
	@return 
	*/
	void ClearUnusedTextures(__in DWORD ticks);

	/*!
	�������� �������� ��� ���������� ����������� ���������
	@param [__in] direction ������ �� ����������� ��������
	@param [__in] id ������ ��������
	@param [__in] offset �������� ������������ ������ ��������
	@return true � ������ �������� ��������
	*/
	bool ExecuteDirectionGroup(__in TTextureAnimationDirection *direction, __in WORD &id, __in int &offset);

	/*!
	��������� ����������� � ������ ����������� �����������
	@param [__inout] dir �����������
	@param [__inout] mirror ���������� �����������
	@return 
	*/
	void GetAnimDirection(__inout BYTE &dir, __inout bool &mirror);

	/*!
	��������� ����������� � ������ ����������� ����������� ��� �������� ���������
	@param [__inout] dir �����������
	@param [__inout] mirror ���������� �����������
	@param [__inout] x ���������� X
	@param [__inout] y ���������� Y
	@return 
	*/
	void GetSittingAnimDirection(__inout BYTE &dir, __inout bool &mirror, __inout int &x, __inout int &y);

	/*!
	�������� ������ �� ������ ��������
	@param [__in] id ������ ��������
	@return ������ �� ��������
	*/
	TTextureAnimation *GetAnimation(__in WORD id);

	/*!
	���������� ���������
	@param [__in] obj ������ �� ���������
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@param [__in] z ���������� Z
	@return 
	*/
	void DrawCharacter(__in TGameCharacter *obj, __in int x, __in int y, __in int z);

	void DrawCharacterAAA(__in TGameCharacter *obj, __in int x, __in int y, __in int z);

	/*!
	��������� ������� ������� ��������� � ��������� �����������
	@param [__in] obj ������ �� ���������
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@param [__in] z ���������� Z
	@return true � ������, ���� ���� 1 ������� ��������� ��� ������
	*/
	bool CharacterPixelsInXY(__in TGameCharacter *obj, __in int x, __in int y, __in int z);

	/*!
	���������� ����
	@param [__in] obj ������ �� ����
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@param [__in] z ���������� Z
	@return 
	*/
	void DrawCorpse(__in TGameItem *obj, __in int x, __in int y, __in int z);

	/*!
	��������� ������� ������� ����� � ��������� �����������
	@param [__in] obj ������ �� ����
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@param [__in] z ���������� Z
	@return 
	*/
	bool CorpsePixelsInXY(__in TGameItem *obj, __in int x, __in int y, __in int z);

	/*!
	�������� ������ ������ ������ ��������
	@param [__in] id Byltrc rfhnbyrb
	@param [__in] second ������ ������ ����� 2
	@return ������ ������ ��������
	*/
	BYTE GetDieGroupIndex(__in WORD id, __in bool second);

	/*!
	�������� ������ ������ �� ������� ��������
	@param [__in] id ������ ��������
	@return ������ ��������
	*/
	ANIMATION_GROUPS GetGroupIndex(__in WORD id);

	/*!
	���������� ����
	@return 
	*/
	void DrawShadows();

	/*!
	���������� �� �������� � �����
	@param [__in] graphic ������ ��������
	@param [__in] group ������ ��������
	@return true � ������ ������
	*/
	bool AnimationExists(__in WORD &graphic, __in BYTE group);

	/*!
	�������� ������ �������� �����
	@param [__inout] graphic ������ ��������
	@return 
	*/
	void GetCorpseGraphic(__inout WORD &graphic);

	/*!
	�������� ������ ��������
	@param [__inout] graphic ������ ��������
	@return 
	*/
	void GetBodyGraphic(__inout WORD &graphic);

	ANIMATION_DIMENSIONS GetAnimationDimensions(TGameObject *obj, BYTE frameIndex = 0xFF, const BYTE &defaultDirection = 0, const BYTE &defaultGroup = 0);

	void CalculateFrameInformation(FRAME_OUTPUT_INFO &info, TGameObject *obj, const bool &mirror, const BYTE &animIndex);

	DRAW_FRAME_INFORMATION CollectFrameInformation(TGameObject *gameObject, const bool &checkLayers = true);
 };
//---------------------------------------------------------------------------
 //!������ �� �������� ��������
extern TAnimationManager *AnimationManager;
//---------------------------------------------------------------------------
#endif