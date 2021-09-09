#pragma once
#include "BaseComponent.h"
class CBoxCollider :
	public CBaseComponent
{
public:
	CBoxCollider(CGameObject* const owner, float width, float height);
	virtual ~CBoxCollider();

	virtual int Update_Component();
	virtual void LateUpdate_Component();
	virtual void Render_Component();
	virtual void Release_Component();

public:
	bool CheckCollision(CBoxCollider* pDst);
	RECT GetBound() { return m_rcBound; }
private:
	void Update_Rect();

private:
	RECT m_rcBound;
	float m_iWidth;
	float m_iHeight;
};

