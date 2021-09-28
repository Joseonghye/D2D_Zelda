#include "stdafx.h"
#include "InteractionObj.h"


CInteractionObj::CInteractionObj()
{
}


CInteractionObj::~CInteractionObj()
{
}

void CInteractionObj::Release_GameObject()
{
	for_each(m_vecComponet.begin(), m_vecComponet.end(), Safe_Delete<CBaseComponent*>);
	m_vecComponet.clear();
	m_vecComponet.swap(vector<CBaseComponent*>());
}
