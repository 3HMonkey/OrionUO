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

	//!��������� �� ������� �������
	PBYTE Ptr;

	/*!
	����������� ���������
	@param [__in] offset �������� ���������
	@return 
	*/
	inline void Move(__in int offset) { Ptr += offset; }

	/*!
	��������� ���� (1 ����)
	@return 
	*/
	BYTE ReadByte();

	/*!
	��������� ����� (2 �����)
	@return 
	*/
	WORD ReadWord();

	/*!
	��������� ������� ����� (4 �����)
	@return 
	*/
	DWORD ReadDWord();

	/*!
	��������� ������ (1 ����)
	@return 
	*/
	char ReadChar();

	/*!
	��������� �������� �������� (2 �����)
	@return 
	*/
	short ReadShort();

	/*!
	��������� ����� (4 �����)
	@return 
	*/
	int ReadInt();

	/*!
	��������� ������
	@param [__in] size ������ ������, ���� 0 - ������ �� ����
	@return 
	*/
	string ReadString(__in int size);
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