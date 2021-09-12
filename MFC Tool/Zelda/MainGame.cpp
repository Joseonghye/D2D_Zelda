#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Initialized()
{
	if (FAILED(GRAPHICDEVICE->Initialized()))
		return E_FAIL;

	//Insert Texture
	if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Tile/tile0%d.png", L"Terrain", L"Tile", 9)))
		return E_FAIL;
	//Insert Player Texture
	{
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Walk/Link_Walk0%d.png", L"Player", L"WALK_FRONT", 2)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Walk/Link_Walk_Back0%d.png", L"Player", L"WALK_BACK", 2)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Walk/Link_Walk_Left0%d.png", L"Player", L"WALK_LEFT", 2)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Walk/Link_Walk_Right0%d.png", L"Player", L"WALK_RIGHT", 2)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Walk/Link_Walk00.png", L"Player", L"IDLE_FRONT", 1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Walk/Link_Walk_Back00.png", L"Player", L"IDLE_BACK", 1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Walk/Link_Walk_Left00.png", L"Player", L"IDLE_LEFT", 1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Walk/Link_Walk_Right00.png", L"Player", L"IDLE_RIGHT", 1)))
			return E_FAIL;
	}

	{
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Monster/HardHat/HardHat0%d.png", L"HardHat", L"IDLE_FRONT", 2)))
			return E_FAIL;
	}
	//Set Scene
	if (FAILED(SCENEMGR->Change_SceneMgr(SCENE::GAME)))
		return E_FAIL;

	return S_OK;
}

void CMainGame::Update()
{
	KEYMGR->Update_KeyMgr();

	SCENEMGR->Update_SceneMgr();
	SCENEMGR->LateUpdateSceneMgr();
}

void CMainGame::Render()
{
	GRAPHICDEVICE->BeginDraw();

	SCENEMGR->Render_SceneMgr();

	GRAPHICDEVICE->EndDraw();
}

void CMainGame::Release()
{
	GAMEOBJECTMGR->DestoryInstacne();
	SCENEMGR->DestoryInstacne();
	TEXTUREMGR->DestoryInstacne();
	GRAPHICDEVICE->DestoryInstacne();
	KEYMGR->DestoryInstacne();
}

CMainGame * CMainGame::Create()
{
	CMainGame* pInstance = new CMainGame;

	if (FAILED(pInstance->Initialized()))
		Safe_Delete(pInstance);

	return pInstance;
}
