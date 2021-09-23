#include "stdafx.h"
#include "GameButton.h"
#include "BoxCollider.h"
#include "Key.h"

CGameButton::CGameButton():m_pObj(nullptr)
{
}


CGameButton::~CGameButton()
{
	Release_GameObject();
}

HRESULT CGameButton::Initialized_GameObject()
{
	m_iRoomIndex = -1;
	m_bVisible = true;
	m_bMove = false;

	m_tInfo.vSize = { 32.f, 32.f, 0.f };

	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);
	m_Collider = static_cast<CBoxCollider*>(AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y)));

	return S_OK;
}

int CGameButton::Update_GameObject()
{
	return 0;
}

void CGameButton::LateUpdate_GameObject()
{
}

void CGameButton::Render_GameObject()
{
	/*const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"Button");
	if (nullptr == pTexInfo)
		return;

	GRAPHICDEVICE->GetSprite()->SetTransform(&m_tInfo.matWorld);
	GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));*/
}

void CGameButton::Release_GameObject()
{
	for_each(m_vecComponet.begin(), m_vecComponet.end(), Safe_Delete<CBaseComponent*>);
	m_vecComponet.clear();
	m_vecComponet.swap(vector<CBaseComponent*>());
}

CGameButton * CGameButton::Create(char* str)
{
	CGameButton* pInstance = new CGameButton;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	pInstance->SetStrValue(str);
	return pInstance;
}

void CGameButton::PushButton()
{
	if (m_pObj) return;

	if (m_strValue=="Key")
		m_pObj = CKey::Create();

	m_pObj->SetRoomIndex(m_iRoomIndex);
	m_pObj->SetPos(m_tInfo.vPos);
	m_pObj->SetTransMat();
	m_pObj->SetWorldMat();

	GAMEOBJECTMGR->Add_GameObject(ITEM, m_pObj);
}
