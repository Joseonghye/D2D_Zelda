#pragma once
#include "BaseComponent.h"
class CAnimator :
	public CBaseComponent
{
public:
	CAnimator(CGameObject* owner, const wstring& wstrObjectKey, ANISTATE eState, DIR dir = DIR::FRONT);
	virtual ~CAnimator();

	// CBaseComponent을(를) 통해 상속됨
	virtual int Update_Component() override;
	virtual void LateUpdate_Component() override;
	virtual void Render_Component()override;
	virtual void Release_Component() override;

	void Update_Animation();

	void SetAniState(ANISTATE eState, DIR eDir, float fEndFrame);
//	void ChangeAnimation();
	//void SetAniSpeed(float fSpeed);
private:
	const wstring m_wstrObjectKey;
	wstring m_wstrStateKey;
	float m_fFrame;
	float m_fEndFrame;
	//float m_fAniSpeed;

	ANISTATE m_eCurState;
	ANISTATE m_eNextState;
	DIR		 m_eDir;

//	const TEXINFO* m_pTexInfo;
};

