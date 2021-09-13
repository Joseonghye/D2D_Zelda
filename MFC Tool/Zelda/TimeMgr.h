#pragma once
#ifndef __TIMEMANAGER_H__
#define __TIMEMANAGER_H__
#include "SingleTon.h"

class CTimeMgr : public CSingleTon<CTimeMgr>
{
	friend CSingleTon;
private:
	CTimeMgr();
	~CTimeMgr();

public:
	float Get_DeltaTime() {	return m_fDeltaTime; }
public:
	HRESULT Initialized_TimeMgr();
	void Update_TimeMgr();
private:
	LARGE_INTEGER m_tBegin;
	LARGE_INTEGER m_tEnd;
	LARGE_INTEGER m_tCPUTick;

	float m_fDeltaTime;
};

#endif // !__TIMEMANAGER_H__
