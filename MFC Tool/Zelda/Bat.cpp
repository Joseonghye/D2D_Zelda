#include "stdafx.h"
#include "Bat.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "Effect.h"

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

	m_bDead = false;
	m_bFall = false;
	m_bAttack = false;
	m_fRad = 40.f;
	m_fDist = 70.f;

	m_bIdle = false;
	m_dwIdleTime = 0;

	m_fSpeed = 20.0f;
	m_tInfo.vSize = D3DXVECTOR3(25.f, 25.f, 0);
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
		CGameObject* effect = CEffect::Create(m_tInfo.vPos);
		effect->SetRoomIndex(m_iRoomIndex);
		GAMEOBJECTMGR->Add_GameObject(EFFECT, effect);
		effect = nullptr;

		SOUNDMGR->PlaySound(L"LOZ_Enemy_Die.wav", CSoundMgr::MONSTER);

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
			if (m_dwPushTime >= 40)
			{
				m_bPushed = false;
				m_dwPushTime = 0;

				if (m_bDead)
					m_bDestory = true;
			}

			D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
			m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
		}
		else
		{
			if (m_bIdle) 
			{
				++m_dwIdleTime;
				if (m_dwIdleTime >= 300)
				{
					m_bIdle = false;
					m_dwIdleTime = 0;
				}
			}
			else
				Attack();
		}
	}

	return NO_EVENT;
}

void CBat::Damaged(int Att)
{
	SOUNDMGR->PlaySound(L"LOZ_Enemy_Hit.wav", CSoundMgr::MONSTER);

	m_bPushed = true;
	
	m_iHp -= Att;

	if (m_iHp <= 0)
	{
		D3DXVec3Normalize(&m_tInfo.vDir,&D3DXVECTOR3(m_pTarget->GetPos() - m_tInfo.vPos));
		m_bDead = true;
	}
	//?????? ?????????? 
}

CBat * CBat::Create(MONSTERID eID)
{
	CBat* pInstance = new CBat;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	pInstance->SetMonsterID(eID);

	return pInstance;
}

void CBat::Attack()
{
	D3DXVECTOR3 vDir = m_pTarget->GetPos() - m_tInfo.vPos;
	float dist = sqrtf(pow(vDir.x, 2) + pow(vDir.y, 2));

	if (!m_bAttack && dist <= m_fDist)
	{
		m_bAttack = true;
		m_Animator->SetAniState(L"ATTACK", L"FRONT", 2,7);

		//???????? ???? ????(??/??, ??/??)
		D3DXVec3Normalize(&vDir, &vDir);
		m_vOrign = m_tInfo.vPos;
		//???????? ???? 
		if (vDir.y > 0)
		{
			m_vCenter.y = m_tInfo.vPos.y + m_fRad;
			m_tInfo.vPos.y = -m_fRad;

			m_fDir = 1;
		}
		else
		{
			m_vCenter.y = m_tInfo.vPos.y - m_fRad;
			m_tInfo.vPos.y = m_fRad;

			m_fDir = -1;
		}
		if (vDir.x > 0) 
		{
			m_vCenter.x = m_tInfo.vPos.x + m_fRad;
			m_tInfo.vPos.x = -m_fRad;

			m_fDir *= -1;
		}
		else 
		{
			m_vCenter.x = m_tInfo.vPos.x - m_fRad;
			m_tInfo.vPos.x = +m_fRad;

			m_fDir *= 1;
		}

		m_fAngle = 0;
		m_fEndAngle = rand() % 200 + 100;
	}
	else 
	{
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}

	if (m_bAttack) 
	{
		//????
		D3DXMATRIX matTrans;
		D3DXMatrixTranslation(&matTrans, m_vCenter.x + SCROLLMGR->GetScrollVec().x, m_vCenter.y + SCROLLMGR->GetScrollVec().y, 0);

		m_fAngle += (m_fDir*300.f) * TIMEMGR->Get_DeltaTime();
		D3DXMatrixRotationZ(&m_tInfo.matRevol, D3DXToRadian(m_fAngle));

		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

		m_tInfo.matWorld = m_tInfo.matScale *m_tInfo.matTrans*m_tInfo.matRevol*matTrans;

		if((m_fDir < 0 && m_fAngle <=  -m_fEndAngle)
			|| (m_fDir > 0 && m_fAngle >= m_fEndAngle))
		{
			//http://egloos.zum.com/scripter/v/1618411
			//???? 
			m_bIdle = true;
			m_Animator->SetAniState(L"IDLE", L"", 1);
			m_bAttack = false;

			D3DXVECTOR3 dir = m_vOrign - m_vCenter;
			float fX = dir.x* cosf(D3DXToRadian(m_fAngle)) - dir.y* sinf(D3DXToRadian(m_fAngle)) + m_vCenter.x;
			float fY = dir.x* sinf(D3DXToRadian(m_fAngle)) - dir.y* cosf(D3DXToRadian(m_fAngle)) + m_vCenter.y;

			m_tInfo.vPos.x = fX;
			m_tInfo.vPos.y = fY;

			D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
			m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;

			m_fAngle = 0;
		}
	}
}

void CBat::Fall()
{
	m_Animator->SetObjectKey(L"Monster");
	m_Animator->AniPlayOnce(L"FALL", L"", 2);

	m_bFall = true;
}
