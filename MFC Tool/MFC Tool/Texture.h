#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__
class CTexture abstract
{
public:
	explicit CTexture();
	virtual ~CTexture();
public:
	virtual const TEXINFO* getTexture(const wstring& wstrStateKey = L"", const int& iCount = 0) PURE;
	virtual HRESULT InsterTexture(const wstring& wstrFilePath, const wstring& wstrObjectKey,
		const wstring& wstrStateKey = L"", const int& iCount = 0)PURE;
	virtual void Release() PURE;
};
#endif

