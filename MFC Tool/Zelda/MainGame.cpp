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
	if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Tile/tile%d.png", L"Terrain", L"Tile", 45)))
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
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Attak/Link_Attack_Right0%d.png", L"Player", L"ATTACK_RIGHT", 3)))
			return E_FAIL;

		//Shield
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Shield/Shield0%d.png", L"Player", L"WALK_SHIELD_FRONT", 2)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Shield/Shield_Back0%d.png", L"Player", L"WALK_SHIELD_BACK", 2)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Shield/Shield_Left0%d.png", L"Player", L"WALK_SHIELD_LEFT", 2)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Shield/Shield_Right0%d.png", L"Player", L"WALK_SHIELD_RIGHT", 2)))
			return E_FAIL;

		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Shield/Shield00.png", L"Player", L"IDLE_SHIELD_FRONT", 1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Shield/Shield_Back00.png", L"Player", L"IDLE_SHIELD_BACK", 1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Shield/Shield_Left00.png", L"Player", L"IDLE_SHIELD_LEFT", 1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Shield/Shield_Right00.png", L"Player", L"IDLE_SHIELD_RIGHT", 1)))
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

		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Fall/Fall0%d.png", L"Player", L"FALL_FRONT", 3)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Fall/Fall0%d.png", L"Player", L"FALL_LEFT", 3)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Fall/Fall0%d.png", L"Player", L"FALL_RIGHT", 3)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Fall/Fall0%d.png", L"Player", L"FALL_BACK", 3)))
			return E_FAIL;

		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Damaged/Damaged0%d.png", L"Player", L"DAMAGED_FRONT",4)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Damaged/Damaged_Back0%d.png", L"Player", L"DAMAGED_BACK", 4)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Damaged/Damaged_Left0%d.png", L"Player", L"DAMAGED_LEFT", 4)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Player/Damaged/Damaged_Right0%d.png", L"Player", L"DAMAGED_RIGHT", 4)))
			return E_FAIL;
		
	}
	//Insert Interaction
	{
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/weed.png", L"Weed")))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/Black.png", L"BALCKSTONE")))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/fire/fire%d.png", L"Fire",L"IDLE_FRONT",4)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/Key.png", L"KEY")))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Event/Button.png", L"Button")))
			return E_FAIL;

		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/Door/Door_Close00.png", L"DOOR",L"IDLE_OPEN_FRONT",1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/Door/Door0%d.png", L"DOOR", L"OPEN_FRONT", 3)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/Door/Door_Close_Left00.png", L"DOOR", L"IDLE_OPEN_LEFT", 1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/Door/Door_Left0%d.png", L"DOOR", L"OPEN_LEFT", 3)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/Door/Door_Close_Right00.png", L"DOOR", L"IDLE_OPEN_RIGHT", 1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/Door/Door_Right0%d.png", L"DOOR", L"OPEN_RIGHT", 3)))
			return E_FAIL;


		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/Door/Door00.png", L"DOOR", L"IDLE_CLOSE_FRONT", 1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/Door/Door_Close0%d.png", L"DOOR", L"CLOSE_FRONT", 3)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/Door/Door_Left00.png", L"DOOR", L"IDLE_CLOSE_LEFT", 1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/Door/Door_Close_Left0%d.png", L"DOOR", L"CLOSE_LEFT", 3)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/Door/Door_Right00.png", L"DOOR", L"IDLE_CLOSE_RIGHT", 1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Object/Door/Door_Close_Right0%d.png", L"DOOR", L"CLOSE_RIGHT", 3)))
			return E_FAIL;

	}
	//Monster
	{
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Monster/HardHat/HardHat0%d.png", L"HardHat", L"IDLE_FRONT", 2)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Monster/Bat/Bat00.png", L"Bat", L"IDLE_FRONT", 1)))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::MULTI, L"../Texture/Monster/Bat/Bat0%d.png", L"Bat", L"ATTACK_FRONT", 2)))
			return E_FAIL;
	}
	//UI
	{
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Ui/Heart_Full.png", L"Heart_Full")))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Ui/Heart_Half.png", L"Heart_Half")))
			return E_FAIL;
		if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Ui/Heart_Frame.png", L"Heart_Frame")))
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
