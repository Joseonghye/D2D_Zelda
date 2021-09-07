#pragma once
#ifndef __MULTITEXTURE_H__
#define __MULTITEXTURE_H__
#include "Texture.h"
class CMultiTexture :
    public CTexture
{
private:
    map<wstring, TEXTUREGROUP> m_mapMulti;
public:
    explicit CMultiTexture();
    virtual ~CMultiTexture();
public:
    virtual const TEXINFO* getTexture(const wstring& wstrStateKey = L"", const int& iCount = 0) override;
    virtual HRESULT InsterTexture(const wstring& wstrFilePath, const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const int& iCount = 0) override;
    virtual void Release() override;
public:
    static CTexture* Create();
};
#endif

