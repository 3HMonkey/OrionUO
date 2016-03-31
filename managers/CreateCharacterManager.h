/****************************************************************************
**
** CreateCharacterManager.h
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
#ifndef CharacterCreateH
#define CharacterCreateH
//---------------------------------------------------------------------------
//!���������� � ��������� �������
struct CC_HAIR_STYLE
{
	//!������ �����
	WORD GumpID;

	//!������ �������� �� Art.mul
	WORD GraphicID;

	//!��������
	string Name;
};
//---------------------------------------------------------------------------
//!����� ��������� �������� ����������
class TCreateCharacterManager
{
private:
	//!��� ���������. false - male; true - female
	bool m_Sex;

	//!����� ���������
	char m_Rase;

	//!������ ����� ��������
	BYTE m_HairStyle;

	//!������ ����� ������
	BYTE m_BeardStyle;

	//!���� ����
	WORD m_SkinTone;

	//!���� ������/��������
	WORD m_ShirtColor;

	//!���� ��������
	WORD m_PantsColor;

	//!���� �����
	WORD m_HairColor;

	//!���� ������
	WORD m_BeardColor;

	//!�������� ������ �������� � ������
	static CC_HAIR_STYLE m_MaleHairStyleTable[10];
	static CC_HAIR_STYLE m_FemaleHairStyleTable[11];
	static CC_HAIR_STYLE m_BeardStyleTable[8];
public:
	TCreateCharacterManager();
	~TCreateCharacterManager();

	//!��������� ��� ���������
	TEntryText *m_Name;

	SETGET(bool, Sex);
	SETGET(char, Rase);
	SETGET(BYTE, HairStyle);
	SETGET(BYTE, BeardStyle);
	SETGET(WORD, SkinTone);
	SETGET(WORD, ShirtColor);
	SETGET(WORD, PantsColor);
	SETGET(WORD, HairColor);
	SETGET(WORD, BeardColor);

	/*!
	�������������
	@return
	*/
	void Init();

	/*!
	�������
	@return
	*/
	void Clear();

	/*!
	�������� ����� �����
	@param [__in] pos ������ �����
	@return ��������� � ������� � �������
	*/
	CC_HAIR_STYLE GetHair(__in BYTE pos) const;

	/*!
	�������� ����� ������
	@param [__in] pos ������ ������
	@return ��������� � ������� � ������
	*/
	CC_HAIR_STYLE GetBeard(__in BYTE pos) const;

};
//---------------------------------------------------------------------------
//!�������� �������� ���������
extern TCreateCharacterManager CreateCharacterManager;
//---------------------------------------------------------------------------
#endif