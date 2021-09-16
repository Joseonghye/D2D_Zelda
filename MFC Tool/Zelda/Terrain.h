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
//	vector<TILE*> m_vecTile; //���� ���� Ÿ�� ���� 
	vector<Room> m_vecRoom; //���� ���� ����?
//	map<int, D3DXVECTOR3> m_mapCollider;
};

#endif // !__TERRAIN_H__