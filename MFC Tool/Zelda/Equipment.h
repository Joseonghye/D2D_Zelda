#pragma once
#include "GameObject.h"

class CBoxCollider;
class CEquipment : public CGameObject
{
public:
	CEquipment();
	~CEquipment();

	void SetPlayer(CGameObject* player) { m_pPlayer = player; }
	virtual void StartUsing(DIR _dir) {};
	
protected:
	virtual void Using() {};

protected:
	CGameObject* m_pPlayer;
	CBoxCollider* m_Collider;
	bool m_bUse;



	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialized_GameObject() override;

	virtual int Update_GameObject() override;

	virtual void LateUpdate_GameObject() override;

	virtual void Render_GameObject() override;

	virtual void Release_GameObject() override;

};

