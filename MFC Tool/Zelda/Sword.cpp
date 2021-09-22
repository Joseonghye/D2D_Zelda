#include "stdafx.h"
#include "Sword.h"
#include "BoxCollider.h"
#include "InteractionObj.h"

CSword::CSword() :m_fAngle(0.f)
{
}

CSword::~CSword()
{
	Release_GameObject();
}

HRESULT CSword::Initialized_GameObject()
{
	m_bVisible = false;

	m_tInfo.vPos = D3DXVECTOR3(-20.f, 0, 0);
	m_tInfo.vSize = D3DXVECTOR3(30, 12, 0);

	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	m_tInfo.matWorld = m_tInfo.matScale *m_tInfo.matTrans*m_pPlayer->GetWorldMat();

	m_Collider = static_cast<CBoxCollider*>(AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y)));
	
	return S_OK;
}

int CSword::Update_GameObject()
{
	if (m_bUse) 
	{
		Using();

		m_tInfo.matWorld = m_tInfo.matScale *m_tInfo.matTrans*m_tInfo.matRevol* m_pPlayer->GetWorldMat();

		m_Collider->Update_Component();

		//몬스터와 충돌체크 
		if (m_Collider != nullptr)
		{
//			map<int,CGameObject*> mapObj = GAMEOBJECTMGR->GetObjList(MONSTER);
			vector<CGameObject*> vecObj = GAMEOBJECTMGR->GetObjList(MONSTER);

			for (size_t i = 0; i < vecObj.size(); ++i)
			{
				CBoxCollider* another = static_cast<CBoxCollider*>(vecObj[i]->GetComponent(COMPONENTID::COLLISION));

				if (another != nullptr && m_Collider->CheckCollision(another))
				{
					//충돌
					//몬스터 사망 
					vecObj[i]->SetDestory();
				}
			}

			vecObj = GAMEOBJECTMGR->GetObjList(INTERACTION);

			for (size_t i = 0; i < vecObj.size(); ++i)
			{
				CBoxCollider* another = static_cast<CBoxCollider*>(vecObj[i]->GetComponent(COMPONENTID::COLLISION));

				if (another != nullptr && m_Collider->CheckCollision(another))
				{
					//충돌
					//오브젝트 파괴
					static_cast<CInteractionObj*>(vecObj[i])->Damaged();
				}
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
	m_Collider->Render_Component();

	const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"Sword");
	if (nullptr == pTexInfo)
		return;

	GRAPHICDEVICE->GetSprite()->SetTransform(&m_tInfo.matWorld);
	GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CSword::Release_GameObject()
{
	for_each(m_vecComponet.begin(), m_vecComponet.end(), Safe_Delete<CBaseComponent*>);
	m_vecComponet.clear();
}

void CSword::StartUsing(DIR _dir)
{
	if (!m_bUse)
	{
		m_bUse = true;
		m_bVisible = true;
		SetAngle(_dir);
	}
}

void CSword::Using()
{
	m_fAngle -= 500.f * TIMEMGR->Get_DeltaTime();
	D3DXMatrixRotationZ(&m_tInfo.matRevol, D3DXToRadian(m_fAngle));

	if (m_fAngle <= m_fStartAngle - 90)
	{
		m_fAngle = 0;
		m_bUse = false;
		m_bVisible = false;
	}
}

void CSword::SetAngle(DIR _dir)
{
	switch (_dir)
	{
	case FRONT:
		m_fStartAngle = 0;
		break;
	case BACK:
		m_fStartAngle = -180;
		break;
	case LEFT:
		m_fStartAngle = 90;
		break;
	case RIGHT :
		m_fStartAngle = -90;
		break;
	}

	m_fAngle = m_fStartAngle;
}
