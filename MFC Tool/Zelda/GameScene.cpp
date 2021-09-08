#include "stdafx.h"
#include "GameScene.h"
#include "Terrain.h"
#include "Player.h"

CGameScene::CGameScene()
{
}


CGameScene::~CGameScene()
{
}

HRESULT CGameScene::Initialized_Scene()
{
	CGameObject* pGameObject = Terrain::Create();
	GAMEOBJECTMGR->Add_GameObject(BACKGROUND, pGameObject);

	pGameObject = CPlayer::Create();
	GAMEOBJECTMGR->Add_GameObject(PLAYER, pGameObject);

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
