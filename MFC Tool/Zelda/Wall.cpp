#include "stdafx.h"
#include "Wall.h"
#include "BoxCollider.h"

CWall::CWall()
{
}
CWall::~CWall()
{
	Release_GameObject();
}

HRESULT CWall::Initialized_GameObject()
{
	m_bMove = false;
	m_bVisible = false;

	m_tInfo.vSize = { 32.f,32.f,0 };
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));

	return S_OK;
}

int CWall::Update_GameObject()
{
	if (GAMEOBJECTMGR->isChanging())
	{
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}
	return 0;
}

void CWall::LateUpdate_GameObject()
{
}

void CWall::Render_GameObject()
{
}

void CWall::Release_GameObject()
{
	for_each(m_vecComponet.begin(), m_vecComponet.end(), Safe_Delete<CBaseComponent*>);
	m_vecComponet.clear();
}

CWall * CWall::Create()
{
	CWall* pInstance = new CWall;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}
