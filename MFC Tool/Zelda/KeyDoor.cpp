#include "stdafx.h"
#include "KeyDoor.h"
#include "BoxCollider.h"
#include "Animator.h"

CKeyDoor::CKeyDoor():m_Animator(nullptr) {}
CKeyDoor::~CKeyDoor() { Release_GameObject(); }

HRESULT CKeyDoor::Initialized_GameObject()
{
	m_iRoomIndex = -1;
	m_bVisible = true;
	m_bMove = false;
	m_bDestory = false;

	m_tInfo.vSize = { 32.f, 32.f, 0.f };

	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	m_Collider = static_cast<CBoxCollider*>(AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y)));
	m_Collider->SetActive(true);
	//	
	return S_OK;
}

int CKeyDoor::Update_GameObject()
{
	if (GAMEOBJECTMGR->isChanging())
	{
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}

	if (KEYMGR->Key_Down(KEY_X))
	{
		m_Animator->SetAniState(L"IDLE_OPEN", L"", 1);
		m_Collider->SetActive(false);
		m_Animator->AniPlayOnce(L"OPEN", L"", 3, 3);
	}
	return NO_EVENT;

}

void CKeyDoor::Render_GameObject(){}

void CKeyDoor::SetDir(wstring _wstr)
{
	if (_wstr == L"FRONT")
	{
		m_wstrDir = _wstr;
		m_tInfo.eDir = FRONT;
	}
	else if (_wstr == L"LEFT")
	{
		m_wstrDir = _wstr;
		m_tInfo.eDir = LEFT;
	}

	m_Animator = static_cast<CAnimator*>(AddComponent(new CAnimator(this, L"KEYDOOR", L"IDLE", m_wstrDir)));

}

CKeyDoor * CKeyDoor::Create()
{
	CKeyDoor* pInstance = new CKeyDoor;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}

