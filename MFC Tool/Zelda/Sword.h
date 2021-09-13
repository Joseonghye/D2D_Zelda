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

	void SetPlayer(CGameObject* player) { m_pPlayer = player; }
	void Attack();
private:
	CBoxCollider* m_Collider;
//	D3DXMATRIX m_matRot;
	CGameObject* m_pPlayer;
	float m_fAngle;
	bool m_bAttack;
};

