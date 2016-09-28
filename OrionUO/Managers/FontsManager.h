/***********************************************************************************
**
** FontsManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef FONTSMANAGER_H
#define FONTSMANAGER_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../MulStruct.h"
#include "../GLEngine/GLTextTexture.h"
//----------------------------------------------------------------------------------
typedef struct MULTILINES_FONT_DATA
{
	wchar_t item;
	ushort flags;
	uchar font;
	ushort linkID;
	uint color;

	MULTILINES_FONT_DATA *Next;
} *PMULTILINES_FONT_DATA;
//----------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------
//!��������� � ������� � ������
struct WEB_LINK
{
	//!���� ��������
	bool Visited;

	//!������
	string WebLink;
};
//----------------------------------------------------------------------------------
//!��������� � ������� � HTML-�������
struct HTML_char
{
	//!������ �������
	wchar_t Char;

	//!������ ������
	uchar Font;

	//!������������
	TEXT_ALIGN_TYPE Align;

	//!����� ������
	ushort Flags;

	//!���� �������
	uint Color;

	//!������ ������
	ushort LinkID;
};
//----------------------------------------------------------------------------------
struct HTML_DATA_INFO
{
	HTML_TAG_TYPE Tag;
	TEXT_ALIGN_TYPE Align;
	ushort Flags;
	uchar Font;
	uint Color;
	ushort Link;
};
//----------------------------------------------------------------------------------
typedef map<ushort, WEB_LINK> WEBLINK_MAP;
typedef vector<HTML_char> HTMLCHAR_LIST;
typedef vector<HTML_DATA_INFO> HTMLINFO_LIST;
//----------------------------------------------------------------------------------
//!����� ��������� �������
class CFontsManager
{
	SETGET(bool, SavePixels);
	SETGET(bool, RecalculateWidthByInfo);
	SETGET(bool, UnusePartialHue);

private:
	//!������ ASCII �������
	FONT_DATA *m_Font;

	//!���������� ASCII �������
	int m_FontCount;

	//!������ ������
	WEBLINK_MAP m_WebLink;

	//!������� ���������� ASCII �������
	static const uchar m_FontIndex[256];

	//!������ � ������ �������: �����, ������
	uint m_UnicodeFontAddress[20];
	uint m_UnicodeFontSize[20];

	//!������������� HTML ����������
	bool m_UseHTML;

	//!���� HTML
	uint m_HTMLColor;

	//!����������� ��������� ���� ������
	bool m_HTMLBackgroundCanBeColored;

	//!���� ���� ������
	uint m_BackgroundColor;

	uint m_WebLinkColor;
	uint m_VisitedWebLinkColor;

	int m_LeftMargin;
	int m_TopMargin;
	int m_RightMargin;
	int m_BottomMargin;

	/*!
	�������� ������ ������
	@param [__in] link ������
	@param [__out] color ���� ������
	@return ������ ������
	*/
	ushort GetWebLinkID(const string &link, uint &color);

	ushort GetWebLinkID(const wstring &link, uint &color);

	/*!
	��������� HTML ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] len ����� ������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@return ������ HTML ��������
	*/
	HTMLCHAR_LIST GetHTMLData(uchar font, const wchar_t *str, int &len, TEXT_ALIGN_TYPE align, ushort flags);

	HTML_DATA_INFO GetHTMLInfoFromTag(const HTML_TAG_TYPE &tag);

	HTML_DATA_INFO GetCurrentHTMLInfo(const HTMLINFO_LIST &list);

	void GetHTMLInfoFromContent(HTML_DATA_INFO &info, const string &content);

	void TrimHTMLString(string &str);

	uint GetHTMLColorFromText(string &str);

	HTML_TAG_TYPE ParseHTMLTag(const wchar_t *str, const int &len, int &i, bool &endTag, HTML_DATA_INFO &info);

	HTMLCHAR_LIST GetHTMLDataOld(uchar font, const wchar_t *str, int &len, TEXT_ALIGN_TYPE align, ushort flags);

	/*!
	��������� ������ �������������� ������ HTML
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] len ����� ������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@param [__in] width ������ ������
	@return ������ �� ������
	*/
	PMULTILINES_FONT_INFO GetInfoHTML(uchar font, const wchar_t *str, int len, TEXT_ALIGN_TYPE align, ushort flags, int width);

	/*!
	�������� ASCII ��������
	@param [__in] font �����
	@param [__out] th ������ ��������
	@param [__in] str �����
	@param [__in] color ����
	@param [__in] width ������ ��������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@return true ��� �������� ���������
	*/
	bool GenerateABase(uchar &font, CGLTextTexture &th, const char *str, ushort &color, int &width, TEXT_ALIGN_TYPE &align, ushort &flags);

	/*!
	�������� Unicode ��������
	@param [__in] font �����
	@param [__out] th ������ ��������
	@param [__in] str �����
	@param [__in] color ����
	@param [__in] cell ����� ������ � ������� ������
	@param [__in] width ������ ��������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@return true ��� �������� ���������
	*/
	bool GenerateWBase(uchar &font, CGLTextTexture &th, const wchar_t *str, ushort &color, uchar &cell, int &width, TEXT_ALIGN_TYPE &align, ushort &flags);

