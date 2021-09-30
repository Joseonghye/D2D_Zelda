#pragma once
#include "BaseComponent.h"
class CAnimator :
	public CBaseComponent
{
public:
	CAnimator(CGameObject* owner, const wstring& wstrObjectKey, wstring wstrState, wstring wstrdir = L"FRONT", float fEndFrame = 1, float fSpeed = 5);
	virtual ~CAnimator();

	// CBaseComponent을(를) 통해 상속됨
	virtual int Update_Component() override;
	virtual void LateUpdate_Component() override;
	virtual void Render_Component()override;
	virtual void Release_Component() override;

	void Update_Animation();

	void SetObjectKey(wstring wstrObjKey) { m_wstrObjectKey = wstrObjKey; }
	void SetAniState(const wstring& wstrState, wstring wstrdir, float fEndFrame, float fSpeed = 5);
	void SetDefensAni(bool bDefens);
	void AniPlayOnce(const wstring& wstrState, wstring wstrdir, float fEndFrame, float fSpeed = 5);

	bool GatPlayOnce() { return m_bOnce; }

private:
	wstring m_wstrObjectKey;
	wstring m_wstrStateKey;
	wstring m_wstrDir;

	wstring m_wstrOnceStateKey;
	float m_fOnceEndFrame;
	float m_fOnceSpeed;

	float m_fFrame;
	float m_fEndFrame;

	float m_fSpeed;
	
	bool m_bOnce;

	//float m_fAniSpeed;
};

