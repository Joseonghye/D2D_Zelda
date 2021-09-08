#pragma once
#include "Scene.h"
class CGameScene :
	public CScene
{
private:
	CGameScene();
public:
	virtual ~CGameScene() override;

	virtual HRESULT Initialized_Scene() override;
	virtual void Update_Scene() override;
	virtual void LateUpdate_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;

public:
	static CScene* Create();
};

