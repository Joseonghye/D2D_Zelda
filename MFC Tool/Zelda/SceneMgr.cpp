#include "stdafx.h"
#include "SceneMgr.h"
#include "GameScene.h"

CSceneMgr::CSceneMgr()
	:m_eCurrentScene(TITLE), m_eNextScene(SCENE::SCENE_END), m_pScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	Release_SceneMgr();
}

HRESULT CSceneMgr::Change_SceneMgr(SCENE eNextScene)
{
	m_eNextScene = eNextScene;
	if (m_eCurrentScene != m_eNextScene)
	{
		Safe_Delete(m_pScene);
		switch (m_eNextScene)
		{
		case SCENE::TITLE:
			break;
		case SCENE::GAME:
			m_pScene = CGameScene::Create();
			break;
		}
		if (nullptr == m_pScene)
			return E_FAIL;

		m_eCurrentScene = m_eNextScene;
	}

	return S_OK;
}

void CSceneMgr::Update_SceneMgr()
{
	m_pScene->Update_Scene();
}

void CSceneMgr::LateUpdateSceneMgr()
{
	m_pScene->LateUpdate_Scene();
}

void CSceneMgr::Render_SceneMgr()
{
	m_pScene->Render_Scene();
}

void CSceneMgr::Release_SceneMgr()
{
	Safe_Delete(m_pScene);
}
