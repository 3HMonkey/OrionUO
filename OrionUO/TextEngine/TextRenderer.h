/***********************************************************************************
**
** TextRenderer.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H
//----------------------------------------------------------------------------------
#include "RenderTextObject.h"
#include "../ImageBounds.h"
#include "../RenderWorldObject.h"
//----------------------------------------------------------------------------------
//����� ��� ��������� ������ ������ �� �����
class CTextRenderer : public CRenderTextObject
{
private:
	//������ ���������, ������� �������
	deque<CTextImageBounds> m_TextRect;

public:
	CTextRenderer();
	virtual ~CTextRenderer();

	//������ ������
	CRenderTextObject *m_TextItems;

	CRenderTextObject *m_DrawPointer;

	//�������� �����
	CRenderTextObject *AddText(CRenderTextObject *obj);

	//����������� ����� ������ �������
	void ToTop(CRenderTextObject *obj);

	//�������� ���������� ������
	void AddRect(CTextImageBounds &rect) { m_TextRect.push_back(rect); }

	//�������� ������ ��������� ������
	void ClearRect() { m_TextRect.clear(); }

	//��������, ���� �� ����� � �����������
	bool InRect(CTextImageBounds &rect, CRenderWorldObject *rwo);

	bool CalculatePositions(const bool &noCalculate);

	void Draw();

	void Select(class CGump *gump);

	bool CalculateWorldPositions(const bool &noCalculate);

	void WorldDraw();
};
//----------------------------------------------------------------------------------
extern CTextRenderer g_WorldTextRenderer;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
