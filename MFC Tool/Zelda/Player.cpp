#include "stdafx.h"
#include "Player.h"
#include "BoxCollider.h"
#include "Animator.h"
#include "Equipment.h"
#include "Equipment.h"
#include "Sword.h"
#include "Shield.h"

CPlayer::CPlayer() :m_eCurState(IDLE), m_eNextState(STATE_END), m_eCurDir(FRONT), m_eNextDir(FRONT)
{
}

CPlayer::~CPlayer()
{
	Release_GameObject();
	RemoveObserver();
}

HRESULT CPlayer::Initialized_GameObject()
{
	m_bRealSuper = false;

	m_iTotalHp = 6;
	m_iHp = 6;

	m_bSuper = false;
	m_dwSuperTime = 0;

	m_fJumpY = 0;
	m_bJump = false;
	m_bUp = true;

	m_bDefense = false;
	m_bPush = false;
	m_dwPushTime = 0;
	
	m_iRoomIndex = -1;
	m_fSpeed = 100.f;
	m_bVisible = true;

	m_tInfo.vDir = { 0.f,1.f,0.f };
	m_tInfo.vSize = { 25.f, 25.f, 0.f };
	m_tInfo.eDir = FRONT;

	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	m_Collider = static_cast<CBoxCollider*>(AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y,true)));
	m_Animator = static_cast<CAnimator*>(AddComponent(new CAnimator(this, L"Player", L"IDLE")));

	m_pItem[0] = new CSword();
	static_cast<CSword*>(m_pItem[0])->SetPlayer(this);
	m_pItem[0]->Initialized_GameObject();

	m_pItem[1] = new CShield();
	static_cast<CShield*>(m_pItem[1])->SetPlayer(this);
	m_pItem[1]->Initialized_GameObject();

	return S_OK;
}

int CPlayer::Update_GameObject()
{
	if (m_bDestory)
	{
		SCENEMGR->Change_SceneMgr(SCENE::PLAYER_DEAD);
		return DEAD;
	}

	if (m_pItem[0] != nullptr)
		m_pItem[0]->Update_GameObject();

	if (m_eCurState == FALL) 
	{
		if (!m_Animator->GatPlayOnce())
		{
			//자리지정 
			m_tInfo.vPos.y += 18;
			//
			Damaged(0, DAMAGED);
		}
	}

	if (m_bJump)
	{
		if (m_bUp)
			m_fJumpY -= 0.2f;
		else {
			m_fJumpY += 0.2f;

			if (m_fJumpY >= 0)
				m_fJumpY = 0;
		}
		if (m_fJumpY <= -10.f)
		{
			m_bUp = false;
		}

	}
	else
	{
		m_bUp = true;
		m_fJumpY = 0;
	}

	if (m_bSuper)
	{
		m_dwSuperTime++;
		if (m_dwSuperTime >= 100)
			m_bSuper = false;
	}
	if (m_bPush)
	{
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * TIMEMGR->Get_DeltaTime();
		m_dwPushTime++;
		if (m_dwPushTime >= 30) 
			m_bPush = false;
	}
	else 
	{
		m_eNextState = IDLE;

		Move();

		if (KEYMGR->Key_Down(KEY_Q))
		{
			if (!m_bRealSuper)m_bRealSuper = true;
			else m_bRealSuper = false;
		}

		if (KEYMGR->Key_Down(KEY_Z))
		{
			m_eNextState = JUMP;
			SOUNDMGR->StopSound(CSoundMgr::PLAYER);
			SOUNDMGR->PlaySound(L"LA_Link_Jump.wav", CSoundMgr::PLAYER);
		}
		else if (KEYMGR->Key_Pressing(KEY_SPACE))
		{
			m_eNextState = ATTACK;
		}
		
		if (KEYMGR->Key_Down(KEY_CTRL) || KEYMGR->Key_Pressing(KEY_CTRL))
		{
			if (!m_bDefense) 
			{
				SOUNDMGR->StopSound(CSoundMgr::PLAYER);
				SOUNDMGR->PlaySound(L"LA_Shield.wav", CSoundMgr::PLAYER);
				m_bDefense = true;
			}
			m_pItem[1]->StartUsing(m_tInfo.eDir);
		}
		else if (m_bDefense)
			m_bDefense = false;
	}
	
	ChangeState();


	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x,
		m_tInfo.vPos.y+ m_fJumpY + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;

	return NO_EVENT;
}

void CPlayer::LateUpdate_GameObject() {}

void CPlayer::Render_GameObject()
{
	if (m_pItem != nullptr && m_pItem[0]->GetVisible())
		m_pItem[0]->Render_GameObject();
}

void CPlayer::Release_GameObject()
{
	for(int i=0; i<2;i++)
		SAFE_DELETE(m_pItem[i]);

	for_each(m_vecComponet.begin(), m_vecComponet.end(), Safe_Delete<CBaseComponent*>);
	m_vecComponet.clear();
	m_vecComponet.swap(vector<CBaseComponent*>());
}

CPlayer * CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer;
	if(FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}

