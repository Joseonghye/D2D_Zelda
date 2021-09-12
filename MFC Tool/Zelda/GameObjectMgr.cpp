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
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			(*iter)->Update_Components();

			if (DEAD == (*iter)->Update_GameObject()) 
			{
				//이벤트 값에 따른 처리 
				SAFE_DELETE(*iter);
				m_ObjList[i].erase(iter);
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
			(*iter)->LateUpdate_Components();
			(*iter)->LateUpdate_GameObject();

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
			(*iter)->Render_Components();
			(*iter)->Render_GameObject();

			iter++;
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
