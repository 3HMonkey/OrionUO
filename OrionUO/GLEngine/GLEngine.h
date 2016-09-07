/***********************************************************************************
**
** GLEngine.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GLENGINE_H
#define GLENGINE_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../Wisp/WispLogger.h"
#include "../Wisp/WispGeometry.h"
#include "GLTexture.h"
#include "GLVector.h"
//----------------------------------------------------------------------------------
typedef deque<WISP_GEOMETRY::CRect> SCISSOR_LIST;
//----------------------------------------------------------------------------------
class CGLEngine
{
	SETGET(HDC, DC);
	SETGET(HGLRC, RC);
	SETGET(GLuint, OldTexture);
	SETGET(bool, Drawing);
	SETGET(bool, CanUseFrameBuffer);
	SETGET(float, SittingCharacterOffset);

private:
	bool GLSetupPixelFormat();

	SCISSOR_LIST m_ScissorList;

public:
	CGLEngine();
	virtual ~CGLEngine();
	
	//������������� OpenGL
	bool Install();

	//���������� ������ � OpenGL
	void Uninstall();

	//���������� ������� ������
	void UpdateRect();

	//�������� ������� 16 � 32 ���
	void BindTexture16(GLuint &texture, const int &width, const int &height, pushort pixels);
	void BindTexture32(GLuint &texture, const int &width, const int &height, puint pixels);

	//�������� ����� � ������ ���������
	void BeginDraw();

	//��������� ��������� � ������� ��� ������������ �� �����
	void EndDraw();

	//�������� ����� ���������
	void BeginStencil();

	//��������� ����� ���������
	void EndStencil();

	//������� ������� ���������
	void ViewPortScaled(const int &x, const int &y, const int &width, const int &height);

	//������� ������� ���������
	void ViewPort(const int &x, const int &y, const int &width, const int &height);

	//������������ ����������� ������� ���������
	void RestorePort();

	//������� ������� ��������� (���������, ��������� �������)
	void PushScissor(const int &x, const int &y, const int &width, const int &height);
	void PushScissor(const WISP_GEOMETRY::CPoint2Di &position, const int &width, const int &height);
	void PushScissor(const int &x, const int &y, const WISP_GEOMETRY::CSize &size);
	void PushScissor(const WISP_GEOMETRY::CPoint2Di &position, const WISP_GEOMETRY::CSize &size);
	void PushScissor(const WISP_GEOMETRY::CRect &rect);

	void PopScissor();

	void ClearScissorList();



	//���������� �����
	void DrawLine(const int &x, const int &y, const int &targetX, const int &targetY);

	//���������� �������������
	void DrawPolygone(const int &x, const int &y, const int &width, const int &height);

	//���������� ����
	void DrawCircle(const float &x, const float &y, const float &radius, const int &gradientMode = 0);



	//���������� �������� ���������
	void DrawLandTexture(GLuint &texture, const int &x, const int &y, const RECT &rc, CVector *normals);

	//���������� ��������
	void Draw(GLuint &texture, const int &x, const int &y, const int &width, const int &height);

	//���������� ���������� ��������
	void DrawRotated(GLuint &texture, const int &x, const int &y, const int &width, const int &height, const float &angle);

	//���������� �������� � ������������ ����������� ���������
	void Draw(GLuint &texture, const int &x, const int &y, const int &width, const int &height, const bool &mirror);

	//���������� �������� �������� ���������
	void DrawSitting(GLuint &texture, const int &x, const int &y, const float &width, const float &height, const bool &mirror, const float &h3mod, const float &h6mod, const float &h9mod);

	//���������� ����
	void DrawShadow(GLuint &texture, const int &x, const int &y, const float &width, const float &height, const bool &mirror);

	//��������� �������� �� �������� ��������
	void Draw(GLuint &texture, const int &x, const int &y, const int &width, const int &height, const int &drawWidth, const int &drawHeight);

	//���������� ���
	void DrawResizepic(CGLTexture **th, const int &x, const int &y, const int &width, const int &height);
};
//---------------------------------------------------------------------------
extern CGLEngine g_GL;
//---------------------------------------------------------------------------
#endif