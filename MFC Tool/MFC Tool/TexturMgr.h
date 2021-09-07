#pragma once
#ifndef __TEXTUREMGR_H__
#define __TEXTUREMGR_H__
#include "SingleTon.h"
class CTexture;
class CTexturMgr : public CSingleTon<CTexturMgr>
{
friend CSingleTon;
private:
	map<wstring, CTexture*> m_mapTexture;
private:
	explicit CTexturMgr();
	virtual ~CTexturMgr();
public:
	void Release();
public:
	HRESULT InsertTexture(TEXTYPE etype, const wstring& wstrFilePath, const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const int& iCount = 0);
	const TEXINFO* getTexture(const wstring& wstrObjKey, const wstring& wstrStateKey = L"", const int& iCount = 0);
};
#endif

