#pragma once
#include "GameObject.h"
class CInteractionObj :	public CGameObject
{
public:
	CInteractionObj();
	virtual ~CInteractionObj();

public:
	virtual void Damaged() PURE;
	virtual bool Pushed(DIR _dir) PURE;

};

