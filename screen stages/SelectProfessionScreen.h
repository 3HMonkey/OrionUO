/****************************************************************************
**
** SelectProfessionScreen.h
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
#ifndef SelectProfessionScreenH
#define SelectProfessionScreenH
//---------------------------------------------------------------------------
class TSelectProfessionScreen : public TBaseScreen
{
private:
	//!�������� � �������� ������������ ���������� � �����������
	int m_PixelOffset;

	//!��������� ����� ��������� ��������� ���������� � �����������
	DWORD m_LastScrollChangeTime;

	//!��������� �����
	int m_SkillSelection;

	//!�������������� ������� ��� �������� ��������
	static const BYTE ID_SMOOTH_SPS_QUIT = 1;
	static const BYTE ID_SMOOTH_SPS_GO_SCREEN_CHARACTER = 2;
	static const BYTE ID_SMOOTH_SPS_GO_SCREEN_GAME_CONNECT = 3;
	static const BYTE ID_SMOOTH_SPS_GO_SCREEN_CREATE = 4;

	//!������� ������
	TTextTexture m_Text;
	TTextTexture m_TextStat[3];
	TTextTexture m_TextSkillInList[56][2];

	//!�������������� ������
	static const int ID_SPS_QUIT = 1;
	static const int ID_SPS_ARROW_PREV = 2;
	static const int ID_SPS_ARROW_NEXT = 3;
	static const int ID_SPS_ARROW_BACK_PROFESSION = 4;
	static const int ID_SPS_LABEL_BACK_PROFESSION = 5;
	static const int ID_SPS_SCROLLBAR_UP = 6;
	static const int ID_SPS_SCROLLBAR_DOWN = 7;
	static const int ID_SPS_SCROLLBAR = 8;
	static const int ID_SPS_SCROLLBAR_BACKGROUND = 9;
	static const int ID_SPS_STATS_SPHERE = 10;
	static const int ID_SPS_SKILLS_SPHERE = 13;
	static const int ID_SPS_SKILLS_FILED = 16;
	static const int ID_SPS_LABEL = 20;
	static const int ID_SPS_SKILLS_LIST = 50;

	/*!
	��������� ��������� �������������
	@param [__in] x ���������� X
	@param [__in] maxSum ������������ ����� �������������
	@param [__in] maxVal ������������ �������� �������������
	@return 
	*/
	void ShuffleStats(__in int x, __in int maxSum, __in int maxVal);

	/*!
	��������� ��������� �������
	@param [__in] x ���������� X
	@return 
	*/
	void ShuffleSkills(__in int x);

	/*!
	���������� ������
	@param [__in] direction �����������
	@param [__in_opt] divizor ��������
	@return 
	*/
	void ListingList(__in bool direction, __in_opt int divizor = 1);

	/*!
	�������� ������ �����������
	@return 
	*/
	int GetScrollBoxHeight();

	/*!
	���������/����� �������� (������ ������ ��������)
	@param [__in] mode true - ���������, false - �����
	@return ��� ������ �������� - ������������� ���������� �������
	*/
	int RenderOld(__in bool &mode);

	/*!
	���������/����� �������� (����� ������ ��������)
	@param [__in] mode true - ���������, false - �����
	@return ��� ������ �������� - ������������� ���������� �������
	*/
	int RenderNew(__in bool &mode);
public:
	TSelectProfessionScreen();
	virtual ~TSelectProfessionScreen();

	/*!
	�������������
	@return 
	*/
	void Init();

	/*!
	��������� ������� ����� �������� ���������� ������
	@param [__in_opt] action ������������� ��������
	@return 
	*/
	void ProcessSmoothAction(__in_opt BYTE action = 0xFF);

	/*!
	������������� ����������� ���������
	@return 
	*/
	void InitToolTip();

	/*!
	���������/����� ��������
	@param [__in] mode true - ���������, false - �����
	@return ��� ������ �������� - ������������� ���������� �������
	*/
	int Render(__in bool mode);



	/*!
	������� ����� ������ ����
	@return 
	*/
	void OnLeftMouseDown();

	/*!
	���������� ����� ������ ����
	@return 
	*/
	void OnLeftMouseUp();

	/*!
	��������� ������� ������ (��������) ����
	@param [__in] state ��������� ��������
	@return 
	*/
	void OnMouseWheel(__in MOUSE_WHEEL_STATE state);
};
//---------------------------------------------------------------------------
extern TSelectProfessionScreen *SelectProfessionScreen;
//---------------------------------------------------------------------------
#endif