#pragma once
#ifndef __FRAMEMGR_H__
#define __FRAMEMGR_H__

class CFrameMgr 
{
public:
	CFrameMgr();
	~CFrameMgr();

public:
	void Initialize_FrameMgr(float fFPS);
	void Render_FrameMgr();
	bool FrameLock();

private:
	LARGE_INTEGER m_tBegin;
	LARGE_INTEGER m_tEnd;
	LARGE_INTEGER m_tCPUTick;

	TCHAR m_szFPS[32];

	float m_fSPF;
	float m_fDeltaTime;
	float m_fFPSTime;
	int m_iFPS;

};

#endif // !__FRAMEMGR_H__