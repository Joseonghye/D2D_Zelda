#include "stdafx.h"
#include "Door.h"
#include "BoxCollider.h"
#include "Animator.h"

CDoor::CDoor():m_Animator(nullptr), m_Collider(nullptr) {}
CDoor::~CDoor() 
{
	Release_GameObject();
}

HRESULT CDoor::Initialized_GameObject()
{
	m_iRoomIndex = -1;
	m_bVisible = true;
	m_bMove = false;
	m_bDestory = false;

	m_tInfo.vSize = { 32.f, 32.f, 0.f };
	
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	m_Collider = static_cast<CBoxCollider*>(AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y)));
	m_Collider->SetActive(false);
//	
	return S_OK;
}

int CDoor::Update_GameObject()
{
	if (GAMEOBJECTMGR->isChanging())
	{
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}
	return 0;
}

void CDoor::LateUpdate_GameObject() {}

void CDoor::Render_GameObject() {}

void CDoor::Release_GameObject()
{
	for_each(m_vecComponet.begin(), m_vecComponet.end(), Safe_Delete<CBaseComponent*>);
	m_vecComponet.clear();
	m_vecComponet.swap(vector<CBaseComponent*>());
}

CDoor * CDoor::Create()
{
	CDoor* pInstance = new CDoor;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}

void CDoor::SetDir(wstring _wstr)
{
	if (_wstr == L"FRONT") 
	{
		m_wstrDir = _wstr;
		m_tInfo.eDir = FRONT;
	}		
	else if (_wstr == L"BACK")
	{
		m_wstrDir = _wstr;
		m_tInfo.eDir = BACK;
	}
	else if (_wstr == L"LEFT")
	{
		m_wstrDir = _wstr;
		m_tInfo.eDir = LEFT;
	}
	else if (_wstr == L"RIGHT")
	{
		m_wstrDir = _wstr;
		m_tInfo.eDir = RIGHT;
	}

	m_Animator = static_cast<CAnimator*>(AddComponent(new CAnimator(this, L"DOOR", L"IDLE_OPEN", m_wstrDir)));
}

void CDoor::MoveDoor(const wstring& wstrState)
{
	if (wstrState == L"OPEN")
	{
		//Ãæµ¹ »ç¶óÁü 
		m_Collider->SetActive(false);
	}
	else
		m_Collider->SetActive(true);

	wstring wstrStateKey = wstrState;
	m_Animator->AniPlayOnce(wstrStateKey,L"",3,3);
}
