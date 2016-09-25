//----------------------------------------------------------------------------------
#include "WispTextFileParser.h"

namespace WISP_FILE
{
//----------------------------------------------------------------------------------
CTextFileParser::CTextFileParser(const string &path, const char *delimiters, const char *comentaries, const char *quotes)
: m_Ptr(NULL), m_EOL(NULL), m_RawLine("")
{
	m_File.Load(path);
	
	StartupInitalize(delimiters, comentaries, quotes);
}
//----------------------------------------------------------------------------------
CTextFileParser::CTextFileParser(const wstring &path, const char *delimiters, const char *comentaries, const char *quotes)
: m_Ptr(NULL), m_EOL(NULL), m_RawLine("")
{
	m_File.Load(path);
	
	StartupInitalize(delimiters, comentaries, quotes);
}
//----------------------------------------------------------------------------------
CTextFileParser::~CTextFileParser()
{
	//��������� ���� �� ������
	m_File.Unload();
}
//----------------------------------------------------------------------------------
//�������� �� ����� �����
void CTextFileParser::StartupInitalize(const char *delimiters, const char *comentaries, const char *quotes)
{
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
	m_End = m_File.End;
}
//----------------------------------------------------------------------------------
//�������� �� ����� �����
void CTextFileParser::Restart()
{
	m_File.ResetPtr();
}
//----------------------------------------------------------------------------------
//�������� �� ����� �����
bool CTextFileParser::IsEOF()
{
	return (m_File.Ptr >= m_End);
}
//----------------------------------------------------------------------------------
//�������� ����� ������
void CTextFileParser::GetEOL()
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
//----------------------------------------------------------------------------------
//�������� �� �����������
bool CTextFileParser::IsDelimiter()
{
	bool result = false;

	//������ �� ���� ������������
	for (int i = 0; i < m_DelimitersSize&& !result; i++)
		result = (*m_Ptr == m_Delimiters[i]);

	return result;
}
//----------------------------------------------------------------------------------
//���������� ��� �� ������
void CTextFileParser::SkipToData()
{
	//���� ������ - �����������, �� ������ �� ���� ������������ � �������� ���������
	while (m_Ptr < m_EOL && *m_Ptr && IsDelimiter())
		m_Ptr++;
}
//----------------------------------------------------------------------------------
//�������� �� �����������
bool CTextFileParser::IsComment()
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
//----------------------------------------------------------------------------------
//�������� ��������� �����
string CTextFileParser::ObtainData()
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
//----------------------------------------------------------------------------------
//�������� ��������� �������� ������ ��� ����� (���� ������� �� ����������)
string CTextFileParser::ObtainQuotedData()
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
			puchar ptr = m_Ptr;

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
//----------------------------------------------------------------------------------
//��������� ������ �� �����
void CTextFileParser::SaveRawLine()
{
	int size = m_EOL - m_Ptr;

	if (size > 0)
	{
		m_RawLine.resize(size, 0);
		memcpy(&m_RawLine[0], &m_Ptr[0], size);

		while (m_RawLine.length() && (m_RawLine[size - 1] == '\r' || m_RawLine[size - 1] == '\n'))
			m_RawLine.resize(m_RawLine.length() - 1);
	}
	else
		m_RawLine = "";
}
//----------------------------------------------------------------------------------
//��������� ������ �� �����
STRING_LIST CTextFileParser::ReadTokens(bool trim)
{
	m_Trim = trim;
	STRING_LIST result;

	//���� �� �������� ����� �����
	if (!IsEOF())
	{
		//������������� ����������
		m_Ptr = m_File.Ptr;
		GetEOL();

		SaveRawLine();

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
//----------------------------------------------------------------------------------
//��������� ������ �� ������
STRING_LIST CTextFileParser::GetTokens(const char *str, bool trim)
{
	m_Trim = trim;
	STRING_LIST result;

	//�������� ���������� �������� ����� ������
	puchar oldEnd = m_End;

	m_Ptr = (puchar)str;
	m_End = (puchar)str + strlen(str);
	m_EOL = m_End;

	SaveRawLine();

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
//----------------------------------------------------------------------------------
}; //namespace
//----------------------------------------------------------------------------------
