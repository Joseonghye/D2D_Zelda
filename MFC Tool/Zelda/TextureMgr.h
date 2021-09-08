#pragma once
#ifndef __TEXTUREMGR_H__
#define __TEXTUREMGR_H__
#include "SingleTon.h"

class CTexture;
class CTextureMgr : public CSingleTon<CTextureMgr>
{
friend CSingleTon;
private:
	explicit CTextureMgr();
	virtual ~CTextureMgr();
public:
	void Release();
public:
	HRESULT InsertTexture(TEXTYPE etype, const wstring& wstrFilePath, const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const int& iCount = 0);
	const TEXINFO* GetTexture(const wstring& wstrObjKey, const wstring& wstrStateKey = L"", const int& iCount = 0);

private:
	map<wstring, CTexture*> m_mapTexture;
};

#endif //__TEXTUREMGR_H__