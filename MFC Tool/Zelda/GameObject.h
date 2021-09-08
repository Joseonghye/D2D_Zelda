#pragma once
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

protected:
	INFO* m_tInfo;
};

