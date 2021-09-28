#include "stdafx.h"
#include "HeartUI.h"


CHeartUI::CHeartUI() {}

CHeartUI::~CHeartUI()
{
}

HRESULT CHeartUI::Initialized_GameObject()
{
	m_iRoomIndex = -1;
	m_bVisible = true;
	m_tInfo.vSize = D3DXVECTOR3(16.f, 16.f, 0);

	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);
	return S_OK;
}

int CHeartUI::Update_GameObject()
{
	return 0;
}

void CHeartUI::Render_GameObject()
{
	const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(m_wstrState);
	if (nullptr == pTexInfo)
		return;

	GRAPHICDEVICE->GetSprite()->SetTransform(&m_tInfo.matWorld);
	GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CHeartUI::SetHeart(int hp)
{
	switch (hp)
	{
	case 0:
		m_wstrState = L"Heart_Frame";
		break;
	case 1:
		m_wstrState = L"Heart_Half";
		break;
	case 2:
		m_wstrState = L"Heart_Full";
		break;
	}
}

