#pragma once
#include "Equipment.h"
class CKey :
	public CEquipment
{
public:
	CKey();
	~CKey();

public:
	// Inherited via CGameObject
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

	// CEquipment을(를) 통해 상속됨
	virtual void StartUsing(DIR _dir) override;

	static CKey* Create();

protected:
	virtual void Using() {};


};

