#include "stdafx.h"
#include "Sword.h"
#include "BoxCollider.h"

CSword::CSword() :m_fAngle(0.f)
{
}


CSword::~CSword()
{
}

HRESULT CSword::Initialized_GameObject()
{
	//m_tInfo.vPos = m_pPlayer->GetPos() +D3DXVECTOR3(-15.f, 0, 0);
	m_tInfo.vPos = D3DXVECTOR3(-15.f, 0, 0);
	m_tInfo.vSize = D3DXVECTOR3(30, 12, 0);

	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
//	m_tInfo.matWorld = m_tInfo.matScale *m_tInfo.matRotateZ* m_tInfo.matTrans* m_tInfo.matRevol*m_pPlayer->GetWorldMat();

	m_tInfo.matWorld = m_tInfo.matScale *m_tInfo.matTrans*m_pPlayer->GetWorldMat();

	m_Collider = static_cast<CBoxCollider*>(AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y)));
	return S_OK;
}

int CSword::Update_GameObject()
{
	if (m_bAttack)
		Attack();

	
	//몬스터와 충돌체크 
	//if (m_Collider != nullptr)
	//{
	//	vector<CGameObject*> vecObj = GAMEOBJECTMGR->GetObjList(MONSTER);

	//	for (size_t i = 0; i < vecObj.size(); ++i)
	//	{
	//		CBoxCollider* another = static_cast<CBoxCollider*>(vecObj[i]->GetComponent(COMPONENTID::COLLISION));

	//		if (another != nullptr && m_Collider->CheckCollision(another))
	//		{
	//			//충돌
	//			//몬스터 사망 
	//			vecObj[i]->SetDestory();

	//		}
	//	}
	//}

	return 0;
}

void CSword::LateUpdate_GameObject()
{
}

void CSword::Render_GameObject()
{
//	m_tInfo.vPos = m_pPlayer->GetPos() + D3DXVECTOR3(-15, 0, 0);
	//D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	//m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans* m_tInfo.matRevol;
//	m_tInfo.matWorld = m_tInfo.matScale *m_tInfo.matRotateZ* m_tInfo.matTrans* m_tInfo.matRevol*m_pPlayer->GetWorldMat();
	m_tInfo.matWorld = m_tInfo.matScale *m_tInfo.matTrans*m_tInfo.matRevol* m_pPlayer->GetWorldMat();
	const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"Sword");
	if (nullptr == pTexInfo)
		return;

	GRAPHICDEVICE->GetSprite()->SetTransform(&m_tInfo.matWorld);
	GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CSword::Release_GameObject()
{
}

void CSword::Attack()
{
	if (!m_bAttack) m_bAttack = true;

	m_fAngle -= 5;
	D3DXMatrixRotationZ(&m_tInfo.matRevol, D3DXToRadian(m_fAngle));

	if (m_fAngle <= -90) 
	{
		m_fAngle = 0;
		m_bAttack = false;
	}
//	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans* m_tInfo.matRevol;
}
