#include "stdafx.h"
#include "GraphicDevice.h"

//IMPLEMENT_SINGLETON(CGraphicDevice)

CGraphicDevice::CGraphicDevice() : m_pSDK(nullptr), m_pDevice(nullptr), m_pSprite(nullptr)//, m_pLine(nullptr)
{
}

CGraphicDevice::~CGraphicDevice()
{
	Release();
}

HRESULT CGraphicDevice::Initialize()
{
	//장치를 조사할 컴객체 생성 (m_pSDK)
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		MSG_BOX(L"Get Caps Fail")
	}

	//버텍스 프로세싱이 제공되는지?
	DWORD vp = 0;
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3pp;
	ZeroMemory(&d3pp, sizeof(D3DPRESENT_PARAMETERS));
	SetParmeter(d3pp);

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3pp, &m_pDevice)))
	{
		MSG_BOX(L"Create Device Fail")
	}

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		MSG_BOX(L"Create Sprite Fail")
	}
	/*if (FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
	{
		MSG_BOX(L"Create Line Fail")
	}*/
	
	return S_OK;
}

void CGraphicDevice::BeginDraw()
{
	m_pDevice->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
		D3DCOLOR_ARGB(255, 0, 0, 255), 1, 0);
	m_pDevice->BeginScene();

}

void CGraphicDevice::EndDraw(HWND _hWnd)
{
	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, _hWnd, nullptr);
}

void CGraphicDevice::Release()
{
	//Safe_Release(m_pLine);
	Safe_Release(m_pSprite);
	Safe_Release(m_pDevice);
	Safe_Release(m_pSDK);
}

void CGraphicDevice::SetParmeter(D3DPRESENT_PARAMETERS& d3pp)
{
	d3pp.BackBufferWidth = WINCX;
	d3pp.BackBufferHeight = WINCY;
	d3pp.BackBufferCount = 1;
	d3pp.BackBufferFormat = D3DFMT_A8R8G8B8;

	d3pp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3pp.MultiSampleQuality = 0;

	d3pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3pp.hDeviceWindow = g_hWnd;
	d3pp.Windowed = TRUE;	//창모드 

	d3pp.EnableAutoDepthStencil = TRUE;
	d3pp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}