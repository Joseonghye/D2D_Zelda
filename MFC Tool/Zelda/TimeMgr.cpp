#include "stdafx.h"
#include "TimeMgr.h"


CTimeMgr::CTimeMgr()
{
}


CTimeMgr::~CTimeMgr()
{
}

HRESULT CTimeMgr::Initialized_TimeMgr()
{
	QueryPerformanceCounter(&m_tBegin);
	QueryPerformanceCounter(&m_tEnd);
	QueryPerformanceFrequency(&m_tCPUTick);
	m_fDeltaTime = 0.f;
	return S_OK;
}

void CTimeMgr::Update_TimeMgr()
{
	QueryPerformanceCounter(&m_tEnd);
	m_fDeltaTime = float(m_tEnd.QuadPart - m_tBegin.QuadPart) / m_tCPUTick.QuadPart;
	m_tBegin.QuadPart = m_tEnd.QuadPart;
}
