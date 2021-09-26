#pragma once
#include "GameObject.h"

class CBoxCollider;
class CEquipment : public CGameObject
{
public:
	CEquipment() {};
	virtual ~CEquipment() {};

public:
	void SetPlayer(CGameObject* player) { m_pPlayer = player; }
	virtual void StartUsing(DIR _dir) = 0;
	
	void SetUse(bool bUse) { m_bUse = bUse; }
	bool isUsing() { return m_bUse; }
	
protected:
	virtual void Using() = 0;

protected:
	CGameObject* m_pPlayer;
	CBoxCollider* m_Collider;
	bool m_bUse;



	

};

