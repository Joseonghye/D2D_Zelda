#include "stdafx.h"
#include "Player.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "Sword.h"

CPlayer::CPlayer() :m_eCurState(IDLE), m_eNextState(STATE_END), m_eCurDir(FRONT), m_eNextDir(FRONT)
{
}

CPlayer::~CPlayer()
{
	Release_GameObject();
}

HRESULT CPlayer::Initialized_GameObject()
{
	m_fSpeed = 100.f;

//	m_tInfo.vPos = { 400.f , 10.f, 0.f };
	m_tInfo.vSize = { 32.f, 32.f, 0.f };
//	m_tInfo.vDir = { 0.f, 1.f, 0.f };
	m_tInfo.eDir = FRONT;

	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_Collider = static_cast<CBoxCollider*>(AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y)));
	m_Animator = static_cast<CAnimator*>(AddComponent(new CAnimator(this, L"Player", L"IDLE")));

	m_pItem = new CSword();
	static_cast<CSword*>(m_pItem)->SetPlayer(this);
	m_pItem->Initialized_GameObject();

	return S_OK;
}

int CPlayer::Update_GameObject()
{
	if (m_pItem != nullptr)
		m_pItem->Update_GameObject();

	m_eNextState = IDLE;

	if (KEYMGR->Key_Pressing(KEY_LEFT)) 
	{
		m_tInfo.vPos.x -= m_fSpeed * TIMEMGR->Get_DeltaTime();
	//	m_tInfo.vDir.x = -1.f;
		m_eNextDir = LEFT;
		m_eNextState = WALK;
	}
	else if (KEYMGR->Key_Pressing(KEY_RIGHT)) 
	{
		m_tInfo.vPos.x += m_fSpeed* TIMEMGR->Get_DeltaTime();
		//m_tInfo.vDir.x = 1.f;
		m_eNextDir = RIGHT;
		m_eNextState = WALK;
	}

	if (KEYMGR->Key_Pressing(KEY_UP))
	{
		m_tInfo.vPos.y -= m_fSpeed* TIMEMGR->Get_DeltaTime();
	//	m_tInfo.vDir.y = -1.f;
		m_eNextDir = BACK;
		m_eNextState = WALK;
	}
	else if (KEYMGR->Key_Pressing(KEY_DOWN)) 
	{
		m_tInfo.vPos.y += m_fSpeed* TIMEMGR->Get_DeltaTime();
	//	m_tInfo.vDir.y = 1.f;
		m_eNextDir = FRONT;
		m_eNextState = WALK;
	}
	if (KEYMGR->Key_Pressing(KEY_RETURN))
	{
		m_eNextState = ATTACK;
	}

	ChangeState();

	float fX = m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x;
	float fY = m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y;

	D3DXMatrixTranslation(&m_tInfo.matTrans, fX, fY, m_tInfo.vPos.z);

	/*
	if (m_Collider != nullptr)
	{
		vector<CGameObject*> vecObj = GAMEOBJECTMGR->GetObjList(WALL);

		for (int i = 0; i < vecObj.size(); ++i) 
		{
			CBoxCollider* another = static_cast<CBoxCollider*>(vecObj[i]->GetComponent(COMPONENTID::COLLISION));

			if (another != nullptr && m_Collider->CheckCollision(another))
			{
				m_tInfo.vPos.x -= m_tInfo.vDir.x *m_fSpeed;
				m_tInfo.vPos.y -= m_tInfo.vDir.y *m_fSpeed;

				D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);	
			}
		}
	}
	*/
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;

	return NO_EVENT;
}

void CPlayer::LateUpdate_GameObject()
{
}

void CPlayer::Render_GameObject()
{
	if (m_pItem != nullptr && m_pItem->GetVisible())
		m_pItem->Render_GameObject();
}

void CPlayer::Release_GameObject()
{
}

CPlayer * CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer;
	if(FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}

void CPlayer::Attack()
{
	static_cast<CSword*>(m_pItem)->StartUsing(m_eCurDir);
}

void CPlayer::ChangeState()
{
	if (m_eCurState == m_eNextState && m_eCurDir == m_eNextDir) return;

	wstring wstrStateKey;
	wstring wstrDir;
	float fEndFrame = -1;

	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case IDLE:
			wstrStateKey = L"IDLE";
			fEndFrame = 1;
			break;
		case WALK:
			wstrStateKey = L"WALK";
			fEndFrame = 2;
			break;
		case ATTACK:
			wstrStateKey = L"ATTACK";
			fEndFrame = 3;
			Attack();
			break;
		case PUSH:
			wstrStateKey = L"PUSH";
			fEndFrame = 2;
			break;
		}
		m_eCurState = m_eNextState;
	}

	if (m_eCurDir != m_eNextDir)
	{
		switch (m_eNextDir)
		{
		case FRONT:
			wstrDir = L"FRONT";
			break;
		case BACK:
			wstrDir = L"BACK";
			break;
		case LEFT:
			wstrDir = L"LEFT";
			break;
		case RIGHT:
			wstrDir = L"RIGHT";
			break;
		}
		m_eCurDir = m_eNextDir;
		m_tInfo.eDir = m_eNextDir;
	}


	m_Animator->SetAniState(wstrStateKey, wstrDir, fEndFrame);

}
