/***********************************************************************************
**
** ConfigManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
//----------------------------------------------------------------------------------
//!����� ��������� �������
class CConfigManager
{
	SETGETE(bool, Sound, OnChangedSound);
	SETGETE(bool, Music, OnChangedMusic);
	SETGET(bool, FootstepsSound);
	SETGET(bool, CombatMusic);
	SETGETE(uchar, SoundVolume, OnChangedSoundVolume);
	SETGETE(uchar, MusicVolume, OnChangedMusicVolume);

	SETGETE(uchar, ClientFPS, OnChangeClientFPS);
	SETGETE(bool, UseScaling, OnChangeUseScaling);
	SETGET(bool, RemoveTextWithBlending);
	SETGETE(uchar, DrawStatusState, OnChangeDrawStatusState);
	SETGETE(bool, DrawStumps, OnChangeDrawStumps);
	SETGET(bool, NoAnimateFields);
	SETGETE(bool, MarkingCaves, OnChangeMarkingCaves);
	SETGETE(bool, ReduceFPSUnactiveWindow, OnChangeReduceFPSUnactiveWindow);
	SETGET(bool, StandartCharactersAnimationDelay);
	SETGET(bool, StandartItemsAnimationDelay);
	SETGET(bool, LockGumpsMoving);
	SETGETE(bool, ConsoleNeedEnter, OnChangeConsoleNeedEnter);

	SETGET(bool, UseToolTips);
	SETGET(ushort, ToolTipsTextColor);
	SETGET(ushort, ToolTipsTextFont);
	SETGET(ushort, ToolTipsDelay);

	SETGET(ushort, ChatColorInputText);
	SETGET(ushort, ChatColorMenuOption);
	SETGET(ushort, ChatColorPlayerInMemberList);
	SETGET(ushort, ChatColorText);
	SETGET(ushort, ChatColorPlayerNameWithout);
	SETGET(ushort, ChatColorMuted);
	SETGET(ushort, ChatColorChannelModeratorName);
	SETGET(ushort, ChatColorChannelModeratorText);
	SETGET(ushort, ChatColorMyName);
	SETGET(ushort, ChatColorMyText);
	SETGET(ushort, ChatColorSystemMessage);
	SETGET(ushort, ChatFont);
	SETGET(ushort, ChatColorBGOutputText);
	SETGET(ushort, ChatColorBGInputText);
	SETGET(ushort, ChatColorBGUserList);
	SETGET(ushort, ChatColorBGConfList);
	SETGET(ushort, ChatColorBGCommandList);

	SETGET(bool, EnablePathfind);
	SETGET(bool, HoldTabForCombat);
	SETGET(bool, OffsetInterfaceWindows);
	SETGET(bool, AutoArrange);
	SETGET(bool, AlwaysRun);
	SETGET(bool, DisableMenubar);
	SETGET(bool, GrayOutOfRangeObjects);
	SETGET(bool, DisableNewTargetSystem);
	SETGET(uchar, ItemPropertiesMode);
	SETGET(bool, ItemPropertiesIcon);
	SETGET(bool, ObjectHandles);
	SETGET(bool, HoldShiftForContextMenus);
	SETGET(bool, HoldShiftForEnablePathfind);

	SETGET(int, GameWindowWidth);
	SETGET(int, GameWindowHeight);
	SETGET(ushort, SpeechDelay);
	SETGET(bool, ScaleSpeechDelay);
	SETGET(ushort, SpeechColor);
	SETGET(ushort, EmoteColor);
	SETGET(ushort, PartyMessageColor);
	SETGET(ushort, GuildMessageColor);
	SETGET(ushort, AllianceMessageColor);
	SETGET(bool, IgnoreGuildMessage);
	SETGET(bool, IgnoreAllianceMessage);
	SETGET(bool, DarkNights);
	SETGET(bool, ColoredLighting);
	SETGET(bool, LockResizingGameWindow);

	SETGET(ushort, InnocentColor);
	SETGET(ushort, FriendlyColor);
	SETGET(ushort, SomeoneColor);
	SETGET(ushort, CriminalColor);
	SETGET(ushort, EnemyColor);
	SETGET(ushort, MurdererColor);
	SETGET(bool, CriminalActionsQuery);

	SETGET(bool, ShowIncomingNames);
	SETGET(bool, UseCircleTrans);
	SETGET(bool, StatReport);
	SETGET(uchar, CircleTransRadius);
	SETGET(uchar, SkillReport);
	SETGET(ushort, SpeechFont);

	SETGET(bool, FilterPWOn);
	SETGET(bool, ObscenityFilter);
	SETGET(string, FilterPassword);

	SETGET(bool, ToggleBufficonWindow);
	SETGET(int, GameWindowX);
	SETGET(int, GameWindowY);
	SETGET(int, UpdateRange);

public:
	CConfigManager();
	~CConfigManager() {}

	/*!
	�������������
	@return 
	*/
	void Init();

	//!������������ �������� ��-���������
	void DefaultPage1();
	void DefaultPage2();
	void DefaultPage3();
	void DefaultPage4();
	//5 ����
	void DefaultPage6();
	void DefaultPage7();
	void DefaultPage8();
	void DefaultPage9();
	//10 ����

	/*!
	�������� ���� ������ �� "���������"
	@param [__in] notoriety ���������
	@return ������ �����
	*/
	ushort GetColorByNotoriety(uchar notoriety);

	/*!
	�������� �������
	@param [__in] path ���� � ����� � ��������
	@return 
	*/
	bool Load(string path);

	/*!
	���������� �������
	@param [__in] path ���� � ����� � ��������
	@return 
	*/
	void Save(string path);
 };
 //----------------------------------------------------------------------------------
//!�������� �������
extern CConfigManager g_ConfigManager;

//!�������� ������� ��� �����
extern CConfigManager g_OptionsConfig;
//----------------------------------------------------------------------------------
#endif