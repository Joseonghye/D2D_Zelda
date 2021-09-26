#pragma once
#include "Equipment.h"
class CShield :
	public CEquipment
{
public:
	CShield();
	~CShield();

	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

	virtual void StartUsing(DIR _dir) override;
	virtual void Using() override;

};

