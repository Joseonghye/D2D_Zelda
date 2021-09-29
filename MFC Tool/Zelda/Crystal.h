#pragma once
#ifndef __CRYSTAL_H__
#define __CRYSTAL_H__

#include "InteractionObj.h"
class CCrystal :
	public CInteractionObj
{
private:
	CCrystal();
public:
	virtual ~CCrystal();

	// CInteractionObj을(를) 통해 상속됨
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Render_GameObject() override;

	virtual void Damaged() override;
	virtual bool Pushed(DIR _dir) override {}
public:
	static CCrystal* Create();

};

#endif // !__CRYSTAL_H__