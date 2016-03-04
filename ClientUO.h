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
//�������� �����
class TUltimaOnline : public IUltimaOnline
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
	TTextureObject *ExecuteGump(WORD id, bool partialHue = true);

	//�������� �������� ��������� �� art.mul
	TTextureObject *ExecuteLandArt(WORD &id);

	//�������� �������� �������
	TTextureObject *ExecuteStaticArt(WORD id);

	//�������� �������� ������������� �������
	TTextureObject *ExecuteStaticArtAnimated(WORD id);

	//�������� �������� ��������� (�� texmaps.mul)
	TTextureObject *ExecuteTexture(WORD id);

	//�������� �������� �����
	TTextureObject *ExecuteLight(BYTE &id);



	//�������� ��������� ������
	bool ExecuteGumpPart(WORD id, int count);

	//�������� ��������� ���� �����
	bool ExecuteResizepic(WORD id) {return ExecuteGumpPart(id, 9);}

	//�������� ��������� ������ �����
	bool ExecuteButton(WORD id) {return ExecuteGumpPart(id, 3);}



	//��������� �����-�������� (��������� ����)
	void DrawSphereGump(int value, float maxValue, int x, int y, int width = 95);



	//���������� ����
	void DrawGump(WORD id, WORD color, int x, int y, bool partialHue = false);

	//���������� ���������� ����
	void DrawGump(WORD id, WORD color, int x, int y, int width, int height, bool partialHue = false);

	//���������� ��� �����
	void DrawResizepicGump(WORD id, int x, int y, int width, int height);

	//���������� �������� (�� texmaps.mul)
	void DrawLandTexture(WORD &id, WORD &color, int &x, int &y, RECT &rc, TVector *normals);

	//���������� �������� (�� art.mul)
	void DrawLandArt(WORD id, WORD color, int x, int y, int z);

	//���������� �������
	void DrawStaticArt(WORD id, WORD color, int x, int y, int z, bool selection = false);

	//���������� ������������� �������
	void DrawStaticArtAnimated(WORD id, WORD color, int x, int y, int z, bool selection = false);

	//���������� ���������� �������
	void DrawStaticArtTransparent(WORD id, WORD color, int x, int y, int z, bool selection = false);

	//���������� ���������� ������������� �������
	void DrawStaticArtAnimatedTransparent(WORD id, WORD color, int x, int y, int z, bool selection = false);

	//���������� ������� � ����������
	void DrawStaticArtInContainer(WORD id, WORD color, int x, int y, bool selection = false, bool onMouse = false);

	//���������� ����
	void DrawLight(BYTE id, WORD color, int x, int y);
	


	//�������� �������������� ��� �������� �����
	bool PolygonePixelsInXY(int x, int y, int width, int height);

	//�������� ����� ��� �������� �����
	bool GumpPixelsInXY(WORD id, int x, int y, bool noSubMouse = false);

	//�������� ����������� ����� ��� �������� �����
	bool GumpPixelsInXY(WORD id, int x, int y, int width, int height, bool noSubMouse = false);

	//�������� ���� ��� �������� �����
	bool ResizepicPixelsInXY(WORD id, int x, int y, int width, int height);

	//�������� ������� ��� �������� �����
	bool StaticPixelsInXY(WORD id, int x, int y, int z);

	//�������� ������������� ������� ��� �������� �����
	bool StaticPixelsInXYAnimated(WORD id, int x, int y, int z);

	//�������� ����� ������������ ��� �������� �����
	bool CircleTransPixelsInXY();

	//�������� ������� � ���������� ��� �������� �����
	bool StaticPixelsInXYInContainer(WORD id, int x, int y);

	//�������� ��������� (�� art.mul) ��� �������� �����
	bool LandPixelsInXY(WORD id, int x, int y, int z);

	//�������� ����������� ��������� (�� texmaps.mul) ��� �������� �����
	bool LandTexturePixelsInXY(int x, int  y, RECT &r);



	//�������� ����� ���������
	DWORD GetLandFlags(WORD id);

	//�������� ����� �������
	DWORD GetStaticFlags(WORD id);



	//�������� �������� �������� �������
	void GetArtDimension(WORD id, POINT &p);

	//�������� �������� �������� �����
	void GetGumpDimension(WORD id, POINT &p);


	
	//�������� ��������� �� ��������� �����
	TIndexObjectStatic *GetStaticPointer(WORD &id);

	//�������� ��������� �� ��������� �����
	TIndexObject *GetGumpPointer(WORD &id);

	//�������� ��������� �� ��������� �����
	TIndexMulti *GetMultiPointer(WORD id);



	//�������� ���� �����
	WORD GetLightColor(WORD id) {return m_StaticDataIndex[id].LightColor;}



	//��������� �������� ������
	void PlaySoundEffect(WORD index, int volume = -1);

	//������� �������������� �������� �������
	void ResetSoundEffects(DWORD ticks);



	//������ �� �������� �� ���������
	LAND_GROUP m_LandData[512];

	//������ �� �������� �� �������
	PSTATIC_GROUP m_StaticData;

	//���������� ������ �� �������
	int m_StaticDataCount;



	//��������� ����� �� ������
	int Send(PBYTE buf, int size);

	//������������� ������
	void InitScreen(GAME_STATE state);

	//��������� ��������
	void Process();



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

	//������� ����� ����������
	void OpenSpellbook();

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
};
//---------------------------------------------------------------------------
extern TUltimaOnline *UO;
//---------------------------------------------------------------------------
#endif