void CPlayer::Move()
{
	if (KEYMGR->Key_Pressing(KEY_LEFT))
	{
		m_tInfo.vPos.x -= m_fSpeed * TIMEMGR->Get_DeltaTime();
		m_tInfo.vDir.x = -1.f;
		m_eNextDir = LEFT;
		m_eNextState = WALK;
	}
	else if (KEYMGR->Key_Pressing(KEY_RIGHT))
	{
		m_tInfo.vPos.x += m_fSpeed* TIMEMGR->Get_DeltaTime();
		m_tInfo.vDir.x = 1.f;
		m_eNextDir = RIGHT;
		m_eNextState = WALK;
	}

	if (KEYMGR->Key_Pressing(KEY_UP))
	{
		m_tInfo.vPos.y -= m_fSpeed* TIMEMGR->Get_DeltaTime();
		m_tInfo.vDir.y = -1.f;
		m_eNextDir = BACK;
		m_eNextState = WALK;
	}
	else if (KEYMGR->Key_Pressing(KEY_DOWN))
	{
		m_tInfo.vPos.y += m_fSpeed* TIMEMGR->Get_DeltaTime();
		m_tInfo.vDir.y = 1.f;
		m_eNextDir = FRONT;
		m_eNextState = WALK;
	}

}

void CPlayer::Attack()
{
	SOUNDMGR->StopSound(CSoundMgr::PLAYER);
	SOUNDMGR->PlaySound(L"LOZ_Sword_Slash.wav", CSoundMgr::PLAYER);
	m_pItem[0]->StartUsing(m_eCurDir);
}

void CPlayer::Damaged(int att, STATE eState)
{
	if (m_bJump) return;
	if (m_bPush) return;
	if(att >0)
		if (m_bSuper) return;
	
	m_dwSuperTime = 0;
	m_bSuper = true;

	if (eState != FALL)
	{
		if (att > 0) {
			m_bPush = true;
			m_dwPushTime = 0;
			m_tInfo.vDir *= -1;
		}
	}

	if (!m_bRealSuper) {
		m_iHp -= att;
		if (m_iHp <= 0)
		{
			m_bDestory = true;
			//사망
			return;
		}

		if (att > 0) {
			//hp UI
			NotifyObserver();
		}
	}

	SetState(eState);
}

bool CPlayer::Defense(D3DXVECTOR3 vPos, D3DXVECTOR3 vMonDir)
{
	if (!m_bDefense) return false;

	//방패앞쪽에서 맞앗나?
	D3DXVECTOR3 vDir = vPos - m_tInfo.vPos;
	D3DXVec3Normalize(&vDir, &vDir);

	if (D3DXVec3Dot(&m_tInfo.vDir, &vDir) > 0)
	{
		m_bPush = true;
		SOUNDMGR->StopSound(CSoundMgr::PLAYER);
		SOUNDMGR->PlaySound(L"LA_Shield_Deflect.wav", CSoundMgr::PLAYER);

		m_dwPushTime = 0;
		//젤다 뒤로 밀림
		m_tInfo.vDir = vMonDir;

		return true;
	}
	return false;
}

void CPlayer::ChangeState()
{
	if (m_Animator->GatPlayOnce()) return;
	else
	{
		if (m_bJump) 
			m_bJump = false;
	}

	if (m_eCurState == m_eNextState && m_eCurDir == m_eNextDir)
	{
		m_Animator->SetDefensAni(m_bDefense);
		return;
	}
	wstring wstrStateKey;
	wstring wstrDir;
	float fEndFrame = -1;
	float fSpeed = 5;

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
		case JUMP:
			wstrStateKey = L"JUMP";
			fEndFrame = 4;
			fSpeed = 1.5f;
			m_bJump = true;
			break;
		case DAMAGED:
			wstrStateKey = L"DAMAGED";
			fEndFrame = 4;
			fSpeed = 5;
			break;
		case FALL:
			wstrStateKey = L"FALL";
			fEndFrame = 3;
			fSpeed = 3;
			SOUNDMGR->StopSound(CSoundMgr::PLAYER);
			SOUNDMGR->PlaySound(L"LA_Link_Fall.wav", CSoundMgr::PLAYER);
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

	if (m_eCurState == JUMP ||m_eCurState == FALL || m_eCurState == DAMAGED)
  		m_Animator->AniPlayOnce(wstrStateKey, wstrDir, fEndFrame, fSpeed);
	else 
	{	
		m_Animator->SetAniState(wstrStateKey, wstrDir, fEndFrame, fSpeed);
		m_Animator->SetDefensAni(m_bDefense);
	}
}

void CPlayer::RegisterObserver(CObserver * observer)
{
	m_pObserver.emplace_back(observer);
}

void CPlayer::RemoveObserver()
{
	m_pObserver.clear();
	m_pObserver.swap(vector<CObserver*>());
}

void CPlayer::NotifyObserver()
{
	for (auto& iter = m_pObserver.begin(); iter != m_pObserver.end(); ++iter)
		(*iter)->OnNotify();
}
