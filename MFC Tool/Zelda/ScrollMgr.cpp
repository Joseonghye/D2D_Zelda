#include "stdafx.h"
#include "ScrollMgr.h"


CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

bool CScrollMgr::ChangeScroll()
{
	D3DXVECTOR3 dir = (m_vNext - m_vScroll);

	if (D3DXVec3Length(&dir) <= 1)
	{
		m_vScroll = m_vNext;
		return true;
	}

	D3DXVec3Normalize(&dir, &dir);

	m_vScroll += (dir * 256 * TIMEMGR->Get_DeltaTime());//(dir * 128 * TIMEMGR->Get_DeltaTime());

	return false;
}

void CScrollMgr::SetScroll(int x, int y)
{
	//m_iIndex = x + (TOTAL_TILEX *y);

	m_vScroll = {-(float)((ROOM_TILEX*TILECX)*x),-(float)((ROOM_TILEY*TILECY)*y),0 };

}

void CScrollMgr::SetScroll(int index)
{
	int y = index / TOTAL_TILEX;
	int x = (index - (TOTAL_TILEX*y));
	m_vNext = { -(float)((ROOM_TILEX*TILECX)*x),-(float)((ROOM_TILEY*TILECY)*y),0 };
}
