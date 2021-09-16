#pragma once
#ifndef __COLLISIONMGR_H__
#define __COLLISIONMGR_H__

class CGameObject;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	bool PlayerCollision(CGameObject* pPlayer, map<int, CGameObject*> pSrc, OBJID _id);// vector<CGameObject*> pSrc, OBJID _id);
};

#endif // !__COLLISIONMGR_H__