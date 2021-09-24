#include "stdafx.h"
#include "Enter.h"
#include "BoxCollider.h"

CEnter::CEnter()
{
}

CEnter::~CEnter()
{
	Release_GameObject();
}

HRESULT CEnter::Initialized_GameObject()
{
	m_bVisible = false;
	m_bMove = false;

	m_tInfo.vSize = { 16.f,16.f,0 };
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));

	return S_OK;
}

int CEnter::Update_GameObject()
{
	if (GAMEOBJECTMGR->isChanging())
	{
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}

	return 0;
}

void CEnter::LateUpdate_GameObject()
{
}

void CEnter::Render_GameObject()
{
}

void CEnter::Release_GameObject()
{
	for_each(m_vecComponet.begin(), m_vecComponet.end(), Safe_Delete<CBaseComponent*>);
	m_vecComponet.clear();
}

CEnter* CEnter::Create(D3DXVECTOR3 vPos, string str,int ID)
{
	CEnter* pInstance = new CEnter;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	pInstance->SetPos(vPos);
	pInstance->SetDir(str);
	pInstance->SetEventID(ID);

	return pInstance;
}

void CEnter::SetDir(string str)
{
	if ("Up" == str) {
		m_tInfo.eDir = DIR::BACK;
		m_tInfo.vPos.y -= 8.f;
	}
	else if ("Down" == str) {
		m_tInfo.eDir = DIR::FRONT;
		m_tInfo.vPos.y += 8.f;
	}
	else if ("Left" == str) {
		m_tInfo.eDir = DIR::LEFT;
		m_tInfo.vPos.x -= 8.f;
	}
	else if ("Right" == str) {
		m_tInfo.eDir = DIR::RIGHT;
		m_tInfo.vPos.x += 8.f;
	}
}

void CEnter::Using()
{
	int index = 0;
	switch (m_tInfo.eDir)
	{
	case FRONT:
		index = GAMEOBJECTMGR->SetNextIndex((int)TOTAL_TILEX);
		SCROLLMGR->SetScroll(index);
		break;
	case BACK:
		index = GAMEOBJECTMGR->SetNextIndex(-((int)TOTAL_TILEX));
		SCROLLMGR->SetScroll(index);
		break;
	case LEFT:
		index = GAMEOBJECTMGR->SetNextIndex(-1);
		SCROLLMGR->SetScroll(index);
		break;
	case RIGHT:
		index = GAMEOBJECTMGR->SetNextIndex(1);
		SCROLLMGR->SetScroll(index);
		break;
	}
}
