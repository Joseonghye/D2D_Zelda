#pragma once
#ifndef __TERRAIN_H__
#define __TERRAIN_H__
#include "GameObject.h"

#define Room vector<TILE*>

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
	int m_RoomIndex;
//	vector<TILE*> m_vecTile; //현재 방의 타일 정보 
	vector<Room> m_vecRoom; //던전 방의 정보?
//	map<int, D3DXVECTOR3> m_mapCollider;
};

#endif // !__TERRAIN_H__