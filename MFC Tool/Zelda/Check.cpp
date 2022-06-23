#include "stdafx.h"
#include "Check.h"
#include "HardHat.h"
#include "Key.h"
#include "Door.h"
#include "Animator.h"

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
	if (GAMEOBJECTMGR->isChanging())
	{
		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	}

	//�� �������� Ȯ�� 
	if (m_iMonsterCount == 0) 
	{
		//�� �������� �׿� ���� ���.
		if (m_strValue == "Key") 
		{
			m_pObj = CKey::Create();

			m_pObj->SetRoomIndex(m_iRoomIndex);
			m_pObj->SetPos(m_tInfo.vPos);
			m_pObj->SetTransMat();
			m_pObj->SetWorldMat();

			GAMEOBJECTMGR->Add_GameObject(ITEM, m_pObj);
		}
		else
		{
			vector<CGameObject*> vecInteraction = GAMEOBJECTMGR->GetObjList(INTERACTION);
			for (auto& iter : vecInteraction)
			{
				if (typeid(*iter) == typeid(CDoor) && iter->GetRoomIndex() == m_iRoomIndex)
				{
					(static_cast<CDoor*>(iter))->GetAnimator()->SetAniState(L"IDLE_OPEN", L"", 1);
					static_cast<CDoor*>(iter)->MoveDoor(L"OPEN");
				}
			}
		}
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

CCheck * CCheck::Create(char* str, int id)
{
	CCheck* pInstance = new CCheck;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	pInstance->SetStrValue(str);
	pInstance->SetEventID(id);
	return pInstance;
}

void CCheck::OnNotify()
{
	--m_iMonsterCount;
}

void CCheck::SetMonsterCount()
{
	//�ش� ���� ���� ��
	vector<CGameObject*> vecMonster = GAMEOBJECTMGR->GetObjList(MONSTER);
	for (auto& iter : vecMonster)
	{
		if (iter->GetRoomIndex() == m_iRoomIndex)
		{
			if (m_iMonsterCount == -1) m_iMonsterCount = 1;
			else  ++m_iMonsterCount;
			
			static_cast<CMonster*>(iter)->RegisterObserver(this);
		}
	}
}
