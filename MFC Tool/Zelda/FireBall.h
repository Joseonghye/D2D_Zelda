#pragma once
#include "Monster.h"
class CFireBall : public CMonster
{
public:
	CFireBall();
	virtual ~CFireBall();

	// CMonster��(��) ���� ��ӵ�
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;

	virtual void Attack() override;
};

