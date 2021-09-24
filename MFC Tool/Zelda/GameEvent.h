#pragma once
#ifndef __GAMEEVENT_H__
#define __GAMEEVENT_H__

#include "GameObject.h"
class CGameEvent :public CGameObject
{
public:
	CGameEvent(){}
	virtual ~CGameEvent(){}

public:
	virtual void Using() = 0;
	void SetEventID(int iID) { m_iEventID = iID; }
	int GetEventID() { return m_iEventID; }

protected:
	int m_iEventID;
};

#endif // !__GAMEEVENT_H__
