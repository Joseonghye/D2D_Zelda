#include "stdafx.h"
#include "MultiTexture.h"

CMultiTexture::CMultiTexture()
{
}

CMultiTexture::~CMultiTexture()
{
	Release();
}

const TEXINFO* CMultiTexture::getTexture(const wstring& wstrStateKey, const int& iCount)
{
	auto iter = m_mapMulti.find(wstrStateKey);
	if (iter == m_mapMulti.end())
		return nullptr;

	return iter->second[iCount];
}

HRESULT CMultiTexture::InsterTexture(const wstring& wstrFilePath, const wstring& wstrObjectKey, const wstring& wstrStateKey, const int& iCount)
{
	auto& iter_Find = m_mapMulti.find(wstrStateKey);
	if (iter_Find == m_mapMulti.end())
	{
		TCHAR szPath[MAX_PATH] = L"";
		vector<TEXINFO*> vecTexture;

		for (int i = 0; i < iCount; ++i)
		{
			wsprintf(szPath, wstrFilePath.c_str(), i);
			TEXINFO* pTexInfo = new TEXINFO;
			ZeroMemory(pTexInfo, sizeof(TEXINFO));

			if (FAILED(D3DXGetImageInfoFromFile(szPath, &pTexInfo->tTextureInfo)))
			{
				MSG_BOX(szPath);
			}

			if (FAILED(D3DXCreateTextureFromFileEx(GRAPHICDEVICE->GetDevice()
				, szPath
				, pTexInfo->tTextureInfo.Width, pTexInfo->tTextureInfo.Height
				, pTexInfo->tTextureInfo.MipLevels, 0, pTexInfo->tTextureInfo.Format
				, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT
				, NULL, &pTexInfo->tTextureInfo, nullptr, &pTexInfo->pTexture)))
			{
				MSG_BOX(szPath)
			}

			pTexInfo->tCenter = { pTexInfo->tTextureInfo.Width * 0.5f,pTexInfo->tTextureInfo.Height * 0.5f,0.f };
			vecTexture.push_back(pTexInfo);
		}

		m_mapMulti.emplace(wstrStateKey, vecTexture);
		return S_OK;
	}
	else if (iter_Find->second.size()!=iCount)
	{
		int i = iter_Find->second.size();
		TCHAR szPath[MAX_PATH] = L"";
		for (; i < iCount; i++)
		{
			wsprintf(szPath, wstrFilePath.c_str(), i);
			TEXINFO* pTexInfo = new TEXINFO;
			ZeroMemory(pTexInfo, sizeof(TEXINFO));

			if (FAILED(D3DXGetImageInfoFromFile(szPath, &pTexInfo->tTextureInfo)))
			{
				MSG_BOX(szPath);
			}

			if (FAILED(D3DXCreateTextureFromFileEx(CGraphicDevice::GetInstance()->GetDevice()
				, szPath
				, pTexInfo->tTextureInfo.Width, pTexInfo->tTextureInfo.Height
				, pTexInfo->tTextureInfo.MipLevels, 0, pTexInfo->tTextureInfo.Format
				, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT
				, NULL, &pTexInfo->tTextureInfo, nullptr, &pTexInfo->pTexture)))
			{
				MSG_BOX(szPath)
			}
			pTexInfo->tCenter = { pTexInfo->tTextureInfo.Width * 0.5f,pTexInfo->tTextureInfo.Height * 0.5f,0.f };
			iter_Find->second.emplace_back(pTexInfo);

			return S_OK;
		}
	}
	return E_FAIL;
}

void CMultiTexture::Release()
{
	for (auto& pPair : m_mapMulti)
	{
		for (auto& tex : pPair.second)
		{
			Safe_Release(tex->pTexture);
			Safe_Delete(tex);
		}
		pPair.second.clear();
	}
	m_mapMulti.clear();
}

CTexture* CMultiTexture::Create()
{
	CTexture* pInstance = new CMultiTexture;
	return pInstance;
}
