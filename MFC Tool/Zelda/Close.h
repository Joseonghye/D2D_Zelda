#pragma once
#ifndef __CLOSE_H__
#define __CLOSE_H__

#include "GameObject.h"
class CClose : public CGameObject
{
public:
	CClose();
	~CClose();

	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CClose* Create();
public:
	void CloseDoor();
};

#endif // !__CLOSE_H__