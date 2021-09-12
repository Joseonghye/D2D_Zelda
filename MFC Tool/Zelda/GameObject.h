#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class CBaseComponent;
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	virtual HRESULT Initialized_GameObject() PURE;
	virtual int Update_GameObject() PURE;
	virtual void LateUpdate_GameObject() PURE;
	virtual void Render_GameObject() PURE;
	virtual void Release_GameObject() PURE;

private: 
	friend class CGameObjectMgr;

	void Update_Components();
	void LateUpdate_Components();
	void Render_Components();
	void Release_Components();

public:
	CBaseComponent* AddComponent(CBaseComponent* _component);
	void SetPos(float x, float y) { m_tInfo.vPos.x = x; m_tInfo.vPos.y = y; }
	void SetPos(D3DXVECTOR3 vec) { m_tInfo.vPos = vec; }
	void SetInfo(const INFO _info) { m_tInfo = _info; }

	void SetDestory() { m_bDestory = true; }
public:
	const D3DXVECTOR3& GetPos() { return m_tInfo.vPos; }
	const D3DXMATRIX& GetWorldMat() { return m_tInfo.matWorld; }
	CBaseComponent* GetComponent(COMPONENTID _id);

protected:
	vector<CBaseComponent*> m_vecComponet;
	INFO m_tInfo;
	bool m_bDestory;
};

#endif