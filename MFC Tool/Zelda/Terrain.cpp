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
	m_vecTile.reserve(TILEX * TILEY);
	
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
	int iSize = m_vecTile.size();

	for (int i = 0; i < iSize; ++i)
	{
		const TEXINFO* pTexInfo = TEXTUREMGR->GetTexture(L"Terrain", L"Tile", m_vecTile[i]->dwDrawID);
		if (nullptr == pTexInfo)
			return;

		D3DXMATRIX matScale, matTrans, matWorld;

		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x, m_vecTile[i]->vPos.y, 0.f);
		matWorld = matScale * matTrans;

		GRAPHICDEVICE->GetSprite()->SetTransform(&matWorld);
		GRAPHICDEVICE->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void Terrain::Release_GameObject()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	m_vecTile.clear();
	m_vecTile.swap(vector<TILE*>());
}

HRESULT Terrain::LoadTileFile(const wstring & wstrFilePath)
{
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);;
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwByte = 0;
	TILE* pTile = nullptr;
	while (true)
	{
		pTile = new TILE;
		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		if (0 == dwByte)
		{
			Safe_Delete(pTile);
			break;
		}

		m_vecTile.emplace_back(pTile);
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
		GAMEOBJECTMGR->Add_GameObject(WALL, pGameObject);

	//	m_mapCollider.emplace(iIndex, vPos);
	}
	CloseHandle(hFile);

	return S_OK;

}
