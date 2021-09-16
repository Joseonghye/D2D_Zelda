#include "stdafx.h"
#include "Terrain.h"
#include "MFC ToolView.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
	ReleaseTerrain();
	ReleaseObject();
	ReleaseColl();
}

void Terrain::AddTileData(TILE * pTile)
{
	//auto& iter = m_vecTile.begin();
	//iter += (index - 1);
	//m_vecTile.insert(iter, pTile);
	//m_vecTile[index] = pTile;
	m_vecTile.emplace_back(pTile);
}

HRESULT Terrain::ReadyTerrain()
{
	//맵 크기만큼 할당 
//	m_vecTile.resize((TOTAL_TILEX*ROOM_TILEX) * (TOTAL_TILEY*ROOM_TILEY),nullptr);
	m_vecTile.reserve((TOTAL_TILEX*ROOM_TILEX) * (TOTAL_TILEY*ROOM_TILEY));
	TILE* pTile = nullptr;

	float halfX = (TILECX *0.5f);
	float halfY = (TILECY *0.5f);

	for (int i = 0; i < (TOTAL_TILEY*ROOM_TILEY); i++)
	{
		for (int j = 0; j < (TOTAL_TILEX*ROOM_TILEX); j++)
		{
			pTile = new TILE;

			float fY = (TILECY * i) + halfY;
			float fX = (TILECX * j) + halfX;
			pTile->vPos = { fX, fY, 0.f };

			pTile->vSize = { 1.f , 1.f , 1.f };
			pTile->dwDrawID = 4;

			int index = j + (i*(TOTAL_TILEX*ROOM_TILEX));
		//	m_vecTile[index] = pTile;

			m_vecTile.emplace_back(pTile);
		}
	}
	return S_OK;
}

void Terrain::RenderTerrain()
{
	int iSize = m_vecTile.size();
	TCHAR szIndex[MAX_PATH] = L"";

	for (int i = 0; i < iSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexturMgr::GetInstance()->getTexture(L"Terrain", L"Tile", m_vecTile[i]->dwDrawID);
		if (nullptr == pTexInfo)
			return;
	
		D3DXMATRIX matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x - m_pView->GetScrollPos(SB_HORZ), m_vecTile[i]->vPos.y - m_pView->GetScrollPos(SB_VERT), 0.f);
		matWorld = matScale * matTrans;

		CGraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
		CGraphicDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		
		CGraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
		swprintf_s(szIndex, L"%d", i);
		CGraphicDevice::GetInstance()->GetFont()->DrawTextW(CGraphicDevice::GetInstance()->GetSprite(), szIndex, lstrlen(szIndex), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}


//	CGraphicDevice::GetInstance()->GetSprite()->End();

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

//		CGraphicDevice::GetInstance()->getLine()->Draw(vLine, 4, D3DCOLOR_ARGB(255, 255, 255, 255));
	}*/
}

