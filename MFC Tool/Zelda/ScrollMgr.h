#pragma once
#ifndef __SCROLLMGR_H__
#define __SCROLLMGR_H__
#include "SingleTon.h"

class CScrollMgr :public CSingleTon<CScrollMgr>
{
	friend CSingleTon;
private:
	CScrollMgr();
	~CScrollMgr();

public:
	void SetScroll(int x, int y);
	D3DXVECTOR3 GetScrollVec() { return m_vScroll; }

private:
	int m_iIndex;
	D3DXVECTOR3 m_vScroll;
};

#endif // !__SCROLLMGR_H__
