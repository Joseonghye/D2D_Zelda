#pragma once
#ifndef __CLOSE_H__
#define __CLOSE_H__

#include "GameEvent.h"
class CBoxCollider;
class CClose : public CGameEvent
{
public:
	CClose();
	~CClose();

	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

	// CGameEvent을(를) 통해 상속됨
	virtual void Using() override;

public:
	static CClose* Create(int id);

private:
	CBoxCollider* m_Collider;
	bool m_bFirst;


};

#endif // !__CLOSE_H__