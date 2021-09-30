#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameObject.h"
#include "Subject.h"

class CBoxCollider;
class CAnimator;
class CEquipment;
class CPlayer :	public CGameObject, public CSubject
{
private:
	CPlayer();
public:
	virtual ~CPlayer();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

	virtual void RegisterObserver(CObserver * observer) override;
	virtual void RemoveObserver() override;

public:
	static CPlayer* Create();

	void SetStartPos(D3DXVECTOR3 vPos) { m_tInfo.vPos = vPos; }
	void SetState(STATE eState) { m_eNextState = eState; ChangeState(); }
	void Damaged(int att, STATE eState);
	bool Defense(D3DXVECTOR3 vPos, D3DXVECTOR3 vMonDir);

	int GetTotalHp() { return m_iTotalHp; }
	int GetHp() { return m_iHp; }

private:
	void Attack();
	void ChangeState();

	virtual void NotifyObserver() override;

private:
	int m_iHp;
	int m_iTotalHp;

	float m_fSpeed;
	CBoxCollider* m_Collider;
	CAnimator* m_Animator;

	CEquipment* m_pItem[2];

	bool m_bJump;
	bool m_bDefense;
	bool m_bPush;
	DWORD m_dwPushTime;

	bool m_bSuper;
	DWORD m_dwSuperTime;

	DIR m_eCurDir;
	DIR m_eNextDir;
	STATE m_eCurState;
	STATE m_eNextState;
};

#endif // !__PLAYER_H__