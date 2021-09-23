#include "stdafx.h"
#include "GameObjectMgr.h"
#include "GameObject.h"

CGameObjectMgr::CGameObjectMgr() :m_bChange(false), m_iNextIndex(-1)
{
}

CGameObjectMgr::~CGameObjectMgr()
{
	Release_GameObjectMgr();
}

void CGameObjectMgr::Update_GameObjectMgr()
{
	if (m_bChange)
		if (SCROLLMGR->ChangeScroll())
		{
			m_iRoomIndex = m_iNextIndex;
			m_iNextIndex = -1;
			m_bChange = false;
		}

	for (int i = 0; i < OBJID::OBJID_END; ++i)
	{
		if (i > OBJID::PLAYER) 
			CollisionMgr.PlayerCollision(m_ObjList[OBJID::PLAYER].front(), m_ObjList[i], (OBJID)i, m_iRoomIndex,m_iNextIndex);
		
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
		{
			int roomIndex = (*iter)->GetRoomIndex();
			if (roomIndex == -1 || roomIndex == m_iRoomIndex 
				|| (m_bChange && roomIndex == m_iNextIndex))
			{
				(*iter)->Update_Components();

				if (DEAD == (*iter)->Update_GameObject())
				{
					//이벤트 값에 따른 처리 
					SAFE_DELETE(*iter);
					iter = m_ObjList[i].erase(iter);
					if (iter == m_ObjList[i].end()) break;
				}
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
			int roomIndex = (*iter)->GetRoomIndex();
			if (roomIndex == -1 || roomIndex == m_iRoomIndex
				|| (m_bChange && roomIndex == m_iNextIndex))
			{
				(*iter)->LateUpdate_Components();
				(*iter)->LateUpdate_GameObject();
			}
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
			int roomIndex = (*iter)->GetRoomIndex();
			if (roomIndex == -1 || roomIndex == m_iRoomIndex
				|| (m_bChange && roomIndex == m_iNextIndex))
			{
				if ((*iter)->GetVisible())
				{
					(*iter)->Render_Components();
					(*iter)->Render_GameObject();
				}
			}
			iter++;
		}
	}
}

void CGameObjectMgr::Release_GameObjectMgr()
{
	for (int i = 0; i < OBJID_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CGameObject*>);
		/*for (auto& iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();)
			SAFE_DELETE(iter->second);
		*/
		m_ObjList[i].clear();
		m_ObjList[i].swap(vector<CGameObject*>());
	}
}

void CGameObjectMgr::Add_GameObject(OBJID eID, CGameObject * pGameObject)
{
	if (pGameObject == nullptr) return;

	m_ObjList[eID].emplace_back(pGameObject);
	//m_ObjList[eID].emplace_back(pGameObject);
}
