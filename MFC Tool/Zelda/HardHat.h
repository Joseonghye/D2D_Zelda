#pragma once
#ifndef __HARDHAT_H__
#define __HARDHAT_H__

#include "Monster.h"
#include "Subject.h"

class CAnimator;
class CHardHat : public CMonster
{
private:
	CHardHat();
public:
	virtual ~CHardHat();

	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;

	virtual void Damaged(int Att) override;
public:
	static CHardHat* Create(MONSTERID eID);

	// CMonster을(를) 통해 상속됨
	virtual void Attack() override;
	virtual void Fall() override;

private:
	CAnimator* m_Animator;

	bool m_bFall;
};

#endif // !__HARDHAT_H__