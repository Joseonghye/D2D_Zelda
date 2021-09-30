#include "stdafx.h"
#include "BottomUI.h"


CBottomUI::CBottomUI() {}
CBottomUI::~CBottomUI() {}

HRESULT CBottomUI::Initialized_GameObject()
{
	m_iRoomIndex = -1;
	m_bVisible = true;
//	m_tInfo.vSize = D3DXVECTOR3(32.f, 32.f, 0);

	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);
	return S_OK;
}

int CBottomUI::Update_GameObject(){	return 0; }

void CBottomUI::LateUpdate_GameObject() {}

void CBottomUI::Render_GameObject()
{
	const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"Bottom");
	if (nullptr == pTexInfo)
		return;

	GRAPHICDEVICE->GetSprite()->SetTransform(&m_tInfo.matWorld);
	GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBottomUI::Release_GameObject() {}

CBottomUI * CBottomUI::Create()
{
	CBottomUI* pInstance = new CBottomUI;
	if (FAILED(pInstance->Initialized_GameObject()))
		SAFE_DELETE(pInstance);

	pInstance->SetPos(160, 288);
	pInstance->SetTransMat();
	pInstance->SetWorldMat();

	return pInstance;
}
