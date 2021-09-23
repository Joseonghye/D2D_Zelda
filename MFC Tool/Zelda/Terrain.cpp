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
	m_iRoomIndex = -1;
	m_bVisible = true;
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

	if(FAILED(LoadColliderFile(L"../Data/Collider/Collider.dat")))
		return E_FAIL;

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
	m_RoomIndex = GAMEOBJECTMGR->GetRoomIndex();

	int iSize = m_vecRoom[m_RoomIndex].size();

	D3DXVECTOR3 vScroll = SCROLLMGR->GetScrollVec();

	if (GAMEOBJECTMGR->isChanging())
	{
		int next = GAMEOBJECTMGR->GetNextRoom();
		for (int i = 0; i < iSize; ++i)
		{
			const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"Terrain", L"Tile", m_vecRoom[next][i]->dwDrawID);
			if (nullptr == pTexInfo)
				return;

			D3DXMATRIX matScale, matTrans, matWorld;

			D3DXMatrixScaling(&matScale, m_vecRoom[next][i]->vSize.x, m_vecRoom[next][i]->vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_vecRoom[next][i]->vPos.x + vScroll.x, m_vecRoom[next][i]->vPos.y + vScroll.y, 0.f);
			matWorld = matScale * matTrans;

			GRAPHICDEVICE->GetSprite()->SetTransform(&matWorld);
			GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	for (int i = 0; i < iSize; ++i)
	{
		const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"Terrain", L"Tile", m_vecRoom[m_RoomIndex][i]->dwDrawID);
		if (nullptr == pTexInfo)
			return;

		D3DXMATRIX matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_vecRoom[m_RoomIndex][i]->vSize.x, m_vecRoom[m_RoomIndex][i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecRoom[m_RoomIndex][i]->vPos.x + vScroll.x , m_vecRoom[m_RoomIndex][i]->vPos.y+ vScroll.y, 0.f);
		matWorld = matScale * matTrans;

		GRAPHICDEVICE->GetSprite()->SetTransform(&matWorld);
		GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void Terrain::Release_GameObject()
{
	for (int i = 0; i <(TOTAL_TILEX*TOTAL_TILEY); ++i)
	{
		for_each(m_vecRoom[i].begin(), m_vecRoom[i].end(), Safe_Delete<TILE*>);
		m_vecRoom[i].clear();
		m_vecRoom[i].swap(vector<TILE*>());
	}
	//for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	//m_vecTile.clear();
	//m_vecTile.swap(vector<TILE*>());

	/*for_each(m_vecRoom.begin(), m_vecRoom.end(), Safe_Delete<Room>);
	m_vecRoom.clear();
	m_vecRoom.swap(vector<Room>());*/
}

int Terrain::GetTileOption(D3DXVECTOR3 vPos)
{
	int iIndex = GetTileIndex(vPos);
	if (iIndex == -1) return -1;

	return 	m_vecRoom[m_iRoomIndex][iIndex]->dwOption;
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
			GAMEOBJECTMGR->SetCurRoomIndex(totalX, totalY);
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

		pTile = nullptr;
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

		int y = iIndex / (TOTAL_TILEX*ROOM_TILEX);
		int x = iIndex - ((TOTAL_TILEX*ROOM_TILEX)*y);

		int totalY = y / ROOM_TILEY;
		int totalX = x / ROOM_TILEX;
		int iRoomIndex = totalX + (TOTAL_TILEX *totalY);

		CGameObject* pGameObject = CWall::Create();
		pGameObject->SetRoomIndex(iRoomIndex);
		pGameObject->SetPos(vPos);
		pGameObject->SetTransMat();
		pGameObject->SetWorldMat();

		GAMEOBJECTMGR->Add_GameObject(OBJID::WALL, pGameObject);

		//	m_mapCollider.emplace(iIndex, vPos);
	}
	CloseHandle(hFile);

	return S_OK;

}

int Terrain::GetTileIndex(D3DXVECTOR3 vPos)
{
	if (vPos.x < 0 || vPos.y < 0)
		return -1;

	//int y = (m_iRoomIndex / TOTAL_TILEX) - 1;
	//int x = m_iRoomIndex % TOTAL_TILEX;

	//vPos.x += x*(ROOM_TILEX*TILECX);
	//vPos.y += y*(ROOM_TILEY*TILECY);

	int iY = vPos.y / TILECY;
	int iX = vPos.x / TILECX;

	int iIndex = iX + (iY * ROOM_TILEX);

	if (iIndex >= m_vecRoom[m_iRoomIndex].size())
		return -1;

	return iIndex;
}
