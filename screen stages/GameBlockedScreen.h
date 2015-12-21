/****************************************************************************
**
** GameBlockedGump.h
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
#ifndef GameBlockedScreenH
#define GameBlockedScreenH
//---------------------------------------------------------------------------
class TGameBlockedScreen : public TBaseScreen
{
private:
	BYTE m_Code;

public:
	TGameBlockedScreen();
	~TGameBlockedScreen();
	
	void Init();
	
	SETGET(BYTE, Code)

	int Render(bool mode);
	
	void OnLeftMouseDown();
	void OnLeftMouseUp();
	void OnCharPress(WPARAM wparam, LPARAM lparam);
	void OnKeyPress(WPARAM wparam, LPARAM lparam);
};

extern TGameBlockedScreen *GameBlockedScreen;
//---------------------------------------------------------------------------
#endif