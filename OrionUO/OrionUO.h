/***********************************************************************************
**
** OrionUO.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef ORIONUO_H
#define ORIONUO_H
//----------------------------------------------------------------------------------
#include "IndexObject.h"
#include "Constants.h"
#include "MulStruct.h"
#include "GLEngine/GLVector.h"
//----------------------------------------------------------------------------------
class COrion
{
	SETGET(string, ClientVersionText);
	SETGET(bool, InverseBuylist);
	SETGET(int, LandDataCount);
	SETGET(int, StaticDataCount);

private:
	uint m_CRC_Table[256];

	deque<CIndexObjectStatic*> m_StaticAnimList;

	deque<CIndexObject*> m_UsedLandList;
	deque<CIndexObject*> m_UsedStaticList;
	deque<CIndexObject*> m_UsedGumpList;
	deque<CIndexObject*> m_UsedTextureList;
	deque<CIndexSound*> m_UsedSoundList;
	deque<CIndexObject*> m_UsedLightList;

	UCHAR_LIST m_AnimData;

	void LoadClientConfig();
	void LoadAutoLoginNames();

	void LoadTiledata(const int &landSize, const int &staticsSize);

	void LoadIndexFiles();

	//�������� ��������� ������
	void UnloadIndexFiles();

	//�������� ������ ������������� ���������
	void InitStaticAnimList();

	//���������� ����� �����
	ushort CalculateLightColor(const ushort &id);

	//��������� ������ ������������� ���������
	void ProcessStaticAnimList();

	//���� ������
	void PatchFiles();

	//������� �������� (�������� ��������� ������)
	void IndexReplaces();

	//�������� ������ � �������
	bool LoadSkills();

	//�������� ���������� �������
	void LoadClientStartupConfig();

	//�������� ��������
	void LoadShaders();

	void CreateObjectHandlesBackground();

	//������� �������������� �������
	void ClearUnusedTextures();

public:
	COrion();
	~COrion();

	//������ �� �������� �� ���������
	vector<LAND_GROUP> m_LandData;

	//������ �� �������� �� �������
	vector<STATIC_GROUP> m_StaticData;

	bool Install();
	void Uninstall();

	//������������� ������
	void InitScreen(const GAME_STATE &state);

	//��������� ������ ����� �� ��������� ������� �������� ���������
	void ProcessDelayedClicks();

	void Process(const bool &rendering = false);

	//�������� ���������� �������
	void LoadStartupConfig();

	//�������� ��������
	void LoadPluginConfig();

	//�������� ������� ���������
	void LoadLocalConfig();

	//���������� ������� ���������
	void SaveLocalConfig();

	CIndexObject m_LandDataIndex[MAX_LAND_DATA_INDEX_COUNT];
	CIndexObjectStatic m_StaticDataIndex[MAX_STATIC_DATA_INDEX_COUNT];
	CIndexObject m_GumpDataIndex[MAX_GUMP_DATA_INDEX_COUNT];
	CIndexObject m_TextureDataIndex[MAX_LAND_TEXTURES_DATA_INDEX_COUNT];
	CIndexSound m_SoundDataIndex[MAX_SOUND_DATA_INDEX_COUNT];
	CIndexMusic m_MP3Data[MAX_MUSIC_DATA_INDEX_COUNT];
	CIndexMulti m_MultiDataIndex[MAX_MULTI_DATA_INDEX_COUNT];
	CIndexObject m_LightDataIndex[MAX_LIGHTS_DATA_INDEX_COUNT];

	ushort m_WinterTile[MAX_LAND_DATA_INDEX_COUNT];


	
	//������������ � ����� ������
	void Connect();

	//�������� ����������
	void Disconnect();

	//��������� ����� �� ������
	int Send(puchar buf, const int &size);

	//��������� ����� �� ������
	int Send(const UCHAR_LIST &buf) { return Send((puchar)&buf[0], (int)buf.size()); }

	//����� �������
	void ServerSelection(int pos);

	//����������� � �������� ������
	void RelayServer(const char *ip, int port, puchar gameSeed);

	//����� ���������
	void CharacterSelection(int pos);

	//������������� � ���������� ������ (�������� �� �������)
	void LoginComplete();

	//!�������� �����
	void ChangeSeason(const SEASON_TYPE &season, const int &music);

	ushort GetLandSeasonGraphic(ushort graphic);
	ushort GetSeasonGraphic(const ushort &graphic);
	ushort GetSpringGraphic(ushort graphic);
	ushort GetSummerGraphic(ushort graphic);
	ushort GetFallGraphic(ushort graphic);
	ushort GetWinterGraphic(ushort graphic);
	ushort GetDesolationGraphic(ushort graphic);



	//�������� ����� ���������
	uint GetLandFlags(const ushort &id);

	//�������� ����� �������
	uint GetStaticFlags(const ushort &id);

	//�������� ���� �����
	ushort GetLightColor(const ushort &id) { return m_StaticDataIndex[id].LightColor; }



	//�������� �������� �������� �������
	WISP_GEOMETRY::CSize GetArtDimension(const ushort &id);

	//�������� �������� �������� ������� (�������� ���������� �������)
	WISP_GEOMETRY::CRect GetStaticArtRealPixelDimension(const ushort &id);

	//�������� �������� �������� �����
	WISP_GEOMETRY::CSize GetGumpDimension(const ushort &id);



	//�������� �������� �����
	CGLTexture *ExecuteGump(const ushort &id);

	//�������� �������� ��������� �� art.mul
	CGLTexture *ExecuteLandArt(const ushort &id);

	//�������� �������� �������
	CGLTexture *ExecuteStaticArt(const ushort &id);

	//�������� �������� ������������� �������
	CGLTexture *ExecuteStaticArtAnimated(const ushort &id);

	//�������� �������� ��������� (�� texmaps.mul)
	CGLTexture *ExecuteTexture(ushort id);

	//�������� �������� �����
	CGLTexture *ExecuteLight(uchar &id);



	//�������� ��������� ������
	bool ExecuteGumpPart(const ushort &id, const int &count);

	//�������� ��������� ���� �����
	bool ExecuteResizepic(const ushort &id) { return ExecuteGumpPart(id, 9); }

	//�������� ��������� ������ �����
	bool ExecuteButton(const ushort &id) { return ExecuteGumpPart(id, 3); }



	//���������� ����
	void DrawGump(const ushort &id, const ushort &color, const int &x, const int &y, const bool &partialHue = false);

	//���������� ���������� ����
	void DrawGump(const ushort &id, const ushort &color, const int &x, const int &y, const int &width, const int &height, const bool &partialHue = false);

	//���������� ��� �����
	void DrawResizepicGump(const ushort &id, const int &x, const int &y, const int &width, const int &height);

	//���������� �������� (�� texmaps.mul)
	void DrawLandTexture(class CLandObject *land, ushort color, const int &x, const int &y);

	//���������� �������� (�� art.mul)
	void DrawLandArt(const ushort &id, ushort color, const int &x, const int &y, const int &z);

	//���������� �������
	void DrawStaticArt(const ushort &id, ushort color, const int &x, const int &y, const int &z, const bool &selection = false);

	//���������� ������������� �������
	void DrawStaticArtAnimated(const ushort &id, const ushort &color, const int &x, const int &y, const int &z, const bool &selection = false);

	//���������� ���������� �������
	void DrawStaticArtRotated(const ushort &id, ushort color, const int &x, const int &y, const int &z, const float &angle);

	//���������� ���������� ������������� �������
	void DrawStaticArtAnimatedRotated(const ushort &id, const ushort &color, const int &x, const int &y, const int &z, const float &angle);

	//���������� ���������� �������
	void DrawStaticArtTransparent(const ushort &id, ushort color, int x, int y, const int &z, const bool &selection = false);

	//���������� ���������� ������������� �������
	void DrawStaticArtAnimatedTransparent(const ushort &id, const ushort &color, const int &x, const int &y, const int &z, const bool &selection = false);

	//���������� ������� � ����������
	void DrawStaticArtInContainer(const ushort &id, ushort color, int x, int y, const bool &selection = false, const bool &onMouse = false);

	//���������� ����
	void DrawLight(struct LIGHT_DATA &light);



	//�������� �������������� ��� �������� �����
	bool PolygonePixelsInXY(int x, int y, const int &width, const int &height);

	//�������� ����� ��� �������� �����
	bool GumpPixelsInXY(const ushort &id, int x, int y, const bool &noSubMouse = false);

	//�������� ����������� ����� ��� �������� �����
	bool GumpPixelsInXY(const ushort &id, int x, int y, int width, int height, const bool &noSubMouse = false);

	//�������� ���� ��� �������� �����
	bool ResizepicPixelsInXY(const ushort &id, int x, int y, const int &width, const int &height);

	//�������� ������� ��� �������� �����
	bool StaticPixelsInXY(const ushort &id, int x, int y, const int &z);

	//�������� ������������� ������� ��� �������� �����
	bool StaticPixelsInXYAnimated(const ushort &id, const int &x, const int &y, const int &z);

	//�������� ����� ������������ ��� �������� �����
	bool CircleTransPixelsInXY();

	//�������� ������� � ���������� ��� �������� �����
	bool StaticPixelsInXYInContainer(const ushort &id, int x, int y);

	//�������� ��������� (�� art.mul) ��� �������� �����
	bool LandPixelsInXY(const ushort &id, int x, int y, const int &z);

	//�������� ����������� ��������� (�� texmaps.mul) ��� �������� �����
	bool LandTexturePixelsInXY(int x, int  y, RECT &r);



	//������� ��������� ��������� � ��������������� ������
	void CreateTextMessageF(uchar font, ushort color, const char *format, ...);

	//������� ��������� ��������� � ��������������� ������ (Unicode)
	void CreateUnicodeTextMessageF(uchar font, ushort color, const char *format, ...);

	//������� ��������� ��������� (ASCII)
	void CreateTextMessage(TEXT_TYPE type, uint serial, uchar font, ushort color, string text);

	//������� ��������� ��������� (Unicode)
	void CreateUnicodeTextMessage(TEXT_TYPE type, uint serial, uchar font, ushort color, wstring text);

	//�������� ��������� � ������ ���
	void AddSystemMessage(class CTextData *msg);

	//�������� ��������� � ������
	void AddJournalMessage(class CTextData *msg, string name);



	//��������� ������� �����
	void ChangeMap(uchar newmap);



	//������� �������
	void PickupItem(class CGameItem *obj, int count = 0, bool isGameFigure = false);

	//������� �������
	void DropItem(uint container, ushort x, ushort y, char z);

	//����� �������
	void EquipItem(uint container = 0);



	//�������� ������
	void ChangeWarmode(uchar status = 0xFF);

	//������ ����-����
	void HelpRequest();

	//������ �������
	void StatusReq(uint serial);

	//������ �������
	void SkillsReq(uint serial);

	//��������� ��������� ������
	void SkillStatusChange(uchar skill, uchar state);

	//�������� �� �������
	void Click(uint serial);

	//������ ����� ������� (����)
	void NameReq(uint serial) { Click(serial); };

	//������� ������� �� ������
	void DoubleClick(uint serial);

	//������ ����������
	void PaperdollReq(uint serial);

	//��������� ����� � �������
	void Attack(uint serial);

	//�������� ������ �� ������
	void AttackReq(uint serial);

	//�������� ASCII ������
	void SendASCIIText(const char *str, SPEECH_TYPE type);

	//������ ���� ����������
	void CastSpell(int index);

	//������ ���� ���������� � �����
	void CastSpellFromBook(int index, uint serial);

	//������������ �����
	void UseSkill(int index);

	//������� �����
	void OpenDoor();

	//������ �������� ������
	void EmoteAction(const char *action);

	//���� �� ���� ���������� � ���� ���������
	void AllNames();

	//�������� ���-��� �����
	uint GetFileHashCode(uint address, uint size);

	//�������� ������������
	void LoadLogin(string &login, int &port);

	//������� �� ���-������
	void GoToWebLink(const string &url);



	//��������� ������ mp3 ���� midi
	void PlayMusic(const int &index, const bool &warmode = false);

	//��������� �������� ������
	void PlaySoundEffect(const ushort &index, float volume = -1);

	//������� �������������� �������� �������
	void AdjustSoundEffects(const uint &ticks, const float &volume = -1);



	//�������� ��������, �������� �� ������� g_UpdateRange
	void RemoveRangedObjects();

	//����� �� ���� �� �������� �����
	void LogOut();



	//��������� ������
	void ConsolePromptSend();

	//��������� ������ �������
	void ConsolePromptCancel();



	//--------------------------------------------
	//---��������� ������ ���������� � ��������---
	//--------------------------------------------

	//������� ���� ����������
	void OpenPaperdoll();

	//������� ���� �������
	void OpenStatus(uint serial);

	//������� ���� ����-�����
	void OpenMinimap();

	//������� ���� ����� ����
	void OpenWorldMap();

	//������� ���� �������
	void OpenJournal();

	//������� ���� �������
	void OpenSkills();

	//������� ������
	void OpenBackpack();

	//������� ���� �������
	void OpenLogOut();

	//������� ���� ����
	void OpenChat();

	//������� ���� �����
	void OpenConfiguration();

	//������� ���� �����
	void OpenMail();

	//������� ���� ����-���������
	void OpenPartyManifest();

	//������� ���� �������
	void OpenProfile(uint serial = 0);

	//��������� ���� �������
	void RequestGuildGump();

	//��������� ���� �������
	void RequestQuestGump();
};
//----------------------------------------------------------------------------------
extern COrion g_Orion;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------

