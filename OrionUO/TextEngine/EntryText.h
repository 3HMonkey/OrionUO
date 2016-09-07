/***********************************************************************************
**
** EntryText.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef ENTRYTEXT_H
#define ENTRYTEXT_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../GLEngine/GLTextTexture.h"
//----------------------------------------------------------------------------------
class CGump;
//----------------------------------------------------------------------------------
//!����� ��� ������ � ����� ��� ����� ������
class CEntryText
{
	SETGET(int, MaxLength);
	SETGET(int, Width);
	SETGET(int, MaxWidth);
	SETGET(bool, Changed);
	SETGET(ushort, Color);
	SETGET(int, DrawOffset);
	SETGET(POINT, CaretPos);
	SETGET(bool, NumberOnly);

private:
	//!Unicode ������
	wstring m_Text;

	//!ASCII ������
	string m_CText;

	//!������� ������� � ������
	int m_Position;

public:
	CEntryText(int maxLength = 0, int width = 0, int maxWidth = 0, bool numberOnly = false);
	virtual ~CEntryText();

	//!�������� ������
	CGLTextTexture m_Texture;

	/*!
	�������� ������
	@return 
	*/
	void Clear();

	//�������� ���������� �����
	int GetLinesCountA(uchar font, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0, int width = 0);

	//�������� ���������� �����
	int GetLinesCountW(uchar font, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0, int width = 0);

	//�������� ������
	bool Insert(wchar_t ch, CGump *gump = NULL);

	//������� ������
	void Remove(bool left, CGump *gump = NULL);

	//�������� ������� ������� � ������
	void AddPos(int val, CGump *gump = NULL);

	//���������� ������� ������� � ������
	void SetPos(int val, CGump *gump = NULL);

	//Unicode ������ ������
	const wchar_t *Data() const {return m_Text.c_str();}

	//ASCII ������ �����
	const char *c_str();

	//���������� ASCII �����
	void SetText(const string &text);

	//���������� Unicode �����
	void SetText(const wstring &text);

	//������� ������� ������ �� �����
	void OnClick(CGump *gump, uchar font, bool unicode, int x, int y, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0);

	//������� ������� � �������� ��������� ����
	void OnKey(CGump *gump, WPARAM wParam);

	int Pos() const {return m_Position;}

	int Length() const {return m_Text.length();}

	//��������� ASCII ������ �� ������
	string CheckMaxWidthA(uchar font, string str);

	//��������� Unicode ������ �� ������
	wstring CheckMaxWidthW(uchar font, wstring str);

	//��������������� ASCII ����� �� ������
	void FixMaxWidthA(uchar font);

	//��������������� Unicode ����� �� ������
	void FixMaxWidthW(uchar font);

	//������� �������� ASCII ������
	void CreateTextureA(uchar font, string str, ushort color, int width, TEXT_ALIGN_TYPE align, ushort flags);

	//������� �������� Unicode ������
	void CreateTextureW(uchar font, wstring str, ushort color, int width, TEXT_ALIGN_TYPE align, ushort flags);

	//���������� ASCII �����
	virtual void DrawA(uchar font, ushort color, int X, int Y, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0);

	//���������� Unicode �����
	virtual void DrawW(uchar font, ushort color, int X, int Y, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0);

	//���������� ASCII ����� ��������������� �����������
	void DrawMaskA(uchar font, ushort color, int X, int Y, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0);

	//���������� Unicode ����� ��������������� �����������
	void DrawMaskW(uchar font, ushort color, int X, int Y, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0);
};
//----------------------------------------------------------------------------------
extern CEntryText *g_EntryPointer;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
