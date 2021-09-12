#pragma once
#include "GameObject.h"

class CBoxCollider;
class CSword :
	public CGameObject
{
public:
	CSword();
	~CSword();

	// Inherited via CGameObject
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

private:
	CBoxCollider* m_Collider;
};