void Terrain::MiniRenderTerrain()
{
	int iSize = m_vecTile.size();
	TCHAR szIndex[MAX_PATH] = L"";

	for (int i = 0; i < iSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexturMgr::GetInstance()->getTexture(L"Terrain", L"Tile", m_vecTile[i]->dwDrawID);
		if (nullptr == pTexInfo)
			return;

		D3DXMATRIX matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x - m_pView->GetScrollPos(SB_HORZ), m_vecTile[i]->vPos.y - m_pView->GetScrollPos(SB_VERT), 0.f);
		matWorld = matScale * matTrans;

		CGraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
		CGraphicDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		CGraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
		swprintf_s(szIndex, L"%d", i);
		CGraphicDevice::GetInstance()->GetFont()->DrawTextW(CGraphicDevice::GetInstance()->GetSprite(), szIndex, lstrlen(szIndex), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

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

void Terrain::AddObjData(int index,OBJDATA* data)
{
	m_ObjMap.emplace(index,data);
}

void Terrain::RenderObject()
{
	if (m_ObjMap.empty()) return;

	for (auto& iter : m_ObjMap)
	{
		const TEXINFO* pTexInfo = CTexturMgr::GetInstance()->getTexture(iter.second->szName, L"Walk");
		if (nullptr == pTexInfo)
			return;

		CGraphicDevice::GetInstance()->GetSprite()->SetTransform(&iter.second->m_tInfo.matWorld);
		CGraphicDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
//	CGraphicDevice::GetInstance()->GetSprite()->End();

}

void Terrain::ReleaseObject()
{
//	for_each(m_ObjMap.begin(), m_ObjMap.end(), Safe_Delete<OBJDATA*>);
	m_ObjMap.clear();
}

void Terrain::AddCollData(int index,D3DXVECTOR3 vPos)
{
	m_CollMap.emplace(index,vPos);
}

void Terrain::RenderColl()
{
	if (m_CollMap.empty()) return;

	float fX = (TILECX*0.5f);
	float fY = (TILECY *0.5f);

	for (auto& iter : m_CollMap)
	{
		float left = iter.second.x - fX;
		float right = iter.second.x + fX;

		float top = iter.second.y - fY;
		float bottom = iter.second.y + fY;
		/*	RECT rc{ iter.second.x - (TILECX*0.5f),iter.second.y - (TILECY *0.5f),iter.second.x + (TILECX*0.5f),iter.second.y + (TILECY *0.5f) };
			_dc->Rectangle((int)rc.left, (int)rc.top, (int)rc.right, (int)rc.bottom);*/

		D3DXVECTOR2 vLine[4] = {
			{ left,top },
			{ right,top},
			{ right,bottom },
			{ left,bottom}
		};

		CGraphicDevice::GetInstance()->getLine()->SetWidth(20.f);
		CGraphicDevice::GetInstance()->getLine()->Draw(vLine, 4, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
}

void Terrain::ReleaseColl()
{
	m_CollMap.clear();
}

void Terrain::ChangeTile(const D3DXVECTOR3 & vMouse, const int & iDrawID, const int & iOption)
{
	int iIndex = GetTileIndex(vMouse);
	if (iIndex == -1) return;

	m_vecTile[iIndex]->dwDrawID = iDrawID;
	m_vecTile[iIndex]->dwOption = iOption;
}

void Terrain::SetStartPos(const D3DXVECTOR3 & vMouse)
{
	int iIndex = GetTileIndex(vMouse);
	if (iIndex == -1) return;

	m_vecTile[iIndex]->dwOption = 1;
}

void Terrain::AddObj(const D3DXVECTOR3 & vMouse, const CString & objName)
{

	int iIndex = GetTileIndex(vMouse);
	if (iIndex == -1) return;

	OBJDATA* pInfo = new OBJDATA;
	lstrcpy(pInfo->szName,objName.GetString());

	pInfo->m_tInfo.vPos = m_vecTile[iIndex]->vPos;
	//pInfo->m_tInfo.vPos = vMouse;
	pInfo->m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);

	D3DXMatrixScaling(&pInfo->m_tInfo.matScale, pInfo->m_tInfo.vSize.x, pInfo->m_tInfo.vSize.y, 0.0f);
	D3DXMatrixTranslation(&pInfo->m_tInfo.matTrans, vMouse.x, vMouse.y, 0.f);
	pInfo->m_tInfo.matWorld = pInfo->m_tInfo.matScale * pInfo->m_tInfo.matTrans;

	m_ObjMap.emplace(iIndex, pInfo);
	//m_ObjMap.emplace_back(pInfo);
}

void Terrain::DeleteObject(D3DXVECTOR3 vMouse)
{
}

void Terrain::AddCollision(const D3DXVECTOR3 & vMouse)
{
	int iIndex = GetTileIndex(vMouse);
	if (iIndex == -1) return;

	m_CollMap.emplace(iIndex,m_vecTile[iIndex]->vPos);
}

void Terrain::DeleteColl(D3DXVECTOR3 vMouse)
{
	int iIndex = GetTileIndex(vMouse);
	if (iIndex == -1) return;

	auto& iter = m_CollMap.find(iIndex);
	if (iter == m_CollMap.end()) return;

	m_CollMap.erase(iter);
}

int Terrain::GetTileIndex(const D3DXVECTOR3 & vMouse)
{
	if (vMouse.x < 0 || vMouse.y < 0)
		return -1;

	int iY = vMouse.y / TILECY;
	int iX = vMouse.x / TILECX;

	int iIndex = iX + (iY * (TOTAL_TILEX* ROOM_TILEX));

	if (iIndex >= m_vecTile.size())
		return -1;

	return iIndex;
}
