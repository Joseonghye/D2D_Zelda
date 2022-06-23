#pragma once
#ifndef __KEYDOOR_H__
#define __KEYDOOR_H__

#include "InteractionObj.h"
class CAnimator;
class CBoxCollider;
class CKeyDoor : public CInteractionObj
{
private:
	CKeyDoor();
public:
	~CKeyDoor();

	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Render_GameObject() override;

	void SetDir(wstring _wstr);
	//void MoveDoor(const wstring& wstrState);
public:
	static CKeyDoor* Create();

private:
	virtual void Damaged() override {}
	virtual bool Pushed(DIR _dir) override { return false; }

private:
	CAnimator* m_Animator;
	CBoxCollider* m_Collider;
	wstring m_wstrDir;
};

#endif // !__KEYDOOR_H__