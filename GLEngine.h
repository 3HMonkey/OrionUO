/****************************************************************************
**
** GLEngine.h
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
#ifndef GLEngineH
#define GLEngineH
//---------------------------------------------------------------------------
class TVector;
//---------------------------------------------------------------------------
//����� �� ������ � ��������� OpenGL
class TGLEngine
{
private:
	//�������� ����������
	HDC m_DC;

	//�������� OpenGL
	HGLRC m_RC;

	//��������� ������� ������
	bool GLSetupPixelFormat();

	//������ ��������� �������������� ��������
	GLuint m_OldTexture;

public:
	TGLEngine() {m_DC = NULL; m_RC = NULL;}
	~TGLEngine() {}
	
	HDC GetDC() const {return m_DC;}
	HGLRC GetRC() const {return m_RC;}

	SETGET(GLuint, OldTexture);

	//������������� OpenGL
	bool Install(HWND hWnd);

	//���������� ������ � OpenGL
	void Uninstall() {wglMakeCurrent(NULL, NULL); wglDeleteContext(m_RC);}

	//���������� ������� ������
	void UpdateRect();

	//�������� ������� 16 � 32 ���
	void BindTexture16(GLuint &texture, const int &width, const int &height, PWORD pixels);
	void BindTexture32(GLuint &texture, const int &width, const int &height, PDWORD pixels);

	//�������� ����� � ������ ���������
	void BeginDraw();

	//��������� ��������� � ������� ��� ������������ �� �����
	void EndDraw();

	//�������� ����� ���������
	void BeginStencil();

	//��������� ����� ���������
	void EndStencil();

	//������� ������� ���������
	void ViewPort(const int &x, const int &y, const int &width, const int &height);

	//������������ ����������� ������� ���������
	void RestorePort();

	//������� ������� ��������� (���������, ��������� �������)
	void Scissor(const int &x, const int &y, const int &width, const int &height);



	//���������� �����
	void DrawLine(const int &x, const int &y, const int &targetX, const int &targetY);

	//���������� �������������
	void DrawPolygone(const int &x, const int &y, const int &width, const int &height);

	//���������� ����
	void DrawCircle(const float &x, const float &y, const float &radius, const int &gradientMode = 0);



	//���������� �������� ���������
	void DrawLandTexture(GLuint &texture, const int &x, const int &y, RECT &rc, TVector *normals);

	//���������� ��������
	void Draw(GLuint &texture, const int &x, const int &y, const int &width, const int &height);

	//���������� ���������� ��������
	void DrawRotated(GLuint &texture, const int &x, const int &y, const int &width, const int &height, const float &angle);

	//���������� �������� � ������������ ����������� ���������
	void Draw(GLuint &texture, const int &x, const int &y, const int &width, const int &height, const bool &mirror);

	//���������� �������� �������� ���������
	void DrawSitting(GLuint &texture, const int &x, const int &y, const int &width, const int &height, const bool &mirror, bool twistTexture = true);

	//���������� ����
	void DrawShadow(GLuint &texture, const int &x, const int &y, const int &width, const int &height, const bool &mirror);

	//��������� �������� �� �������� ��������
	void Draw(GLuint &texture, const int &x, const int &y, const int &width, const int &height, const int &drawWidth, const int &drawHeight);

	//���������� ���
	void DrawResizepic(TTextureObject **th, const int &x, const int &y, const int &width, const int &height);
};
//---------------------------------------------------------------------------
extern TGLEngine g_GL;
//---------------------------------------------------------------------------
#endif