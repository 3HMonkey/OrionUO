/****************************************************************************
**
** FontsManager.h
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
//--------------------------------------------------------------------------
#ifndef FontsManagerH
#define FontsManagerH
//--------------------------------------------------------------------------
//!��������� � ������� � ������
struct WEB_LINK
{
	//!���� ��������
	bool Visited;

	//!������
	string WebLink;
};
//--------------------------------------------------------------------------
//!��������� � ������� � HTML-�������
struct HTML_char
{
	//!������ �������
	wchar_t Char;

	//!������ ������
	BYTE Font;

	//!������������
	TEXT_ALIGN_TYPE Align;

	//!����� ������
	WORD Flags;

	//!���� �������
	DWORD Color;

	//!������ ������
	WORD LinkID;
};
//--------------------------------------------------------------------------
typedef std::map<WORD, WEB_LINK> WEBLINK_MAP;
//--------------------------------------------------------------------------
//!����� ��������� �������
class TFontsManager
{
private:
	//!������ ASCII �������
	FONT_DATA *m_Font;

	//!���������� ASCII �������
	int m_FontCount;

	//!������ ������
	WEBLINK_MAP m_WebLink;

	//!������� ���������� ASCII �������
	static const BYTE m_FontIndex[256];

	//!������ � ������ �������: �����, ������
	DWORD m_UnicodeFontAddress[20];
	DWORD m_UnicodeFontSize[20];

	//!���������� �������� ��������
	bool m_SavePixels;

	//!������������� HTML ����������
	bool m_UseHTML;

	//!���� HTML
	DWORD m_HTMLColor;

	/*!
	�������� ������ ������
	@param [__in] link ������
	@param [__out] color ���� ������
	@return ������ ������
	*/
	WORD GetWebLinkID(__in wchar_t *link, __out DWORD &color);

	/*!
	��������� HTML ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] len ����� ������
	@param [__in] align ������������ ������
	@param [__in] flags ������� ������
	@return ������ HTML ��������
	*/
	HTML_char *GetHTMLData(__in BYTE font, __in const wchar_t *str, __in int &len, __in TEXT_ALIGN_TYPE align, __in WORD flags);

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
	PMULTILINES_FONT_INFO GetInfoHTML(__in BYTE font, __in const wchar_t *str, __in int len, __in TEXT_ALIGN_TYPE align, __in WORD flags, __in int width);

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
	bool GenerateABase(__in BYTE &font, __out TTextTexture &th, __in const char *str, __in WORD &color, __in int &width, __in TEXT_ALIGN_TYPE &align, __in WORD &flags);

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
	bool GenerateWBase(__in BYTE &font, __out TTextTexture &th, __in const wchar_t *str, __in WORD &color, __in BYTE &cell, __in int &width, __in TEXT_ALIGN_TYPE &align, __in WORD &flags);

