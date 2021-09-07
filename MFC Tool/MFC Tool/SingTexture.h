#pragma once
#ifndef __SINGLETEXTURE_H__
#define __SINGLETEXTURE_H__
#include "Texture.h"
class CSingTexture :
    public CTexture
{
private:
    TEXINFO* m_pTextureInfo;

public:
    explicit CSingTexture();
    virtual ~CSingTexture();
public:
    virtual const TEXINFO* getTexture(const wstring& wstrStateKey = L"", const int& iCount = 0) override;
    virtual HRESULT InsterTexture(const wstring& wstrFilePath, const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const int& iCount = 0) override;
    virtual void Release() override;
public:
    static CTexture* Create();
};
#endif