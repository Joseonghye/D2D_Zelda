#pragma once
class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual HRESULT Initialized_Scene() PURE;
	virtual void Update_Scene() PURE;
	virtual void LateUpdate_Scene() PURE;
	virtual void Render_Scene() PURE;
	virtual void Release_Scene() PURE;
};

