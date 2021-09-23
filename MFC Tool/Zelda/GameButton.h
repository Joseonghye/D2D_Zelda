#pragma once
#ifndef __GAMEBUTTON_H__
#define __GAMEBUTTON_H__

#include "GameObject.h"
class CBoxCollider;
class CGameButton :
	public CGameObject
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

	void SetStrValue(char* str) { m_strValue= str; }
	static CGameButton* Create(char* str);

	void PushButton();

private:
	CGameObject* m_pObj;
	string m_strValue;
	CBoxCollider* m_Collider;
};

#endif //!__GAMEBUTTON_H__