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
	if (FAILED(TEXTUREMGR->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Player/Link.png", L"Player", L"Attack", 9)))
		return E_FAIL;

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
