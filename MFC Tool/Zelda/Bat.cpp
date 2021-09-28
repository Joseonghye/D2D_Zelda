#include "stdafx.h"
#include "Bat.h"
#include "BoxCollider.h"
#include "Animator.h"

CBat::CBat()
{
}
CBat::~CBat()
{
	Release_GameObject();
}

HRESULT CBat::Initialized_GameObject()
{
	m_iHp = 2;
	m_iTotalHp = 2;
	m_iAtt = 1;

	m_fRad = 3.f;

	m_fSpeed = 20.0f;
	m_tInfo.vSize = D3DXVECTOR3(32.f, 32.f, 0);
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);
	
	m_pTarget = GAMEOBJECTMGR->GetPlayer();

	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));
	m_Animator = static_cast<CAnimator*>(AddComponent(new CAnimator(this, L"Bat", L"IDLE", L"FRONT", 1)));

	return S_OK;
}

int CBat::Update_GameObject()
{
	if (m_bDestory)
	{
		NotifyObserver();
		return DEAD;
	}
	if (m_bPushed)
	{
		m_tInfo.vPos += (-m_tInfo.vDir) * (m_fSpeed * 10) * TIMEMGR->Get_DeltaTime();
		m_dwPushTime++;
		if (m_dwPushTime >= 40) 
		{
			m_bPushed = false;
			m_dwPushTime = 0;
		}

		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}
	else 
	{
		Attack();
		m_tInfo.matWorld = m_tInfo.matScale *m_tInfo.matTrans*m_tInfo.matRevol;
	}

	
	return NO_EVENT;
}

CBat * CBat::Create()
{
	CBat* pInstance = new CBat;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}

void CBat::Attack()
{
	if (!m_bAttack) 
	{
		m_bAttack = true;
		//플레이어 위치 확인(좌/우, 상/하)
		D3DXVECTOR3 vDir = m_pTarget->GetPos() - m_tInfo.vPos;
		D3DXVec3Normalize(&vDir, &vDir);

		//중심점을 구함 
		if (vDir.y > 0)
			m_vCenter.y = m_tInfo.vPos.y + m_fRad;
		else
			m_vCenter.y = m_tInfo.vPos.y - m_fRad;

		if (vDir.x > 0)
			m_vCenter.x = m_pTarget->GetPos().x - m_fRad;
		else
			m_vCenter.x = m_pTarget->GetPos().x + m_fRad;
	}
	//회전
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, m_vCenter.x, m_vCenter.y, 0);

	m_fAngle += 300.f * TIMEMGR->Get_DeltaTime();
	D3DXMatrixRotationZ(&m_tInfo.matRevol, D3DXToRadian(m_fAngle));

	m_tInfo.matRevol *= matTrans;

	m_Animator->SetAniState(L"ATTACK", L"", 2);

	if (m_fAngle >= 200.f)
	{
		m_fAngle = 0;
		//대기 
		
		m_Animator->SetAniState(L"IDLE", L"", 2);
		m_bAttack = false;
	}
}
