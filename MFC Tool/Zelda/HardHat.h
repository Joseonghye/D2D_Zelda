#pragma once
#include "GameObject.h"
class CHardHat :
	public CGameObject
{
private:
	CHardHat();
public:
	virtual ~CHardHat();

	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

public:
	static CHardHat* Create();
private:
	CGameObject* m_pTarget;
	float m_fSpeed;
};

