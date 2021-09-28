#include "stdafx.h"
#include "BlackStone.h"
#include "BoxCollider.h"

CBlackStone::CBlackStone()
{
}
CBlackStone::~CBlackStone()
{
	Release_GameObject();
}

HRESULT CBlackStone::Initialized_GameObject()
{
	m_bMove = true;
	m_tInfo.vSize = { 32.f, 32.f, 0.f };
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));

	vMove = { 0,0,0 };
	m_fMoving = 0;
	m_bMoving = false;
	return S_OK;
}

int CBlackStone::Update_GameObject()
{
	if (m_bColl)
		m_fCollTime += TIMEMGR->Get_DeltaTime();

	if (GAMEOBJECTMGR->isChanging()) 
	{
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}
	if (m_bMoving)
	{
		m_fMoving += (32 *TIMEMGR->Get_DeltaTime());
		m_tInfo.vPos += (vMove *TIMEMGR->Get_DeltaTime());
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;

		if (m_fMoving >= 32) {

			m_bColl = false;
			m_fCollTime = 0;

			m_fMoving = 0;
			m_bMoving = false;
		}
	}

	return 0;
}

void CBlackStone::Render_GameObject()
{
	const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"BALCKSTONE");
	if (nullptr == pTexInfo)
		return;

	GRAPHICDEVICE->GetSprite()->SetTransform(&m_tInfo.matWorld);
	GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

bool CBlackStone::Pushed(DIR _dir)
{
	if (!m_bColl) m_bColl = true;

	if (m_bMoving) return false;

	if (m_fCollTime < 1.f) return false;

	//if (m_fCollTime >= 1.1f)
	//{
	//	m_fCollTime = 0;
	//	return false;
	//}

	float moveX = 32;
	float moveY = 32;
	switch (_dir)
	{
	case FRONT:
		vMove = { 0,moveY,0 };
		break;
	case BACK:
		vMove = { 0,-moveY,0 };
		break;
	case LEFT:
		vMove = { -moveX,0,0 };
		break;
	case RIGHT:
		vMove = { moveX,0,0 };
		break;
	}
	m_bMoving = true;

	return true;

}

CBlackStone * CBlackStone::Create()
{
	CBlackStone* pInstance = new CBlackStone;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}
