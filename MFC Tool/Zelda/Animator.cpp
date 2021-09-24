#include "stdafx.h"
#include "Animator.h"

CAnimator::CAnimator(CGameObject* owner, const wstring & wstrObjectKey, wstring wstrState, wstring wstrdir, float fEndFrame, float fSpeed)
	:CBaseComponent(owner, COMPONENTID::ANIMATOR),
	m_wstrObjectKey(wstrObjectKey), m_fSpeed(fSpeed)
{
	m_bOnce = false;

	m_wstrStateKey = wstrState;
	m_wstrDir = wstrdir;

	m_wstrStateKey += L"_" + m_wstrDir;

	m_fFrame = 0;
	m_fEndFrame = fEndFrame;
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
	m_fFrame += m_fEndFrame * TIMEMGR->Get_DeltaTime() *m_fSpeed;
	if (m_fFrame >= m_fEndFrame) 
	{
		m_fFrame = 0;
		if (m_bOnce)
		{
			m_bOnce = false;
			m_wstrStateKey = m_wstrOnceStateKey;
			m_fEndFrame = m_fOnceEndFrame;
		}
	}
}

void CAnimator::SetAniState(const wstring& wstrState, wstring wstrdir,float fEndFrame, float fSpeed)
{
	if (fEndFrame != -1)
	{
		m_wstrStateKey = wstrState;
		m_fEndFrame = fEndFrame;
	}
	if (!wstrdir.empty()) 
	{
		size_t index = m_wstrStateKey.rfind('_');
		m_wstrStateKey = m_wstrStateKey.substr(0, index);

		m_wstrDir = wstrdir;
	}

	m_wstrStateKey += L"_" + m_wstrDir;
	m_fFrame = 0;
	m_fSpeed = fSpeed;
}

void CAnimator::AniPlayOnce(const wstring & wstrState, wstring wstrdir, float fEndFrame, float fSpeed)
{
	m_bOnce = true;
	m_wstrOnceStateKey = m_wstrStateKey;
	m_fOnceEndFrame = m_fEndFrame;

	if (fEndFrame != -1)
	{
		m_wstrStateKey = wstrState;
		m_fEndFrame = fEndFrame;
	}
	if (!wstrdir.empty())
	{
		size_t index = m_wstrStateKey.rfind('_');
		m_wstrStateKey = m_wstrStateKey.substr(0, index);

		m_wstrDir = wstrdir;
	}
	m_wstrStateKey += L"_" + m_wstrDir;
	m_fFrame = 0;
	m_fSpeed = fSpeed;
}


