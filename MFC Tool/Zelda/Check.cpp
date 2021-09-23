#include "stdafx.h"
#include "Check.h"
#include "HardHat.h"
#include "Key.h"

CCheck::CCheck() :m_pObj(nullptr), m_iMonsterCount(-1){}

CCheck::~CCheck()
{
	Release_GameObject();
}

HRESULT CCheck::Initialized_GameObject()
{
	m_bVisible = false;

	return S_OK;
}

int CCheck::Update_GameObject()
{
	//다 잡혔는지 확인 
	if (m_iMonsterCount == 0) 
	{
		//다 잡혔으면 그에 따른 결과.
		if (m_strValue == "Key")
			m_pObj = CKey::Create();

		m_pObj->SetRoomIndex(m_iRoomIndex);
		m_pObj->SetPos(m_tInfo.vPos);
		m_pObj->SetTransMat();
		m_pObj->SetWorldMat();

		GAMEOBJECTMGR->Add_GameObject(ITEM, m_pObj);

		return DEAD;
	}
	return NO_EVENT;
}

void CCheck::LateUpdate_GameObject() {}

void CCheck::Render_GameObject() {}

void CCheck::Release_GameObject()
{
	m_pObj = nullptr;
}

CCheck * CCheck::Create(char* str)
{
	CCheck* pInstance = new CCheck;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	pInstance->SetStrValue(str);
	return pInstance;
}

void CCheck::OnNotify()
{
	--m_iMonsterCount;
}

void CCheck::SetMonsterCount()
{
	//해당 방의 몬스터 수
	vector<CGameObject*> vecMonster = GAMEOBJECTMGR->GetObjList(MONSTER);
	for (auto& iter : vecMonster)
	{
		if (iter->GetRoomIndex() == m_iRoomIndex)
		{
			if (m_iMonsterCount == -1) m_iMonsterCount = 1;
			else  ++m_iMonsterCount;
			
			static_cast<CHardHat*>(iter)->RegisterObserver(this);
		}

	}
}
