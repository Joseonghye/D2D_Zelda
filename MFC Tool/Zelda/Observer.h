#pragma once
class CObserver
{
public:
	CObserver() {};
	virtual ~CObserver() {};

	virtual void OnNotify() = 0;
};

