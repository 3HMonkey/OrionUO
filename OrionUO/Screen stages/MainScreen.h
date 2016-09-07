/***********************************************************************************
**
** MainScreen.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef MAINSCREEN_H
#define MAINSCREEN_H
//----------------------------------------------------------------------------------
#include "BaseScreen.h"
#include "../Gumps/GumpScreenMain.h"
//----------------------------------------------------------------------------------
class CMainScreen : public CBaseScreen
{
private:
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
	string CryptPW(const char *buf, int len);

	/*!
	����������� ������
	@param [__in] buf ������������� ������
	@param [__in] len ����� ������
	@return �������������� ������
	*/
	string DecryptPW(const char *buf, int len);

	/*!
	�������� ��� ������� �� �����
	@param [__in] key ����
	@return ��� �������
	*/
	int GetConfigKeyCode(const string &key);

	CGumpScreenMain m_MainGump;

public:
	CMainScreen();
	virtual ~CMainScreen();

	//!�������������� ������� ��� �������� ��������
	static const uchar ID_SMOOTH_MS_QUIT = 1;
	static const uchar ID_SMOOTH_MS_CONNECT = 2;

	//!���� ��� ����� �������� � ������
	CEntryText *m_Account;
	CEntryText *m_Password;
	CGUICheckbox *m_SavePassword;
	CGUICheckbox *m_AutoLogin;

	/*!
	��������� ������� ����� �������� ���������� ������
	@param [__in_opt] action ������������� ��������
	@return 
	*/
	void ProcessSmoothAction(uchar action = 0xFF);

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



	virtual void OnCharPress(const WPARAM &wParam, const LPARAM &lParam);
	virtual void OnKeyDown(const WPARAM &wParam, const LPARAM &lParam);
 };
 //----------------------------------------------------------------------------------
 extern CMainScreen g_MainScreen;
 //----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
