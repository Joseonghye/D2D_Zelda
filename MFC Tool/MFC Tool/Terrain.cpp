#include "stdafx.h"
#include "Terrain.h"


Terrain::Terrain()
{
}

Terrain::~Terrain()
{
	ReleaseTerrain();
	ReleaseObject();
}

void Terrain::AddTileData(TILE * pTile)
{
	m_vecTile.emplace_back(pTile);
}

HRESULT Terrain::ReadyTerrain()
{
	//맵 크기만큼 할당 
	m_vecTile.reserve(TILEX * TILEY);
	TILE* pTile = nullptr;

	float halfX = (TILECX *0.5f);
	float halfY = (TILECY *0.5f);

	for (int i = 0; i < TILEY; i++) 
	{
		for (int j = 0; j < TILEX; j++) 
		{
			pTile = new TILE;

			float fY = (TILECY * i) + halfY;
			float fX = (TILECX * j) + halfX;
			pTile->vPos = { fX, fY, 0.f };

			pTile->vSize = { 1.f , 1.f , 1.f };
			pTile->dwDrawID = 4;

			m_vecTile.emplace_back(pTile);
		}
	}
	return S_OK;
}

void Terrain::RenderTerrain()
{
	int iSize = m_vecTile.size();

	for (int i = 0; i < iSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexturMgr::getInstance()->getTexture(L"Terrain", L"Tile", m_vecTile[i]->dwDrawID);
		if (nullptr == pTexInfo)
			return;
	
		D3DXMATRIX matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x, m_vecTile[i]->vPos.y, 0.f);
		matWorld = matScale * matTrans;

		CGraphicDevice::getInstance()->GetSprite()->SetTransform(&matWorld);
		CGraphicDevice::getInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

//	CGraphicDevice::getInstance()->GetSprite()->End();

	 //라인 그리기 
	/*float fY = (TILECY >> 1);
	float fX = (TILECX >> 1);

	for (int i = 0; i < iSize; i++)
	{
		TILE* temp = m_vecTile[i];
		
		D3DXVECTOR2 vLine[4] = {
			{ temp->vPos.x - fX, temp->vPos.y - fY },
			{ temp->vPos.x + fX, temp->vPos.y - fY },
			{ temp->vPos.x + fX, temp->vPos.y + fY },
			{ temp->vPos.x - fX, temp->vPos.y + fY } 
		};

//		CGraphicDevice::getInstance()->getLine()->Draw(vLine, 4, D3DCOLOR_ARGB(255, 255, 255, 255));
	}*/
}

void Terrain::ReleaseTerrain()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	m_vecTile.clear();
	m_vecTile.swap(vector<TILE*>());
}

Terrain * Terrain::Create() /*LPVOID pArg = nullptr   >> 이게 뭐지? nullptr을 넣을거면 굳이?*/
{
	Terrain* pInstance = new Terrain;
	if (FAILED(pInstance->ReadyTerrain()))
		Safe_Delete(pInstance);

	return pInstance;
}

void Terrain::AddObjData(OBJDATA* data)
{
	m_ObjList.emplace_back(data);
}

void Terrain::RenderObject()
{
	if (m_ObjList.empty()) return;

	for (auto& iter : m_ObjList)
	{
		const TEXINFO* pTexInfo = CTexturMgr::getInstance()->getTexture(iter->szName, L"Walk");
		if (nullptr == pTexInfo)
			return;

		CGraphicDevice::getInstance()->GetSprite()->SetTransform(&iter->m_tInfo.matWorld);
		CGraphicDevice::getInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
//	CGraphicDevice::getInstance()->GetSprite()->End();

}

void Terrain::ReleaseObject()
{
	for_each(m_ObjList.begin(), m_ObjList.end(), Safe_Delete<OBJDATA*>);
	m_ObjList.clear();
}

void Terrain::ChangeTile(const D3DXVECTOR3 & vMouse, const int & iDrawID, const int & iOption)
{
	int iIndex = GetTileIndex(vMouse);
	if (iIndex == -1) return;

	m_vecTile[iIndex]->dwDrawID = iDrawID;
	m_vecTile[iIndex]->dwOption = iOption;
}

void Terrain::AddObj(const D3DXVECTOR3 & vMouse, const CString & objName)
{
	OBJDATA* pInfo = new OBJDATA;
	lstrcpy(pInfo->szName,objName.GetString());

	pInfo->m_tInfo.vPos = vMouse;
	pInfo->m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);

	D3DXMatrixScaling(&pInfo->m_tInfo.matScale, pInfo->m_tInfo.vSize.x, pInfo->m_tInfo.vSize.y, 0.0f);
	D3DXMatrixTranslation(&pInfo->m_tInfo.matTrans, vMouse.x, vMouse.y, 0.f);
	pInfo->m_tInfo.matWorld = pInfo->m_tInfo.matScale * pInfo->m_tInfo.matTrans;

	m_ObjList.emplace_back(pInfo);
}

int Terrain::GetTileIndex(const D3DXVECTOR3 & vMouse)
{
	if (vMouse.x < 0 || vMouse.y < 0)
		return -1;

	int iY = vMouse.y / TILECY;
	int iX = vMouse.x / TILECX;

	int iIndex = iX + (iY * TILEX);

	if (iIndex >= m_vecTile.size())
		return -1;

	return iIndex;
}
