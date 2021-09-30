#include "stdafx.h"
#include "SpikedBettle.h"
#include "BoxCollider.h"
#include "Animator.h"

CSpikedBettle::CSpikedBettle() {}
CSpikedBettle::~CSpikedBettle() { Release_GameObject(); }

HRESULT CSpikedBettle::Initialized_GameObject()
{
	m_iHp = 1;
	m_iTotalHp = 1;
	m_iAtt = 1;

	m_bDead = false;
	m_bFall = false;
	m_bReverse = false; 
	m_bAttack = false;

	m_fSpeed = 20.0f;
	m_tInfo.vSize = D3DXVECTOR3(32.f, 32.f, 0);
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	m_pTarget = GAMEOBJECTMGR->GetPlayer();

	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));
	m_Animator = static_cast<CAnimator*>(AddComponent(new CAnimator(this, L"HardHat", L"IDLE", L"FRONT", 2)));

	return S_OK;
}

int CSpikedBettle::Update_GameObject()
{
	if (m_bDestory)
	{
		NotifyObserver();
		return DEAD;
	}

	if (m_bFall || m_bDead)
	{
		if (!m_Animator->GatPlayOnce())
			m_bDestory = true;
	}
	else
	{
		if (m_bPushed)
		{
			m_bReverse = true;

			m_tInfo.vPos += (-m_tInfo.vDir) * (m_fSpeed * 10) * TIMEMGR->Get_DeltaTime();
			m_dwPushTime++;
			if (m_dwPushTime >= 40) {
				m_bPushed = false;
				m_dwPushTime = 0;
			}
		}
		else
			Attack();
	}

	return NO_EVENT;
}

void CSpikedBettle::Damaged(int Att)
{
	if (m_bReverse)
	{
		m_iHp -= Att;

		if (m_iHp <= 0)
		{
			D3DXVec3Normalize(&m_tInfo.vDir, &D3DXVECTOR3(m_pTarget->GetPos() - m_tInfo.vPos));
			m_bDead = true;
		}
		//데미지 애니메이션 
	}
}

void CSpikedBettle::Fall()
{
	m_Animator->SetObjectKey(L"Monster");
	m_Animator->AniPlayOnce(L"FALL", L"", 2);

	m_bFall = true;
}

void CSpikedBettle::Attack()
{
	D3DXVECTOR3 vDir = m_pTarget->GetPos() - m_tInfo.vPos;
	if (!m_bAttack)
	{
		//플레이어 방향(상하좌우)로 돌진 
		D3DXVec3Normalize(&vDir, &vDir);
		m_tInfo.vDir = vDir;
		if (fabs(vDir.x) <= 10.f)
		{
			//상하	
			m_tInfo.vPos.y += m_tInfo.vDir.y * m_fSpeed * TIMEMGR->Get_DeltaTime();
		}
		else if (fabs(vDir.y) <= 10.f)
		{
			//좌우
			m_tInfo.vPos.x += m_tInfo.vDir.x * m_fSpeed * TIMEMGR->Get_DeltaTime();
		}
	}
	else
	{
		//플레이어 위치까지 돌진
		if (D3DXVec3Length(&vDir) <= 1)
		{
			m_bAttack = false;
		}
	}

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;

}
