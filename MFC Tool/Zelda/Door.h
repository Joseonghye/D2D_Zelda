#pragma once
#ifndef __DOOR_H__
#define __DOOR_H__

#include "InteractionObj.h"
class CAnimator;
class CBoxCollider;
class CDoor :
	public CInteractionObj
{
public:
	CDoor();
	~CDoor();

public:
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;
public:
	static CDoor* Create();
public:
	void SetDir(wstring _wstr);
	void MoveDoor(const wstring& wstrState);
	CAnimator* GetAnimator() { return m_Animator; }
private:
	virtual void Damaged() override {}
	virtual bool Pushed(DIR _dir) override {}

private:
	CAnimator* m_Animator;
	CBoxCollider* m_Collider;
	wstring m_wstrDir;
};

#endif // !__DOOR_H__