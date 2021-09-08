#pragma once
#ifndef __COLLISIONMGR_H__
#define __COLLISIONMGR_H__
#include "SingleTon.h"

class CGameObject;
class CCollisionMgr: public CSingleTon<CCollisionMgr>
{
	friend CSingleTon;
private:
	CCollisionMgr();
	~CCollisionMgr();

public:
	bool CollisionRect(CGameObject* pSrc, CGameObject* pDst);
};

#endif // !__COLLISIONMGR_H__