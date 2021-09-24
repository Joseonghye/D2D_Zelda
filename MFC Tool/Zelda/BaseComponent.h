#pragma once
#ifndef __BASECOMPONENT_H__
#define __BASECOMPONENT_H__
#include "GameObject.h"

class CBaseComponent
{
public:		
	CBaseComponent() = delete;
	CBaseComponent(CGameObject* _object, COMPONENTID _id) noexcept
		: m_pObject(_object), m_identification(_id), m_bActive(true) {}
	virtual ~CBaseComponent(){}

public:
	virtual int Update_Component() = 0;
	virtual void LateUpdate_Component() = 0;
	virtual void Render_Component() = 0;
	virtual void Release_Component() = 0;

	void SetActive(bool bActive) { m_bActive = bActive; }

	COMPONENTID	GetType() const noexcept { return m_identification; }
	CGameObject* GetParent() { return m_pObject; }
	bool GetActive() { return m_bActive; }
protected:	
	CGameObject* m_pObject;
private:
	COMPONENTID m_identification;
	bool m_bActive;
};

#endif // !__BASECOMPONENT_H__