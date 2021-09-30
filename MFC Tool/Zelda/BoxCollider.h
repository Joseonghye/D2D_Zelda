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
	void WallCollision();
public:
	bool CheckCollision(CBoxCollider* pDst);
	bool PointCollision(CBoxCollider* pDst);

	RECT GetBound() { return m_rcBound; }

	void SetbColl(bool b) { m_bColl = b; }
	bool GetbColl() { return m_bColl; }
private:
	void Update_Rect();

private:
	RECT m_rcBound;
	RECT m_rcCollision;

	float m_iWidth;
	float m_iHeight;

	bool m_bColl;
};

