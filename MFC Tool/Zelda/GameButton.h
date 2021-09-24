#pragma once
#ifndef __GAMEBUTTON_H__
#define __GAMEBUTTON_H__

#include "GameEvent.h"
class CBoxCollider;
class CGameButton : public CGameEvent
{
public:
	CGameButton();
	~CGameButton();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

	virtual void Using() override;
	
public:
	static CGameButton* Create(char* str,int id);
	void SetStrValue(char* str) { m_strValue = str; }

private:
	CGameObject* m_pObj;
	string m_strValue;
	CBoxCollider* m_Collider;
};

#endif //!__GAMEBUTTON_H__