#pragma once
#ifndef __CHECK_H__
#define __CHECK_H__

#include "GameObject.h"
#include "Observer.h"

class CCheck :  public CGameObject , public CObserver
{
public:
	CCheck();
	~CCheck();

public:
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CCheck* Create(char* str);

public:
	virtual void OnNotify()override;

	void SetMonsterCount();
	void SetStrValue(char* str) { m_strValue = str; }
private:
	int m_iMonsterCount;
	string m_strValue;
	CGameObject* m_pObj;
};

#endif // !__CHECK_H__