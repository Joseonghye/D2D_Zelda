#pragma once
#include "GameObject.h"
class CWall :
	public CGameObject
{
private:
	CWall();

public:
	~CWall();

	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CWall* Create();
};

