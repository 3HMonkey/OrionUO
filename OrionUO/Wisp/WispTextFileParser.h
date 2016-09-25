//----------------------------------------------------------------------------------
#ifndef WISPTEXTFILEPARSER_H
#define WISPTEXTFILEPARSER_H
//----------------------------------------------------------------------------------
#include "WispMappedFile.h"
//----------------------------------------------------------------------------------
namespace WISP_FILE
{
//----------------------------------------------------------------------------------
class CTextFileParser
{
	SETGET(string, RawLine);

private:
	//��������� �� ����� � ������, ���� �������� ����
	CMappedFile m_File;

	//��������� �� ������� �������������� ������
	puchar m_Ptr;

	//����� ����� ������
	puchar m_EOL;

	//����� ����� �����
	puchar m_End;

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

	void StartupInitalize(const char *delimiters, const char *comentaries, const char *quotes);

	void SaveRawLine();

public:
	CTextFileParser(const string &path, const char *delimiters = "", const char *comentaries = "", const char *quotes = "");
	CTextFileParser(const wstring &path, const char *delimiters = "", const char *comentaries = "", const char *quotes = "");
	~CTextFileParser();

	//�������� ��������� �� �����
	void Restart();

	//�������� �� ����� �����
	bool IsEOF();

	//��������� ������ �� �����
	STRING_LIST ReadTokens(bool trim = true);

	//��������� ������ �� ������
	STRING_LIST GetTokens(const char *str, bool trim = true);
};
//----------------------------------------------------------------------------------
}; //namespace
//----------------------------------------------------------------------------------
#endif

