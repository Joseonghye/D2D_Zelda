#include "stdafx.h"
#include "GameObjectMgr.h"
#include "GameObject.h"

CGameObjectMgr::CGameObjectMgr()
{
}

CGameObjectMgr::~CGameObjectMgr()
{
	Release_GameObjectMgr();
}

void CGameObjectMgr::Update_GameObjectMgr()
{
	for (int i = 0; i < OBJID::OBJID_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Update_GameObject();
			//이벤트 값에 따른 처리 
		}
	}
}

void CGameObjectMgr::LateUpdate_GameObjectMgr()
{
	for (int i = 0; i < OBJID::OBJID_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->LateUpdate_GameObject();
		}
	}
}

void CGameObjectMgr::Render_GameObjectMgr()
{
	for (int i = 0; i < OBJID::OBJID_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Render_GameObject();
		}
	}
}

void CGameObjectMgr::Release_GameObjectMgr()
{
	for (int i = 0; i < OBJID_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CGameObject*>);
		m_ObjList[i].clear();
	}
}

void CGameObjectMgr::Add_GameObject(OBJID eID, CGameObject * pGameObject)
{
	if (pGameObject == nullptr) return;

	m_ObjList[eID].emplace_back(pGameObject);
}
