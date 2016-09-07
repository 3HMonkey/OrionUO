/***********************************************************************************
**
** CreateCharacterManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef CREATECHARACTERMANAGER_H
#define CREATECHARACTERMANAGER_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../TextEngine/EntryText.h"
//----------------------------------------------------------------------------------
//!���������� � ��������� �������
struct CC_HAIR_STYLE
{
	//!������ �����
	ushort GumpID;

	//!������ �������� �� Art.mul
	ushort GraphicID;

	//!��������
	string Name;
};
//----------------------------------------------------------------------------------
//!����� ��������� �������� ����������
class CCreateCharacterManager
{
	SETGET(bool, Sex);
	SETGET(char, Rase);
	SETGET(uchar, HairStyle);
	SETGET(uchar, BeardStyle);
	SETGET(ushort, SkinTone);
	SETGET(ushort, ShirtColor);
	SETGET(ushort, PantsColor);
	SETGET(ushort, HairColor);
	SETGET(ushort, BeardColor);

private:
	//!�������� ������ �������� � ������
	static CC_HAIR_STYLE m_MaleHairStyleTable[10];
	static CC_HAIR_STYLE m_FemaleHairStyleTable[11];
	static CC_HAIR_STYLE m_BeardStyleTable[8];

public:
	CCreateCharacterManager();
	~CCreateCharacterManager();


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
	CC_HAIR_STYLE GetHair(uchar pos) const;

	/*!
	�������� ����� ������
	@param [__in] pos ������ ������
	@return ��������� � ������� � ������
	*/
	CC_HAIR_STYLE GetBeard(uchar pos) const;

};
//----------------------------------------------------------------------------------
//!�������� �������� ���������
extern CCreateCharacterManager g_CreateCharacterManager;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
