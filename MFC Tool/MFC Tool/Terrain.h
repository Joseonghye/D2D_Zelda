#pragma once
#ifndef __TERRAIN_H__
#define __TERRAIN_H__

typedef struct tagData
{
	TCHAR	szName[16];
	INFO	m_tInfo;
}OBJDATA;

class Terrain final
{
private:
	Terrain();
public:
	~Terrain();

public:
	void AddTileData(TILE* pTile);
	HRESULT ReadyTerrain();
	void RenderTerrain();
	void ReleaseTerrain();

	static Terrain* Create();

public:
	void AddObjData(OBJDATA* data);
	void RenderObject();
	void ReleaseObject();

public:
	vector<TILE*>& GetTile() { return m_vecTile; }
	void ChangeTile(const D3DXVECTOR3 & vMouse, const int & iDrawID, const int & iOption = 0);

	list<OBJDATA*>& GetObj() { return m_ObjList; }
	void AddObj(const D3DXVECTOR3 & vMouse, const CString & objName);

private:
	int GetTileIndex(const D3DXVECTOR3& vMouse);

private:
	vector<TILE*> m_vecTile;
	list<OBJDATA*> m_ObjList;
};

#endif // !__TERRAIN_H__