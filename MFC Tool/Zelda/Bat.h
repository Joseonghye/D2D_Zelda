#pragma once
#ifndef __BAT_H__
#define __BAT_H__

#include "Monster.h"
class CAnimator;
class CBat : public CMonster
{
public:
	CBat();
	virtual ~CBat();

	// CMonster을(를) 통해 상속됨
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;

	virtual void Damaged(int Att) override;

public:
	static CBat* Create(MONSTERID eID);

private:
	// CMonster을(를) 통해 상속됨
	virtual void Attack() override;

private:
	bool m_bAttack;
	
	bool m_bIdle;
	DWORD m_dwIdleTime;
	
	float m_fEndAngle;
	float m_fAngle;
	float m_fDir;

	float m_fRad;
	float m_fDist;
	
	D3DXVECTOR3 m_vCenter;
	D3DXVECTOR3 m_vOrign;
	CAnimator* m_Animator;
};

#endif // !__BAT_H__