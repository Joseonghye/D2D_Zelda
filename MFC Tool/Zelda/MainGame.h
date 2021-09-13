#pragma once
#ifndef __MAINGAME_H__
#define __MAINGAME_H__
#include "FrameMgr.h"

class CMainGame final
{
private:
	CMainGame();
public:
	~CMainGame();

public:
	HRESULT Initialized();
	void Update();
	void Render(CFrameMgr& rFrameMgr);
	void Release();

public:
	static CMainGame* Create();
};

#endif //__MAINGAME_H__