#include "stdafx.h"
#include "BoxCollider.h"

CBoxCollider::CBoxCollider(CGameObject * const owner, float width, float height)
	:CBaseComponent(owner, COMPONENTID::COLLISION),
	m_iWidth(width), m_iHeight(height)
{
	m_rcBound = { 0,0,0,0 };
	Update_Rect();
}

CBoxCollider::~CBoxCollider()
{
}

int CBoxCollider::Update_Component()
{
	Update_Rect();
	return NO_EVENT;
}

void CBoxCollider::LateUpdate_Component()
{
}

void CBoxCollider::Render_Component()
{
}

void CBoxCollider::Release_Component()
{
}

bool CBoxCollider::CheckCollision(CBoxCollider * pDst)
{
	RECT rt;
	return IntersectRect(&rt, &m_rcBound, &pDst->GetBound());
}

void CBoxCollider::Update_Rect()
{
	D3DXVECTOR3 pos = m_pObject->GetPos();

	m_rcBound.left =(LONG)( pos.x - (m_iWidth*0.5f));
	m_rcBound.top = (LONG)(pos.y - (m_iHeight*0.5f));
	m_rcBound.right = (LONG)(pos.x + (m_iWidth*0.5f));
	m_rcBound.bottom = (LONG)(pos.y + (m_iHeight*0.5f));
}
