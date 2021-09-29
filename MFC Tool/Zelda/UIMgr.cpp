#include "stdafx.h"
#include "UIMgr.h"
#include "Player.h"
#include "HeartUI.h"

CUIMgr::CUIMgr(){}
CUIMgr::~CUIMgr()
{}

void CUIMgr::OnNotify()
{
	int iTotal = m_pPlayer->GetTotalHp();
	int iHp = m_pPlayer->GetHp();

	if (iHp <= 0)return;

	int value = (iTotal - iHp);
	if (value > 0)
	{
		int div = value / 2;
		int size = m_vecHeart.size() - 1;
		if (div > 0)
		{
			for (int i = size; i > size - div; --i)
			{
				m_vecHeart[i]->SetHeart(0);
			}
		}
		if (value % 2 > 0)
			m_vecHeart[(size - div)]->SetHeart(1);
	}
}

void CUIMgr::SetPlayer(CGameObject * _player)
{
	m_pPlayer = static_cast<CPlayer*>(_player);
	m_pPlayer->RegisterObserver(this);

	int size = (int)(m_pPlayer->GetTotalHp()/2);
	m_vecHeart.resize(size);

	D3DXVECTOR3 vStart{ 200.f,270.f,0.f };
	for (size_t i = 0; i < m_vecHeart.size(); ++i)
	{
		m_vecHeart[i] = new CHeartUI;
		m_vecHeart[i]->Initialized_GameObject();

		D3DXVECTOR3 vPos = vStart;
		vPos.x = vStart.x + (i * 16);
		m_vecHeart[i]->SetPos(vPos);
		m_vecHeart[i]->SetTransMat();
		m_vecHeart[i]->SetWorldMat();

		m_vecHeart[i]->SetHeart(2);

		GAMEOBJECTMGR->Add_GameObject(UI, m_vecHeart[i]);
	}
}
