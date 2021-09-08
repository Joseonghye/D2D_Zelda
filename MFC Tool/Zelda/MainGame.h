#pragma once
class CMainGame final
{
private:
	CMainGame();
public:
	~CMainGame();

public:
	HRESULT Initialized();
	void Update();
	void Render();
	void Release();

public:
	static CMainGame* Create();
};

