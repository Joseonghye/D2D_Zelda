#pragma once
#ifndef __KIND_H__
#define __KIND_H__

enum COLOR { YELLOW, RED, GREEN, BLUE };

#include "Monster.h"
class CAnimator;
class CKind : public CMonster
{
public:
	CKind();
	virtual ~CKind();

	// CMonster을(를) 통해 상속됨
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;

	virtual void Damaged(int Att) override;

public:
	static CKind* Create(MONSTERID eID);

	const int GetColorID() { return (int)m_fColor; }
	
	const bool isStop() { return m_bStop; }
	void StartMove() { m_bStop = false; }

private:
	virtual void Attack() override;
	virtual void Fall() override {}

private:
	CAnimator* m_Animator;

	float m_fColor;
	bool m_bStop;

	bool m_bMove;
	DWORD m_dwMoveTime;
	DWORD m_dwTime;

	bool m_bWait;
	DWORD m_dwWaitTime;
};

#endif // !__KIND_H__