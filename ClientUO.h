/****************************************************************************
**
** ClientUO.h
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
#ifndef ClientUOH
#define ClientUOH
//---------------------------------------------------------------------------
#pragma once
#include "resource.h"
//---------------------------------------------------------------------------
#define IDT_UPDATE_MOUSE_TIMER		666
//---------------------------------------------------------------------------
//�������� �����
class TUltimaOnline
{
private:
	//CRC32 �������
	DWORD m_CRC_Table[256];

	//������ ���������� � ������ �������, ������ � �.�.
	TIndexObject m_LandDataIndex[MAX_LAND_DATA_INDEX_COUNT];
	TIndexObjectStatic m_StaticDataIndex[MAX_STATIC_DATA_INDEX_COUNT];
	TIndexObject m_GumpDataIndex[MAX_GUMP_DATA_INDEX_COUNT];
	TIndexObject m_TextureDataIndex[MAX_LAND_TEXTURES_DATA_INDEX_COUNT];
	TIndexSound m_SoundDataIndex[MAX_SOUND_DATA_INDEX_COUNT];
	TMP3Struct m_MP3Data[MAX_MP3_COUNT];
	TIndexMulti m_MultiDataIndex[0x2000];
	TIndexObject m_LightDataIndex[MAX_LIGHTS_DATA_INDEX_COUNT];

	//������ ������������� ��������
	TLinkedList *m_StaticAnimList;

	//������ ����������� ��������
	TLinkedList *m_UsedLandList;
	TLinkedList *m_UsedStaticList;
	TLinkedList *m_UsedGumpList;
	TLinkedList *m_UsedTextureList;
	TLinkedList *m_UsedSoundList;
	TLinkedList *m_UsedLightList;

	//������ �� ��������
	PBYTE m_AnimData;

	//�������� ���������� �������
	void LoadClientStartupConfig();

	//�������� ��������� ������
	void LoadIndexFiles();

	//�������� ��������� ������
	void UnloadIndexFiles();

	//�������� ������ ������������� ���������
	void InitStaticAnimList();

	//������� �������������� �������
	void ClearUnusedTextures();

	//�������� ������ �� ��������
	void LoadTiledata();

	//���� ������
	void PatchFiles();

	//������� �������� (�������� ��������� ������)
	void IndexReplaces();

	//�������� ������ � �������
	bool LoadSkills();

	//�������� ������ � �������
	void UnloadSkills();

	//�������� ������������
	void LoadLogin();

	//�������� ��������
	void LoadShaders();

	//�������� ������������ �������
	void LoadClientConfig();

	//�������� ���� ��� ���������
	void LoadAutoLoginNames();

	//���������� ����� �����
	WORD CalculateLightColor(WORD id);

	//��������� ����� �����
	void SendWalkStack();

	void CreateObjectHandlesBackground();

public:
	TUltimaOnline();
	~TUltimaOnline();

	//�������������
	bool Install();

	//�������� ���������� �������
	void LoadStartupConfig();

	//�������� ��������
	void LoadPluginConfig();

	//�������� ������� ���������
	void LoadLocalConfig();

	//���������� ������� ���������
	void SaveLocalConfig();

	//�������� ���-��� �����
	DWORD GetFileHashCode(DWORD address, DWORD size);

	//�������� ������� ����� � ������ ���������
	bool AutoLoginNameExists(string name);

	//��������� ������ ������������� ���������
	void ProcessStaticAnimList();



	//�������� �������� �����
	TTextureObject *ExecuteGump(const WORD &id, const bool &partialHue = true);

	//�������� �������� ��������� �� art.mul
	TTextureObject *ExecuteLandArt(const WORD &id);

	//�������� �������� �������
	TTextureObject *ExecuteStaticArt(const WORD &id);

	//�������� �������� ������������� �������
	TTextureObject *ExecuteStaticArtAnimated(const WORD &id);

	//�������� �������� ��������� (�� texmaps.mul)
	TTextureObject *ExecuteTexture(WORD id);

	//�������� �������� �����
	TTextureObject *ExecuteLight(BYTE &id);



	//�������� ��������� ������
	bool ExecuteGumpPart(const WORD &id, const int &count);

	//�������� ��������� ���� �����
	bool ExecuteResizepic(const WORD &id) { return ExecuteGumpPart(id, 9); }

	//�������� ��������� ������ �����
	bool ExecuteButton(const WORD &id) { return ExecuteGumpPart(id, 3); }



	//��������� �����-�������� (��������� ����)
	void DrawSphereGump(const int &value, const float &maxValue, const int &x, const int &y, const int &width = 95);



	//���������� ����
	void DrawGump(const WORD &id, const WORD &color, const int &x, const int &y, const bool &partialHue = false);

	//���������� ���������� ����
	void DrawGump(const WORD &id, const WORD &color, const int &x, const int &y, int width, int height, const bool &partialHue = false);

	//���������� ��� �����
	void DrawResizepicGump(const WORD &id, const int &x, const int &y, const int &width, const int &height);

	//���������� �������� (�� texmaps.mul)
	void DrawLandTexture(const WORD &id, WORD color, const int &x, const int &y, RECT &rc, TVector *normals);

	//���������� �������� (�� art.mul)
	void DrawLandArt(const WORD &id, WORD color, const int &x, const int &y, const int &z);

	//���������� �������
	void DrawStaticArt(const WORD &id, WORD color, const int &x, const int &y, const int &z, const bool &selection = false);

	//���������� ������������� �������
	void DrawStaticArtAnimated(const WORD &id, const WORD &color, const int &x, const int &y, const int &z, const bool &selection = false);

	//���������� ���������� �������
	void DrawStaticArtRotated(const WORD &id, WORD color, const int &x, const int &y, const int &z, const float &angle);

	//���������� ���������� ������������� �������
	void DrawStaticArtAnimatedRotated(const WORD &id, const WORD &color, const int &x, const int &y, const int &z, const float &angle);

	//���������� ���������� �������
	void DrawStaticArtTransparent(const WORD &id, WORD color, int x, int y, const int &z, const bool &selection = false);

	//���������� ���������� ������������� �������
	void DrawStaticArtAnimatedTransparent(const WORD &id, const WORD &color, const int &x, const int &y, const int &z, const bool &selection = false);

	//���������� ������� � ����������
	void DrawStaticArtInContainer(const WORD &id, WORD color, int x, int y, const bool &selection = false, const bool &onMouse = false);

	//���������� ����
	void DrawLight(BYTE id, const WORD &color, const int &x, const int &y);
	


	//�������� �������������� ��� �������� �����
	bool PolygonePixelsInXY(int x, int y, const int &width, const int &height);

	//�������� ����� ��� �������� �����
	bool GumpPixelsInXY(const WORD &id, int x, int y, const bool &noSubMouse = false);

	//�������� ����������� ����� ��� �������� �����
	bool GumpPixelsInXY(const WORD &id, int x, int y, int width, int height, const bool &noSubMouse = false);

	//�������� ���� ��� �������� �����
	bool ResizepicPixelsInXY(const WORD &id, int x, int y, const int &width, const int &height);

	//�������� ������� ��� �������� �����
	bool StaticPixelsInXY(const WORD &id, int x, int y, const int &z);

	//�������� ������������� ������� ��� �������� �����
	bool StaticPixelsInXYAnimated(const WORD &id, const int &x, const int &y, const int &z);

	//�������� ����� ������������ ��� �������� �����
	bool CircleTransPixelsInXY();

	//�������� ������� � ���������� ��� �������� �����
	bool StaticPixelsInXYInContainer(const WORD &id, int x, int y);

	//�������� ��������� (�� art.mul) ��� �������� �����
	bool LandPixelsInXY(const WORD &id, int x, int y, const int &z);

	//�������� ����������� ��������� (�� texmaps.mul) ��� �������� �����
	bool LandTexturePixelsInXY(int x, int  y, RECT &r);



	//�������� ����� ���������
	DWORD GetLandFlags(const WORD &id);

	//�������� ����� �������
	DWORD GetStaticFlags(const WORD &id);



	//�������� �������� �������� �������
	void GetArtDimension(const WORD &id, POINT &p);

	//�������� �������� �������� ������� (�������� ���������� �������)
	void GetStaticArtRealPixelDimension(const WORD &id, RECT &r);

	//�������� �������� �������� �����
	void GetGumpDimension(const WORD &id, POINT &p);


	
	//�������� ��������� �� ��������� �����
	TIndexObjectStatic *GetStaticPointer(const WORD &id);

	//�������� ��������� �� ��������� �����
	TIndexObject *GetGumpPointer(const WORD &id);

	//�������� ��������� �� ��������� �����
	TIndexMulti *GetMultiPointer(const WORD &id);



	//�������� ���� �����
	WORD GetLightColor(const WORD &id) { return m_StaticDataIndex[id].LightColor; }

	int GetConfigValue(const char *option, int value = -1);



	//��������� �������� ������
	void PlaySoundEffect(const WORD &index, int volume = -1);

	//��������� ������ mp3 ���� midi
	void PlayMusic(int index);

	//������� �������������� �������� �������
	void ResetSoundEffects(DWORD ticks);



	//������ �� �������� �� ���������
	LAND_GROUP m_LandData[512];

	//������ �� �������� �� �������
	STATIC_GROUP m_StaticData[512];



	//��������� ����� �� ������
	int Send(PBYTE buf, int size);

	//������������� ������
	void InitScreen(GAME_STATE state);

	//��������� ��������
	void Process();



	//������� ��������� ��������� � ��������������� ������
	void CreateTextMessageF(BYTE font, WORD color, const char *format, ...);

	//������� ��������� ��������� � ��������������� ������ (Unicode)
	void CreateUnicodeTextMessageF(BYTE font, WORD color, const char *format, ...);

	//������� ��������� ��������� (ASCII)
	void CreateTextMessage(TEXT_TYPE type, DWORD serial, WORD font, WORD color, string text);

	//������� ��������� ��������� (Unicode)
	void CreateUnicodeTextMessage(TEXT_TYPE type, DWORD serial, WORD font, WORD color, wstring text);

	//�������� ��������� � ������ ���
	void AddSystemMessage(TTextData *msg);

	//�������� ��������� � ������
	void AddJournalMessage(TTextData *msg, string name);



	//��������� ������� �����
	void ChangeMap(BYTE newmap);



	//������������ � ����� ������
	void Connect();

	//�������� ����������
	void Disconnect();

	//����� �������
	void ServerSelection(int pos);

	//����������� � �������� ������
	void RelayServer(const char *ip, int port, PBYTE gameSeed);

	//����� ���������
	void CharacterSelection(int pos);

	//������������� � ���������� ������ (�������� �� �������)
	void LoginComplete();



	//��������� ������
	void ConsolePromptSend();

	//��������� ������ �������
	void ConsolePromptCancel();



	//������� �������
	void PickupItem(TGameItem *obj, int count = 0, bool isGameFigure = false);

	//������� �������
	void DropItem(DWORD container, WORD x, WORD y, char z);

	//����� �������
	void EquipItem(DWORD container = 0);



	//�������� ������
	void ChangeWarmode(BYTE status = 0xFF);

	//������ ����-����
	void HelpRequest();

	//������ �������
	void StatusReq(DWORD serial);

	//������ �������
	void SkillsReq(DWORD serial);

	//��������� ��������� ������
	void SkillStatusChange(BYTE skill, BYTE state);

	//�������� �� �������
	void Click(DWORD serial);

	//������ ����� ������� (����)
	void NameReq(DWORD serial) {Click(serial);};

	//������� ������� �� ������
	void DoubleClick(DWORD serial);

	//������ ����������
	void PaperdollReq(DWORD serial);

	//��������� ����� � �������
	void Attack(DWORD serial);

	//�������� ������ �� ������
	void AttackReq(DWORD serial);

	//�������� ASCII ������
	void SendASCIIText(const char *str, SPEECH_TYPE type);

	//������ ���� ����������
	void CastSpell(int index);

	//������ ���� ���������� � �����
	void CastSpellFromBook(int index, DWORD serial);

	//������������ �����
	void UseSkill(int index);

	//������� �����
	void OpenDoor();

	//������ �������� ������
	void EmoteAction(const char *action);

	//���� �� ���� ���������� � ���� ���������
	void AllNames();

	//������� �� ���-������
	void GoToWebLink(string url);



	//�������� ��������, �������� �� ������� g_UpdateRange
	void RemoveRangedObjects();



	//����� �� ���� �� �������� �����
	void LogOut();



	//--------------------------------------------
	//---��������� ������ ���������� � ��������---
	//--------------------------------------------

	//������� ���� ����������
	void OpenPaperdoll();

	//������� ���� �������
	void OpenStatus(DWORD serial);

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
	void OpenProfile(DWORD serial = 0);

	//��������� ���� �������
	void RequestGuildGump();

	//��������� ���� �������
	void RequestQuestGump();
};
//---------------------------------------------------------------------------
extern TUltimaOnline *UO;
//---------------------------------------------------------------------------
#endif