#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "GameObject.h"
#include "Subject.h"
class CMonster : public CGameObject, public CSubject
{
public:
	CMonster();
	virtual ~CMonster();
	virtual void LateUpdate_GameObject() override {}
	virtual void Render_GameObject() override {}
	virtual void Release_GameObject() override;

public:
	virtual void RegisterObserver(CObserver * observer) override;
	virtual void RemoveObserver() override;

	virtual void Damaged(int Att) = 0;
	virtual void Fall() = 0;

	void SetMonsterID(MONSTERID eID) { m_eID = eID; }
	MONSTERID GetMonsterID() { return m_eID; }
	
	bool isPushed() { return m_bPushed; }
	void Pushed() { m_bPushed = true; }

	int GetAtt() { return m_iAtt; }

protected:
	virtual void NotifyObserver() override;

	virtual void Attack() = 0;

protected:
	CGameObject* m_pTarget;
	MONSTERID m_eID;

	int m_iHp;
	int m_iTotalHp;
	int m_iAtt;

	float m_fSpeed;

	bool m_bPushed;
	DWORD m_dwPushTime;	
};

#endif // !__MONSTER_H__