#pragma once
#ifndef __ENTER_H__
#define __ENTER_H__
#include "GameObject.h"

class CEnter : public CGameObject
{
public:
	CEnter();
	~CEnter();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CEnter* Create();
};

#endif // !__ENTER_H__