/****************************************************************************
**
** FileManager.h
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
#ifndef FileManagerH
#define FileManagerH
//---------------------------------------------------------------------------
//!����� ��� �������� ������ � ������ � �������, ���������������� � ������
class TMappedHeader
{
public:
	TMappedHeader();
	~TMappedHeader() {}

	//!����� �����
	HANDLE File;

	//!������ �����
	DWORD Size;

	//!������ �� �����
	HANDLE Map;

	//!����� ����� � ������
	PVOID Address;

	//!��������� �� ����� �����
	PBYTE End;

	//!��������� �� ������� �������
	PBYTE Ptr;

	inline bool IsEof() { return (Ptr >= End); }

	/*!
	����������� ���������
	@param [__in] offset �������� ���������
	@return 
	*/
	inline void Move(__in int offset) { Ptr += offset; }

	/*!
	��������� ���� (1 ����) little-endian
	@return 
	*/
	BYTE ReadByte();

	/*!
	��������� ���� (1 ����) big-endian
	@return
	*/
	BYTE ReadByteBE();

	/*!
	��������� ����� (2 �����) little-endian
	@return 
	*/
	WORD ReadWord();

	/*!
	��������� ����� (2 �����) big-endian
	@return
	*/
	WORD ReadWordBE();

	/*!
	��������� ������� ����� (4 �����) little-endian
	@return 
	*/
	DWORD ReadDWord();

	/*!
	��������� ������� ����� (4 �����) big-endian
	@return
	*/
	DWORD ReadDWordBE();

	/*!
	��������� ������ (1 ����) little-endian
	@return 
	*/
	char ReadChar();

	/*!
	��������� ������ (1 ����) big-endian
	@return
	*/
	char ReadCharBE();

	/*!
	��������� �������� �������� (2 �����) little-endian
	@return 
	*/
	short ReadShort();

	/*!
	��������� �������� �������� (2 �����) big-endian
	@return
	*/
	short ReadShortBE();

	/*!
	��������� ����� (4 �����) little-endian
	@return 
	*/
	int ReadInt();

	/*!
	��������� ����� (4 �����) big-endian
	@return
	*/
	int ReadIntBE();

	/*!
	��������� ������
	@param [__in] size ������ ������, ���� 0 - ������ �� ����
	@return 
	*/
	string ReadString(__in int size);

	/*!
	��������� ������ utf-8
	@param [__in] size ������ ������
	@return
	*/
	wstring ReadUtf8String(__in int size);
};
//---------------------------------------------------------------------------
//!����� ��� ������ � �������
class TFileManager
{
private:
	//!������������ �� ���� ������ (verdata.mul)
	bool m_UseVerdata;

	//!���������� ����������� ������ � Unicode-��������
	int m_UnicodeFontCount;

public:
	TFileManager() :m_UseVerdata(true), m_UnicodeFontCount(0) {}
	~TFileManager() {}
	
	//!������ ������ � ������
	TMappedHeader AnimIdx[6];
	TMappedHeader ArtIdx;
	TMappedHeader GumpIdx;
	TMappedHeader LightIdx;
	TMappedHeader MultiIdx;
	TMappedHeader SkillsIdx;
	TMappedHeader SoundIdx;
	TMappedHeader StaticIdx[6];
	TMappedHeader TextureIdx;
	
	TMappedHeader AnimMul[6];
	TMappedHeader AnimdataMul;
	TMappedHeader ArtMul;
	TMappedHeader HuesMul;
	TMappedHeader FontsMul;
	TMappedHeader GumpMul;
	TMappedHeader LightMul;
	TMappedHeader MapMul[6];
	TMappedHeader MultiMul;
	TMappedHeader PaletteMul;
	TMappedHeader RadarcolMul;
	TMappedHeader SkillsMul;
	TMappedHeader SoundMul;
	TMappedHeader StaticMul[6];
	TMappedHeader TextureMul;
	TMappedHeader TiledataMul;
	TMappedHeader UnifontMul[20];
	TMappedHeader VerdataMul;
	
	TMappedHeader MultiMap;
	TMappedHeader SpeechMul;
	TMappedHeader LangcodeIff;

	SETGET(bool, UseVerdata);
	SETGET(int, UnicodeFontCount);

	/*!
	��������� �����
	@return 
	*/
	bool Load();

	/*!
	��������� �����
	@return 
	*/
	void Unload();

	/*!
	������������� ���� � ������
	@param [__inout] object ������ ��� ������ � ������
	@param [__in] fName ���� � �����
	@return 
	*/
	bool LoadFileToMemory(__inout TMappedHeader &object, __in const char *fName);

	/*!
	��������� ���� �� ������
	@param [__inout] object ������ ��� ������ � ������
	@return 
	*/
	void UnloadFileFromMemory(__inout TMappedHeader &object);

};
//---------------------------------------------------------------------------
//!����� ��� ������ �������� ������
class TFileWriter
{
private:
	//!����� �����
	FILE *m_File;

	//!���� � �����
	string m_FilePath;

	//!������������ �� ���������� ����� ��� ������
	bool m_UseBuffer;

	//!������ �� ����
	bool m_Ready;

	//!���������� ������ � ������
	int m_BufferCount;

	//!�����
	BYTE m_Buffer[MAX_FILE_BUFFER_SIZE];

public:
	TFileWriter(string path, bool useBuffer);
	~TFileWriter();
	
	//��������� �� ������ �� ���������� ������
	PBYTE Ptr;

	SETGET(string, FilePath);
	SETGET(bool, Ready);
	SETGET(bool, UseBuffer);
	SETGET(int, BufferCount);

	/*!
	����������� ��������� ����������� ������
	@param [__in] offset ��������
	@return 
	*/
	void Move(__in int offset);

	/*!
	�������� ����
	@param [__in] val ������
	@return 
	*/
	void WriteByte(__in BYTE val);

	/*!
	�������� ������
	@param [__in] val ������
	@return
	*/
	void WriteChar(char val);

	/*!
	�������� �����
	@param [__in] val ������
	@return
	*/
	void WriteWord(WORD val);

	/*!
	�������� �������� ��������
	@param [__in] val ������
	@return
	*/
	void WriteShort(short val);

	/*!
	�������� ������� �����
	@param [__in] val ������
	@return
	*/
	void WriteDWord(DWORD val);

	/*!
	�������� �����
	@param [__in] val ������
	@return
	*/
	void WriteInt(int val);

	/*!
	�������� ASCII ������
	@param [__in] val ������
	@return 
	*/
	void WriteAsciiString(__in string val);

	/*!
	�������� Unicode ������
	@param [__in] val ������
	@return 
	*/
	void WriteUnicodeString(__in wstring val);

	/*!
	�������� ����� � ����
	@return 
	*/
	void WriteBuffer();
};
//---------------------------------------------------------------------------
//!�������� ������
extern TFileManager FileManager;
//---------------------------------------------------------------------------
#endif