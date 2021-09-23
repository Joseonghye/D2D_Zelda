#pragma once
#ifndef __HARDHAT_H__
#define __HARDHAT_H__

#include "GameObject.h"
#include "Subject.h"
class CHardHat : public CGameObject, public CSubject
{
private:
	CHardHat();
public:
	virtual ~CHardHat();

	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CHardHat* Create();

public:
	virtual void RegisterObserver(CObserver * observer) override;
	virtual void RemoveObserver() override;

private:
	virtual void NotifyObserver() override;

private:
	CGameObject* m_pTarget;
	float m_fSpeed;

	CObserver* m_pObserver;


};

#endif // !__HARDHAT_H__