#pragma once
#include "GameObject.h"

class CBoxCollider;
class CAnimator;
class CEquipment;
class CPlayer :
	public CGameObject
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

public:
	static CPlayer* Create();

	void SetStartPos(D3DXVECTOR3 vPos) { m_tInfo.vPos = vPos; }
	void SetState(STATE eState) { m_eNextState = eState; ChangeState(); }
	bool Defense(D3DXVECTOR3 vPos, D3DXVECTOR3 vMonDir);

private:
	void Attack();
	void ChangeState();

private:
	float m_fSpeed;
	CBoxCollider* m_Collider;
	CAnimator* m_Animator;

	CEquipment* m_pItem[2];

	bool m_bDefense;
	bool m_bPush;
	DWORD m_dwPushTime;

	DIR m_eCurDir;
	DIR m_eNextDir;
	STATE m_eCurState;
	STATE m_eNextState;

	//아이템 두개 장착 
};

