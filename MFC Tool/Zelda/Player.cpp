#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer() :m_fSpeed(5.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}


CPlayer::~CPlayer()
{
	Release_GameObject();
}

HRESULT CPlayer::Initialized_GameObject()
{
	m_tInfo.vPos = { 400.f , 300.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };
	m_tInfo.vDir = { 1.f, -1.f, 0.f };

	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
		
	return S_OK;
}

int CPlayer::Update_GameObject()
{
	if (KEYMGR->Key_Pressing(KEY_LEFT))
		m_tInfo.vPos.x -= m_fSpeed;
	else if (KEYMGR->Key_Pressing(KEY_RIGHT))
		m_tInfo.vPos.x += m_fSpeed;

	if (KEYMGR->Key_Pressing(KEY_UP))
		m_tInfo.vPos.y -= m_fSpeed;
	else if (KEYMGR->Key_Pressing(KEY_DOWN))
		m_tInfo.vPos.y += m_fSpeed;

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	return 0;
}

void CPlayer::LateUpdate_GameObject()
{
}

void CPlayer::Render_GameObject()
{
	const TEXINFO* pTexInfo =TEXTUREMGR->GetTexture(L"Player", L"Attack");
	if (nullptr == pTexInfo)
		return;

	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;

	GRAPHICDEVICE->GetSprite()->SetTransform(&m_tInfo.matWorld);
	GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayer::Release_GameObject()
{
}

CPlayer * CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer;
	if(FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}
