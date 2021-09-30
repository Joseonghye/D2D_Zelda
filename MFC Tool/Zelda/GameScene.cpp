#include "stdafx.h"
#include "GameScene.h"
#include "Terrain.h"
#include "Player.h"
#include "ThreeOfOne.h"
#include "BottomUI.h"

CGameScene::CGameScene()
{
}


CGameScene::~CGameScene()
{
}

HRESULT CGameScene::Initialized_Scene()
{
	CGameObject* pGameObject = CBottomUI::Create();
	GAMEOBJECTMGR->Add_GameObject(UI, pGameObject);

	pGameObject = Terrain::Create();
	GAMEOBJECTMGR->Add_GameObject(BACKGROUND, pGameObject);
	
	D3DXVECTOR3 vStart = pGameObject->GetPos();

	pGameObject = CPlayer::Create();
	pGameObject->SetPos(vStart);
	pGameObject->SetTransMat();
	pGameObject->SetWorldMat();
	GAMEOBJECTMGR->Add_GameObject(PLAYER,pGameObject);

	pGameObject = CThreeOfOne::Create(THREE);
	GAMEOBJECTMGR->Add_GameObject(MONSTER, pGameObject);

	pGameObject = nullptr;

	LoadGameObject(L"../Data/Obj/ObjData.dat");
	LoadEvent(L"../Data/Event.dat");

	return S_OK;
}

void CGameScene::Update_Scene()
{
	GAMEOBJECTMGR->Update_GameObjectMgr();
}

void CGameScene::LateUpdate_Scene()
{
	GAMEOBJECTMGR->LateUpdate_GameObjectMgr();
}

void CGameScene::Render_Scene()
{
	GAMEOBJECTMGR->Render_GameObjectMgr();
}

void CGameScene::Release_Scene()
{
	GAMEOBJECTMGR->Release_GameObjectMgr();
}

CScene * CGameScene::Create()
{
	CScene* pInstance = new CGameScene;
	if (FAILED(pInstance->Initialized_Scene()))
		Safe_Delete(pInstance);

	return pInstance;
}
