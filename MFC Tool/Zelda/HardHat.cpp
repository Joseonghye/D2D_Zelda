#include "stdafx.h"
#include "HardHat.h"
#include "BoxCollider.h"
#include "Animator.h"
CHardHat::CHardHat()
{
}


CHardHat::~CHardHat()
{
}

HRESULT CHardHat::Initialized_GameObject()
{
	m_fSpeed = 1.0f;
	m_tInfo.vSize = D3DXVECTOR3(16, 16, 0);

	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);
	m_pTarget = GAMEOBJECTMGR->GetPlayer();

	AddComponent(new CBoxCollider(this, 16.f, 16.f));
	AddComponent(new CAnimator(this, L"HardHat", L"IDLE",L"FRONT",2));

	return S_OK;
}

int CHardHat::Update_GameObject()
{
	if (m_bDestory) return DEAD;

	D3DXVECTOR3 dir = (m_pTarget->GetPos() - m_tInfo.vPos);
	D3DXVec3Normalize(&dir, &dir);

	m_tInfo.vPos += (dir * m_fSpeed);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;

	return NO_EVENT;
}

void CHardHat::LateUpdate_GameObject()
{
}

void CHardHat::Render_GameObject()
{
}

void CHardHat::Release_GameObject()
{
}

CHardHat * CHardHat::Create()
{
	CHardHat* pInstance = new CHardHat;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}
