#pragma once
#ifndef __TERRAIN_H__
#define __TERRAIN_H__

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
	void AddObjData(CString wstrName,INFO* pInfo);
	void RenderObject();
	void ReleaseObject();

public:
	vector<TILE*>& GetTile() { return m_vecTile; }
	void ChangeTile(const D3DXVECTOR3 & vMouse, const int & iDrawID, const int & iOption = 0);

	map<CString, INFO*>& GetObj() { return m_ObjMap; }
	void AddObj(const D3DXVECTOR3 & vMouse, const OBJINFO& tObjInfo);

private:
	int GetTileIndex(const D3DXVECTOR3& vMouse);

private:
	vector<TILE*> m_vecTile;
	map<CString,INFO*> m_ObjMap;
};

#endif // !__TERRAIN_H__