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
#include "stdafx.h"
//---------------------------------------------------------------------------
TTextFileParser::TTextFileParser(const char *fileName, const char *delimiters, const char *comentaries, const char *quotes)
: m_Ptr(NULL), m_EOL(NULL)
{
	memset(&m_File, 0, sizeof(m_File));

	//��������� ���� � ������
	FileManager.LoadFileToMemory(m_File, fileName);

	//������������� ������������
	memset(&m_Delimiters[0], 0, sizeof(m_Delimiters));
	m_DelimitersSize = strlen(delimiters);

	if (m_DelimitersSize)
		memcpy(&m_Delimiters[0], &delimiters[0], m_DelimitersSize);

	//������������� ������������
	memset(&m_Comentaries[0], 0, sizeof(m_Comentaries));
	m_ComentariesSize = strlen(comentaries);

	if (m_ComentariesSize)
		memcpy(&m_Comentaries[0], &comentaries[0], m_ComentariesSize);

	//������������� �������
	memset(&m_Quotes[0], 0, sizeof(m_Quotes));
	m_QuotesSize = strlen(quotes);

	if (m_QuotesSize)
		memcpy(&m_Quotes[0], &quotes[0], m_QuotesSize);

	//��������� ����� �����
	m_End = ((PBYTE)m_File.Address + m_File.Size);

	if (m_File.Address == NULL)
		memset(&m_File, 0, sizeof(m_File));
}
//---------------------------------------------------------------------------
TTextFileParser::~TTextFileParser()
{
	//��������� ���� �� ������
	FileManager.UnloadFileFromMemory(m_File);
}
//---------------------------------------------------------------------------
//�������� �� ����� �����
bool TTextFileParser::IsEOF()
{
	return (m_File.Ptr >= m_End);
}
//---------------------------------------------------------------------------
//�������� ����� ������
void TTextFileParser::GetEOL()
{
	//����� ������ ����� �������� ������
	m_EOL = m_File.Ptr;

	//���� ���� �������� �� �� �����
	if (!IsEOF())
	{
		//���� ����� ������
		while (m_EOL < m_End && *m_EOL)
		{
			if (*m_EOL == '\n')
				break;

			m_EOL++;
		}
	}
}
//---------------------------------------------------------------------------
//�������� �� �����������
bool TTextFileParser::IsDelimiter()
{
	bool result = false;

	//������ �� ���� ������������
	for (int i = 0; i < m_DelimitersSize&& !result; i++)
		result = (*m_Ptr == m_Delimiters[i]);

	return result;
}
//---------------------------------------------------------------------------
//���������� ��� �� ������
void TTextFileParser::SkipToData()
{
	//���� ������ - �����������, �� ������ �� ���� ������������ � �������� ���������
	while (m_Ptr < m_EOL && *m_Ptr && IsDelimiter())
		m_Ptr++;
}
//---------------------------------------------------------------------------
//�������� �� �����������
bool TTextFileParser::IsComment()
{
	bool result = (*m_Ptr == '\n');

	//������ �� ���� ������������
	for (int i = 0; i < m_ComentariesSize && !result; i++)
	{
		result = (*m_Ptr == m_Comentaries[i]);

		if (result && i + 1 < m_ComentariesSize && m_Comentaries[i] == m_Comentaries[i + 1] && m_Ptr + 1 < m_EOL)
		{
			result = (m_Ptr[0] == m_Ptr[1]);
			i++;
		}
	}

	return result;
}
//---------------------------------------------------------------------------
//�������� ��������� �����
string TTextFileParser::ObtainData()
{
	bool exit = false;
	string result = "";

	//���� ����������� ������� - ���������� ������ � ������� ���������
	while (m_Ptr < m_End && *m_Ptr && *m_Ptr != '\n' && !exit)
	{
		//�������� �� �����������
		if (IsDelimiter())
		{
			exit = true;
			break;
		}
		//�������� �� �����������
		else if (IsComment())
		{
			exit = true;
			m_Ptr = m_EOL;
			break;
		}

		//���� ��� �������� ������
		if (!exit)
		{
			//��������� �� ������� ������, ��� ������������� �������� �������
			if (*m_Ptr != '\r' && (!m_Trim || (*m_Ptr != ' ' && *m_Ptr != '\t')))
				result.push_back(*m_Ptr);

			m_Ptr++;
		}
	}

	return result;
}
//---------------------------------------------------------------------------
//�������� ��������� �������� ������ ��� ����� (���� ������� �� ����������)
string TTextFileParser::ObtainQuotedData()
{
	bool exit = false;
	string result = "";

	//��������� �� ��������, ������ ������� � ������: openQuote, closeQuote (����� ���� �����������)
	for (int i = 0; i < m_QuotesSize; i += 2)
	{
		//���� ������� �������
		if (*m_Ptr == m_Quotes[i])
		{
			//�������� ����������� �������
			char endQuote = m_Quotes[i + 1];
			exit = true;

			//������� ���������, �.�. ������� ������ �� �����
			m_Ptr++;
			PBYTE ptr = m_Ptr;

			//��������� ��� �� ����� ������ ��� �� ����������� �������
			while (ptr < m_EOL && *ptr && *ptr != '\n' && *ptr != endQuote)
				ptr++;

			//������ ���������
			int size = ptr - m_Ptr;

			if (size > 0)
			{
				//�������� ������ ��� ��������
				result.resize(size + 1);

				//�������� ��������
				memcpy(&result[0], &m_Ptr[0], size);
				result[size] = 0;

				//��������� �� ��������� � ����� � ������ ������
				for (int j = size - 1; j >= 0 && result[j] == '\r'; j--)
					result[j] = 0;

				//��������� �� ����� ��������
				m_Ptr = ptr;

				if (m_Ptr < m_EOL && *m_Ptr == endQuote)
					m_Ptr++;
			}

			break;
		}
	}

	//���� ��� �� ������� - �������� �����
	if (!exit)
		result = ObtainData();

	return result;
}
//---------------------------------------------------------------------------
//��������� ������ �� �����
vector<string> TTextFileParser::ReadTokens(bool trim)
{
	m_Trim = trim;
	vector<string> result;

	//���� �� �������� ����� �����
	if (!IsEOF())
	{
		//������������� ����������
		m_Ptr = m_File.Ptr;
		GetEOL();

		//������ �� ����� ������
		while (m_Ptr < m_EOL)
		{
			//���������� �����������
			SkipToData();

			//���� ��� ����������� - �������
			if (IsComment())
				break;

			//�������� �����
			string buf = ObtainQuotedData();

			//���� ����� �� ���� - ������� ��� � ����
			if (buf.length())
				result.push_back(buf);
		}

		m_File.Ptr = m_EOL + 1;
	}

	return result;
}
//---------------------------------------------------------------------------
//��������� ������ �� ������
vector<string> TTextFileParser::GetTokens(const char *str, bool trim)
{
	m_Trim = trim;
	vector<string> result;

	//�������� ���������� �������� ����� ������
	PBYTE oldEnd = m_End;

	m_Ptr = (PBYTE)str;
	m_End = (PBYTE)str + strlen(str);
	m_EOL = m_End;

	//��������� �� ������
	while (m_Ptr < m_EOL)
	{
		//���������� �����������
		SkipToData();

		//���� ��� ����������� - �������
		if (IsComment())
			break;

		//�������� �����
		string buf = ObtainQuotedData();

		//���� ����� �� ���� - ������� ��� � ����
		if (buf.length())
			result.push_back(buf);
	}

	//����������� ���������� �������� ����� ������
	m_End = oldEnd;

	return result;
}
//---------------------------------------------------------------------------