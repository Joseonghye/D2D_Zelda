#include "pch.h"
#include "Terrein.h"

CTerrein::CTerrein() : m_pSprite(nullptr)
{
}

CTerrein::~CTerrein()
{
    Release();
}

HRESULT CTerrein::Initialize()
{
    m_pSprite = CGraphicDevice::getInstance()->getSprite();
    m_pTextureMgr = CTexturMgr::getInstance();

    m_pTextureMgr->InsertTexture(TEXTYPE::SINGLE, L"../Texture/BackGround/ancient.png", L"BackGround");

    return S_OK;
}

void CTerrein::Render()
{
    m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
    const TEXINFO* pTexture = m_pTextureMgr->getTexture(L"BackGround");
    m_pSprite->Draw(pTexture->pTexture, nullptr, &pTexture->tCenter, &D3DXVECTOR3(WINCX*0.5f,WINCY*0.5f,0.f), D3DCOLOR_ARGB(255, 255, 255, 255));
    m_pSprite->End();
}

void CTerrein::Release()
{
}

CTerrein* CTerrein::Create()
{
    CTerrein* pInstance = new CTerrein();
    if (FAILED(pInstance->Initialize()))
        Safe_Delete(pInstance);
    return pInstance;
}
