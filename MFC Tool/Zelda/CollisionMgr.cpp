#include "stdafx.h"
#include "CollisionMgr.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "InteractionObj.h"
#include "Player.h"
#include "GameButton.h"
#include "GameEvent.h"
#include "Close.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

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
					static_cast<CPlayer*>(pPlayer)->SetState(STATE::DAMAGED);
					// hp 감소 

					break;
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
					static_cast<CPlayer*>(pPlayer)->SetState(STATE::FALL);
					//데미지
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
