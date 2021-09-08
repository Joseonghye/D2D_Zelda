#pragma once
#ifndef __TERRAIN_H__
#define __TERRAIN_H__
#include "GameObject.h"

class Terrain final :public CGameObject
{
private:
	Terrain();
public:
	~Terrain();

public:
	static Terrain* Create();

	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

private:
	HRESULT LoadTileFile(const wstring & wstrFilePath);
	HRESULT LoadColliderFile(const wstring & wstrFilePath);

private:
	vector<TILE*> m_vecTile;
	map<int, D3DXVECTOR3> m_mapCollider;
};

#endif // !__TERRAIN_H__