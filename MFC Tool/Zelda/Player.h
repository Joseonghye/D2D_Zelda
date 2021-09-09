#pragma once
#include "GameObject.h"

class CBoxCollider;
class CPlayer :
	public CGameObject
{
private:
	CPlayer();
public:
	virtual ~CPlayer();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CPlayer* Create();

private:
	float m_fSpeed;

	CBoxCollider* m_Collider;
};

