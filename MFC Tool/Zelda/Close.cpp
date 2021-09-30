#include "stdafx.h"
#include "Close.h"
#include "Door.h"
#include "Animator.h"
#include "BoxCollider.h"

CClose::CClose() {}
CClose::~CClose()
{
	Release_GameObject();
}

HRESULT CClose::Initialized_GameObject()
{
	m_bFirst = true;

	m_bVisible = false;
	m_bMove = false;

	m_tInfo.vSize = { 32.f, 32.f, 0.f };

	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);
	m_Collider = static_cast<CBoxCollider*>(AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y)));

	return S_OK;
}

int CClose::Update_GameObject()
{
	if (!m_bFirst) return DEAD;

	if (GAMEOBJECTMGR->isChanging())
	{
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}
	return NO_EVENT;
}

void CClose::LateUpdate_GameObject() {}
void CClose::Render_GameObject() {}

void CClose::Release_GameObject()
{
	for_each(m_vecComponet.begin(), m_vecComponet.end(), Safe_Delete<CBaseComponent*>);
	m_vecComponet.clear();
	m_vecComponet.swap(vector<CBaseComponent*>());
}

CClose * CClose::Create(int id)
{
	CClose* pInstance = new CClose;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	pInstance->SetEventID(id);
	return pInstance;
}

void CClose::Using()
{
	if (!m_bFirst) return;
	else m_bFirst = false;

	vector<CGameObject*> vecObj = GAMEOBJECTMGR->GetObjList(INTERACTION);
	for (auto& iter : vecObj)
	{
		if (iter->GetRoomIndex() == m_iRoomIndex&& typeid(*iter) == typeid(CDoor))
		{
			(static_cast<CDoor*>(iter))->GetAnimator()->SetAniState(L"IDLE_CLOSE", L"", 1);
			static_cast<CDoor*>(iter)->MoveDoor(L"CLOSE");
		}
	}
}
