/****************************************************************************
**
** Constants.h
**
** Copyright (C) February 2016 Hotride
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
#ifndef ConstantsH
#define ConstantsH
//---------------------------------------------------------------------------
//������������ ���������� ����� �� ������
static const int MAX_SHADOWS_COUNT = 100;

//����������� ���������� ���������� ����� �� ������
const int MAX_LIGHT_SOURCES = 100;

//������������ ������ fastwalk �����
const int MAX_FAST_WALK_STACK_SIZE = 255;

//�������� ��� �������� �������� ��������� �� ��� X
const int SITTING_WIDTH_OFFSET = 10;

//������������ ������ ������ ��� ������ ��� ������ � ���� (����� TFileWriter)
const int MAX_FILE_BUFFER_SIZE = 0x1000;

//������������ ������ ������
const int SIZE_VARIABLE = 0;

//������ ������� ��� ������ �������
const int UNICODE_SPACE_WIDTH = 8;

//������������ ��� ������� ������� ������
const float ITALIC_FONT_KOEFFICIENT = 3.3f;

//����������� ��������� ������ HTML ������
const int MAX_HTML_TEXT_HEIGHT = 18;

//�������� �� ������� �������� �� ������ ������� ������ (��� ������)
const int GAME_FIGURE_GUMP_OFFSET = 11369;

//������������ ������ ���������� ��������� �� ������� ����
const int TEXT_MESSAGE_MAX_WIDTH = 190;

//����� ����� ������� ������
const DWORD DEATH_SCREEN_DELAY = 3000;

//�������� ����� ������� ��� ��������� ���� ����������
const int FRAME_DELAY_ACTIVE_WINDOW = 30;

//�������� ����� ������� ��� ����������� ���� ����������
const int FRAME_DELAY_UNACTIVE_WINDOW = (FRAME_DELAY_ACTIVE_WINDOW + 1) * 7;

//�������� �������� � �������
static int g_FrameDelay[2] = { FRAME_DELAY_UNACTIVE_WINDOW, FRAME_DELAY_ACTIVE_WINDOW };

//���� ���������� ���������
const WORD SELECT_LAND_COLOR = 0x0044;

//���� ��������� �������
const WORD SELECT_STATIC_COLOR = 0x0077;

//���� ���������� ������-�������
const WORD SELECT_MULTI_COLOR = 0x0066;

//�������� ������ ��� ��������� �������� ����
const int MALE_GUMP_OFFSET = 50000;

//�������� ������ ��� ��������� �������� ����
const int FEMALE_GUMP_OFFSET = 60000;

//��������� �� ��������-�����������, ���� ������� ���� ������ ���������
const int REMOVE_CONTAINER_GUMP_RANGE = 3;

//������������ ����������� ������ �������
const int g_MaxBlockZ = 15;

//������������ ������, �� ������� ����� ���������
const int g_MaxClimbZ = 9;

//������������ ������, �� ������� ����� ������
const int g_MaxFallZ = 19;

//������������ ������ ������
const int g_MaxClimbMapZ = 19;

//������ ���������
const int DEFAULT_CHARACTER_HEIGHT = 16;

//�������� ��� ����������� ����� �� ������
const int STEP_DELAY_MOUNT_RUN = 85;

//�������� ��� ����������� ������ �� ������
const int STEP_DELAY_MOUNT_WALK = 185;

//�������� ��� ����������� �����
const int STEP_DELAY_RUN = 185;

//�������� ��� ����������� ������
const int STEP_DELAY_WALK = 385;

//������� �������� �����������
const int CHARACTER_ANIMATION_DELAY_TABLE[2][2] =
{
	//without mount
	{
		//walk
		STEP_DELAY_WALK,
		//run
		STEP_DELAY_RUN
	},
	//on mount
	{
		//walk
		STEP_DELAY_MOUNT_WALK,
		//run
		STEP_DELAY_MOUNT_RUN
	}
};

//�������� �� ������� ������� �����
const int DCLICK_DELAY = 350;

//�������� ����� ���������� ���������
const int SCROLL_LISTING_DELAY = 150;

//�������� ����� ���������� ���������� ��������� � ��������
const int CHANGE_SHOP_COUNT_DELAY = 50;

//�������� ����� ������ �������� � ������
const int CHANGE_MACRO_DELAY = 100;

//�������� ����� ���������� �������� � ������
const int CHANGE_MACRO_LIST_DELAY = 500;

//�������� ����� ��������� ���������� ������ � Ping (0x73) �������, 55 ������
const int SEND_TIMEOUT_DELAY = 55000;

//��� � �������� ��� ��������� ��������� � ����
const int GUMP_MENU_PIXEL_STEP = 5;

//��� � �������� ��� ��������� ���������
const int GUMP_SCROLLING_PIXEL_STEP = 10;

//�����, ����� ������� ����������� �������� �������
const int CLEAR_TEXTURES_DELAY = 30000;

//������ ������
const int WEATHER_TIMER = (6 * 60 * 1000);

//������������ ����� �������� ��� ������� �� ������
const int WAIT_FOR_TARGET_DELAY = 2000;

//������ �����, ���������� �� �����
static const bool LAYER_UNSAFE[30] =
{
	false,   //0
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	false,
	true,
	true,
	true,
	false,
	false,
	true,
	true,
	true,
	true,
	false, //0x15
	true,
	true,
	true,
	false,
	false,
	false,
	false,
	false
};

//�������� �������
static const char *CITY_NAMES[9] =
{
	"Yew",
	"Minoc",
	"Britain",
	"Moonglow",
	"Trinsic",
	"Magincia",
	"Jhelom",
	"Skara Brae",
	"Vesper"
};

//�������� ������ ����������
static char SPELL_CIRCLES_NAMES[8][15] =
{
	"First Circle",
	"Second Circle",
	"Third Circle",
	"Fourth Circle",
	"Fifth Circle",
	"Sixth Circle",
	"Seventh Circle",
	"Eighth Circle"
};

//����������� �������� �� ����������
static const WORD SPELL_REAGENTS[64][4] =
{
	{ 0x0F7B, 0x0F88, 0, 0 },
	{ 0x0F84, 0x0F85, 0x0F86, 0 },
	{ 0x0F85, 0x0F88, 0, 0 },
	{ 0x0F84, 0x0F85, 0x0F8D, 0 },
	{ 0x0F7A, 0x0F88, 0, 0 },
	{ 0x0F8C, 0x0F8D, 0, 0 },
	{ 0x0F84, 0x0F8C, 0x0F8D, 0 },
	{ 0x0F84, 0x0F88, 0, 0 },
	{ 0x0F7B, 0x0F86, 0, 0 },
	{ 0x0F86, 0x0F88, 0, 0 },
	{ 0x0F84, 0x0F85, 0, 0 },
	{ 0x0F88, 0x0F8D, 0, 0 },
	{ 0x0F84, 0x0F8C, 0x0F8D, 0 },
	{ 0x0F7B, 0x0F8C, 0, 0 },
	{ 0x0F84, 0x0F85, 0x0F8C, 0 },
	{ 0x0F86, 0x0F88, 0, 0 },
	{ 0x0F84, 0x0F86, 0, 0 },
	{ 0x0F7A, 0x0F8C, 0, 0 },
	{ 0x0F8C, 0x0F7B, 0x0F84, 0 },
	{ 0x0F88, 0, 0, 0 },
	{ 0x0F7B, 0x0F86, 0, 0 },
	{ 0x0F7B, 0x0F86, 0, 0 },
	{ 0x0F7B, 0x0F8C, 0, 0 },
	{ 0x0F7B, 0x0F84, 0, 0 },
	{ 0x0F84, 0x0F85, 0x0F86, 0 },
	{ 0x0F84, 0x0F85, 0x0F86, 0x0F8C },
	{ 0x0F84, 0x0F88, 0x0F8C, 0 },
	{ 0x0F7A, 0x0F8D, 0x0F8C, 0 },
	{ 0x0F84, 0x0F85, 0x0F86, 0x0F8D },
	{ 0x0F7A, 0x0F86, 0x0F8C, 0 },
	{ 0x0F7A, 0x0F86, 0x0F8D, 0 },
	{ 0x0F7A, 0x0F7B, 0x0F86, 0 },
	{ 0x0F7A, 0x0F86, 0x0F88, 0 },
	{ 0x0F84, 0x0F7A, 0x0F8D, 0x0F8C },
	{ 0x0F7B, 0x0F84, 0x0F88, 0 },
	{ 0x0F84, 0x0F86, 0x0F8D, 0 },
	{ 0x0F7A, 0x0F86, 0x0F88, 0x0F8C },
	{ 0x0F84, 0x0F86, 0x0F8D, 0 },
	{ 0x0F7A, 0x0F88, 0x0F8D, 0 },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0 },
	{ 0x0F84, 0x0F86, 0x0F8C, 0 },
	{ 0x0F7A, 0x0F88, 0, 0 },
	{ 0x0F7A, 0x0F86, 0x0F8C, 0 },
	{ 0x0F7B, 0x0F88, 0, 0 },
	{ 0x0F7A, 0x0F7B, 0x0F86, 0 },
	{ 0x0F84, 0x0F86, 0x0F88, 0x0F8C },
	{ 0x0F7A, 0x0F85, 0x0F8D, 0 },
	{ 0x0F7B, 0x0F8C, 0, 0 },
	{ 0x0F7A, 0x0F86, 0x0F7B, 0x0F8C },
	{ 0x0F7A, 0x0F86, 0x0F8D, 0x0F8C },
	{ 0x0F8D, 0x0F8C, 0, 0 },
	{ 0x0F7A, 0x0F86, 0x0F8C, 0 },
	{ 0x0F7A, 0x0F7B, 0x0F86, 0x0F8D },
	{ 0x0F7A, 0x0F84, 0x0F86, 0x0F8C },
	{ 0x0F7B, 0x0F8D, 0x0F86, 0x0F8C },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0 },
	{ 0x0F7B, 0x0F85, 0x0F86, 0x0F8C },
	{ 0x0F7A, 0x0F7B, 0x0F86, 0x0F88 },
	{ 0x0F7B, 0x0F84, 0x0F85, 0 },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0 },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0x0F8C },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0 },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0x0F8C },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0 }
};

//������������ ����������
static char SPELL_CAST_ABBREVIATURE[64][8] =
{
	"U J",
	"I M Y",
	"R W",
	"I M",
	"I P Y",
	"I L",
	"S F",
	"D M",
	"E U",
	"U W",
	"A N",
	"A M",
	"I J",
	"A J",
	"U S",
	"U M",
	"R S",
	"V F",
	"A P",
	"I N",
	"O P Y",
	"R P",
	"E P",
	"I S Y",
	"W A N",
	"V U S",
	"D S",
	"I F G",
	"I V M",
	"P O G",
	"O R",
	"K O P",
	"I J H Y",
	"A G",
	"K I E",
	"I J S",
	"P C W",
	"A E P",
	"I N G",
	"K X",
	"A O",
	"C P",
	"V O F",
	"K P Y",
	"V D S",
	"I E G",
	"W Q",
	"V O G",
	"I S G",
	"K V F",
	"V R P",
	"O S",
	"V A O",
	"K D F Y",
	"V Y R",
	"I V P",
	"V C P",
	"A C",
	"K V X A",
	"K V X D",
	"K V X T",
	"K V X F",
	"K V X A"
};
//---------------------------------------------------------------------------
#endif