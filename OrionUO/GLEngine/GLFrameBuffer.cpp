/***********************************************************************************
**
** GLFrameBuffer.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "GLFrameBuffer.h"
#include "GLEngine.h"
//----------------------------------------------------------------------------------
CGLFrameBuffer::CGLFrameBuffer()
: m_Width(0), m_Height(0), m_Ready(false), m_OldFrameBuffer(0), m_FrameBuffer(0),
m_Texture(0)
{
}
//----------------------------------------------------------------------------------
CGLFrameBuffer::~CGLFrameBuffer()
{
	Free();
}
//----------------------------------------------------------------------------------
/*!
�������������� ������
@param [__in] width ������ ������
@param [__in] height ������ ������
@return true � ������ ������
*/
bool CGLFrameBuffer::Init(int width, int height)
{
	Free();

	bool result = false;

	if (g_GL.CanUseFrameBuffer)
	{
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB5_A1, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		GLint currentFrameBuffer = 0;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFrameBuffer); 

		glGenFramebuffers(1, &m_FrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_Texture, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		{
			m_Width = width;
			m_Height = height;

			result = true;
			m_Ready = true;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, currentFrameBuffer);
	}

	return result;
}
//----------------------------------------------------------------------------------
/*!
������� �����������
@return
*/
void CGLFrameBuffer::Free()
{
	if (m_Texture != 0)
	{
		glDeleteTextures(1, &m_Texture);
		m_Texture = 0;
	}

	if (m_FrameBuffer != 0)
	{
		glDeleteFramebuffers(1, &m_FrameBuffer);
		m_FrameBuffer = 0;
	}

	m_OldFrameBuffer = 0;
}
//----------------------------------------------------------------------------------
/*!
���������� ������������� �����������
@return 
*/
void CGLFrameBuffer::Release()
{
	if (g_GL.CanUseFrameBuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_OldFrameBuffer);
	
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}
//----------------------------------------------------------------------------------
/*!
�������� ���������� ������ � ������������� �������������
@param [__in] width ������ ������
@param [__in] height ������ ������
@return true � ������ ����������
*/
bool CGLFrameBuffer::Ready( __in int &width, __in int &height)
{
	return (g_GL.CanUseFrameBuffer && m_Ready && m_Width == width && m_Height == height);
}
//----------------------------------------------------------------------------------
/*!
������������� ������
@return true � ������ ������
*/
bool CGLFrameBuffer::Use()
{
	bool result = false;

	if (g_GL.CanUseFrameBuffer && m_Ready)
	{
		glEnable(GL_TEXTURE_2D);
		
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_OldFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
        glBindTexture(GL_TEXTURE_2D, m_Texture);

		glViewport(0, 0, m_Width, m_Height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		glOrtho(0.0, m_Width, 0.0, m_Height, -150.0, 150.0);

		glMatrixMode(GL_MODELVIEW);
		
		result = true;
	}

	return result;
}
//----------------------------------------------------------------------------------
/*!
���������� �������� ������
@param [__in] x �������� ���������� X
@param [__in] y �������� ���������� Y
@return 
*/
void CGLFrameBuffer::Draw( __in int x, __in int y)
{
	if (g_GL.CanUseFrameBuffer && m_Ready)
	{
		g_GL.OldTexture = 0;
		g_GL.Draw(m_Texture, x, y, m_Width, m_Height);
	}
}
//----------------------------------------------------------------------------------

