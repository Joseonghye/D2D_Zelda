#include "stdafx.h"
#include "Sword.h"
#include "BoxCollider.h"

CSword::CSword()
{
}


CSword::~CSword()
{
}

HRESULT CSword::Initialized_GameObject()
{
	m_Collider = static_cast<CBoxCollider*>(AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y)));


	return S_OK;
}

int CSword::Update_GameObject()
{
	//몬스터와 충돌체크 
	if (m_Collider != nullptr)
	{
		vector<CGameObject*> vecObj = GAMEOBJECTMGR->GetObjList(MONSTER);

		for (int i = 0; i < vecObj.size(); ++i)
		{
			CBoxCollider* another = static_cast<CBoxCollider*>(vecObj[i]->GetComponent(COMPONENTID::COLLISION));

			if (another != nullptr && m_Collider->CheckCollision(another))
			{
				//충돌
				//몬스터 사망 
				vecObj[i]->SetDestory();

			}
		}
	}

	return 0;
}

void CSword::LateUpdate_GameObject()
{
}

void CSword::Render_GameObject()
{
}

void CSword::Release_GameObject()
{
}
