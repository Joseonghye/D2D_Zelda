#pragma once
#ifndef __GAMEOBJMGR_H__
#define __GAMEOBJMGR_H__
#include "SingleTon.h"

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

	vector<CGameObject*> GetObjList(int objID) { return m_ObjList[objID]; }

private:
	vector<CGameObject*> m_ObjList[OBJID::OBJID_END];
};

#endif //__GAMEOBJMGR_H__