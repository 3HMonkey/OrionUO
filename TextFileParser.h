/****************************************************************************
**
** TextFileParser.h
**
** Copyright (C) Marth 2016 Hotride
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
#ifndef TextFileParserH
#define TextFileParserH
//---------------------------------------------------------------------------
//����� ��� ������ � ���������� ������� �������
class TTextFileParser
{
private:
	//��������� �� ����� � ������, ���� �������� ����
	TMappedHeader m_File;

	//��������� �� ������� �������������� ������
	PBYTE m_Ptr;

	//����� ����� ������
	PBYTE m_EOL;

	//����� ����� �����
	PBYTE m_End;

	//�����������
	char m_Delimiters[50];

	//���������� ������������
	int m_DelimitersSize;

	//�����������
	char m_Comentaries[50];

	//���������� �����������
	int m_ComentariesSize;

	//����� �������, ������ ������� � ������: openQuote, closeQuote (����� ���� �����������)
	char m_Quotes[50];

	//���������� ��������� � ������ �������
	int m_QuotesSize;

	//�������� ������ �� ������
	bool m_Trim;

	//�������� ����� ������
	void GetEOL();

	//�������� �� �����������
	bool IsDelimiter();

	//���������� ��� �� ������
	void SkipToData();

	//�������� �� �����������
	bool IsComment();

	//�������� ��������� �����
	string ObtainData();

	//�������� ��������� �������� ������ ��� ����� (���� ������� �� ����������)
	string ObtainQuotedData();
public:
	TTextFileParser(const char *fileName, const char *delimiters, const char *comentaries, const char *quotes);
	~TTextFileParser();

	//�������� �� ����� �����
	bool IsEOF();

	//��������� ������ �� �����
	vector<string> ReadTokens(bool trim = true);

	//��������� ������ �� ������
	vector<string> GetTokens(const char *str, bool trim = true);
};
//---------------------------------------------------------------------------
#endif