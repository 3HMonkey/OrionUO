/***********************************************************************************
**
** Skills.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "Skills.h"
#include "Managers/FontsManager.h"
//----------------------------------------------------------------------------------
CSkillSort g_SkillSort;
vector<CSkillData> g_Skills;
int g_SkillsCount = 0;
//----------------------------------------------------------------------------------
CSkill::CSkill()
: m_BaseValue(0.0f), m_Value(0.0f), m_Cap(0.0f), m_Status(0)
{
}
//----------------------------------------------------------------------------------
bool CSkillSort::SkillCmp(const char *str1, int len1, const char *str2, int len2)
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
//----------------------------------------------------------------------------------
void CSkillSort::Init()
{
	//��������� ��� ����������� ����������
	memset(m_Skills, 0xFF, sizeof(m_Skills));

	//� �����
	uchar skillBuf[60];
	memset(skillBuf, 0xFF, sizeof(skillBuf));

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
			if (SkillCmp(g_Skills[skillBuf[j]].Name.c_str(), g_Skills[skillBuf[j]].Name.length(), g_Skills[i].Name.c_str(), g_Skills[i].Name.length()))
			{
				//�������� ������ ������
				uchar buf = skillBuf[j];
				//�����������
				skillBuf[j] = (uchar)i;

				//� ���������� ������
				j++;

				//��������� ��������� ������������ � ����������� ������ ��� �������������
				for(; j < parsed; j++)
				{
					uchar ptr = skillBuf[j];
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
//----------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------
