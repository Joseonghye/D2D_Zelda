#pragma once
#ifndef __BASECOMPONENT_H__
#define __BASECOMPONENT_H__
#include "GameObject.h"

class CBaseComponent
{
public:		
	CBaseComponent() = delete;
	CBaseComponent(CGameObject* _object, int _id, BOOL _isUniq = FALSE, BOOL _bDependency = FALSE, COMPONENT_ID::ID _dependencyID = 0)
	noexcept : m_pObject(_object), m_identification(_id), m_isUniq(_isUniq), m_bHasDependency(FALSE), m_dependencyID(_dependencyID) {
	__noop;
}
public:		virtual ~CBaseComponent() noexcept { __noop; }

public:
	virtual int Update_Compenet() noexcept = 0;
	virtual void LateUpdate_Comppente() noexcept = 0;
	virtual void Release_Component() noexcept = 0;

	int	GetType() const noexcept { return m_identification; }
protected:	
	CGameObject*				m_pObject;
private:
	int m_identification;
};

#endif // !__BASECOMPONENT_H__