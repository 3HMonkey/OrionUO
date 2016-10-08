/***********************************************************************************
**
** AnimationManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H
//----------------------------------------------------------------------------------
#include "../IndexObject.h"
#include "../TextureObject.h"
#include "../Wisp/WispDataStream.h"
//----------------------------------------------------------------------------------
static const float UPPER_BODY_RATIO = 0.35f;
static const float MID_BODY_RATIO = 0.60f;
static const float LOWER_BODY_RATIO = 0.94f;
//----------------------------------------------------------------------------------
struct FRAME_OUTPUT_INFO
{
	int StartX;
	int StartY;
	int EndX;
	int EndY;
};
//----------------------------------------------------------------------------------
struct ANIMATION_DIMENSIONS
{
	int Width;
	int Height;
	int CenterX;
	int CenterY;
};
//----------------------------------------------------------------------------------
//!����� ��������� ��������
class CAnimationManager : public WISP_DATASTREAM::CDataReader
{
	//!���� �������� �����
	SETGET(ushort, Color);
	//!������ �������� �������� �����
	SETGET(int, AnimGroup);
	//!����������� �������� �����
	SETGET(uchar, Direction);

private:
	//!������ ������ � ������
	uint m_AddressIdx[6];
	uint m_AddressMul[6];
	uint m_SizeIdx[6];

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

	//!������� ���� �����
	int m_Sitting;

	//!������������� ������ ����� ��� ����������� ������� ���������� ��� ���� ����������� ���������
	static const int USED_LAYER_COUNT = 23;
	static int m_UsedLayers[8][USED_LAYER_COUNT];

	//!������ ��������
	CIndexAnimation m_DataIndex[MAX_ANIMATIONS_DATA_INDEX_COUNT];

	//!������ ����� ��� ������
	ushort m_CorpseReplaces[MAX_ANIMATIONS_DATA_INDEX_COUNT];

	//!������ ������������ ��������
	deque<CIndexAnimation*> m_UsedAnimList;

	puchar GetAnimationAddress(const ushort &graphic, int &size, const uchar &group, const int &direction = 0);

	//�������� �������� �������� � ��������� �����������
	bool TestImagePixels(CTextureAnimationDirection *direction, const uchar &frame, const int &checkX, const int &checkY);

	bool TestPixels(class CGameObject *obj, int x, int y, const bool &mirror, uchar &frameIndex, ushort id = 0x0000);

	//������������� ����������� �������� ���������, �������� ����. �� ��� �� �����
	void FixSittingDirection(uchar &layerDirection, bool &mirror, int &x, int &y);

	//���������� ������� ���������
	void Draw(class CGameObject *obj, int x, int y, const bool &mirror, uchar &frameIndex, int id = 0);

	void DrawIntoFrameBuffer(class CGameCharacter *obj, int x, int y);

	//!������ ���� ������ ������ �� ����, ��������� ����������� ����-����� ����.
	bool DrawEquippedLayers(const bool &selection, class CGameObject *obj, const int &drawX, const int &drawY, const bool &mirror, const uchar &layerDir, uchar animIndex, const int &lightOffset);

	//!���������-�� ������ ���� ��� �����
	bool IsCovered(const int &layer, class CGameObject *owner);

	bool m_Transform;

	ushort m_CharacterLayerGraphic[25];
	ushort m_CharacterLayerAnimID[25];

public:
	CAnimationManager();
	~CAnimationManager();

	/*!
	������������� �������
	@param [__in] idx ������ �����
	@param [__in] AddressIdx ����� ����� � �������� �������
	@param [__in] AddressMul ����� ����� � �������
	@param [__in] SizeIdx ������ ����� � �������� �������
	@return 
	*/
	void Init(const int &graphic, const uint &addressIdx, const uint &addressMul, const uint &sizeIdx)
	{
		m_AddressIdx[graphic] = addressIdx;
		m_AddressMul[graphic] = addressMul;
		m_SizeIdx[graphic] = sizeIdx;
	}

	/*!
	�������� ����� ���������� �������� �������� ��������
	@param [__in] verdata ������ �� ����� � ������ ����� ������ (verdata.mul)
	@return
	*/
	void InitIndexReplaces(puint verdata);

	/*!
	�������� ������
	@param [__in] verdata ������ �� ����� � ������ ����� ������ (verdata.mul)
	@return 
	*/
	void Load(puint verdata);

	/*!
	��������� ������ �� ��������� �����
	@param [__in] obj ������� ������
	@param [__inout] frameIndex ������ �����
	@param [__in_opt] id ������ ��������
	@return ������ �� ���� ��������
	*/
	CTextureAnimationFrame *GetFrame(class CGameObject *obj, uchar frameIndex, ushort graphic = 0);

	/*!
	������� �������������� �������
	@param [__in] ticks ������ ��������
	@return 
	*/
	void ClearUnusedTextures(uint ticks);

	/*!
	�������� �������� ��� ���������� ����������� ���������
	@param [__in] direction ������ �� ����������� ��������
	@param [__in] id ������ ��������
	@param [__in] offset �������� ������������ ������ ��������
	@return true � ������ �������� ��������
	*/
	bool ExecuteDirectionGroup(CTextureAnimationDirection *direction, const ushort &graphic, const int &group, const int &dir);

	/*!
	��������� ����������� � ������ ����������� �����������
	@param [__inout] dir �����������
	@param [__inout] mirror ���������� �����������
	@return 
	*/
	void GetAnimDirection(uchar &dir, bool &mirror);

	/*!
	��������� ����������� � ������ ����������� ����������� ��� �������� ���������
	@param [__inout] dir �����������
	@param [__inout] mirror ���������� �����������
	@param [__inout] x ���������� X
	@param [__inout] y ���������� Y
	@return 
	*/
	void GetSittingAnimDirection(uchar &dir, bool &mirror, int &x, int &y);

	/*!
	�������� ������ �� ������ ��������
	@param [__in] id ������ ��������
	@return ������ �� ��������
	*/
	CTextureAnimation *GetAnimation(const ushort &graphic);

	/*!
	���������� ���������
	@param [__in] obj ������ �� ���������
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@param [__in] z ���������� Z
	@return 
	*/
	void DrawCharacter(class CGameCharacter *obj, int x, int y, int z);

	/*!
	��������� ������� ������� ��������� � ��������� �����������
	@param [__in] obj ������ �� ���������
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@param [__in] z ���������� Z
	@return true � ������, ���� ���� 1 ������� ��������� ��� ������
	*/
	bool CharacterPixelsInXY(class CGameCharacter *obj, int x, int y, int z);

	/*!
	���������� ����
	@param [__in] obj ������ �� ����
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@param [__in] z ���������� Z
	@return 
	*/
	void DrawCorpse(class CGameItem *obj, const int &x, const int &y);

	/*!
	��������� ������� ������� ����� � ��������� �����������
	@param [__in] obj ������ �� ����
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@param [__in] z ���������� Z
	@return 
	*/
	bool CorpsePixelsInXY(class CGameItem *obj, const int &x, const int &y);

	/*!
	�������� ������ ������ ������ ��������
	@param [__in] id Byltrc rfhnbyrb
	@param [__in] second ������ ������ ����� 2
	@return ������ ������ ��������
	*/
	uchar GetDieGroupIndex(ushort id, const bool &second);

	/*!
	�������� ������ ������ �� ������� ��������
	@param [__in] id ������ ��������
	@return ������ ��������
	*/
	ANIMATION_GROUPS GetGroupIndex(const ushort &id);

	/*!
	���������� �� �������� � �����
	@param [__in] graphic ������ ��������
	@param [__in] group ������ ��������
	@return true � ������ ������
	*/
	bool AnimationExists(const ushort &graphic, uchar group);

	/*!
	�������� ������ �������� �����
	@param [__inout] graphic ������ ��������
	@return 
	*/
	void GetCorpseGraphic(ushort &graphic);

	/*!
	�������� ������ ��������
	@param [__inout] graphic ������ ��������
	@return 
	*/
	void GetBodyGraphic(ushort &graphic);

	ANIMATION_DIMENSIONS GetAnimationDimensions(class CGameObject *obj, uchar frameIndex = 0xFF, const uchar &defaultDirection = 0, const uchar &defaultGroup = 0);

	void CalculateFrameInformation(FRAME_OUTPUT_INFO &info, class CGameObject *obj, const bool &mirror, const uchar &animIndex);

	struct DRAW_FRAME_INFORMATION CollectFrameInformation(class CGameObject *gameObject, const bool &checkLayers = true);
 };
//----------------------------------------------------------------------------------
//!������ �� �������� ��������
extern CAnimationManager g_AnimationManager;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
