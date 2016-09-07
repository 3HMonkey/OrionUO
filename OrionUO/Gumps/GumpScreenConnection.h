/***********************************************************************************
**
** GumpScreenConnection.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GUMPSCREENCONNECTION_H
#define GUMPSCREENCONNECTION_H
//----------------------------------------------------------------------------------
#include "Gump.h"
//----------------------------------------------------------------------------------
class CGumpScreenConnection : public CGump
{
private:
	//!�������������� ������
	static const int ID_CS_OK = 1;
	static const int ID_CS_CANCEL = 2;

public:
	CGumpScreenConnection();
	virtual ~CGumpScreenConnection();

	virtual void UpdateContent();



	virtual void OnButton(const uint &serial);
 };
 //----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
