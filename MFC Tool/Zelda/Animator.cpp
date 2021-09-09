#include "stdafx.h"
#include "Animator.h"

CAnimator::CAnimator(CGameObject* owner, const wstring & wstrObjectKey, ANISTATE eState, DIR dir)
	:CBaseComponent(owner, COMPONENTID::ANIMATOR),
	m_wstrObjectKey(wstrObjectKey), m_eCurState(ANISTATE_END), m_eNextState(eState), m_eDir(dir)
{
	m_wstrStateKey = L"Walk";
	m_fFrame = 0;
	m_fEndFrame = 2;
}

CAnimator::~CAnimator()
{
	Release_Component();
}

int CAnimator::Update_Component()
{
	Update_Animation();
	return 0;
}

void CAnimator::LateUpdate_Component()
{
}

void CAnimator::Render_Component()
{
	const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(m_wstrObjectKey, m_wstrStateKey, DWORD(m_fFrame));
	if (nullptr == pTexInfo)
		return;

	GRAPHICDEVICE->GetSprite()->SetTransform(&m_pObject->GetWorldMat());
	GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CAnimator::Release_Component()
{
}

void CAnimator::Update_Animation()
{
	m_fFrame += m_fEndFrame*0.1f;
	if (m_fFrame >= m_fEndFrame)
		m_fFrame = 0;
}

void CAnimator::SetAniState(ANISTATE eState, DIR eDir, float fEndFrame)
{
	if (eState == m_eCurState) return;

	m_eNextState = eState;
	m_wstrStateKey = m_eNextState + m_eDir;
	m_fEndFrame = fEndFrame;

	m_eCurState = m_eNextState;
}


