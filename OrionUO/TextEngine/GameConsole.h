/***********************************************************************************
**
** GameConsole.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GAMECONSOLE_H
#define GAMECONSOLE_H
//----------------------------------------------------------------------------------
#include "EntryText.h"
#include "../Constants.h"
//----------------------------------------------------------------------------------
//����� ��� ������ � ������� �������� (�����) ����� ����� �������� ����
class CGameConsole : public CEntryText
{
private:
	//��� �������
	GAME_CONSOLE_TEXT_TYPE m_Type;

	//���� ������ �� �� ����������� ���������
	wstring IsSystemCommand(const wchar_t *text, int &len, int &member);

	//!���� ���������� ���������� ������
	wstring m_ConsoleStack[MAX_CONSOLE_STACK_SIZE];

	//!���������� ������������ � ���� ������
	int m_ConsoleStackCount;

	//!��������� �� ������� ������� �����
	int m_ConsoleSelectedIndex;

public:
	CGameConsole();
	virtual ~CGameConsole();

	//��������� ������ �������
	void Send();

	//���������� ����� �������
	void DrawW(BYTE font, WORD color, int x, int y, TEXT_ALIGN_TYPE align = TS_LEFT, WORD flags = 0);

	void SaveConsoleMessage();

	void ChangeConsoleMessage();

	void ClearStack();
};
//----------------------------------------------------------------------------------
static const wstring g_ConsolePrefix[7] =
{
	L"", //Normal
	L"! ", //Yell
	L"; ", //Whisper
	L": ", //Emote
	L".", //Command
	L"? ", //Broadcast
	L"/ ", //Party
};
//----------------------------------------------------------------------------------
extern CGameConsole g_GameConsole;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
