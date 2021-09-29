#include "stdafx.h"
#include "ThreeOfOne.h"
#include "Kind.h"

CThreeOfOne::CThreeOfOne(){}
CThreeOfOne::~CThreeOfOne()
{
	m_vecKind.clear();
	m_vecKind.swap(vector<CKind*>());
}

HRESULT CThreeOfOne::Initialized_GameObject()
{
	m_vecKind.reserve(3);
	m_bVisible = false;
	m_bMove = false;
	return S_OK;
}

int CThreeOfOne::Update_GameObject()
{
	bool bChk = true;
	for (int i = 0; i < 3; ++i)
		if (!(m_vecKind[i]->isStop())) bChk = false;

	if (bChk)
	{
		if ((m_vecKind[0]->GetColorID() == m_vecKind[1]->GetColorID()) &&
			(m_vecKind[1]->GetColorID() == m_vecKind[2]->GetColorID()))
		{
			for (int i = 0; i < 3; ++i)
				m_vecKind[i]->SetDestory();
		}
		else
		{
			for (int i = 0; i < 3; ++i)
				m_vecKind[i]->StartMove();
		}

	}

	return 0;
}

CThreeOfOne * CThreeOfOne::Create(MONSTERID eID)
{
	CThreeOfOne* pInstance = new CThreeOfOne;
	if (FAILED(pInstance->Initialized_GameObject()))
		SAFE_DELETE(pInstance);

	pInstance->SetMonsterID(eID);
	return pInstance;
}
