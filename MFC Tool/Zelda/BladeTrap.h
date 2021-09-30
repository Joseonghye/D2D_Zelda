#pragma once
#ifndef __BLADE_TRAP_H__
#define __BLADE_TRAP_H__

#include "Monster.h"
class CBoxCollider;
class CBladeTrap : public CMonster
{
private:
	CBladeTrap();
public:
	virtual ~CBladeTrap();

	// Inherited via CMonster
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Render_GameObject() override;

public:
	static CBladeTrap* Create(MONSTERID eID);
	virtual void Damaged(int Att) override;

private:
	virtual void Attack() override;
	virtual void Fall() override {}

private:
	CBoxCollider* m_Collider;
	D3DXVECTOR3 m_vecOrign;

	bool m_bBack;
	float m_fBackSpeed;

	bool m_bAttack;

};

#endif // !__BLADE_TRAP_H__