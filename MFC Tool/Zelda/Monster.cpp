#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release_GameObject();
}


void CMonster::Release_GameObject()
{
	RemoveObserver();
	for_each(m_vecComponet.begin(), m_vecComponet.end(), Safe_Delete<CBaseComponent*>);
	m_vecComponet.clear();
	m_vecComponet.swap(vector<CBaseComponent*>());
}

void CMonster::RegisterObserver(CObserver * observer)
{
	m_pObserver = observer;
}

void CMonster::RemoveObserver()
{
	m_pObserver = nullptr;
}

void CMonster::NotifyObserver()
{
	if (m_pObserver)
		m_pObserver->OnNotify();
}
