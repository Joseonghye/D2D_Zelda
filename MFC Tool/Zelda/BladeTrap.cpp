#include "stdafx.h"
#include "BladeTrap.h"
#include "BoxCollider.h"

CBladeTrap::CBladeTrap() {}
CBladeTrap::~CBladeTrap() {	Release_GameObject(); }

HRESULT CBladeTrap::Initialized_GameObject()
{
	m_iAtt = 1;

	m_fSpeed = 20.0f;
	m_fBackSpeed = 10.f;

	m_tInfo.vSize = D3DXVECTOR3(32.f, 32.f, 0);
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	m_pTarget = GAMEOBJECTMGR->GetPlayer();

	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));

}

int CBladeTrap::Update_GameObject()
{
	return NO_EVENT;
}

CBladeTrap * CBladeTrap::Create(MONSTERID eID)
{
	CBladeTrap* pInstance = new CBladeTrap;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	pInstance->SetMonsterID(eID);

	return pInstance;
}

void CBladeTrap::Damaged(int Att) { return; }

void CBladeTrap::Attack()
{
	// 상 하 좌 우 중 플레이어가 있다면 
	D3DXVECTOR3 vDir = m_pTarget->GetPos() - m_tInfo.vPos;

	if()

}
