#include "stdafx.h"
#include "Shield.h"


CShield::CShield()
{
}
CShield::~CShield()
{
	Release_GameObject();
}

HRESULT CShield::Initialized_GameObject()
{
	m_bVisible = false;
	return S_OK;
}

int CShield::Update_GameObject()
{
	return 0;
}

void CShield::LateUpdate_GameObject()
{
}

void CShield::Render_GameObject()
{
}

void CShield::Release_GameObject()
{
}

void CShield::StartUsing(DIR _dir)
{
	if (m_bUse) return;
	m_bUse = true;

	if (m_tInfo.eDir == _dir) return;

	switch (_dir)
	{
	case FRONT:
		m_tInfo.vDir = D3DXVECTOR3(0, -1, 0);
		break;
	case BACK:
		m_tInfo.vDir = D3DXVECTOR3(0, 1, 0);
		break;
	case LEFT:
		m_tInfo.vDir = D3DXVECTOR3(-1,0, 0);
		break;
	case RIGHT:
		m_tInfo.vDir = D3DXVECTOR3(1,0, 0);
		break;
	}
}

void CShield::Using()
{
}
