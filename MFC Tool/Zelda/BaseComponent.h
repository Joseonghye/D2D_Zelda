#pragma once
#ifndef __BASECOMPONENT_H__
#define __BASECOMPONENT_H__
#include "GameObject.h"

class CBaseComponent
{
public:		
	CBaseComponent() = delete;
	CBaseComponent(CGameObject* _object, COMPONENTID _id) noexcept 
		: m_pObject(_object), m_identification(_id) {}		
	virtual ~CBaseComponent(){}

public:
	virtual int Update_Component() = 0;
	virtual void LateUpdate_Component() = 0;
	virtual void Render_Component() = 0;
	virtual void Release_Component() = 0;

	COMPONENTID	GetType() const noexcept { return m_identification; }
	CGameObject* GetParent() { return m_pObject; }
protected:	
	CGameObject* m_pObject;
private:
	COMPONENTID m_identification;
};

#endif // !__BASECOMPONENT_H__