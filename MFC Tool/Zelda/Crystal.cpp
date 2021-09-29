#include "stdafx.h"
#include "Crystal.h"
#include "BoxCollider.h"

CCrystal::CCrystal() {}
CCrystal::~CCrystal() {	Release_GameObject(); }

HRESULT CCrystal::Initialized_GameObject()
{
	m_bMove = false;
	m_tInfo.vSize = { 32.f, 32.f, 0.f };
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));

	return S_OK;
}

int CCrystal::Update_GameObject()
{
	if (m_bDestory) return DEAD;

	if (GAMEOBJECTMGR->isChanging())
	{
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}

	return NO_EVENT;
}

void CCrystal::Render_GameObject()
{
	const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"Crystal");
	if (nullptr == pTexInfo)
		return;

	GRAPHICDEVICE->GetSprite()->SetTransform(&m_tInfo.matWorld);
	GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CCrystal::Damaged()
{
	m_bDestory = true;
}

CCrystal * CCrystal::Create()
{
	CCrystal* pInstance = new CCrystal;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}
