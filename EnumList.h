/****************************************************************************
**
** EnumList.h
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
#ifndef EnumListH
#define EnumListH
//---------------------------------------------------------------------------
//!�� ����� ������ ��������� ������ (� ������ ������)
enum GAME_STATE
{
	GS_MAIN = 0,			//!�������� ���� (������ ������ ���������)
	GS_MAIN_CONNECT,		//!���� �������� � ������� �����������
	GS_SERVER,				//!���� ������ ��������
	GS_SERVER_CONNECT,		//!���� �������� � ���� �������
	GS_CHARACTER,			//!���� ������� �����
	GS_DELETE,				//!���� �������� ���������
	GS_PROFESSION_SELECT,	//!���� ������ ���������
	GS_CREATE,				//!���� �������� ���������
	GS_SELECT_TOWN,			//!���� ������ ���������� ������
	GS_GAME_CONNECT,		//!���� ����� � ����
	GS_GAME,				//!������� ���� (����������� ���� � �������)
	GS_GAME_BLOCKED			/*!����������� �������� �����, �� ������������, �� �������������
							��� ������, ����������� � ��������� ����-����, ����� ����� (������)
							���������� ��� ������ �������
							*/
};
//---------------------------------------------------------------------------
//!��� ���������� ������� ��� �������
enum SELECT_OBJECT_TYPE
{
	SOT_NO_OBJECT = 0,		//!������ �� �������
	SOT_GAME_GUMP_SCOPE,	//!����� �������� ����
	SOT_GAME_OBJECT,		//!������� ������
	SOT_STATIC_OBJECT,		//!�������
	SOT_LAND_OBJECT,		//!��������
	SOT_TEXT_OBJECT			//!�����
};
//---------------------------------------------------------------------------
//!��� ������� ��� �������
enum RENDER_OBJECT_TYPE
{
	ROT_NO_OBJECT = 0,		//������ �� �������
	ROT_GAME_OBJECT,		//������� ������
	ROT_STATIC_OBJECT,		//�������
	ROT_LAND_OBJECT,		//��������
	ROT_MULTI_OBJECT,		//������
	ROT_EFFECT				//������
};
//---------------------------------------------------------------------------
//!��� ������� ������
enum SCAN_TYPE_OBJECT
{
	STO_HOSTLE = 0,
	STO_PARTY,
	STO_FOLLOWERS,
	STO_OBJECTS,
	STO_MOBILES
};
//---------------------------------------------------------------------------
//!��� ������ �������
enum SCAN_MODE_OBJECT
{
	SMO_NEXT = 0,
	SMO_PREV,
	SMO_NEAREST
};
//---------------------------------------------------------------------------
//!��� �������
enum EFFECT_TYPE
{
	EF_MOVING = 0,		//!��������
	EF_LIGHTING,		//!���� �������
	EF_STAY_AT_POS,		//!����� �� �����
	EF_STAY_AT_SOURCE,	//!�������� � ���������
	EF_DRAG				//!�������� ����������� ��������
};
//---------------------------------------------------------------------------
//!��� ����������
enum ENCRYPTION_TYPE
{
	ET_NOCRYPT = 0,	//!��� ����������
	ET_OLD_BFISH,	//!������ BlowFish
	ET_1_25_36,		//!����������� ��� ������� 1.25.36 (BlowFish, ������� �������� ����� ����������)
	ET_BFISH,		//!����������� BlowFish
	ET_203,			//!����������� ��� 2.0.3 ������� (BlowFish + TwoFish ��� MD5)
	ET_TFISH		//!TwoFish + MD5
};
//---------------------------------------------------------------------------
//!������ ������� (��� ��������� � ��������� � ������ ������)
enum CLIENT_VERSION
{
	CV_OLD = 0,		//�������������� ������� 2.0.0, ��������� �� ������, ������ �� ��������
	CV_200,			//������������ ����� � ���������� ������
	CV_305D,		//������������� ��������, ���������� ������ � ������ ���������� ����� ���������� ����������
	CV_306E,		//�������� ����� � ����� ������� (0xBF subcmd 0x0F)
	CV_308D,		//�������� �������� Maximum Stats � ���������
	CV_308J,		//�������� �������� Followers � ���������
	CV_308Z,		//��������� ������ paladin, necromancer; custom houses, 5 resistances, �������� ���� ������ ���������, ������ ������� Save Password
	CV_400B,		//�������� ��������
	CV_405A,		//��������� ������ ninja, samurai
	CV_4011D,		//��������� ���� �������� ���������. ��������� ����� elves
	CV_500A,		//������ ���������� ��������: Journal -> Quests; Chat -> Guild, ������������� Mega Cliloc
	CV_5020,		//�������� ���� �����
	CV_5090,		//
	CV_6000,		//��������� ����� �����/���� ����, ������ �����. ��������� ����� ����� ������ �������, ����� ������� ���������, Object Handles,
	CV_6013,		//
	CV_6017,		//
	CV_6040,		//����������� ���������� ������ ����������
	CV_6060,		//
	CV_60142,		//
	CV_60144,		//��������� ���� �������� ���������. ��������� ����� gargoyle
	CV_7000,		//
	CV_7090,		//
	CV_70130,		//
	CV_70160,		//
	CV_70180,		//
	CV_70240,		//*.mul -> *.uop
	CV_70331		//
};
//---------------------------------------------------------------------------
//!�� ����� ������ ��������� ���� ��������
enum CONNECTION_SCREEN_TYPE
{
	CST_LOGIN = 0,
	CST_CHARACTER_LIST,
	CST_CONLOST,
	CST_SELECT_PROFESSOIN,
	CST_GAME_LOGIN,
	CST_GAME
};
//---------------------------------------------------------------------------
//!���� ���������
enum PROFESSION_TYPE
{
	PT_NO_PROF = 0,
	PT_CATEGORY,
	PT_PROFESSION
};
//---------------------------------------------------------------------------
//!��������� �����
enum CHARACTER_RACE_TYPE
{
	CRT_HUMAN = 0,
	CRT_ELVEN,
	CRT_GARGOYLE
};
//---------------------------------------------------------------------------
//!��������� ClientFlag ��� �������� ��� �������� ���������
enum CLIENT_FLAG
{
	CF_T2A = 0x00,
	CF_RE = 0x01,
	CF_TD = 0x02,
	CF_LBR = 0x04,
	CF_AOS = 0x08,
	CF_SE = 0x10,
	CF_SA = 0x20,
	CF_UO3D = 0x40,
	CF_RESERVED = 0x80,
	CF_3D = 0x100
};
//---------------------------------------------------------------------------
//!��������� client features
enum LOCKED_FEATURE_FLAG
{
	LFF_T2A = 0x01,
	LFF_RE = 0x02,
	LFF_TD = 0x04,
	LFF_LBR = 0x08,
	LFF_AOS = 0x10,
	LFF_6_SLOT = 0x20,
	LFF_SE = 0x40,
	LFF_ML = 0x80,
	LFF_8_AGE = 0x100,
	LFF_9_AGE = 0x200,
	LFF_10_AGE = 0x400,
	LFF_HOUSING = 0x800,
	LFF_7_SLOT = 0x1000,
	LFF_KR = 0x2000,
	LFF_TRIAL_ACC = 0x4000,
	LFF_11_AGE = 0x8000,
	LFF_SA = 0x10000,
	LFF_HSA = 0x20000,
	LFF_GOTHIC_HOUSING = 0x40000,
	LFF_RUSTIC_HOUSING = 0x80000
};
//---------------------------------------------------------------------------
//!���� �������� ��� �������
enum SPELLBOOK_TYPE
{
	ST_MAGE = 1,
	ST_NECRO,
	ST_PALADIN,
	ST_BUSHIDO,
	ST_NINJITSU,
	ST_SPELL_WEAVING,
	ST_MYSTICISM
};
//---------------------------------------------------------------------------
//!��������� �������� ������������ �������
enum SMOOTH_MONITOR_TYPE
{
	SMT_NONE = 0,
	SMT_SUNRISE,
	SMT_SUNSET
};
//---------------------------------------------------------------------------
//!��������� �������� ������������ �������
enum WEATHER_TYPE
{
	WT_RAIN = 0,
	WT_FIERCE_STORM,
	WT_SNOW,
	WT_STORM
};
//---------------------------------------------------------------------------
//!���� ������
enum GUMP_TYPE
{
	GT_NONE = 0,			//!��� �����
	GT_PAPERDOLL,			//!��������� 95%
	GT_STATUSBAR,			//!������ ��� (��� ����) 100%
	GT_DYE,					//!���� ������ ����� 100% (�������� ������� �� GT_SELECT_COLOR)
	GT_OPTIONS,				//!����� 90%
	GT_GENERIC,				//!���� �� ������� 100%
	GT_MENU,				//!���� �� ������� 100%
	GT_GRAY_MENU,			//!"�����" ���� �� ������� (�����������) 100%
	GT_TRADE,				//!����� ���� 100%
	GT_SHOP,				//!����� �������/������� 100% / 100%
	GT_MINIMAP,				//!����-����� 100%
	GT_MAP,					//!����� (�������/������) 90%
	GT_SKILLS,				//!������ 100%
	GT_JOURNAL,				//!������ 100%
	GT_CONTAINER,			//!���������� 100%
	GT_SPELLBOOK,			//!��������� 100%
	GT_SPELL,				//!������ ������ 100%
	GT_DRAG,				//!���������� ��������� ��������� (������ 1 ����� � �����) 100%
	GT_TEXT_ENTRY_DIALOG,	//!���� ����� ������ �� ������� (�����������) 100%
	GT_QUESTION,			//!���� ������� (�����������) 100%
	GT_SELECT_COLOR,		//!���� ������ ����� (��� �����) 100%
	GT_SELECT_FONT,			//!���� ������ ������ (��� �����) 100%
	GT_NOTIFY,				//!���� ��������� (�����������) 100%
	GT_BOOK,				//!���� ���� 10%
	GT_TIP,					//!Tip window 90%
	GT_PARTY_MANIFEST,		//!���� �������� ���� 100%
	GT_MAIL,				//!���� ����� 0%
	GT_PROFILE,				//!���� ������� 100%
	GT_MENUBAR,				//!���� �������� 90%
	GT_BUFF,				//!���� ������ 0%
	GT_CHAT,				//!���� ���� 0%
	GT_BULLETIN_BOARD,		//!���� ����� ���������� 100%
	GT_BULLETIN_BOARD_ITEM,	//!���� �������� ����� ���������� 100%
	GT_WORLD_MAP,			//!���� ����� ���� 100%
	GT_PLUGIN,				//!����� �������� 0%
	GT_TARGET_SYSTEM,		//!���� ������ ������� (���������) 100%
	GT_POPUP_MENU			//!���� ������������ ���� 80%
};
//---------------------------------------------------------------------------
//!���� �������� ������
enum GUMP_OBJECT_TYPE
{
	GOT_NONE = 0,			//!��� ����
	GOT_PAGE,				//!������������� ��������
	GOT_GROUP,				//!������������� ������ (��� �����-������)
	GOT_ENDGROUP,			//!������������� ��������� ������
	GOT_MASTERGUMP,			//!���?
	GOT_RESIZEPIC,			//!��� (������� �� 9 ������)
	GOT_CHECKTRANS,			//!�������������� ���� �� �����
	GOT_BUTTON,				//!������
	GOT_BUTTONTILEART,		//!������ � ���������
	GOT_CHECKBOX,			//!�������
	GOT_RADIO,				//!�����-������
	GOT_TILEPIC,			//!�������� �� �������
	GOT_TILEPICHUE,			//!�������� �� ������� (�������)
	GOT_GUMPPIC,			//!�������� �� �����
	GOT_GUMPPICTILED,		//!�������� �� ����� � �������
	GOT_TEXT,				//!����� (������, ��� � ��������� ������ ������)
	GOT_TEXTENTRY,			//!���� ������
	GOT_TEXTENTRYLIMITED,	//!����������� ���� ������
	GOT_CROPPEDTEXT,		//!������������ ���� ������ (� ���������� �� '...' ��� ������� ������ �� ������)
	GOT_HTMLGUMP,			//!���� ����
	GOT_XFMHTMLGUMP,		//!���� ���� �� ������� (������� ��� ��)
	GOT_XFMHTMLTOKEN,		//
	GOT_TOOLTIP,				//
	GOT_NOMOVE,
	GOT_NOCLOSE,
	GOT_NODISPOSE
};
//---------------------------------------------------------------------------
enum SELECT_COLOR_GUMP_STATE
{
	SCGS_OPT_POPUP_TEXT = 0,
	SCGS_OPT_TOOLTIP_TEXT,
	SCGS_OPT_CHAT_INPUT_TEXT,
	SCGS_OPT_CHAT_MENU_OPTION,
	SCGS_OPT_CHAT_PLAYER_IN_MEMBER_LIST,
	SCGS_OPT_CHAT_TEXT,
	SCGS_OPT_CHAT_PLAYER_WITHOUT_PRIV,
	SCGS_OPT_CHAT_MUTED_TEXT,
	SCGS_OPT_CHAT_CHAN_MODER_NAME,
	SCGS_OPT_CHAT_CHAN_MODER_TEXT,
	SCGS_OPT_CHAT_MY_NAME,
	SCGS_OPT_CHAT_MY_TEXT,
	SCGS_OPT_CHAT_SYSTEM_MESSAGE,
	SCGS_OPT_CHAT_BG_OUTPUT,
	SCGS_OPT_CHAT_BG_INPUT,
	SCGS_OPT_CHAT_BG_USER_LIST,
	SCGS_OPT_CHAT_BG_CONF_LIST,
	SCGS_OPT_CHAT_BG_COMMAND_LIST,
	SCGS_OPT_DISPLAY_SPEECH,
	SCGS_OPT_DISPLAY_EMOTE,
	SCGS_OPT_DISPLAY_PARTY_MESSAGE,
	SCGS_OPT_DISPLAY_GUILD_MESSAGE,
	SCGS_OPT_DISPLAY_ALLIANCE_MESSAGE,
	SCGS_OPT_REPSYS_INNOCENT,
	SCGS_OPT_REPSYS_FRIENDLY,
	SCGS_OPT_REPSYS_SOMEONE,
	SCGS_OPT_REPSYS_CRIMINAL,
	SCGS_OPT_REPSYS_ENEMY,
	SCGS_OPT_REPSYS_MURDERER
};
//---------------------------------------------------------------------------
enum SELECT_FONT_GUMP_STATE
{
	SFGS_OPT_POPUP = 1,
	SFGS_OPT_TOOLTIP,
	SFGS_OPT_CHAT,
	SFGS_OPT_MISCELLANEOUS
};
//---------------------------------------------------------------------------
enum MAP_MESSAGE
{
	MM_ADD = 1,
	MM_INSERT,
	MM_MOVE,
	MM_REMOVE,
	MM_CLEAR,
	MM_EDIT,
	MM_EDIT_RESPONSE
};
//------------------------------------------------------------------------------
//!���� ��������� ���������
enum OBJECT_LAYERS
{
	OL_NONE = 0,	//0
	OL_1_HAND,		//1
	OL_2_HAND,		//2
	OL_SHOES,		//3
	OL_PANTS,		//4
	OL_SHIRT,		//5
	OL_HELMET,		//6
	OL_GLOVES,		//7
	OL_RING,		//8
	OL_TALISMAN,	//9
	OL_NECKLACE,	//10
	OL_HAIR,		//11
	OL_WAIST,		//12
	OL_TORSO,		//13
	OL_BRACELET,	//14
	OL_15,			//15
	OL_BEARD,		//16
	OL_TUNIC,		//17
	OL_EARRINGS,	//18
	OL_ARMS,		//19
	OL_CLOAK,		//20
	OL_BACKPACK,	//21
	OL_ROBE,		//22
	OL_SKIRT,		//23
	OL_LEGS,		//24
	OL_MOUNT,		//25
	OL_BUY_RESTOCK,	//26
	OL_BUY,			//27
	OL_SELL,		//28
	OL_BANK			//29
};
//------------------------------------------------------------------------------
//!���� ��������� ���������
enum SPEECH_TYPE
{
	ST_NORMAL = 0,
	ST_BROADCAST,				//System
	ST_EMOTE,					//Emote
	ST_SYSTEM = 0x06,			//System / Lower Corner
	ST_SYSTEM_WHITE_NAME = 0x07,//Message / Corner With Name
	ST_WHISPER = 0x08,			//Whisper
	ST_YELL = 0x09,				//Yell
	ST_SPELL = 0x0A,			//Spell
	ST_GUILD_CHAT = 0x0D,		//Guild Chat
	ST_ALLIANCE_CHAT = 0x0E,	//Alliance Chat
	ST_COMMAND_PROMT = 0x0F,	//Command Prompts
	ST_ENCODED_COMMAND = 0xC0,	//Encoded Commands
};
//---------------------------------------------------------------------------
enum TEXT_TYPE
{
	TT_CLIENT = 0,
	TT_SYSTEM,
	TT_OBJECT
};
//---------------------------------------------------------------------------
enum TEXT_ALIGN_TYPE
{
	TS_LEFT = 0,
	TS_CENTER,
	TS_RIGHT
};
//---------------------------------------------------------------------------
//!���� ��������
enum PROMPT_TYPE
{
	PT_NONE = 0,
	PT_ASCII,
	PT_UNICODE
};
//---------------------------------------------------------------------------
enum MOUSE_WHEEL_STATE
{
	MWS_UP = 0,
	MWS_DOWN,
	MWS_PRESS
};
//---------------------------------------------------------------------------
//!����������� ����
enum DIRECTION_TYPE
{
	DT_N = 0,
	DT_NE,
	DT_E,
	DT_SE,
	DT_S,
	DT_SW,
	DT_W,
	DT_NW
};
//---------------------------------------------------------------------------
enum ANIMATION_GROUPS
{
	AG_NONE = 0,
	AG_LOW,
	AG_HIGHT,
	AG_PEOPLE
};
//---------------------------------------------------------------------------
enum LOW_ANIMATION_GROUP
{
	LAG_WALK = 0,
	LAG_RUN,
	LAG_STAND,
	LAG_EAT,
	LAG_UNKNOWN,
	LAG_ATTACK_1,
	LAG_ATTACK_2,
	LAG_ATTACK_3,
	LAG_DIE_1,
	LAG_FIDGET_1,
	LAG_FIDGET_2,
	LAG_LIE_DOWN,
	LAG_DIE_2
};
//---------------------------------------------------------------------------
enum HIGHT_ANIMATION_GROUP
{
	HAG_WALK = 0,
	HAG_STAND,
	HAG_DIE_1,
	HAG_DIE_2,
	HAG_ATTACK_1,
	HAG_ATTACK_2,
	HAG_ATTACK_3,
	HAG_MISC_1,
	HAG_MISC_2,
	HAG_MISC_3,
	HAG_STUMBLE,
	HAG_SLAP_GROUND,
	HAG_CAST,
	HAG_GET_HIT_1,
	HAG_MISC_4,
	HAG_GET_HIT_2,
	HAG_GET_HIT_3,
	HAG_FIDGET_1,
	HAG_FIDGET_2,
	HAG_FLY,
	HAG_LAND,
	HAG_DIE_IN_FLIGHT
};
//---------------------------------------------------------------------------
enum PEOPLE_ANIMATION_GROUP
{
	PAG_WALK_UNARMED = 0,
	PAG_WALK_ARMED,
	PAG_RUN_UNARMED,
	PAG_RUN_ARMED,
	PAG_STAND,
	PAG_FIDGET_1,
	PAG_FIDGET_2,
	PAG_STAND_ONEHANDED_ATTACK,
	PAG_STAND_TWOHANDED_ATTACK,
	PAG_ATTACK_ONEHANDED,
	PAG_ATTACK_UNARMED_1,
	PAG_ATTACK_UNARMED_2,
	PAG_ATTACK_TWOHANDED_DOWN,
	PAG_ATTACK_TWOHANDED_WIDE,
	PAG_ATTACK_TWOHANDED_JAB,
	PAG_WALK_WARMODE,
	PAG_CAST_DIRECTED,
	PAG_CAST_AREA,
	PAG_ATTACK_BOW,
	PAG_ATTACK_CROSSBOW,
	PAG_GET_HIT,
	PAG_DIE_1,
	PAG_DIE_2,
	PAG_ONMOUNT_RIDE_SLOW,
	PAG_ONMOUNT_RIDE_FAST,
	PAG_ONMOUNT_STAND,
	PAG_ONMOUNT_ATTACK,
	PAG_ONMOUNT_ATTACK_BOW,
	PAG_ONMOUNT_ATTACK_CROSSBOW,
	PAG_ONMOUNT_SLAP_HORSE,
	PAG_TURN,
	PAG_ATTACK_UNARMED_AND_WALK,
	PAG_EMOTE_BOW,
	PAG_EMOTE_SALUTE,
	PAG_FIDGET_3
};
//---------------------------------------------------------------------------
//!��������� ���������
enum NOTORIETY_TYPE
{
	NT_NONE = 0,
	NT_INNOCENT,
	NT_FRIENDLY,
	NT_SOMEONE_GRAY,
	NT_CRIMINAL,
	NT_ENEMY,
	NT_MURDERER,
	NT_INVULNERABLE
};
//---------------------------------------------------------------------------
enum CLICK_OBJECT_TYPE
{
	COT_NONE = 0,
	COT_GAME_OBJECT,
	COT_STATIC,
	COT_GUMP
};
//---------------------------------------------------------------------------
enum MACRO_CODE
{
	MC_NONE = 0,
	MC_SAY,
	MC_EMOTE,
	MC_WHISPER,
	MC_YELL,
	MC_WALK,
	MC_WAR_PEACE,
	MC_PASTE,
	MC_OPEN,
	MC_CLOSE,
	MC_MINIMIZE,
	MC_MAXIMIZE,
	MC_OPEN_DOOR,
	MC_USE_SKILL,
	MC_LAST_SKILL,
	MC_CAST_SPELL,
	MC_LAST_SPELL,
	MC_LAST_OBJECT,
	MC_BOW,
	MC_SALUTE,
	MC_QUIT_GAME,
	MC_ALL_NAMES,
	MC_LAST_TARGET,
	MC_TARGET_SELF,
	MC_ARM_DISARM,
	MC_WAIT_FOR_TARGET,
	MC_TARGET_NEXT,
	MC_ATTACK_LAST,
	MC_DELAY,
	MC_CIRCLE_TRANS,
	MC_CLOSE_GUMPS,
	MC_ALWAYS_RUN,
	MC_SAVE_DESKTOP,
	MC_KILL_GUMP_OPEN,
	MC_PRIMARY_ABILITY,
	MC_SECONDARY_ABILITY,
	MC_EQUIP_LAST_WEAPON,
	MC_SET_UPDATE_RANGE,
	MC_MODIFY_UPDATE_RANGE,
	MC_INCREASE_UPDATE_RANGE,
	MC_DECREASE_UPDATE_RANGE,
	MC_MAX_UPDATE_RANGE,
	MC_MIN_UPDATE_RANGE,
	MC_DEFAULT_UPDATE_RANGE,
	MC_UPDATE_RANGE_INFO,
	MC_ENABLE_RANGE_COLOR,
	MC_DISABLE_RANGE_COLOR,
	MC_TOGGLE_RANGE_COLOR,
	MC_INVOKE_VIRTURE,
	MC_SELECT_NEXT,
	MC_SELECT_PREVEOUS,
	MC_SELECT_NEAREST,
	MC_ATTACK_SELECTED_TARGET,
	MC_USE_SELECTED_TARGET,
	MC_CURRENT_TARGET,
	MC_TARGET_SYSTEM_ON_OFF,
	MC_TOGGLE_BUICON_WINDOW,
	MC_BANDAGE_SELF,
	MC_BANDAGE_TARGET,
	MC_TOGGLE_GARGOYLE_FLYING
};
//---------------------------------------------------------------------------
enum MACRO_SUB_CODE
{
	MSC_NONE = 0,
	MSC_G1_NW, //Walk group
	MSC_G1_N,
	MSC_G1_NE,
	MSC_G1_E,
	MSC_G1_SE,
	MSC_G1_S,
	MSC_G1_SW,
	MSC_G1_W,
	MSC_G2_CONFIGURATION, //Open/Close/Minimize/Maximize group
	MSC_G2_PAPERDOLL,
	MSC_G2_STATUS,
	MSC_G2_JOURNAL,
	MSC_G2_SKILLS,
	MSC_G2_MAGE_SPELLBOOK,
	MSC_G2_CHAT,
	MSC_G2_BACKPACK,
	MSC_G2_OWERVIEW,
	MSC_G2_WORLD_MAP,
	MSC_G2_MAIL,
	MSC_G2_PARTY_MANIFEST,
	MSC_G2_PARTY_CHAT,
	MSC_G2_NECRO_SPELLBOOK,
	MSC_G2_PALADIN_SPELLBOOK,
	MSC_G2_COMBAT_BOOK,
	MSC_G2_BUSHIDO_SPELLBOOK,
	MSC_G2_NINJITSU_SPELLBOOK,
	MSC_G2_GUILD,
	MSC_G2_SPELL_WEAVING_SPELLBOOK,
	MSC_G2_QUEST_LOG,
	MSC_G2_MYSTICISM_SPELLBOOK,
	MSC_G2_RACIAL_ABILITIES_BOOK,
	MSC_G2_BARD_SPELLBOOK,
	MSC_G3_ANATOMY, //Skills group
	MSC_G3_ANIMAL_LORE,
	MSC_G3_ANIMAL_TAMING,
	MSC_G3_ARMS_LORE,
	MSC_G3_BEGGING,
	MSC_G3_CARTOGRAPHY,
	MSC_G3_DETECTING_HIDDEN,
	MSC_G3_ENTICEMENT,
	MSC_G3_EVALUATING_INTELLIGENCE,
	MSC_G3_FORENSIC_EVALUATION,
	MSC_G3_HIDING,
	MSC_G3_IMBUING,
	MSC_G3_INSCRIPTION,
	MSC_G3_ITEM_IDENTIFICATION,
	MSC_G3_MEDITATION,
	MSC_G3_PEACEMAKING,
	MSC_G3_POISONING,
	MSC_G3_PROVOCATION,
	MSC_G3_REMOVE_TRAP,
	MSC_G3_SPIRIT_SPEAK,
	MSC_G3_STEALING,
	MSC_G3_STEALTH,
	MSC_G3_TASTE_IDENTIFICATION,
	MSC_G3_TRACKING,
	MSC_G4_LEFT_HAND, ///Arm/Disarm group
	MSC_G4_RIGHT_HAND,
	MSC_G5_HONOR, //Invoke Virture group
	MSC_G5_SACRIFICE,
	MSC_G5_VALOR,
	MSC_G6_CLUMSY, //Cast Spell group
	MSC_G6_CREATE_FOOD,
	MSC_G6_FEEBLEMIND,
	MSC_G6_HEAL,
	MSC_G6_MAGIC_ARROW,
	MSC_G6_NIGHT_SIGHT,
	MSC_G6_REACTIVE_ARMOR,
	MSC_G6_WEAKEN,
	MSC_G6_AGILITY,
	MSC_G6_CUNNING,
	MSC_G6_CURE,
	MSC_G6_HARM,
	MSC_G6_MAGIC_TRAP,
	MSC_G6_MAGIC_UNTRAP,
	MSC_G6_PROTECTION,
	MSC_G6_STRENGTH,
	MSC_G6_BLESS,
	MSC_G6_FIREBALL,
	MSC_G6_MAGIC_LOCK,
	MSC_G6_POISON,
	MSC_G6_TELEKINESIS,
	MSC_G6_TELEPORT,
	MSC_G6_UNLOCK,
	MSC_G6_WALL_OF_STONE,
	MSC_G6_ARCH_CURE,
	MSC_G6_ARCH_PROTECTION,
	MSC_G6_CURSE,
	MSC_G6_FIRE_FIELD,
	MSC_G6_GREATER_HEAL,
	MSC_G6_LIGHTNING,
	MSC_G6_MANA_DRAIN,
	MSC_G6_RECALL,
	MSC_G6_BLADE_SPIRITS,
	MSC_G6_DISPELL_FIELD,
	MSC_G6_INCOGNITO,
	MSC_G6_MAGIC_REFLECTION,
	MSC_G6_MIND_BLAST,
	MSC_G6_PARALYZE,
	MSC_G6_POISON_FIELD,
	MSC_G6_SUMMON_CREATURE,
	MSC_G6_DISPEL,
	MSC_G6_ENERGY_BOLT,
	MSC_G6_EXPLOSION,
	MSC_G6_INVISIBILITY,
	MSC_G6_MARK,
	MSC_G6_MASS_CURSE,
	MSC_G6_PARALYZE_FIELD,
	MSC_G6_REVEAL,
	MSC_G6_CHAIN_LIGHTNING,
	MSC_G6_ENERGY_FIELD,
	MSC_G6_FLAME_STRIKE,
	MSC_G6_GATE_TRAVEL,
	MSC_G6_MANA_VAMPIRE,
	MSC_G6_MASS_DISPEL,
	MSC_G6_METEOR_SWARM,
	MSC_G6_POLYMORPH,
	MSC_G6_EARTHQUAKE,
	MSC_G6_ENERGY_VORTEX,
	MSC_G6_RESURRECTION,
	MSC_G6_AIR_ELEMENTAL,
	MSC_G6_SUMMON_DAEMON,
	MSC_G6_EARTH_ELEMENTAL,
	MSC_G6_FIRE_ELEMENTAL,
	MSC_G6_WATER_ELEMENTAL,
	MSC_G6_ANIMATE_DEAD,
	MSC_G6_BLOOD_OATH,
	MSC_G6_CORPSE_SKIN,
	MSC_G6_CURSE_WEAPON,
	MSC_G6_EVIL_OMEN,
	MSC_G6_HORRIFIC_BEAST,
	MSC_G6_LICH_FORM,
	MSC_G6_MIND_ROT,
	MSC_G6_PAIN_SPIKE,
	MSC_G6_POISON_STRIKE,
	MSC_G6_STRANGLE,
	MSC_G6_SUMMON_FAMILAR,
	MSC_G6_VAMPIRIC_EMBRACE,
	MSC_G6_VENGEFUL_SPIRIT,
	MSC_G6_WITHER,
	MSC_G6_WRAITH_FORM,
	MSC_G6_EXORCISM,
	MSC_G6_CLEANCE_BY_FIRE,
	MSC_G6_CLOSE_WOUNDS,
	MSC_G6_CONSECRATE_WEAPON,
	MSC_G6_DISPEL_EVIL,
	MSC_G6_DIVINE_FURY,
	MSC_G6_ENEMY_OF_ONE,
	MSC_G6_HOLY_LIGHT,
	MSC_G6_NOBLE_SACRIFICE,
	MSC_G6_REMOVE_CURSE,
	MSC_G6_SACRED_JOURNEY,
	MSC_G6_HONORABLE_EXECUTION,
	MSC_G6_CONFIDENCE,
	MSC_G6_EVASION,
	MSC_G6_COUNTER_ATTACK,
	MSC_G6_LIGHTING_STRIKE,
	MSC_G6_MOMENTUM_STRIKE,
	MSC_G6_FOCUS_ATTACK,
	MSC_G6_DEATH_STRIKE,
	MSC_G6_ANIMAL_FORM,
	MSC_G6_KI_ATTACK,
	MSC_G6_SURPRICE_ATTACK,
	MSC_G6_BACKSTAB,
	MSC_G6_SHADOWJUMP,
	MSC_G6_MIRROR_IMAGE,
	MSC_G6_ARCANE_CIRCLE,
	MSC_G6_GIFT_OF_RENEWAL,
	MSC_G6_IMMOLATING_WEAPON,
	MSC_G6_ATTUNEMENT,
	MSC_G6_THUNDERSTORM,
	MSC_G6_NATURES_FURY,
	MSC_G6_SUMMON_FEY,
	MSC_G6_SUMMON_FIEND,
	MSC_G6_REAPER_FORM,
	MSC_G6_WILDFIRE,
	MSC_G6_ESSENCE_OF_WIND,
	MSC_G6_DRYAD_ALLURE,
	MSC_G6_ETHEREAL_VOYAGE,
	MSC_G6_WORD_OF_DEATH,
	MSC_G6_GIFT_OF_LIFE,
	MSC_G6_ARCANE_EMPOWERMEN,
	MSC_G6_NETHER_BOLT,
	MSC_G6_HEALING_STONE,
	MSC_G6_PURGE_MAGIC,
	MSC_G6_ENCHANT,
	MSC_G6_SLEEP,
	MSC_G6_EAGLE_STRIKE,
	MSC_G6_ANIMATED_WEAPON,
	MSC_G6_STONE_FORM,
	MSC_G6_SPELL_TRIGGER,
	MSC_G6_MASS_SLEEP,
	MSC_G6_CLEANSING_WINDS,
	MSC_G6_BOMBARD,
	MSC_G6_SPELL_PLAGUE,
	MSC_G6_HAIL_STORM,
	MSC_G6_NETHER_CYCLONE,
	MSC_G6_RISING_COLOSSUS,
	MSC_G6_INSPIRE,
	MSC_G6_INVIGORATE,
	MSC_G6_RESILIENCE,
	MSC_G6_PERSEVERANCE,
	MSC_G6_TRIBULATION,
	MSC_G6_DESPAIR,
	MSC_G7_HOSTLE, //Select Next/Preveous/Nearest group
	MSC_G7_PARTY,
	MSC_G7_FOLLOWER,
	MSC_G7_OBJECT,
	MSC_G7_MOBILE
};
//---------------------------------------------------------------------------
enum MACRO_RETURN_CODE
{
	MRC_PARSE_NEXT = 0,
	MRC_BREAK_PARSER,
	MRC_STOP
};
//---------------------------------------------------------------------------
enum GAME_CONSOLE_TEXT_TYPE
{
	GCTT_NORMAL = 0,
	GCTT_YELL,
	GCTT_WHISPER,
	GCTT_EMOTE,
	GCTT_C,
	GCTT_BROADCAST,
	GCTT_PARTY,
	GCTT_PARTY_ACCEPT,
	GCTT_PARTY_DECLINE
};
//---------------------------------------------------------------------------
#endif
