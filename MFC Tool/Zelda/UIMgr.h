#pragma once
#ifndef __UIMGR_H__
#define __UIMGR_H__

#include "Observer.h"
class CHeartUI;
class CPlayer;
class CUIMgr : public CObserver
{
public:
	CUIMgr();
	~CUIMgr();

	// CObserver��(��) ���� ��ӵ�
	virtual void OnNotify() override;

	void SetPlayer(CGameObject* _player);

private:
	vector<CHeartUI*> m_vecHeart;
	CPlayer* m_pPlayer;
};

#endif // !__UIMGR_H__
