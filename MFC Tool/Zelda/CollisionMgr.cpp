#include "stdafx.h"
#include "CollisionMgr.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "InteractionObj.h"
#include "Player.h"
#include "GameButton.h"

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
			
			if (another != nullptr && playerCollider->CheckCollision(another)) 
			{
				switch (_id)
				{
				case MONSTER:
					static_cast<CPlayer*>(pPlayer)->SetState(STATE::DAMAGED);
					// hp °¨¼Ò 
					break;
				case ENTER: // ¸Ê ÀÌµ¿
				{
					if (pPlayer->GetDir() != another->GetParent()->GetDir()) break;
					int index = 0;
					switch (pPlayer->GetDir())
					{
					case FRONT:
						index = GAMEOBJECTMGR->SetNextIndex((int)TOTAL_TILEX);
						SCROLLMGR->SetScroll(index);
						break;
					case BACK:
						index = GAMEOBJECTMGR->SetNextIndex(-((int) TOTAL_TILEX));
						SCROLLMGR->SetScroll(index);
						break;
					case LEFT:
						index = GAMEOBJECTMGR->SetNextIndex(-1);
						SCROLLMGR->SetScroll(index);
						break;
					case RIGHT:
						index = GAMEOBJECTMGR->SetNextIndex(1);
						SCROLLMGR->SetScroll(index);
						break;
					}
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
				case EVENT:
					static_cast<CGameButton*>(another->GetParent())->PushButton();
				}
				/*
				if (_id == WALL || _id == INTERACTION)
				{
					static_cast<CPlayer*>(pPlayer)->SetState(STATE::PUSH);

					if (another->GetParent()->GetMove())
					{
						if (!static_cast<CInteractionObj*>(another->GetParent())->Pushed(pPlayer->GetDir()))
							playerCollider->WallCollision();
					}
					else
						playerCollider->WallCollision();
				}
				*/
			}
		}
		/*
		for (int i = 0; i < (int)pSrc.size(); ++i)
		{
			CBoxCollider* another = static_cast<CBoxCollider*>(pSrc[i]->GetComponent(COMPONENTID::COLLISION));

			if (another != nullptr && playerCollider->CheckCollision(another))
			{
				if (_id == WALL || _id == INTERACTION) 
				{
					static_cast<CPlayer*>(pPlayer)->SetState(STATE::PUSH);
					if (another->GetParent()->GetMove())
					{
						if (!static_cast<CInteractionObj*>(another->GetParent())->Pushed(pPlayer->GetDir()))
							playerCollider->WallCollision();
					}
					else
						playerCollider->WallCollision();
				}
			}
		}*/
	}
	return false;
}
