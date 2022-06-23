#include "stdafx.h"
#include "HardHat.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "Observer.h"

CHardHat::CHardHat()
{
}

CHardHat::~CHardHat()
{
	Release_GameObject();
}

HRESULT CHardHat::Initialized_GameObject()
{
	m_iHp = 1;
	m_iTotalHp = 1;
	m_iAtt = 1;

	m_bFall = false;

	m_fSpeed = 20.0f;
	m_tInfo.vSize = D3DXVECTOR3(32.f,32.f, 0);
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	m_pTarget = GAMEOBJECTMGR->GetPlayer();

	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));
	m_Animator= static_cast<CAnimator*>(AddComponent(new CAnimator(this, L"HardHat", L"IDLE",L"FRONT",2)));

	return S_OK;
}

int CHardHat::Update_GameObject()
{
	if (m_bDestory)
	{
		NotifyObserver();
		return DEAD;
	}
	if (m_bFall)
	{
		if (!m_Animator->GatPlayOnce())
			m_bDestory = true;
	}
	else
	{
		if (m_bPushed)
		{
			m_tInfo.vPos += (-m_tInfo.vDir) * (m_fSpeed * 10) * TIMEMGR->Get_DeltaTime();
			m_dwPushTime++;
			if (m_dwPushTime >= 40) {
				m_bPushed = false;
				m_dwPushTime = 0;
			}
		}

		else
			Attack();

		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);

		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}

	return NO_EVENT;
}

void CHardHat::Damaged(int Att)
{
	m_bPushed = true;
}


CHardHat * CHardHat::Create(MONSTERID eID)
{
	CHardHat* pInstance = new CHardHat;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	pInstance->SetMonsterID(eID);

	return pInstance;
}

void CHardHat::Attack()
{
	m_tInfo.vDir = (m_pTarget->GetPos() - m_tInfo.vPos);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	m_tInfo.vPos += (m_tInfo.vDir * m_fSpeed * TIMEMGR->Get_DeltaTime());

}

void CHardHat::Fall()
{
	if (m_bFall) return;

	m_Animator->SetObjectKey(L"Monster");
	m_Animator->AniPlayOnce(L"FALL", L"", 2);

	m_bFall = true;
}
