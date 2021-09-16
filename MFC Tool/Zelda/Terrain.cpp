#include "stdafx.h"
#include "Terrain.h"
#include "Wall.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
	Release_GameObject();
}

Terrain * Terrain::Create()
{
	Terrain* pInstance = new Terrain;
	if (FAILED(pInstance->Initialized_GameObject()))
		Safe_Delete(pInstance);

	return pInstance;
}

HRESULT Terrain::Initialized_GameObject()
{
	//맵 크기만큼 할당 
//	m_vecTile.reserve(ROOM_TILEX * ROOM_TILEY);
	m_vecRoom.resize(TOTAL_TILEX*TOTAL_TILEY);

	for (int i = 0; i < TOTAL_TILEY; ++i)
	{
		for (int j = 0; j < TOTAL_TILEX; ++j)
			m_vecRoom[j + (i*TOTAL_TILEX)].reserve(ROOM_TILEX * ROOM_TILEY);
	}
	
	Release_GameObject();
	if(FAILED(LoadTileFile(L"../Data/Tile/Tile.dat")))
		return E_FAIL;

	//if(FAILED(LoadColliderFile(L"../Data/Collider/Collider.dat")))
	//	return E_FAIL;

	//SCROLLMGR->SetScroll(1, 0);

	return S_OK;
}

int Terrain::Update_GameObject()
{
	return NO_EVENT;
}

void Terrain::LateUpdate_GameObject()
{
}

void Terrain::Render_GameObject()
{
	//int iSize = m_vecTile.size();
	int iSize = m_vecRoom[m_RoomIndex].size();

	D3DXVECTOR3 vScroll = SCROLLMGR->GetScrollVec();

	for (int i = 0; i < iSize; ++i)
	{
		const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"Terrain", L"Tile", m_vecRoom[m_RoomIndex][i]->dwDrawID);
		if (nullptr == pTexInfo)
			return;

		D3DXMATRIX matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_vecRoom[m_RoomIndex][i]->vSize.x, m_vecRoom[m_RoomIndex][i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecRoom[m_RoomIndex][i]->vPos.x + vScroll.x , m_vecRoom[m_RoomIndex][i]->vPos.y+ vScroll.y, 0.f);


		//D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f);
		//D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x, m_vecTile[i]->vPos.y, 0.f);
		matWorld = matScale * matTrans;

		GRAPHICDEVICE->GetSprite()->SetTransform(&matWorld);
		GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void Terrain::Release_GameObject()
{
	for (int i = 0; i < OBJID_END; ++i)
	{
		for_each(m_vecRoom[i].begin(), m_vecRoom[i].end(), Safe_Delete<TILE*>);
		m_vecRoom[i].clear();
	}
	//for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	//m_vecTile.clear();
	//m_vecTile.swap(vector<TILE*>());

	/*for_each(m_vecRoom.begin(), m_vecRoom.end(), Safe_Delete<Room>);
	m_vecRoom.clear();
	m_vecRoom.swap(vector<Room>());*/
}

HRESULT Terrain::LoadTileFile(const wstring & wstrFilePath)
{
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);;
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwByte = 0;
	TILE* pTile = nullptr;

	int x = 0;
	int y = 0;
	int totalX = 0;
	int totalY = 0;
	while (true)
	{
		pTile = new TILE;
		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete(pTile);
			break;
		}
		
		int RoomIndex = totalX + (TOTAL_TILEX*totalY);
		m_vecRoom[RoomIndex].emplace_back(pTile);
		
		if (pTile->dwOption == 1)
		{
			SCROLLMGR->SetScroll(totalX, totalY);
			m_RoomIndex = RoomIndex;

			m_tInfo.vPos = pTile->vPos;
		}

		++x;
		if (x == ROOM_TILEX)
		{
			++totalX;
			x = 0;
			if (totalX == TOTAL_TILEX) {
				totalX = 0;

				++y;
				if (y == ROOM_TILEY)
				{
					y = 0;
					++totalY;
					if (totalY == TOTAL_TILEY) break;
				}
			}
		}

	//	m_vecTile.emplace_back(pTile);
	}
	CloseHandle(hFile);

	return S_OK;
}

HRESULT Terrain::LoadColliderFile(const wstring & wstrFilePath)
{
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);;
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwByte = 0;
	int iIndex = -1;
	D3DXVECTOR3 vPos;

	while (true)
	{
		ReadFile(hFile, &iIndex, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &vPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);

		if (0 == dwByte)
		{
			break;
		}

		CGameObject* pGameObject = CWall::Create();
		pGameObject->SetPos(vPos);
		pGameObject->SetTransMat();
		pGameObject->SetWorldMat();

		GAMEOBJECTMGR->Add_GameObject(OBJID::WALL, iIndex, pGameObject);

	//	m_mapCollider.emplace(iIndex, vPos);
	}
	CloseHandle(hFile);

	return S_OK;

}
