#pragma once
#ifndef __TERREIN_H__
#define __TERREIN_H__
class CTerrein final
{
private:
	LPD3DXSPRITE m_pSprite;
	CTexturMgr* m_pTextureMgr;
private:
	explicit CTerrein();
public:
	~CTerrein();
public:
	HRESULT Initialize();
	void Render();
	void Release();
public:
	static CTerrein* Create();
};
#endif

