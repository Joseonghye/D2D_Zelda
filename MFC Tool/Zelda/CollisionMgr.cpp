#include "stdafx.h"
#include "CollisionMgr.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "InteractionObj.h"
#include "Player.h"
#include "GameButton.h"
#include "GameEvent.h"
#include "Close.h"
#include "Monster.h"

CCollisionMgr::CCollisionMgr() {}
CCollisionMgr::~CCollisionMgr() {}

bool CCollisionMgr::PlayerCollision(CGameObject * pPlayer, vector<CGameObject*> pSrc, OBJID _id, int iRoomIndex, int iNextRoom)
{
	CBoxCollider* playerCollider = static_cast<CBoxCollider*>(pPlayer->GetComponent(COMPONENTID::COLLISION));

	if (playerCollider != nullptr)
	{
		for (auto& iter = pSrc.begin(); iter != pSrc.end(); ++iter)
		{
			int index = (*iter)->GetRoomIndex();
			if (iNextRoom == -1) {
				if (index != iRoomIndex) continue;
			}
			else
				if (index != iNextRoom) continue;

			CBoxCollider* another = static_cast<CBoxCollider*>((*iter)->GetComponent(COMPONENTID::COLLISION));
			
			if (another == nullptr || !another->GetActive())
				continue;

			if (playerCollider->CheckCollision(another))
			{
				switch (_id)
				{
				case MONSTER: 
				{
					CMonster* monster = static_cast<CMonster*>(another->GetParent());
					if (static_cast<CPlayer*>(pPlayer)->Defense(monster->GetPos(), monster->GetVecDir()))
					{
						//적밀림	
						(monster)->Pushed();
					}
					else 
					{
						// hp 감소 
						static_cast<CPlayer*>(pPlayer)->Damaged(monster->GetAtt(), DAMAGED);
					}
					monster = nullptr;
					break;
				}  
				case POTAL:
					break;
				case INTERACTION:
				case WALL:
				{
					static_cast<CPlayer*>(pPlayer)->SetState(STATE::PUSH);

					if (another->GetParent()->GetMove())
					{
						if (!static_cast<CInteractionObj*>(another->GetParent())->Pushed(pPlayer->GetDir()))
							playerCollider->WallCollision();
					}
					else
						playerCollider->WallCollision();

					break;
				}
				case HOLE:
					//데미지
					static_cast<CPlayer*>(pPlayer)->Damaged(1, FALL);
					// 재위치
					break;
				case EVENT:
				{
					if (static_cast<CGameEvent*>(another->GetParent())->GetEventID() == (int)ENTER)
						if (another->GetParent()->GetDir() != pPlayer->GetDir()) continue;

					static_cast<CGameEvent*>(another->GetParent())->Using();
					break;
				}
				}
			}
		}
	}
	return false;
}

bool CCollisionMgr::MonsterCollision(vector<CGameObject*> pDst, vector<CGameObject*> pSrc, OBJID _id, int iRoomIndex, int iNextRoom)
{
	for (auto& dst = pDst.begin(); dst != pDst.end(); ++dst)
	{
		for (auto& src = pSrc.begin(); src != pSrc.end(); ++src)
		{
			int index = (*src)->GetRoomIndex();
			if (iNextRoom == -1) {
				if (index != iRoomIndex) continue;
			}
			else
				if (index != iNextRoom) continue;

			if (static_cast<CMonster*>(*dst)->GetMonsterID() == BAT) continue;

			CBoxCollider* MonsterColl = static_cast<CBoxCollider*>((*dst)->GetComponent(COMPONENTID::COLLISION));
			CBoxCollider* another = static_cast<CBoxCollider*>((*src)->GetComponent(COMPONENTID::COLLISION));

			if (!MonsterColl || !another) continue;

			if (MonsterColl->CheckCollision(another))
			{
				switch (_id)
				{
				case INTERACTION:
				case WALL:
					MonsterColl->WallCollision();
					break;

				case HOLE: 
				{
					if (static_cast<CMonster*>(*dst)->isPushed())
					{
						D3DXVECTOR3 vec = (*dst)->GetPos() - (*src)->GetPos();
						if(D3DXVec3Length(&vec) <=8.f)
							static_cast<CMonster*>(*dst)->Fall();
					}
					else
						MonsterColl->WallCollision();
				}
					break;
				}
			}

		}

	}
	return false;
}
