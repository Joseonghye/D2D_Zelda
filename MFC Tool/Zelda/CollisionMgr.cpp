#include "stdafx.h"
#include "CollisionMgr.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "InteractionObj.h"
#include "Player.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::PlayerCollision(CGameObject * pPlayer, map<int, CGameObject*> pSrc, OBJID _id)//vector<CGameObject*> pSrc, OBJID _id)
{
	CBoxCollider* playerCollider = static_cast<CBoxCollider*>(pPlayer->GetComponent(COMPONENTID::COLLISION));

	if (playerCollider != nullptr)
	{
		for (auto& iter = pSrc.begin(); iter != pSrc.end();)
		{
			CBoxCollider* another = static_cast<CBoxCollider*>(iter->second->GetComponent(COMPONENTID::COLLISION));
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
