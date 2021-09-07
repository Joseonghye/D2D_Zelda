#include "stdafx.h"
#include "Mouse.h"


Mouse::Mouse()
	: chkMouse(false), m_wstrObjKey("")
{
}


Mouse::~Mouse()
{
	ReleaseMouse();
}

void Mouse::RenderMouse(HWND _pHWnd)
{
	if (!chkMouse) return;

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(_pHWnd, &pt);

	D3DXVECTOR3 mousPos = {(float)pt.x, (float)pt.y, 0.f};

	const TEXINFO* pTexInfo = CTexturMgr::getInstance()->getTexture(m_wstrObjKey.GetString(), L"Walk");
	if (nullptr == pTexInfo)
		return;

	CGraphicDevice::getInstance()->GetSprite()->Draw(pTexInfo->pTexture,nullptr, &pTexInfo->tCenter, &mousPos, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void Mouse::ReleaseMouse()
{
}

void Mouse::RenderObj(HWND _pHWnd,OBJINFO * _obj) {

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(_pHWnd, &pt);
	D3DXVECTOR3 mousPos = { (float)pt.x, (float)pt.y, 0.f };

	const TEXINFO* pTexInfo = CTexturMgr::getInstance()->getTexture(_obj->strObjKey.GetString(),L"Walk");
	if (nullptr == pTexInfo)
		return;

	CGraphicDevice::getInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	CGraphicDevice::getInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, &mousPos, D3DCOLOR_ARGB(255, 255, 255, 255));
	CGraphicDevice::getInstance()->GetSprite()->End();
}
