#pragma once
#ifndef __HARDHAT_H__
#define __HARDHAT_H__

#include "Monster.h"
#include "Subject.h"
class CHardHat : public CMonster
{
private:
	CHardHat();
public:
	virtual ~CHardHat();

	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;

public:
	static CHardHat* Create();

	// CMonster을(를) 통해 상속됨
	virtual void Attack() override;
};

#endif // !__HARDHAT_H__