public:
	CFontsManager();
	~CFontsManager();

	/*!
	���������� ������������� HTML-�����
	@param [__in] val ��������� �������������
	@param [__in_opt] htmlStartColor ��������� ����
	@return
	*/
	void SetUseHTML(const bool &val, const uint &htmlStartColor = 0xFFFFFFFF, const bool backgroundCanBeColored = false) { m_UseHTML = val; m_HTMLColor = htmlStartColor; m_HTMLBackgroundCanBeColored = backgroundCanBeColored; }
	bool GetUseHTML() const { return m_UseHTML; }
	__declspec(property(get = GetUseHTML)) bool UseHTML;

	/*!
	�������� ASCII �������
	@return true ��� �������� ��������
	*/
	bool LoadFonts();

	uchar UnicodeFontExists(const uchar &font);

	/*!
	������� �� ������ �� �������
	@param [__in] link ������ ������
	@return 
	*/
	void GoToWebLink(ushort link);



	//-----------------------------
	//---������ � ASCII ��������---
	//-----------------------------

	/*!
	��������, ���������� �� ������
	@param [__in] index ������ �������
	@return true ���� ��� ���������� ������
	*/
	bool IsPrintASCII(uchar index) { return (m_FontIndex[index] != 0xFF); }

	/*!
	�������� �������� ������� �������
	@param [__in] font �����
	@param [__in] index ������ �������
	@return �������� � ��������
	*/
	int GetFontOffsetY(uchar font, uchar index);

	/*!
	�������� ������� ������� � ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] pos ������� ������� � ������
	@param [__in] width ������ ��������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@return ���������� �������
	*/
	POINT GetCaretPosA(uchar font, const char *str, int pos, int width, TEXT_ALIGN_TYPE align, ushort flags);

	/*!
	��������� ��������� �������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] x ���������� ������� �� ��� X
	@param [__in] y ���������� ������� �� ��� Y
	@param [__in] width ������ ��������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@return ������� ������� � ������
	*/
	int CalculateCaretPosA(uchar font, const char *str, int x, int y, int width, TEXT_ALIGN_TYPE align, ushort flags);

	/*!
	�������� ������ ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in_opt] len ����� ������
	@return ������ ������ � ��������
	*/
	int GetWidthA(uchar font, const char *str, int len = 0);

	/*!
	�������� ������ ������ (� ������ ���������� ���������)
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] len ����� ������
	@param [__in] maxWidth ������������ ������ ��������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@return ������ ������ � ��������
	*/
	int GetWidthExA(uchar font, const char *str, int len, int maxWidth, TEXT_ALIGN_TYPE align, ushort flags);

	/*!
	�������� ������ ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in_opt] width ������ ��������
	@param [__in_opt] align ������������ ������
	@param [__in_opt] flags ������� ������
	@return ������ ������ � ��������
	*/
	int GetHeightA(uchar font, const char *str, int width = 0, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0);

	/*!
	�������� ������ ������ �� ������ �����
	@param [__in] info ������ �� �������������� �����
	@return ������ ������ � ��������
	*/
	int GetHeightA(PMULTILINES_FONT_INFO info);

	/*!
	�������� ����� ��������� ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] len ����� ������
	@param [__in] width ������ ��������
	@param [__in] IsCropped ������������ �����, �������� �� ��������� ������� ����� ���������� � ���������� �� ����������
	@return �������������� �����
	*/
	string GetTextByWidthA(uchar font, const char *str, int len, int width, bool IsCropped);

	/*!
	�������� ���������� � ������ (� �������������� ����)
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] len ����� ������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@param [__in] width ������ ��������
	@return ������ �� �������������� ����� ��� NULL
	*/
	PMULTILINES_FONT_INFO GetInfoA(uchar font, const char *str, int len, TEXT_ALIGN_TYPE align, ushort flags, int width);

	/*!
	������������� ������� �������� ������
	@param [__in] font �����
	@param [__inout] th ������ � �������� ������
	@param [__in] str �����
	@param [__in] color ���� ������
	@param [__in] width ������ ��������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@return ������ �� ������ ��������
	*/
	UINT_LIST GeneratePixelsA(uchar &font, CGLTextTexture &th, const char *str, ushort &color, int &width, TEXT_ALIGN_TYPE &align, ushort &flags);

	/*!
	������������� �������� ������
	@param [__in] font �����
	@param [__inout] th ������ � �������� ������
	@param [__in] str �����
	@param [__in_opt] color ����
	@param [__in_opt] width ������ ��������
	@param [__in_opt] align ������������ ������
	@param [__in_opt] flags ������� ������
	@return true ��� �������� ���������
	*/
	bool GenerateA(uchar font, CGLTextTexture &th, const char *str, ushort color = 0, int width = 0, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0);

	/*!
	���������� �����
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] color ����
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@param [__in_opt] width ������ ��������
	@param [__in_opt] align ������������ ������
	@param [__in_opt] flags ������� ������
	@return 
	*/
	void DrawA(uchar font, const char *str, ushort color, int x, int y, int width = 0, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0);



	//-------------------------------
	//---������ � Unicode ��������---
	//-------------------------------

	/*!
	�������� ������� ������� � ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] pos ������� ������� � ������
	@param [__in] width ������ ��������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@return ���������� �������
	*/
	POINT GetCaretPosW(uchar font, const wchar_t *str, int pos, int width, TEXT_ALIGN_TYPE align, ushort flags);

	/*!
	��������� ��������� �������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] x ���������� ������� �� ��� X
	@param [__in] y ���������� ������� �� ��� Y
	@param [__in] width ������ ��������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@return ������� ������� � ������
	*/
	int CalculateCaretPosW(uchar font, const wchar_t *str, int x, int y, int width, TEXT_ALIGN_TYPE align, ushort flags);

	/*!
	�������� ������ ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in_opt] len ����� ������
	@return ������ ������ � ��������
	*/
	int GetWidthW(uchar font, const wchar_t *str, int len = 0);

	/*!
	�������� ������ ������ (� ������ ���������� ���������)
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] len ����� ������
	@param [__in] maxWidth ������������ ������ ��������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@return ������ ������ � ��������
	*/
	int GetWidthExW(uchar font, const wchar_t *str, int len, int maxWidth, TEXT_ALIGN_TYPE align, ushort flags);

	/*!
	�������� ������ ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in_opt] width ������ ��������
	@param [__in_opt] align ������������ ������
	@param [__in_opt] flags ������� ������
	@return ������ ������ � ��������
	*/
	int GetHeightW(uchar font, const wchar_t *str, int width = 0, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0);

	/*!
	�������� ������ ������ �� ������ �����
	@param [__in] info ������ �� �������������� �����
	@return ������ ������ � ��������
	*/
	int GetHeightW(PMULTILINES_FONT_INFO info);

	/*!
	�������� ����� ��������� ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] len ����� ������
	@param [__in] width ������ ��������
	@param [__in] IsCropped ������������ �����, �������� �� ��������� ������� ����� ���������� � ���������� �� ����������
	@return �������������� �����
	*/
	wstring GetTextByWidthW(uchar font, const wchar_t *str, int len, int width, bool IsCropped);

	/*!
	�������� ���������� � ������ (� �������������� ����)
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] len ����� ������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@param [__in] width ������ ��������
	@return ������ �� �������������� ����� ��� NULL
	*/
	PMULTILINES_FONT_INFO GetInfoW(uchar font, const wchar_t *str, int len, TEXT_ALIGN_TYPE align, ushort flags, int width);

	/*!
	������������� ������� �������� ������
	@param [__in] font �����
	@param [__inout] th ������ � �������� ������
	@param [__in] str �����
	@param [__in] color ���� ������
	@param [__in] cell ������ � ������� ������
	@param [__in] width ������ ��������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@return ������ �� ������ ��������
	*/
	UINT_LIST GeneratePixelsW(uchar &font, CGLTextTexture &th, const wchar_t *str, ushort &color, uchar &cell, int &width, TEXT_ALIGN_TYPE &align, ushort &flags);

	/*!
	������������� �������� ������
	@param [__in] font �����
	@param [__inout] th ������ � �������� ������
	@param [__in] str �����
	@param [__in_opt] color ����
	@param [__in_opt] cell ������ � ������� ������
	@param [__in_opt] width ������ ��������
	@param [__in_opt] align ������������ ������
	@param [__in_opt] flags ������� ������
	@return true ��� �������� ���������
	*/
	bool GenerateW(uchar font, CGLTextTexture &th, const wchar_t *str, ushort color = 0, uchar cell = 30, int width = 0, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0);

	/*!
	���������� �����
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] color ����
	@param [__in] x �������� ���������� X
	@param [__in] y �������� ���������� Y
	@param [__in_opt] cell ������ � ������� ������
	@param [__in_opt] width ������ ��������
	@param [__in_opt] align ������������ ������
	@param [__in_opt] flags ������� ������
	@return
	*/
	void DrawW(uchar font, const wchar_t *str, ushort color, int x, int y, uchar cell = 30, int width = 0, TEXT_ALIGN_TYPE align = TS_LEFT, ushort flags = 0);
};
//--------------------------------------------------------------------------
//!������ �� �������� �������
extern CFontsManager g_FontManager;
//--------------------------------------------------------------------------
#endif