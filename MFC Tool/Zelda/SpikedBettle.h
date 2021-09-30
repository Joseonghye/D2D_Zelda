#pragma once
#ifndef __SPIKEBETTLE_H__
#define __SPIKEBETTLE_H__

#include "Monster.h"
class CAnimator;
class CSpikedBettle : public CMonster
{
public:
	CSpikedBettle();
	virtual ~CSpikedBettle();

	// Inherited via CMonster
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Damaged(int Att) override;
	virtual void Fall() override;
	virtual void Attack() override;

private:
	CAnimator* m_Animator;
	
	bool m_bDead;
	bool m_bFall;
	bool m_bReverse;
	bool m_bAttack
};
#endif // !__SPIKEBETTLE_H__