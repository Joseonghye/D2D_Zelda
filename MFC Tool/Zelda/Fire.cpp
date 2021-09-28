#include "stdafx.h"
#include "Fire.h"
#include "BoxCollider.h"
#include "Animator.h"

CFire::CFire() {}
CFire::~CFire() { Release_GameObject(); }

HRESULT CFire::Initialized_GameObject()
{
	m_bMove = false;
	m_bVisible = true;

	m_tInfo.vSize = { 32.f, 32.f, 0.f };
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));
	AddComponent(new CAnimator(this, L"Fire", L"IDLE", L"FRONT", 4, 3.f));

	return S_OK;
}

int CFire::Update_GameObject()
{
	if (GAMEOBJECTMGR->isChanging())
	{
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}

	return NO_EVENT;
}

CFire * CFire::Create()
{
	CFire* pInstance = new CFire;
	if(FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}