public:
	TFontsManager();
	~TFontsManager();
	
	SETGET(bool, SavePixels);

	/*!
	���������� ������������� HTML-�����
	@param [__in] val ��������� �������������
	@param [__in_opt] htmlStartColor ��������� ����
	@return
	*/
	void SetUseHTML(__in bool val, __in_opt DWORD htmlStartColor = 0xFFFFFFFF) { m_UseHTML = val; m_HTMLColor = htmlStartColor;}
	bool GetUseHTML() const { return m_UseHTML; }
	__declspec(property(get = GetUseHTML)) bool UseHTML;

	/*!
	�������� ASCII �������
	@return true ��� �������� ��������
	*/
	bool LoadFonts();

	/*!
	������� �� ������ �� �������
	@param [__in] link ������ ������
	@return 
	*/
	void GoToWebLink(__in WORD link);



	//-----------------------------
	//---������ � ASCII ��������---
	//-----------------------------

	/*!
	��������, ���������� �� ������
	@param [__in] index ������ �������
	@return true ���� ��� ���������� ������
	*/
	bool IsPrintASCII(__in BYTE index) __in{ return (m_FontIndex[index] != 0xFF); }

	/*!
	�������� �������� ������� �������
	@param [__in] font �����
	@param [__in] index ������ �������
	@return �������� � ��������
	*/
	int GetFontOffsetY(__in BYTE font, __in BYTE index);

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
	POINT GetCaretPosA(__in BYTE font, __in const char *str, __in int pos, __in int width, __in TEXT_ALIGN_TYPE align, __in WORD flags);

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
	int CalculateCaretPosA(__in BYTE font, __in const char *str, __in int x, __in int y, __in int width, __in TEXT_ALIGN_TYPE align, __in WORD flags);

	/*!
	�������� ������ ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in_opt] len ����� ������
	@return ������ ������ � ��������
	*/
	int GetWidthA(__in BYTE font, __in const char *str, __in_opt int len = 0);

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
	int GetWidthExA(__in BYTE font, __in const char *str, __in int len, __in int maxWidth, __in TEXT_ALIGN_TYPE align, __in WORD flags);

	/*!
	�������� ������ ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in_opt] width ������ ��������
	@param [__in_opt] align ������������ ������
	@param [__in_opt] flags ������� ������
	@return ������ ������ � ��������
	*/
	int GetHeightA(__in BYTE font, __in const char *str, __in_opt int width = 0, __in_opt TEXT_ALIGN_TYPE align = TS_LEFT, __in_opt WORD flags = 0);

	/*!
	�������� ������ ������ �� ������ �����
	@param [__in] info ������ �� �������������� �����
	@return ������ ������ � ��������
	*/
	int GetHeightA(__in PMULTILINES_FONT_INFO info);

	/*!
	�������� ����� ��������� ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] len ����� ������
	@param [__in] width ������ ��������
	@param [__in] IsCropped ������������ �����, �������� �� ��������� ������� ����� ���������� � ���������� �� ����������
	@return �������������� �����
	*/
	string GetTextByWidthA(__in BYTE font, __in const char *str, __in int len, __in int width, __in bool IsCropped);

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
	PMULTILINES_FONT_INFO GetInfoA(__in BYTE font, __in const char *str, __in int len, __in TEXT_ALIGN_TYPE align, __in WORD flags, __in int width);

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
	PDWORD GeneratePixelsA(__in BYTE &font, __inout TTextTexture &th, __in const char *str, __in WORD &color, __in int &width, __in TEXT_ALIGN_TYPE &align, __in WORD &flags);

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
	bool GenerateA(__in BYTE font, __inout TTextTexture &th, __in const char *str, __in_opt WORD color = 0, __in_opt int width = 0, __in_opt TEXT_ALIGN_TYPE align = TS_LEFT, __in_opt WORD flags = 0);

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
	void DrawA(__in BYTE font, __in const char *str, __in WORD color, __in int x, __in int y, __in_opt int width = 0, __in_opt TEXT_ALIGN_TYPE align = TS_LEFT, __in_opt WORD flags = 0);



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
	POINT GetCaretPosW(__in BYTE font, __in const wchar_t *str, __in int pos, __in int width, __in TEXT_ALIGN_TYPE align, __in WORD flags);

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
	int CalculateCaretPosW(__in BYTE font, __in const wchar_t *str, __in int x, __in int y, __in int width, __in TEXT_ALIGN_TYPE align, __in WORD flags);

	/*!
	�������� ������ ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in_opt] len ����� ������
	@return ������ ������ � ��������
	*/
	int GetWidthW(__in BYTE font, __in const wchar_t *str, __in_opt int len = 0);

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
	int GetWidthExW(__in BYTE font, __in const wchar_t *str, __in int len, __in int maxWidth, __in TEXT_ALIGN_TYPE align, __in WORD flags);

	/*!
	�������� ������ ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in_opt] width ������ ��������
	@param [__in_opt] align ������������ ������
	@param [__in_opt] flags ������� ������
	@return ������ ������ � ��������
	*/
	int GetHeightW(__in BYTE font, __in const wchar_t *str, __in_opt int width = 0, __in_opt TEXT_ALIGN_TYPE align = TS_LEFT, __in_opt WORD flags = 0);

	/*!
	�������� ������ ������ �� ������ �����
	@param [__in] info ������ �� �������������� �����
	@return ������ ������ � ��������
	*/
	int GetHeightW(__in PMULTILINES_FONT_INFO info);

	/*!
	�������� ����� ��������� ������
	@param [__in] font �����
	@param [__in] str �����
	@param [__in] len ����� ������
	@param [__in] width ������ ��������
	@param [__in] IsCropped ������������ �����, �������� �� ��������� ������� ����� ���������� � ���������� �� ����������
	@return �������������� �����
	*/
	wstring GetTextByWidthW(__in BYTE font, __in const wchar_t *str, __in int len, __in int width, __in bool IsCropped);

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
	PMULTILINES_FONT_INFO GetInfoW(__in BYTE font, __in const wchar_t *str, __in int len, __in TEXT_ALIGN_TYPE align, __in WORD flags, __in int width);

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
	PDWORD GeneratePixelsW(__in BYTE &font, __inout TTextTexture &th, __in const wchar_t *str, __in WORD &color, __in BYTE &cell, __in int &width, __in TEXT_ALIGN_TYPE &align, __in WORD &flags);

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
	bool GenerateW(__in BYTE font, __inout TTextTexture &th, __in const wchar_t *str, __in_opt WORD color = 0, __in_opt BYTE cell = 30, __in_opt int width = 0, __in_opt TEXT_ALIGN_TYPE align = TS_LEFT, __in_opt WORD flags = 0);

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
	void DrawW(__in BYTE font, __in const wchar_t *str, __in WORD color, __in int x, __in int y, __in_opt BYTE cell = 30, __in_opt int width = 0, __in_opt TEXT_ALIGN_TYPE align = TS_LEFT, __in_opt WORD flags = 0);
};
//--------------------------------------------------------------------------
//!������ �� �������� �������
extern TFontsManager *FontManager;
//--------------------------------------------------------------------------
#endif