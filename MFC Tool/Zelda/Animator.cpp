#include "stdafx.h"
#include "Animator.h"

CAnimator::CAnimator(CGameObject* owner, const wstring & wstrObjectKey, wstring wstrState, wstring wstrdir,float fEndFrame)
	:CBaseComponent(owner, COMPONENTID::ANIMATOR),
	m_wstrObjectKey(wstrObjectKey)
{
	m_wstrStateKey = wstrState;
	m_wstrDir = wstrdir;

	//string str = enumToString(m_eNextState);
	//m_wstrStateKey.assign(str.begin(), str.end());

	//str = enumToString(m_eDir);
	//wstring wstr;
	//wstr.assign(str.begin(), str.end());

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
	// wstrState += wstr;
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
	m_fFrame += m_fEndFrame*0.05f;
	if (m_fFrame >= m_fEndFrame)
		m_fFrame = 0;
}

void CAnimator::SetAniState(const wstring& wstrState, wstring wstrdir,float fEndFrame)
{
	if (fEndFrame != -1)
	{
		m_wstrStateKey = wstrState;
		m_fEndFrame = fEndFrame;
	}
	if(!wstrdir.empty())
		m_wstrDir = wstrdir;

	m_wstrStateKey += L"_" + m_wstrDir;

	/*wstring wstrState;
	wstrState.assign(m_wstrStateKey.begin(), m_wstrStateKey.end());
	wstrState.append(L"_");
	wstring wstr;
	wstr.assign(m_wstrDir.begin(), m_wstrDir.end());*/

	m_fFrame = 0;
	//m_eCurState = m_eNextState;
}


