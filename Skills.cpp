/****************************************************************************
**
** Skills.cpp
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
#include "stdafx.h"

TSkillSort g_SkillSort;
PSKILLS_DATA g_Skills = NULL;
int g_SkillsCount = 0;
//---------------------------------------------------------------------------
TSkill::TSkill()
: m_BaseValue(0.0f), m_Value(0.0f), m_Cap(0.0f), m_Status(0)
{
}
//---------------------------------------------------------------------------
bool TSkillSort::SkillCmp(const char *str1, int len1, const char *str2, int len2)
{
	//��������� ����������� ����� ������ ��� ���������
	int len = len1;
	if (len > len2)
		len = len2;

	bool result = false;

	//��������� �� ���� �������� ���� ������, ��������� �� ���� � ������
	IFOR(i, 0, len)
	{
		if (str1[i] < str2[i])
		{
			result = true;
			break;
		}
		else if (str1[i] > str2[i])
		{
			result = false;
			break;
		}
	}

	//������ ��� ����������
	return result;
}
//---------------------------------------------------------------------------
void TSkillSort::Init()
{
	//��������� ��� ����������� ����������
	memset(m_Skills, 0xFF, sizeof(m_Skills));

	//� �����
	BYTE skillBuf[60];
	memset(skillBuf, 0xFF, sizeof(skillBuf));

	//��������� �� ������
	PSKILLS_DATA skills = g_Skills;

	//��������� ������ ������� ����� � ���������� ������������ ������� - 1
	int parsed = 1;
	skillBuf[0] = 0;

	//��������� �� ���� ������ (����� �������)
	IFOR(i, 1, g_SkillsCount)
	{
		//TPRINT("Skill[%d] = %s\n", i, skills[i].SkillName);

		//��������� �� ������������
		IFOR(j, 0, parsed)
		{
			//���� ����� �������� � ������� ������� - 
			if (SkillCmp(skills[skillBuf[j]].m_Name.c_str(), skills[skillBuf[j]].m_Name.length(), skills[i].m_Name.c_str(), skills[i].m_Name.length()))
			{
				//�������� ������ ������
				BYTE buf = skillBuf[j];
				//�����������
				skillBuf[j] = (BYTE)i;

				//� ���������� ������
				j++;

				//��������� ��������� ������������ � ����������� ������ ��� �������������
				for(; j < parsed; j++)
				{
					BYTE ptr = skillBuf[j];
					skillBuf[j] = buf;
					buf = ptr;
				}

				//������� ������ � ������� ������������
				skillBuf[parsed] = buf;

				//����������� �������
				parsed++;

				break;
			}
		}
	}

	//�������������� ������� �������
	for (int i = 0, j = parsed - 1; i < parsed; i++, j--)
		m_Skills[i] = skillBuf[j];
}
//---------------------------------------------------------------------------
string g_SkillName[54] =
{
	"Alchemy",
	"Anatomy",
	"AnimalLore",
	"Item ID",
	"Arms Lore",
	"Parrying",
	"Begging",
	"Blacksmith",
	"Bowcraft",
	"Peacemaking",
	"Camping",
	"Carpentry",
	"Cartography",
	"Cooking",
	"Detect Hidden",
	"Enticement",
	"EvaluateIntelligence",
	"Healing",
	"Fishing",
	"Forensic Evaluation",
	"Herding",
	"Hiding",
	"Provocation",
	"Inscription",
	"Lockpicking",
	"Magery",
	"ResistingSpells",
	"Tactics",
	"Snooping",
	"Musicianship",
	"Poisoning",
	"Archery",
	"Spirit Speak",
	"Stealing",
	"Tailoring",
	"AnimalTaming",
	"Taste Identification",
	"Tinkering",
	"Tracking",
	"Veterinary",
	"Swordsmanship",
	"MaceFighting",
	"Fencing",
	"Wrestling",
	"Lumberjacking",
	"Mining",
	"Meditation",
	"Stealth",
	"Remove Trap",
	"Necromancy",
	"Focus",
	"Chivalry",
	"Bushido",
	"Ninjitsu"
};
//---------------------------------------------------------------------------