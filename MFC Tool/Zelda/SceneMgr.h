#pragma once
#ifndef __SCENEMGR_H__
#define __SCENEMGR_H__
#include "SingleTon.h"
#include "Scene.h"

class CSceneMgr: public CSingleTon<CSceneMgr>
{
	friend CSingleTon;
private:
	CSceneMgr();
	~CSceneMgr();

public:
	HRESULT Change_SceneMgr(SCENE eNextScene);
	void Update_SceneMgr();
	void LateUpdateSceneMgr();
	void Render_SceneMgr();
	void Release_SceneMgr();

private:
	SCENE m_eCurrentScene;
	SCENE m_eNextScene;
	CScene* m_pScene;

};

#endif // !__SCENEMGR_H__