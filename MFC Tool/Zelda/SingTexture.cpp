#include "stdafx.h"
#include "SingTexture.h"

CSingTexture::CSingTexture() : m_pTextureInfo(nullptr)
{
}

CSingTexture::~CSingTexture()
{
	Release();
}

const TEXINFO* CSingTexture::getTexture(const wstring& wstrStateKey, const int& iCount)
{
	return m_pTextureInfo;
}

HRESULT CSingTexture::InsterTexture(const wstring& wstrFilePath, const wstring& wstrObjectKey, const wstring& wstrStateKey, const int& iCount)
{
	m_pTextureInfo = new TEXINFO;
	ZeroMemory(m_pTextureInfo, sizeof(TEXINFO));

	TCHAR szPath[MAX_PATH] = L"";
	wsprintf(szPath, wstrFilePath.c_str());

	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_pTextureInfo->tTextureInfo)))
	{
		//MSG_BOX(wstrFilePath.c_str());
		MSG_BOX(szPath);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(GRAPHICDEVICE->GetDevice()
		, szPath
		, m_pTextureInfo->tTextureInfo.Width, m_pTextureInfo->tTextureInfo.Height
		, m_pTextureInfo->tTextureInfo.MipLevels, 0, m_pTextureInfo->tTextureInfo.Format
		, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT
		, 0, nullptr, nullptr,&m_pTextureInfo->pTexture)))
	{
		//MSG_BOX(wstrObjectKey.c_str());
		MSG_BOX(szPath);
	}
	m_pTextureInfo->tCenter = { m_pTextureInfo->tTextureInfo.Width *0.5f, m_pTextureInfo->tTextureInfo.Height *0.5f,0.f };
	return S_OK;
}

void CSingTexture::Release()
{
	Safe_Release(m_pTextureInfo->pTexture);
	Safe_Delete(m_pTextureInfo);
}

CTexture* CSingTexture::Create()
{
	CTexture* pInstance = new CSingTexture;

	return pInstance;
}
