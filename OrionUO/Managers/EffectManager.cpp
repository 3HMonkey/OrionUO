/***********************************************************************************
**
** EffectManager.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "EffectManager.h"
#include "../Game objects/GameWorld.h"
#include "../Game objects/GameEffectMoving.h"
#include "../OrionUO.h"
#include "../Managers/MapManager.h"
//----------------------------------------------------------------------------------
CEffectManager g_EffectManager;
//----------------------------------------------------------------------------------
CEffectManager::CEffectManager()
: CBaseQueue()
{
}
//----------------------------------------------------------------------------------
/*!
�������� ������
@param [__in] effect ������ �� ������
@return 
*/
void CEffectManager::AddEffect(CGameEffect *effect)
{
	switch (effect->EffectType)
	{
		case EF_MOVING:
		case EF_STAY_AT_POS:
		case EF_DRAG:
		{
			if (effect->EffectType == EF_MOVING)
			{
				CGameObject *obj = g_World->FindWorldObject(effect->DestSerial);
				if (obj != NULL)
				{
					obj = obj->GetTopObject();

					if (obj != NULL)
					{
						effect->DestX = obj->X;
						effect->DestY = obj->Y;
						effect->DestZ = obj->Z;
					}
				}

				CGameEffectMoving *moving = (CGameEffectMoving*)effect;

				if (moving->X == moving->DestX && moving->Y == moving->DestY)
				{
					if (moving->Explode && obj != NULL)
						CreateExplodeEffect(moving);

					delete effect;

					return;
				}
			}

			if (effect->EffectType != EF_STAY_AT_POS)
			{
				CGameEffectDrag *effectDrag = (CGameEffectDrag*)effect;
				effectDrag->OffsetX = 0;
				effectDrag->OffsetY = 0;
			}

			Add(effect);

			g_MapManager->AddRender(effect);

			effect->Update(NULL);

			break;
		}
		case EF_LIGHTING:
		case EF_STAY_AT_SOURCE:
		{
			CGameObject *obj = g_World->FindWorldObject(effect->Serial);
			if (obj != NULL)
			{
				if (effect->EffectType == EF_LIGHTING)
				{
					g_Orion.ExecuteGumpPart(0x4E20, 10);

					effect->Duration = g_Ticks + 400;
					effect->Speed = 50;
				}

				obj->AddEffect(effect);
			}
			else
				delete effect;

			break;
		}
		default:
			break;
	}
}
//----------------------------------------------------------------------------------
/*!
������� ������
@param [__in] effect ������ �� ������
@return 
*/
void CEffectManager::RemoveEffect(CGameEffect *effect)
{
	Unlink(effect);

	effect->m_Next = NULL;
	effect->m_Prev = NULL;
	delete effect;
}
//----------------------------------------------------------------------------------
/*!
������� ������ ������
@param [__in] effect ������ �� ������
@return 
*/
void CEffectManager::CreateExplodeEffect(CGameEffect *effect)
{
	CGameEffect *newEffect = new CGameEffect();

	newEffect->EffectType = EF_STAY_AT_SOURCE;
	newEffect->Serial = effect->DestSerial;
	newEffect->Graphic = 0x36CB;
	newEffect->Speed = 50;
	newEffect->Duration = g_Ticks + 400;
	//newEffect->FixedDirection = (fixedDirection != 0);
	
	newEffect->Color = effect->Color;
	newEffect->RenderMode = effect->RenderMode;

	AddEffect(newEffect);
}
//----------------------------------------------------------------------------------
/*!
���������� ��������
@return 
*/
void CEffectManager::UpdateEffects()
{
	for (CGameEffect *effect = (CGameEffect*)m_Items; effect != NULL;)
	{
		CGameEffect *next = (CGameEffect*)effect->m_Next;

		effect->Update(NULL);

		effect = next;
	}
}
//----------------------------------------------------------------------------------
/*!
�������� ��������, �������� �� ������� ������
@return 
*/
void CEffectManager::RemoveRangedEffects()
{
}
//----------------------------------------------------------------------------------
