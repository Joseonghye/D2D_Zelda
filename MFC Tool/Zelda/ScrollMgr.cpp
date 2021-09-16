#include "stdafx.h"
#include "ScrollMgr.h"


CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::SetScroll(int x, int y)
{
	m_iIndex = x + (TOTAL_TILEX *y);

	m_vScroll = {-(float)((ROOM_TILEX*TILECX)*x),-(float)((ROOM_TILEY*TILECY)*y),0 };

}
