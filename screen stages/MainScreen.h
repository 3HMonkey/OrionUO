/****************************************************************************
**
** MainScreen.h
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
#ifndef MainScreenH
#define MainScreenH
//---------------------------------------------------------------------------
class TMainScreen : public TBaseScreen
{
private:
	//!�������������� ������� ��� �������� ��������
	static const BYTE ID_SMOOTH_MS_QUIT = 1;
	static const BYTE ID_SMOOTH_MS_CONNECT = 2;

	//!�������������� ������
	static const int ID_MS_QUIT = 1;
	static const int ID_MS_ARROW_NEXT = 2;
	static const int ID_MS_ACCOUNT = 3;
	static const int ID_MS_PASSWORD = 4;
	static const int ID_MS_SAVEPASSWORD = 5;
	static const int ID_MS_AUTOLOGIN = 6;

	enum
	{
		MSCC_ACTID = 1,
		MSCC_ACTPWD,
		MSCC_REMEMBERPWD,
		MSCC_AUTOLOGIN,
		MSCC_SMOOTHMONITOR_SCALE,
		MSCC_SMOOTHMONITOR
	};

	/*!
	���������� ������ ��� ���������� � ������
	@param [__in] buf �� ������������� ������
	@param [__in] len ����� ������
	@return ������������� ������
	*/
	string CryptPW(__in const char *buf, __in int len);

	/*!
	����������� ������
	@param [__in] buf ������������� ������
	@param [__in] len ����� ������
	@return �������������� ������
	*/
	string DecryptPW(__in const char *buf, __in int len);

	/*!
	�������� ��� ������� �� �����
	@param [__in] key ����
	@return ��� �������
	*/
	int GetConfigKeyCode(__in string &key);

public:
	TMainScreen();
	virtual ~TMainScreen();

	//!���� ��� ����� �������� � ������
	TEntryText *m_Account;
	TEntryText *m_Password;
	TEntryText *m_PasswordFake;
	TGumpInterfaceButton *m_Arrow;
	TGumpInterfaceCheckbox *m_SavePassword;
	TGumpInterfaceCheckbox *m_AutoLogin;

	/*!
	��������� ������� ����� �������� ���������� ������
	@param [__in_opt] action ������������� ��������
	@return 
	*/
	void ProcessSmoothAction(__in_opt BYTE action = 0xFF);

	/*!
	�������� �������
	@return 
	*/
	void LoadGlobalConfig();

	/*!
	���������� �������
	@return 
	*/
	void SaveGlobalConfig();

	/*!
	�������������
	@return 
	*/
	void Init();

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
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return 
	*/
	void OnCharPress(__in WPARAM wparam, __in LPARAM lparam);

	/*!
	��������� ������� �������
	@param [__in] wparam �� ����������� ��������
	@param [__in] lparam �� ����������� ��������
	@return 
	*/
	void OnKeyPress(__in WPARAM wparam, __in LPARAM lparam);
 };
//---------------------------------------------------------------------------
extern TMainScreen *MainScreen;
//---------------------------------------------------------------------------
#endif