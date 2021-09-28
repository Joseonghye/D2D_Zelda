#pragma once
#ifndef __GAMEOBJMGR_H__
#define __GAMEOBJMGR_H__
#include "SingleTon.h"
#include "CollisionMgr.h"
#include "UIMgr.h"

class CGameObject;
class CGameObjectMgr :public CSingleTon<CGameObjectMgr>
{
	friend CSingleTon;
private:
	CGameObjectMgr();
	~CGameObjectMgr();

public:
	void Update_GameObjectMgr();
	void LateUpdate_GameObjectMgr();
	void Render_GameObjectMgr();
	void Release_GameObjectMgr();

	void Add_GameObject(OBJID eID, CGameObject* pGameObject);
	void SetCurRoomIndex(int x, int y) { m_iRoomIndex = x + (TOTAL_TILEX *y); }
	int SetNextIndex(int value) { m_bChange = true; return m_iNextIndex = (m_iRoomIndex + value); }

	CGameObject* GetPlayer() { return m_ObjList[PLAYER].front(); }
	vector<CGameObject*> GetObjList(int objID) { return m_ObjList[objID]; }
	int GetRoomIndex() { return m_iRoomIndex; }
	bool isChanging() { return m_bChange; }
	int GetNextRoom() { return m_iNextIndex; }

private:
	vector<CGameObject*> m_ObjList[OBJID::OBJID_END];
	CCollisionMgr CollisionMgr;
	CUIMgr UIMgr;
	
	int m_iRoomIndex;
	int m_iNextIndex;
	bool m_bChange;
};

#endif //__GAMEOBJMGR_H__