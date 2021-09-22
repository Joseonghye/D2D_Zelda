#pragma once
#ifndef __TERRAIN_H__
#define __TERRAIN_H__

typedef struct tagData
{
	TCHAR	szName[16];
	INFO	m_tInfo;
}OBJDATA;


class CMFCToolView;
class Terrain final
{
private:
	Terrain();
public:
	~Terrain();

public:
	void Set_View(CMFCToolView* pView) { m_pView = pView; }

	void AddTileData(TILE* pTile);
	HRESULT ReadyTerrain();
	void RenderTerrain();
	void MiniRenderTerrain();
	void ReleaseTerrain();

	static Terrain* Create();

public:
	void AddObjData(int index,OBJDATA* data);
	void RenderObject();
	void ReleaseObject();

public:
	void AddEventData(int index, EVENTINFO* data);
	void RenderEvent();
	void ReleaseEvent();

public:
	void AddCollData(int index,D3DXVECTOR3 vPos);
	void RenderColl();
	void ReleaseColl();

public:
	vector<TILE*>& GetTile() { return m_vecTile; }
	void ChangeTile(const D3DXVECTOR3 & vMouse, const int & iDrawID, const int & iOption = 0);
	void SetStartPos(const D3DXVECTOR3 & vMouse);

	map<int,OBJDATA*>& GetObj() { return m_ObjMap; }
	void AddObj(const D3DXVECTOR3 & vMouse, const CString & objName);
	void DeleteObject(D3DXVECTOR3 vMouse);

	map<int, EVENTINFO*>& GetEvent() { return m_EventMap; }
	void AddEvent(const D3DXVECTOR3 & vMouse, EVENTINFO* _Event);
	void DeleteEvent(D3DXVECTOR3 vMouse);

	map<int,D3DXVECTOR3>& GetColl() { return m_CollMap; }
	void AddCollision(const D3DXVECTOR3 & vMouse);
	void DeleteColl(D3DXVECTOR3 vMouse);

private:
	int GetTileIndex(const D3DXVECTOR3& vMouse);

private:
	CMFCToolView* m_pView;

	vector<TILE*> m_vecTile;
	//list<OBJDATA*> m_ObjList;
	map<int, OBJDATA*> m_ObjMap;
	map<int,D3DXVECTOR3>m_CollMap;

	map<int, EVENTINFO*>m_EventMap;

};

#endif // !__TERRAIN_H__