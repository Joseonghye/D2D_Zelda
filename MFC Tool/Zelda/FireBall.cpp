#include "stdafx.h"
#include "FireBall.h"
#include "BoxCollider.h"
#include "Animator.h"

CFireBall::CFireBall() {}
CFireBall::~CFireBall()
{
	Release_GameObject();
}

HRESULT CFireBall::Initialized_GameObject()
{
	m_iAtt = 1;
	m_iHp = 0;
	m_iTotalHp = 0;
	m_fSpeed = 0.f;

	m_tInfo.vSize = D3DXVECTOR3(32.f, 32.f, 0);
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	m_pTarget = GAMEOBJECTMGR->GetPlayer();

	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));
	AddComponent(new CAnimator(this, L"HardHat", L"IDLE", L"FRONT", 2));

	return S_OK;
}

int CFireBall::Update_GameObject()
{
	return 0;
}

void CFireBall::Attack()
{
}
