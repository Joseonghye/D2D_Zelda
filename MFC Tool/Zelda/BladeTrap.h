#pragma once
#ifndef __BLADE_TRAP_H__
#define __BLADE_TRAP_H__

#include "Monster.h"
class CBladeTrap : public CMonster
{
private:
	CBladeTrap();
public:
	virtual ~CBladeTrap();

	// Inherited via CMonster
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;

public:
	static CBladeTrap* Create(MONSTERID eID);
	virtual void Damaged(int Att) override;

private:
	virtual void Attack() override;

private:
	float m_fBackSpeed;
};

#endif // !__BLADE_TRAP_H__