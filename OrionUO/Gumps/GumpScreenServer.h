/***********************************************************************************
**
** GumpScreenServer.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GUMPSCREENSERVER_H
#define GUMPSCREENSERVER_H
//----------------------------------------------------------------------------------
#include "Gump.h"
//----------------------------------------------------------------------------------
class CGumpScreenServer : public CGump
{
private:
	//!�������������� ������
	static const int ID_SS_QUIT = 1;
	static const int ID_SS_ARROW_PREV = 2;
	static const int ID_SS_ARROW_NEXT = 3;
	static const int ID_SS_TIME_ZONE = 4;
	static const int ID_SS_FULL = 5;
	static const int ID_SS_CONNECTION = 6;
	static const int ID_SS_EARTH = 7;
	static const int ID_SS_HTML_GUMP = 8;
	static const int ID_SS_SERVER_LIST = 10;

public:
	CGumpScreenServer();
	virtual ~CGumpScreenServer();

	virtual void UpdateContent();

	virtual void InitToolTip();



	virtual void OnButton(const uint &serial);

	virtual void OnTextEntry(const uint &serial);
 };
 //----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
