#include "stdafx.h"
#include "BladeTrap.h"
#include "BoxCollider.h"

CBladeTrap::CBladeTrap() {}
CBladeTrap::~CBladeTrap() {	Release_GameObject(); }

HRESULT CBladeTrap::Initialized_GameObject()
{
	m_bBack = false;
	m_bAttack = false;
	m_iAtt = 1;

	m_fSpeed = 150.0f;
	m_fBackSpeed = 20.f;

	m_tInfo.vSize = D3DXVECTOR3(30.f, 30.f, 0);
	D3DXMatrixScaling(&m_tInfo.matScale, 1.f, 1.f, 1.f);

	m_pTarget = GAMEOBJECTMGR->GetPlayer();

	m_Collider = static_cast<CBoxCollider*>(AddComponent(new CBoxCollider(this, m_tInfo.vSize.x, m_tInfo.vSize.y)));

	return S_OK;
}

int CBladeTrap::Update_GameObject()
{
	Attack();
	if (m_Collider->GetbColl()) 
	{
		m_Collider->SetbColl(false);
		m_bBack = true;
	}
	return NO_EVENT;
}

void CBladeTrap::Render_GameObject()
{
	const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"BLADE_TRAP");
	if (nullptr == pTexInfo)
		return;

	GRAPHICDEVICE->GetSprite()->SetTransform(&m_tInfo.matWorld);
	GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

CBladeTrap * CBladeTrap::Create(MONSTERID eID)
{
	CBladeTrap* pInstance = new CBladeTrap;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	pInstance->SetMonsterID(eID);

	return pInstance;
}

void CBladeTrap::Damaged(int Att) { return; }

void CBladeTrap::Attack()
{
	if (!m_bAttack) 
	{
		m_vecOrign = m_tInfo.vPos;
		// �� �� �� �� �� �÷��̾ �ִٸ� 
		D3DXVECTOR3 vDir = m_pTarget->GetPos() - m_tInfo.vPos;

		if (vDir.x < vDir.y)
		{
			//�� ��
			if (fabs(vDir.x) <= 25)
			{
				//��
				if (vDir.y <= 0)
				{
					if (vDir.y <= -100) {
						m_tInfo.vDir.y = -1;
						m_bAttack = true;
					}
				}
				//��
				else if (vDir.y <= 100)
				{
					m_tInfo.vDir.y = 1;
					m_bAttack = true;
				}
			}
		}
		else
		{
			//�¿�
			if (fabs(vDir.y) <= 25)
			{
				//��
				if (vDir.x <= 0)
				{
					if (vDir.x <= -100) {
						m_tInfo.vDir.x = -1;
						m_bAttack = true;
					}
				}
				//��
				else if (vDir.x <= 100)
				{
					m_tInfo.vDir.x = 1;
					m_bAttack = true;
				}
			}
		}
	}
	else
	{
		if (!m_bBack) 
		{
			m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * TIMEMGR->Get_DeltaTime();
	}
		else
		{
			m_tInfo.vPos += (-m_tInfo.vDir) * m_fBackSpeed * TIMEMGR->Get_DeltaTime();
			
			//���� ���� 
			if (D3DXVec3Length(&(m_tInfo.vPos-m_vecOrign))<=1)
			{
				m_tInfo.vDir = D3DXVECTOR3{ 0, 0, 0 };
				m_bAttack = false;
				m_bBack = false;
			}
		}
	}

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x + SCROLLMGR->GetScrollVec().x, m_tInfo.vPos.y + SCROLLMGR->GetScrollVec().y, m_tInfo.vPos.z);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;

}