/****************************************************************************
**
** stdafx.h
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
#ifndef stdafxH
#define stdafxH
//---------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
// ����� ���������� Windows:
#include <windows.h>
// ����� ���������� C RunTime
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <map>
#include <algorithm>
#include <time.h>
#include "glew.h"
#include "wglew.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include "bass.h"
#include <winsock.h>
#include <deque>
#include <Shellapi.h>
#include <Shlwapi.h>
#include "zlib.h"
#include <Mmsystem.h>
#include <process.h>

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::wstring;

#include <unordered_map>
using std::unordered_map;

using std::pair;

#define _USE_MATH_DEFINES // for C++
#include <math.h>

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "Glu32.lib")
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "zdll.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "bass.lib")

#pragma warning(disable: 4390)
#pragma warning(disable: 4800)
//---------------------------------------------------------------------------
#define UO_FW_SHARD 0
#define UO_ABYSS_SHARD 0

#define UO_USE_SHADER_FILES 0

#include "Constants.h"
#include "EnumList.h"
#include "PluginInterface.h"
#include "DefinitionMacro.h"
//---------------------------------------------------------------------------
//!��������� �� �������� �������
extern GLuint ShaderTexture;

//!��������� �� ��������� ��������� �������
extern GLuint ShaderDrawMode;

//!��������� �� ������� ������ ��� �������
extern GLuint ShaderColorTable;
//---------------------------------------------------------------------------
//!�������� �������� (������ ��� �������)
extern int g_LandObjectsCount;
extern int g_StaticsObjectsCount;
extern int g_GameObjectsCount;
extern int g_MultiObjectsCount;
extern int g_RenderedObjectsCountInGameWindow;
//---------------------------------------------------------------------------
//!�������� ������ ��� ������ (locked/unlocked)
extern GLuint g_TextureGumpState[2];

//!����������� ������������ ����������
extern bool g_UseFrameBuffer;

const int g_ObjectHandlesWidth = 142;
const int g_ObjectHandlesHeight = 20;
extern WORD g_ObjectHandlesBackgroundPixels[g_ObjectHandlesWidth * g_ObjectHandlesHeight];
//---------------------------------------------------------------------------
//!���������� ��������� ������� �������������� �������
extern bool g_AltPressed;
extern bool g_CtrlPressed;
extern bool g_ShiftPressed;
//---------------------------------------------------------------------------
//!������������� ����� ��� ����������� ���������
extern bool g_MovingFromMouse;

//!������������� ��������������� ����������� ��������� �� �������� �����, ����� ������ ��������� � ������� ����
extern bool g_AutoMoving;

extern bool g_AbyssPacket03First;
//---------------------------------------------------------------------------
//!������� ����������
extern HINSTANCE g_Hinstance;

//!����� ����
extern HWND g_hWnd;

//!�������� ���������� ������� ����
extern int g_ClientWidth;
extern int g_ClientHeight;

//!�������� �������� � �������
extern int g_FrameDelay[2];

//!������ ������������ ���� ��������
extern char g_FoliageIndex;

//!���� � ����� �������
extern string g_DirectoryPath;

//!��� ���������� �����, �������� �������� ����������� �������
extern string g_LastLoadFileError;

//!����� ������ �������
extern string g_ClientVersionText;

//!����� ��� ���������
extern string g_AutoLoginNames;

//!���� ���������� ���������� ������
extern wstring g_ConsoleStack[MAX_CONSOLE_STACK_SIZE];

//!���������� ������������ � ���� ������
extern int g_ConsoleStackCount;

//!��������� �� ������� ������� �����
extern int g_ConsoleSelectedIndex;

//!IP �������
extern string g_ShardIP;

//!���� � �������� ������������ � �������
extern int g_ShardPort;

//!����� ��������� �������� ������ �������
extern DWORD g_LastSendTime;

//!����� ���������� ������ �� �������
extern DWORD g_LastPacketTime;

//!����� ������ ������������ �������
extern DWORD g_TotalSendSize;

//!����� ������ �������� �������
extern DWORD g_TotalRecvSize;

//!���� �������� �������
extern bool g_ConfigLoaded;

//!��������� ���� (������������ �����)
extern GAME_STATE g_GameState;

//!����� �����
extern DWORD g_CryptKey[3];

//!����������� ����� �����
extern WORD g_SeedKey;

//!��������� ������������� ���������� �������
extern BYTE g_GameSeed[4];

//!������� ������������
extern BYTE g_LightLevel;

//!������� ������������ ���������
extern BYTE g_PersonalLightLevel;

//!������������� �������
extern bool g_InverseBuylist;

//!����� �������
extern DWORD g_ClientFlag;

//!����� ���������� �������
extern DWORD g_LockedClientFeatures;

//!������������ �������� ����� � ������ �� ����
extern short g_MapSizeX[6];
extern short g_MapSizeY[6];

//!������������ �������� ����� � ������ �� ����
extern short g_MapBlockX[6];
extern short g_MapBlockY[6];

//!�������� ���� ����
extern GLuint g_MapTexture[6];

//!������ ������� �����
extern BYTE g_CurrentMap;

//!�������� �������� ����
extern int g_GameWindowWidth;
extern int g_GameWindowHeight;

//!������� �������� ����
extern int g_GameWindowPosX;
extern int g_GameWindowPosY;

//!������� �������� ������������
extern int g_CodePage;

//!����� �������
extern BYTE g_ServerTimeHour;
extern BYTE g_ServerTimeMinute;
extern BYTE g_ServerTimeSecond;

//!������� ����� �����
extern BYTE g_PingCount;
extern BYTE g_PingSequence;

//!����� � ���������� ����� � ���� �������
extern bool g_PacketLoginComplete;

//!�������� ��� � �����-����� �������������
extern bool g_GrayedPixels;

//!���������� �������� ������-��������
extern int g_MultiIndexCount;

//!���������� �������� �����������
extern BYTE g_WalkRequestCount;

//!����� ���������� ����
extern DWORD g_LastStepTime;

//!����� �������� �������
extern float g_SkillsTotal;

//!�������� ���������
extern DWORD g_PlayerSerial;

//!���������� ����������� ����
extern int g_GrayMenuCount;

//!���������� � ������� ��������� ���������
extern bool g_JournalShowSystem;

//!���������� � ������� ��������� �� ��������
extern bool g_JournalShowObjects;

//!���������� � ������� ���������� ��������� �������
extern bool g_JournalShowClient;

//!�������� ���������� ��� ������
extern DWORD g_StatusbarUnderMouse;

//!������ ������� ������ �� ������
extern DWORD g_DeathScreenTimer;

//!������ �������� ������� �����
extern bool g_CancelDoubleClick;

//!��� �������
extern PROMPT_TYPE g_ConsolePrompt;

//!������ ���������� ASCII �������
extern BYTE g_LastASCIIPrompt[11];

//!������ ���������� Unicode �������
extern BYTE g_LastUnicodePrompt[11];

//!����� ���������. true - ���������, false - ����� ��������
extern bool g_DrawMode;

//!������� ����
extern string g_Language;

//!���� ��� ��������, �������� �� ������� g_UpdateRange (���� ��� ������������� �������)
extern WORD g_OutOfRangeColor;

//!���������� �� ����������� � ������ �� ����
extern bool g_SendLogoutNotification;

//!�������� �� ����������� ���� ���
extern bool g_NPCPopupEnabled;

//!������� �� ���
extern bool g_ChatEnabled;

//!������� ����� ����
extern BYTE g_Season;

//!����������� ������� �������� ���������
extern float g_AnimCharactersDelayValue;

//!���������� �� ������ ������
extern bool g_ShowGumpLocker;

//!�������� ��� ������� �� ������ ����-�����
extern DWORD g_PartyHelperTarget;

//!����� ����� ��� ������� �� ������ ����-�����
extern DWORD g_PartyHelperTimer;

//!���� OpenGL ���������
extern float g_DrawColor;

//!�� �������� �����
extern bool g_NoDrawRoof;

//!������������ �������� Z ���������� ��������� ��� �������
extern char g_MaxGroundZ;

//!��� ���������� ���������
extern char g_SelectedCharName[30];

//!����� �������� ����������� ���������
extern CHARACTER_SPEED_TYPE g_SpeedMode;

//!�������� Z-buffer'�
extern int g_ZBuffer;

//!����������� ������������� ����� ������������
extern bool g_UseCircleTrans;

extern bool g_GumpPressed;
extern bool g_GumpPressedScroller;
extern DWORD g_GumpSelectElement;
extern DWORD g_GumpPressedElement;
extern int g_GumpMovingOffsetX;
extern int g_GumpMovingOffsetY;
extern float g_GumpTranslateX;
extern float g_GumpTranslateY;
//---------------------------------------------------------------------------
//!������� ���������� ����
extern int g_MouseX;
extern int g_MouseY;

//!���������� ������� ����� ������ ����
extern int g_DroppedLeftMouseX;
extern int g_DroppedLeftMouseY;

//!���������� ������� ������ ������ ����
extern int g_DroppedRightMouseX;
extern int g_DroppedRightMouseY;

//!��������� ������� ������ ����
extern bool g_RightMouseDown;
extern bool g_LeftMouseDown;
//---------------------------------------------------------------------------
//!����� �������� ������
extern bool g_SelectGumpObjects;

//!��� ���������� �������
extern SELECT_OBJECT_TYPE g_LastObjectType;

//!��������� ��������� ������
extern int g_LastSelectedObject;

//!��������� ������, �� ������� ���� ������ ����� ������ ����
extern int g_LastObjectLeftMouseDown;

//!��������� ������, �� ������� ���� ������ ������ ������ ����
extern int g_LastObjectRightMouseDown;

//!��������� ��������� ����
extern DWORD g_LastSelectedGump;

//!��������� ����, �� ������� ���� ������ ����� ������ ����
extern DWORD g_LastGumpLeftMouseDown;

//!����� ���������� ������� ������ �� ����
extern DWORD g_LastGumpMouseDownTime;

//!����� ���������� ������� �����
extern DWORD g_LastMouseDownTime;

//!��������� ����, �� ������� ���� ������ ������ ������ ����
extern DWORD g_LastGumpRightMouseDown;

//!��������������� ������� ������� ������ ����
extern bool g_GeneratedMouseDown;

//!��������� ����� ����� ������
extern DWORD g_LastLClickTime;

//!������ ���������� ���������� ����������
extern int g_LastSpellIndex;

//!������ ���������� ���������� ������
extern int g_LastSkillIndex;

//!������ ������� �� ������
extern bool g_ClickObjectReq;

//!��������� �������������� ������
extern DWORD g_LastUseObject;

//!��������� ������, �� ������� ������ ��������
extern DWORD g_LastTargetObject;

//!��������� ����������� ������
extern DWORD g_LastAttackObject;

//!����� ��������� ���������
extern DWORD g_LastRenderTime;

//!��������� ��� ���������� ���������
extern int g_UpdateRange;

//!����������, � ������� ������� �������� ������ �������� ��������
extern POINT g_RemoveRangeXY;

typedef vector<pair<DWORD, DWORD>> CORPSE_LIST_MAP;
extern CORPSE_LIST_MAP g_CorpseSerialList;
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
typedef struct MULTILINES_FONT_DATA
{
	wchar_t item;
	WORD flags;
	BYTE font;
	WORD linkID;
	DWORD color;

	MULTILINES_FONT_DATA *Next;
} *PMULTILINES_FONT_DATA;
//---------------------------------------------------------------------------
typedef struct MULTILINES_FONT_INFO
{
	int Width;
	int IndentionOffset;
	int MaxHeight;
	int CharStart;
	int CharCount;
	TEXT_ALIGN_TYPE Align;
	vector<MULTILINES_FONT_DATA> Data;

	MULTILINES_FONT_INFO *m_Next;

	void Reset()
	{
		Width = 0;
		IndentionOffset = 0;
		MaxHeight = 0;
		CharStart = 0;
		CharCount = 0;
		Align = TS_LEFT;
		m_Next = NULL;
	}
} *PMULTILINES_FONT_INFO;




#define DPOLY(x, y, w, h) g_GL.DrawPolygone(x, y, w, h)
//---------------------------------------------------------------------------
typedef std::vector<BYTE> WaveFile;




//---------------------------------------------------------------------------
#include "CommonFunctions.h"
#include "CommonInterfaces.h"
#include "MulStruct.h"
#include "ExceptionFilter.h"
#include "network\\platform.h"
#include "network\\aes.h"
#include "network\\table.h"
#include "network\\UOHuffman.h"
#include "network\\Packet.h"
#include "network\\LoginCrypt.h"
#include "network\\GameCrypt.h"
#include "network\\Connection.h"
#include "managers\\ConnectionManager.h"
#include "managers\\PacketManager.h"
#include "managers\\FileManager.h"
#include "TextFileParser.h"
#include "ImageBounds.h"
#include "TargetGump.h"
#include "SmoothMonitor.h"
#include "BaseQueue.h"
#include "TextureObject.h"
#include "IndexObject.h"
#include "LinkedList.h"
#include "EntryText.h"
#include "BookEntryText.h"
#include "GameConsole.h"
#include "Logger.h"
#include "TextData.h"
#include "GLEngine.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "RenderObject.h"
#include "MapObject.h"
#include "Multi.h"
#include "game object\\GameEffect.h"
#include "game object\\GameObject.h"
#include "game object\\ShopItem.h"
#include "game object\\GameItem.h"
#include "game object\\ObjectOnCursor.h"
#include "Walker.h"
#include "game object\\GameCharacter.h"
#include "Skills.h"
#include "game object\\GamePlayer.h"
#include "game object\\GameWorld.h"
#include "ToolTip.h"
#include "game object\\ClickObject.h"
#include "Target.h"
#include "Party.h"
#include "ServerList.h"
#include "CharacterList.h"
#include "Profession.h"
#include "Target.h"
#include "SkillGroup.h"
#include "Weather.h"
#include "MapBlock.h"
#include "Container.h"
#include "QuestArrow.h"
#include "MultiMap.h"
#include "PathFinder.h"
#include "Macro.h"
#include "CityList.h"
#include "ScreenshotBuilder.h"
#include "VideoRecorder.h"
#include "gump\\GumpObject.h"
#include "gump\\Gump.h"
#include "gump\\GumpPaperdoll.h"
#include "gump\\GumpMinimap.h"
#include "gump\\GumpDrag.h"
#include "gump\\GumpContainer.h"
#include "gump\\GumpGrayMenu.h"
#include "gump\\GumpMenu.h"
#include "gump\\GumpMenubar.h"
#include "gump\\GumpNotify.h"
#include "gump\\GumpQuestion.h"
#include "gump\\GumpSelectFont.h"
#include "gump\\GumpStatusbar.h"
#include "gump\\GumpJournal.h"
#include "gump\\GumpOptions.h"
#include "gump\\GumpSecureTrading.h"
#include "gump\\GumpSelectColor.h"
#include "gump\\GumpSpell.h"
#include "gump\\GumpSpellbook.h"
#include "gump\\GumpTextEntryDialog.h"
#include "gump\\GumpTip.h"
#include "gump\\GumpGeneric.h"
#include "gump\\GumpSkills.h"
#include "gump\\GumpBuy.h"
#include "gump\\GumpSell.h"
#include "gump\\GumpMap.h"
#include "gump\\GumpDye.h"
#include "gump\\GumpProfile.h"
#include "gump\\GumpPartyManifest.h"
#include "gump\\GumpBook.h"
#include "gump\\GumpBulletinBoard.h"
#include "gump\\GumpBulletinBoardItem.h"
#include "gump\\GumpWorldMap.h"
#include "gump\\GumpTargetSystem.h"
#include "gump\\GumpPopupMenu.h"
#include "gump\\GumpConsoleType.h"
#include "gump\\GumpBuff.h"
#include "screen stages\\BaseScreen.h"
#include "screen stages\\DebugScreen.h"
#include "screen stages\\MainScreen.h"
#include "screen stages\\ConnectionScreen.h"
#include "screen stages\\ServerScreen.h"
#include "screen stages\\CharacterListScreen.h"
#include "screen stages\\CreateCharacterScreen.h"
#include "screen stages\\SelectProfessionScreen.h"
#include "screen stages\\SelectTownScreen.h"
#include "screen stages\\GameScreen.h"
#include "screen stages\\GameBlockedScreen.h"
#include "managers\\CreateCharacterManager.h"
#include "managers\\SkillGroupManager.h"
#include "managers\\GumpManager.h"
#include "managers\\EffectManager.h"
#include "managers\\ColorManager.h"
#include "managers\\ClilocManager.h"
#include "managers\\ConfigManager.h"
#include "managers\\FontsManager.h"
#include "managers\\AnimationManager.h"
#include "managers\\MapManager.h"
#include "managers\\MouseManager.h"
#include "managers\\MulReader.h"
#include "managers\\SoundManager.h"
#include "managers\\MacroManager.h"
#include "managers\\OptionsMacroManager.h"
#include "managers\\CityManager.h"
#include "managers\\PluginManager.h"
#include "managers\\ProfessionManager.h"
#include "managers\\SpeechManager.h"
#include "ShaderData.h"
#include "ClientUO.h"
//---------------------------------------------------------------------------
#endif
