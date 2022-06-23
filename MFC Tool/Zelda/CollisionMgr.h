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
	void PlayerCollision(CGameObject* pPlayer, vector<CGameObject*> pSrc, OBJID _id, int iRoomIndex, int iNextRoom);
	bool MonsterCollision(vector<CGameObject*> pDst, vector<CGameObject*> pSrc, OBJID _id, int iRoomIndex, int iNextRoom);
	void InteractionCollision(vector<CGameObject*> pDst, vector<CGameObject*> pSrc, OBJID _id, int iRoomIndex, int iNextRoom);
};

#endif // !__COLLISIONMGR_H__