/***********************************************************************************
**
** GLShader.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GLSHADER_H
#define GLSHADER_H
//----------------------------------------------------------------------------------
#include "GLEngine.h"
//----------------------------------------------------------------------------------
void UnuseShader();
//----------------------------------------------------------------------------------
//������� ����� ��� ������ � ���������
class CGLShader
{
protected:
	//��������� ���������
	GLhandleARB m_Shader;

	//��������� ������
	GLhandleARB m_VertexShader;

	//����������� (����������) ������
	GLhandleARB m_FragmentShader;

	//��������� �� �������� ��� �������� �� ������� (����� �� ������������, �������� ���������� ������������� ��� glBingTexture)
	GLuint m_TexturePointer;

public:
	CGLShader(const char *vertexShaderData, const char *fragmentShaderData);
	virtual ~CGLShader();

	//������������ ������
	virtual bool Use();

	//���������� ������������� �������
	virtual void Pause();

	//������������ ������ �������
	virtual void Resume();
};
//----------------------------------------------------------------------------------
//����� ��� ������ � �������� ������ (�����-����� ������)
class CDeathShader : public CGLShader
{
public:
	CDeathShader(const char *vertexShaderData, const char *fragmentShaderData);
};
//----------------------------------------------------------------------------------
//����� ��� ������ � ������� ��������
class CColorizerShader : public CGLShader
{
protected:
	//��������� �� ������� ������ ��� �������� �� �������
	GLuint m_ColorTablePointer;

	//��������� �� ����� ������ ��������
	GLuint m_DrawModePointer;

public:
	CColorizerShader(const char *vertexShaderData, const char *fragmentShaderData);

	//������������ ������
	virtual bool Use();
};
//----------------------------------------------------------------------------------
extern CGLShader *g_CurrentShader;
extern CDeathShader *g_DeathShader;
extern CColorizerShader *g_ColorizerShader;
extern CColorizerShader *g_FontColorizerShader;
extern CColorizerShader *g_LightColorizerShader;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
