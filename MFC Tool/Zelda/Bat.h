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

	// CMonster��(��) ���� ��ӵ�
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;

public:
	static CBat* Create();

private:
	// CMonster��(��) ���� ��ӵ�
	virtual void Attack() override;

private:
	bool m_bAttack;
	float m_fAngle;
	float m_fRad;
	D3DXVECTOR3 m_vCenter;
	CAnimator* m_Animator;
};

#endif // !__BAT_H__