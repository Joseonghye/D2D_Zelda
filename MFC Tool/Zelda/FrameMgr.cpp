#include "stdafx.h"
#include "FrameMgr.h"


CFrameMgr::CFrameMgr()
	:m_fDeltaTime(0.f),m_fSPF(0.f), m_fFPSTime(0.f), m_iFPS(0), m_szFPS(L"")
{
	ZeroMemory(&m_tBegin, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_tEnd, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_tCPUTick, sizeof(LARGE_INTEGER));
}


CFrameMgr::~CFrameMgr()
{
}

void CFrameMgr::Initialize_FrameMgr(float fFPS)
{
	m_fSPF = 1.f / fFPS;
	QueryPerformanceCounter(&m_tBegin);
	QueryPerformanceCounter(&m_tEnd);
	QueryPerformanceFrequency(&m_tCPUTick);
}

void CFrameMgr::Render_FrameMgr()
{
	m_fFPSTime += TIMEMGR->Get_DeltaTime();
	if (m_fFPSTime >= 1.f)
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		m_iFPS = 0;
		m_fFPSTime = 0.f;
	}

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f);
	GRAPHICDEVICE->GetSprite()->SetTransform(&matTrans);
	GRAPHICDEVICE->GetFont()->DrawTextW(GRAPHICDEVICE->GetSprite(), m_szFPS, lstrlen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));

}

bool CFrameMgr::FrameLock()
{
	QueryPerformanceCounter(&m_tEnd);
	m_fDeltaTime += float(m_tEnd.QuadPart - m_tBegin.QuadPart) / m_tCPUTick.QuadPart;
	m_tBegin.QuadPart = m_tEnd.QuadPart;
	if (m_fDeltaTime >= m_fSPF)
	{
		++m_iFPS;
		m_fDeltaTime = 0.f;
		QueryPerformanceFrequency(&m_tCPUTick);
		return true;
	}

	return false;
}
