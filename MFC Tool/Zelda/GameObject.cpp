#include "stdafx.h"
#include "GameObject.h"
#include "BaseComponent.h"

CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}


void CGameObject::Update_Components()
{
	for (auto& pComponent : m_vecComponet)
	{
		pComponent->Update_Component();
	}
}

void CGameObject::LateUpdate_Components()
{
	for (auto& pComponent : m_vecComponet)
	{
		pComponent->LateUpdate_Component();
	}
}

void CGameObject::Render_Components()
{
	for (auto& pComponent : m_vecComponet)
	{
		pComponent->Render_Component();
	}
}

void CGameObject::Release_Components()
{
	for (auto& pComponent : m_vecComponet)
	{
		pComponent->Release_Component();
	}
}

CBaseComponent* CGameObject::AddComponent(CBaseComponent* _component)
{
	for (auto& pComponent : m_vecComponet) 
	{
		if (pComponent->GetType() == _component->GetType())
			return nullptr;
	}

	m_vecComponet.emplace_back(_component);
	return _component;
}

CBaseComponent * CGameObject::GetComponent(COMPONENTID _id)
{
	for (auto& pComponent : m_vecComponet)
	{
		if (pComponent->GetType() == _id)
			return pComponent;
	}
	return nullptr;
}

