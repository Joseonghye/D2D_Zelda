#pragma once
#ifndef __INTERACTION_H__
#define __INTERACTION_H__

#include "GameObject.h"
class CInteractionObj :	public CGameObject
{
public:
	CInteractionObj();
	virtual ~CInteractionObj();

public:
	virtual void LateUpdate_GameObject() override {}
	virtual void Release_GameObject() override;

	virtual void Damaged() PURE;
	virtual bool Pushed(DIR _dir) PURE;
};

#endif // !__INTERACTION_H__