/****************************************************************************
**
** ConnectionScreen.h
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
#ifndef ConnectionScreenH
#define ConnectionScreenH
//---------------------------------------------------------------------------
class TConnectionScreen : public TBaseScreen
{
private:
	//!���� �������� �����������
	bool m_ConnectionFailed;

	//!���� �����������
	bool m_Connected;

	//!���� ���������� ������ ������
	bool m_Completed;

	//!��� ������
	int m_ErrorCode;

	//!��� ������
	CONNECTION_SCREEN_TYPE m_Type;

	//!������� ������
	TTextTexture m_Text[32];

	//!�������������� ������� ��� �������� ��������
	static const BYTE ID_SMOOTH_CS_GO_SCREEN_MAIN = 1;
	static const BYTE ID_SMOOTH_CS_GO_SCREEN_CHARACTER = 2;
	static const BYTE ID_SMOOTH_CS_GO_SCREEN_PROFESSION = 3;
	static const BYTE ID_SMOOTH_CS_SEND_DELETE = 4;

	//!�������������� ������
	static const int ID_CS_OK = 1;
	static const int ID_CS_CANCEL = 2;

public:
	TConnectionScreen();
	~TConnectionScreen();
	
	SETGET(bool, ConnectionFailed);
	SETGET(bool, Connected);
	SETGET(bool, Completed);
	SETGET(int, ErrorCode);
	SETGET(CONNECTION_SCREEN_TYPE, Type);

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
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return 
	*/
	void OnKeyPress(__in WPARAM wparam, __in LPARAM lparam);

};
//---------------------------------------------------------------------------
extern TConnectionScreen *ConnectionScreen;
//---------------------------------------------------------------------------
#endif