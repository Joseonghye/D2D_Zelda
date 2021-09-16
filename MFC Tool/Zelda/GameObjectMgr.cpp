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
		if(i > OBJID::PLAYER)
			CollisionMgr.PlayerCollision(m_ObjList[OBJID::PLAYER].begin()->second, m_ObjList[i],(OBJID)i );

		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			(iter->second)->Update_Components();

			if (DEAD == (iter->second)->Update_GameObject()) 
			{
				//이벤트 값에 따른 처리 
				SAFE_DELETE(iter->second);
				iter = m_ObjList[i].erase(iter);
				if (iter == m_ObjList[i].end()) break;
			}
			iter++;
		}
	}
}

void CGameObjectMgr::LateUpdate_GameObjectMgr()
{
	for (int i = 0; i < OBJID::OBJID_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			(iter->second)->LateUpdate_Components();
			(iter->second)->LateUpdate_GameObject();

			iter++;
		}
	}
}

void CGameObjectMgr::Render_GameObjectMgr()
{
	for (int i = 0; i < OBJID::OBJID_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			if ((iter->second)->GetVisible())
			{
				(iter->second)->Render_Components();
				(iter->second)->Render_GameObject();
			}
			iter++;
		}
	}
}

void CGameObjectMgr::Release_GameObjectMgr()
{
	for (int i = 0; i < OBJID_END; ++i)
	{
	//	for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CGameObject*>);
		for (auto& iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
			SAFE_DELETE(iter->second);
		m_ObjList[i].clear();
	}
}

void CGameObjectMgr::Add_GameObject(OBJID eID, int index, CGameObject * pGameObject)
{
	if (pGameObject == nullptr) return;

	m_ObjList[eID].emplace(index, pGameObject);
	//m_ObjList[eID].emplace_back(pGameObject);
}
