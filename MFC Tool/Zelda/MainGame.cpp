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

	if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Player/Sword.png", L"Sword")))
		return E_FAIL;

	//Insert Tile Texture
	if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Tile/tile%d.png", L"Terrain", L"Tile", 28)))
		return E_FAIL;
	//Insert Player Texture
	{
		//Walk
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
		//Attack
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Attak/Link_Attack0%d.png", L"Player", L"ATTACK_FRONT", 3)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Attak/Link_Attack_Back0%d.png", L"Player", L"ATTACK_BACK", 3)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Attak/Link_Attack_Left0%d.png", L"Player", L"ATTACK_LEFT", 3)))
			return E_FAIL;

		//Push
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Push/Link_Push0%d.png", L"Player", L"PUSH_FRONT", 2)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Push/Link_Push_Back0%d.png", L"Player", L"PUSH_BACK", 2)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Push/Link_Push_Left0%d.png", L"Player", L"PUSH_LEFT", 2)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Push/Link_Push_Right0%d.png", L"Player", L"PUSH_RIGHT", 2)))
			return E_FAIL;

	}
	//Insert Monster Texture
	{
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Monster/HardHat/HardHat0%d.png", L"HardHat", L"IDLE_FRONT", 2)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/weed.png", L"Weed")))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/Black.png", L"BALCKSTONE")))
			return E_FAIL;
	}

	//Set Scene
	if (FAILED(SCENEMGR->Change_SceneMgr(SCENE::GAME)))
		return E_FAIL;
	
	if (FAILED(TIMEMGR->Initialized_TimeMgr()))
		return E_FAIL;

	return S_OK;
}

void CMainGame::Update()
{
	KEYMGR->Update_KeyMgr();
	TIMEMGR->Update_TimeMgr();

	SCENEMGR->Update_SceneMgr();
	SCENEMGR->LateUpdateSceneMgr();
}

void CMainGame::Render(CFrameMgr& rFrameMgr)
{
	GRAPHICDEVICE->BeginDraw();
	GRAPHICDEVICE->GetLine()->Begin();

	SCENEMGR->Render_SceneMgr();
//	rFrameMgr.Render_FrameMgr();
	GRAPHICDEVICE->GetLine()->End();
	GRAPHICDEVICE->EndDraw();
}

void CMainGame::Release()
{
	GAMEOBJECTMGR->DestoryInstacne();
	SCENEMGR->DestoryInstacne();
	TEXTUREMGR->DestoryInstacne();
	GRAPHICDEVICE->DestoryInstacne();
	KEYMGR->DestoryInstacne();
	TIMEMGR->DestoryInstacne();
	SCROLLMGR->DestoryInstacne();
}

CMainGame * CMainGame::Create()
{
	CMainGame* pInstance = new CMainGame;

	if (FAILED(pInstance->Initialized()))
		Safe_Delete(pInstance);

	return pInstance;
}
