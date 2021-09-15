#include "stdafx.h"
#include "Weed.h"
#include "BoxCollider.h"

CWeed::CWeed()
{
}

CWeed::~CWeed()
{
	Release_GameObject();
}

HRESULT CWeed::Initialized_GameObject()
{
	m_bMove = false;
	m_tInfo.vSize = { 32.f, 32.f, 0.f };
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));

	return S_OK;
}

int CWeed::Update_GameObject()
{
	if (m_bDestory) return DEAD;

	return NO_EVENT;
}

void CWeed::LateUpdate_GameObject()
{
}

void CWeed::Render_GameObject()
{
	const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"Weed");
	if (nullptr == pTexInfo)
		return;

	GRAPHICDEVICE->GetSprite()->SetTransform(&m_tInfo.matWorld);
	GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CWeed::Release_GameObject()
{
}

void CWeed::Damaged()
{
	//ÆÄ±«µÊ
	m_bDestory = true;
}

bool CWeed::Pushed(DIR _dir)
{
	return false;
}

CWeed * CWeed::Create()
{
	CWeed* pInstance = new CWeed;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}
