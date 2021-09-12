#include "stdafx.h"
#include "TextureMgr.h"
#include "SingTexture.h"
#include "MultiTexture.h"

CTextureMgr::CTextureMgr() {}

CTextureMgr::~CTextureMgr()
{
	Release();
}

void CTextureMgr::Release()
{
	for_each(m_mapTexture.begin(), m_mapTexture.end(),
		[](auto& MyPair)
		{
			if (MyPair.second)
			{
				delete MyPair.second;
				MyPair.second = nullptr;
			}
		});
	m_mapTexture.clear();

}

HRESULT CTextureMgr::InsertTexture(TEXTYPE etype, const wstring& wstrFilePath, const wstring& wstrObjectKey, const wstring& wstrStateKey, const int& iCount)
{
	auto iter = m_mapTexture.find(wstrObjectKey);
	if (iter == m_mapTexture.end())
	{
		CTexture* pTexture = nullptr;
		switch (etype)
		{
			case TEXTYPE::SINGLE:
				pTexture = CSingTexture::Create();
				break;
			case TEXTYPE::MULTI:
				pTexture = CMultiTexture::Create();
				break;
		}
		if (FAILED(pTexture->InsterTexture(wstrFilePath, wstrObjectKey, wstrStateKey, iCount)))
		{
			MSG_BOX(L"텍스쳐 생성 실패")
		}

		m_mapTexture.emplace(wstrObjectKey, pTexture);
	}
	else
	{
		if (etype == TEXTYPE::MULTI)
		{
			//iter->second->Release();
			if (FAILED(iter->second->InsterTexture(wstrFilePath, wstrObjectKey, wstrStateKey, iCount)))
			{
				MSG_BOX(L"멀티 텍스쳐 생성 실패")
			}
		}
	}
	return S_OK;
}

const TEXINFO* CTextureMgr::GetTexture(const wstring& wstrObjKey, const wstring& wstrStateKey, const int& iCount)
{
	auto iter = m_mapTexture.find(wstrObjKey);
	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second->getTexture(wstrStateKey,iCount);
}
