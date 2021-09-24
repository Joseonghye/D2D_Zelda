#pragma once
#ifndef __ENTER_H__
#define __ENTER_H__
#include "GameEvent.h"

class CEnter : public CGameEvent
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

	virtual void Using();
public:
	static CEnter* Create(D3DXVECTOR3 vPos,string str,int ID);
	
	void SetDir(string str);

};

#endif // !__ENTER_H__