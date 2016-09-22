/***********************************************************************************
**
** GameEffect.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "GameEffect.h"
#include "../OrionUO.h"
#include "GameEffectDrag.h"
#include "GameEffectMoving.h"
#include "../Managers/EffectManager.h"
#include "../Managers/FileManager.h"
#include "../Game objects/GameObject.h"
//----------------------------------------------------------------------------------
CGameEffect::CGameEffect()
: CRenderWorldObject(ROT_EFFECT, 0, 0, 0, 0, 0, 0), m_EffectType(EF_MOVING),
m_DestSerial(0), m_DestX(0), m_DestY(0), m_DestZ(0), m_Speed(0), m_Duration(0),
m_FixedDirection(false), m_Explode(false), m_RenderMode(0), m_AnimIndex(0),
m_Increment(0), m_LastChangeFrameTime(0)
{
	m_RenderQueueIndex = 8;
}
//----------------------------------------------------------------------------------
CGameEffect::~CGameEffect()
{
}
//----------------------------------------------------------------------------------
/*!
���������� ������
@param [__in] mode ����� ���������. true - ���������, false - ����� ��������
@param [__in] drawX �������� ���������� X �������
@param [__in] drawY �������� ���������� Y �������
@param [__in] ticks ������ �������
@return ��� ������ �������� ���������� ��������� �������
*/
void CGameEffect::Draw(const int &x, const int &y)
{
#if UO_DEBUG_INFO!=0
	g_RenderedObjectsCountInGameWindow++;
#endif

	ushort objGraphic = GetCurrentGraphic();

	ApplyRenderMode();

	if (m_EffectType == EF_MOVING)
	{
		CGameEffectMoving *moving = (CGameEffectMoving*)this;

		int drawEffectX = x + moving->OffsetX;
		int drawEffectY = y + moving->OffsetY + moving->OffsetZ;

		if (moving->FixedDirection)
			g_Orion.DrawStaticArt(objGraphic, m_Color, drawEffectX, drawEffectY, m_Z);
		else
			g_Orion.DrawStaticArtRotated(objGraphic, m_Color, drawEffectX, drawEffectY, m_Z, moving->Angle);
	}
	else if (m_EffectType == EF_DRAG)
	{
		CGameEffectDrag *dragEffect = (CGameEffectDrag*)this;

		g_Orion.DrawStaticArt(m_Graphic, m_Color, x - dragEffect->OffsetX, y - dragEffect->OffsetY, m_Z);
	}
	else
		g_Orion.DrawStaticArt(objGraphic, m_Color, x, y, m_Z);

	RemoveRenderMode();
}
//----------------------------------------------------------------------------------
void CGameEffect::Update(CGameObject *parent)
{
	if (m_EffectType != EF_MOVING)
	{
		if (m_Duration < g_Ticks)
		{
			if (parent != NULL)
				parent->RemoveEffect(this);
			else
				g_EffectManager.RemoveEffect(this);
		}
		else if (m_LastChangeFrameTime < g_Ticks)
		{
			m_LastChangeFrameTime = g_Ticks + m_Speed;

			if (m_EffectType == EF_LIGHTING)
			{
				m_AnimIndex++;

				if (m_AnimIndex >= 10)
				{
					if (parent != NULL)
						parent->RemoveEffect(this);
					else
						g_EffectManager.RemoveEffect(this);
				}
			}
			else
				CalculateCurrentGraphic();
		}
	}
	else if (m_LastChangeFrameTime < g_Ticks)
	{
		m_LastChangeFrameTime = g_Ticks + 50;

		CalculateCurrentGraphic();
	}
}
//----------------------------------------------------------------------------------
/*!
��������� ������� ������ ��������
@return ������ ��������
*/
ushort CGameEffect::CalculateCurrentGraphic()
{
	uint addressAnimData = (uint)g_FileManager.m_AnimdataMul.Start;

	if (addressAnimData)
	{
		uint addr = (m_Graphic * 68) + 4 * ((m_Graphic / 8) + 1);
		PANIM_DATA pad = (PANIM_DATA)(addressAnimData + addr);

		if (m_AnimIndex < (int)pad->FrameCount)
		{
			m_Increment = pad->FrameData[m_AnimIndex];
			m_AnimIndex++;
		}

		if (m_AnimIndex >= (int)pad->FrameCount)
			m_AnimIndex = 0;
	}

	return m_Graphic + m_Increment;
}
//----------------------------------------------------------------------------------
/*!
�������� ������� ������ ��������
@return ������ ��������
*/
ushort CGameEffect::GetCurrentGraphic()
{
	return m_Graphic + m_Increment;
}
//----------------------------------------------------------------------------------
/*!
���������� ������ �����������
@return 
*/
void CGameEffect::ApplyRenderMode()
{
	switch (m_RenderMode)
	{
		case 1: //ok
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_ZERO, GL_SRC_COLOR);
			break;
		}
		case 2: //ok
		case 3: //ok
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			break;
		}
		case 4: //?
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
			break;
		}
		case 5: //?
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
			break;
		}
		case 6: //ok
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
			glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
			break;
		}
		default:
			break;
	}
}
//----------------------------------------------------------------------------------
/*!
������ ������ �����������
@return 
*/
void CGameEffect::RemoveRenderMode()
{
	switch (m_RenderMode)
	{
		case 1: //ok
		case 2: //ok
		case 3: //ok
		{
			glDisable(GL_BLEND);
			break;
		}
		case 4:
		{
			glDisable(GL_BLEND);
			break;
		}
		case 5:
		{
			glDisable(GL_BLEND);
			break;
		}
		case 6: //ok
		{
			glDisable(GL_BLEND);
			glBlendEquation(GL_FUNC_ADD);
			break;
		}
		default:
			break;
	}
}
//---------------------------------------------------------------------------