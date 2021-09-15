#pragma once
#ifndef __GRAPHICDEVICE_H__
#define __GRAPHICDEVICE_H__
#include "SingleTon.h"

class CGraphicDevice : public CSingleTon<CGraphicDevice>
{
friend CSingleTon;
private:
	explicit CGraphicDevice();
	virtual ~CGraphicDevice();
public:
	HRESULT Initialized();
	void BeginDraw();
	void EndDraw(HWND _hWnd=g_hWnd);
	void Release();

public:
	const LPDIRECT3DDEVICE9& const GetDevice() { return m_pDevice; }
	const LPD3DXSPRITE& const GetSprite() { return m_pSprite; }
	const LPD3DXFONT& const GetFont() { return m_pFont; }
	const LPD3DXLINE& const GetLine() { return m_pLine; }
private:
	void SetParmeter(D3DPRESENT_PARAMETERS& d3pp);

private:
	LPDIRECT3D9 m_pSDK;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;
	LPD3DXFONT m_pFont;
	LPD3DXLINE m_pLine;
};
#endif

