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
	D3DXVECTOR2 vLine[4] = {
		{ (float)m_rcBound.left,(float)m_rcBound.top },
		{ (float)m_rcBound.right,(float)m_rcBound.top },
		{ (float)m_rcBound.right, (float)m_rcBound.bottom },
		{ (float)m_rcBound.left, (float)m_rcBound.bottom }
	};

	GRAPHICDEVICE->GetLine()->SetWidth(5.f);
	GRAPHICDEVICE->GetLine()->Draw(vLine, 4, D3DCOLOR_ARGB(255, 255, 0, 0));

	GRAPHICDEVICE->GetLine()->End();
}

void CBoxCollider::Release_Component()
{
}

void CBoxCollider::WallCollision()
{
	int collX = m_rcCollision.right - m_rcCollision.left;
	int collY = m_rcCollision.bottom - m_rcCollision.top;

	D3DXVECTOR3 vecMove{ 0,0,0 };
	// �¿� �浹�� �� �߿��� 
	if (collX < collY)
	{
		//�����浹
		if (m_rcCollision.left == m_rcBound.left)
			vecMove.x += collX;
		//�����浹
		if (m_rcCollision.right == m_rcBound.right)
			vecMove.x -= collX;
	}
	else
	{
		if (m_rcCollision.top == m_rcBound.top)
			vecMove.y += collY;
		//���� �浹 
		if (m_rcCollision.bottom == m_rcBound.bottom)
			vecMove.y -= collY;
	}

	vecMove *= 30*TIMEMGR->Get_DeltaTime();
	m_pObject->AddPos(vecMove);

	/*
	//�Ѵ� true �� �� �Ϸθ� �浹�� 
	bool bLeft = false;
	bool bRight = false;
	//���� �浹
	if (m_rcCollision.left == m_rcCollision.left)
		bLeft = true;
	//�����浹
	if (m_rcCollision.right == m_rcCollision.right)
		bRight = true;

	//�Ѵ� true �� �¿�θ� �浹��
	bool bUp = false;
	bool bDown = false;
	//���� �浹
	if (m_rcCollision.top == m_rcCollision.top)
		bUp = true;
	//���� �浹 
	if (m_rcCollision.bottom == m_rcCollision.bottom)
		bDown = true;

	D3DXVECTOR3 vecMove;
	//�� �Ʒ���! �浹 
	if (bLeft && bRight)
	{
		if (bUp)
			vecMove.y += collY;
		else
			vecMove.y -= collY;
	}
	//�� �츸! �浹
	else if (bUp && bDown)
	{
		if (bLeft)
			vecMove.x += collX;
		else
			vecMove.x -= collX;
	}
	else //�����¿� ��� ���� �浹 
	{

	}
	*/
}

bool CBoxCollider::CheckCollision(CBoxCollider * pDst)
{
	return IntersectRect(&m_rcCollision, &m_rcBound, &pDst->GetBound());
	//https://m.blog.naver.com/winterwolfs/10165506488
	//http://www.zeldagalaxy.com/sprites-gbc-ladx/
}

bool CBoxCollider::PointCollision(CBoxCollider * pDst)
{
	/*RECT rcOther = pDst->GetBound();
	if( (m_rcBound.left <= rcOther.left &&  rcOther.left <= m_rcBound.right )
		&& m_rcBound.top <= rcOther.left &&  rcOther.left <= m_rcBound.right)
*/
	return false;
}

void CBoxCollider::Update_Rect()
{
	D3DXVECTOR3 pos = m_pObject->GetPos();
	D3DXVECTOR3 pOut[2];
	D3DXVECTOR3 pIn[2];

	/*m_rcBound.left =(LONG)(pos.x - (m_iWidth*0.5f));
	m_rcBound.top = (LONG)(pos.y - (m_iHeight*0.5f));
	m_rcBound.right = (LONG)(pos.x + (m_iWidth*0.5f));
	m_rcBound.bottom = (LONG)(pos.y + (m_iHeight*0.5f));*/

	m_rcBound.left = (LONG)-(m_iWidth*0.5f);
	m_rcBound.top = (LONG)-(m_iHeight*0.5f);
	m_rcBound.right = (LONG)(m_iWidth*0.5f);
	m_rcBound.bottom = (LONG)(m_iHeight*0.5f);

	pIn[0] = { (float)m_rcBound.left, (float)m_rcBound.top, 0 };
	pIn[1] = { (float)m_rcBound.right, (float)m_rcBound.bottom, 0 };

	for (int i = 0; i < 2; ++i)
		D3DXVec3TransformCoord(&pOut[i], &pIn[i], &m_pObject->GetWorldMat());

	m_rcBound.left = (LONG) pOut[0].x;
	m_rcBound.top = (LONG) pOut[0].y;
	m_rcBound.right = (LONG) pOut[1].x;
	m_rcBound.bottom = (LONG) pOut[1].y;
}
