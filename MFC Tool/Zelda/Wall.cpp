#include "stdafx.h"
#include "Wall.h"
#include "BoxCollider.h"

CWall::CWall()
{
}
CWall::~CWall()
{
}

HRESULT CWall::Initialized_GameObject()
{
	m_tInfo.vSize = { 16.f,16.f,0 };
	AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y));

	return S_OK;
}

int CWall::Update_GameObject()
{
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
}

CWall * CWall::Create()
{
	CWall* pInstance = new CWall;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}
