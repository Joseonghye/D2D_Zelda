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
	void AddPos(D3DXVECTOR3 vec) { m_tInfo.vPos += vec; }

	void SetInfo(const INFO _info) { m_tInfo = _info; }

	void SetTransMat() { D3DXMatrixTranslation(&m_tInfo.matTrans, 
							m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);}
	void SetWorldMat() { m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans; }

	void SetDestory() { m_bDestory = true; }
	void SetVisible(bool _visible) { m_bVisible = _visible; }

	void SetMove(bool _b) { m_bMove = _b; }
	void SetRoomIndex(int index) { m_iRoomIndex = index; }
	
public:
	CBaseComponent* GetComponent(COMPONENTID _id);

	const D3DXVECTOR3& GetPos() { return m_tInfo.vPos; }
	const D3DXMATRIX& GetWorldMat() { return m_tInfo.matWorld; }
	//const D3DXVECTOR3& GetDir() { return m_tInfo.vDir; }
	const int GetRoomIndex() { return m_iRoomIndex; }
	const D3DXVECTOR3& GetVecDir() { return m_tInfo.vDir; }
	DIR GetDir() { return m_tInfo.eDir; }

	const bool& const GetVisible() { return m_bVisible; }
	bool GetMove() { return m_bMove; }
protected:
	vector<CBaseComponent*> m_vecComponet;
	INFO m_tInfo;

	int m_iRoomIndex;
	bool m_bDestory;
	bool m_bVisible;
	bool m_bMove;
};

#endif