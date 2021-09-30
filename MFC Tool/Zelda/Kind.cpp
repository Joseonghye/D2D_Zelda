#include "stdafx.h"
#include "Kind.h"
#include "BoxCollider.h"
#include "Animator.h"

CKind::CKind() {}
CKind::~CKind() {	Release_GameObject();	}

HRESULT CKind::Initialized_GameObject()
{
	m_fColor = (float)YELLOW;
	m_bStop = false;
	m_bWait = false;
	m_bMove = false;

	m_dwWaitTime = 20;
	m_dwMoveTime = 0;
	m_dwTime = 0;

	m_iHp = 0;
	m_iTotalHp = 0;
	m_iAtt = 1;

	m_fSpeed = 20.0f;
	m_tInfo.vSize = D3DXVECTOR3(32.f, 32.f, 0);
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	m_pTarget = GAMEOBJECTMGR->GetPlayer();

	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));
	m_Animator=static_cast<CAnimator*>(AddComponent(new CAnimator(this, L"Three", L"YELLOW", L"FRONT", 1)));

	return S_OK;
}

int CKind::Update_GameObject()
{
	if (m_bDestory)
	{
		NotifyObserver();
		return DEAD;
	}

	if(!m_bStop)
		Attack();
	return 0;
}

void CKind::Attack()
{
	++m_dwTime;

	if (!m_bWait) {
		if (!m_bMove)
		{
			m_bMove = true;
			//상하좌우 랜덤으로 움직임
			int iDir = rand() % 4;
			m_dwMoveTime = rand() % 100 + 50;

			D3DXVECTOR3 vDir;
			switch (iDir)
			{
			case FRONT:
				m_tInfo.vDir = D3DXVECTOR3(0, 1, 0);
				break;
			case BACK:
				m_tInfo.vDir = D3DXVECTOR3(0, -1, 0);
				break;
			case LEFT:
				m_tInfo.vDir = D3DXVECTOR3(-1, 0, 0);
				break;
			case RIGHT:
				m_tInfo.vDir = D3DXVECTOR3(1, 0, 0);
				break;
			}
		}
		else
		{
			if (m_dwTime >= m_dwMoveTime)
			{
				m_dwTime = 0;
				m_bMove = false;
				m_bWait = true;
			}
		}

		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * TIMEMGR->Get_DeltaTime();
	}
	else
	{
		if (m_dwTime >= m_dwWaitTime)
		{
			m_dwTime = 0;
			m_bWait = false;
		}
	}

	//계속해서 문양이 바뀜
	m_fColor += (3*TIMEMGR->Get_DeltaTime());
	if (m_fColor >= 4) m_fColor = 0;

	switch ((int)m_fColor)
	{
	case YELLOW:
		m_Animator->SetAniState(L"YELLOW",L"",1);
		break;
	case RED:
		m_Animator->SetAniState(L"RED", L"", 1);
		break;
	case GREEN:
		m_Animator->SetAniState(L"GREEN", L"", 1);
		break;
	case BLUE:
		m_Animator->SetAniState(L"BLUE", L"", 1);
		break;
	}

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;

}

void CKind::Damaged(int Att)
{
	//정지 
	m_bStop = true;
}

CKind * CKind::Create(MONSTERID eID)
{
	CKind* pInstance = new CKind;
	if (FAILED(pInstance->Initialized_GameObject()))
		SAFE_DELETE(pInstance);

	pInstance->SetMonsterID(eID);
	return pInstance;
}
