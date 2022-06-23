#include "stdafx.h"
#include "Key.h"
#include "BoxCollider.h"

CKey::CKey()
{
}

CKey::~CKey()
{
	Release_GameObject();
}

HRESULT CKey::Initialized_GameObject()
{
	m_bVisible = true;
	m_tInfo.vSize = D3DXVECTOR3(16, 32, 0);

	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);
	m_Collider = static_cast<CBoxCollider*>(AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y)));

	return S_OK;
}

int CKey::Update_GameObject()
{
	if (KEYMGR->Key_Down(KEY_X))
		return DEAD;

	if (GAMEOBJECTMGR->isChanging())
	{
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}
	return NO_EVENT;
}

void CKey::LateUpdate_GameObject()
{
}

void CKey::Render_GameObject()
{
	const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"KEY");
	if (nullptr == pTexInfo)
		return;

	GRAPHICDEVICE->GetSprite()->SetTransform(&m_tInfo.matWorld);
	GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CKey::Release_GameObject()
{
}

void CKey::StartUsing(DIR _dir)
{
}

CKey * CKey::Create()
{
	CKey* pInstance = new CKey;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}
