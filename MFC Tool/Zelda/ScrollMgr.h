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
	bool ChangeScroll();
public:
	void SetScroll(int x, int y);
	void SetScroll(int index);
	D3DXVECTOR3 GetScrollVec() { return m_vScroll; }

private:
//	int m_iIndex;
	D3DXVECTOR3 m_vScroll;
	D3DXVECTOR3 m_vNext;
};

#endif // !__SCROLLMGR_H__
