#include "stdafx.h"
#include "Close.h"
#include "Door.h"
#include "Animator.h"

CClose::CClose()
{
}


CClose::~CClose()
{
}

HRESULT CClose::Initialized_GameObject()
{
	return E_NOTIMPL;
}

int CClose::Update_GameObject()
{
	return 0;
}

void CClose::LateUpdate_GameObject()
{
}

void CClose::Render_GameObject() {}

void CClose::Release_GameObject()
{
}

CClose * CClose::Create()
{
	CClose* pInstance = new CClose;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);
	return pInstance;
}

void CClose::CloseDoor()
{
	vector<CGameObject*> vecMonster = GAMEOBJECTMGR->GetObjList(MONSTER);
	for (auto& iter : vecMonster)
	{
		if (typeid(iter) == typeid(CDoor*) && iter->GetRoomIndex() == m_iRoomIndex)
		{
			(static_cast<CDoor*>(iter))->GetAnimator()->SetAniState(L"IDLE_CLOSE",L"",1);
			static_cast<CDoor*>(iter)->MoveDoor(L"CLOSE");
		}
	}
}
