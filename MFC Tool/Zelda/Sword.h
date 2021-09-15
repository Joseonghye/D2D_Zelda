#pragma once
#include "Equipment.h"

class CSword : public CEquipment
{
public:
	CSword();
	~CSword();

	// Inherited via CGameObject
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

	// CEquipment을(를) 통해 상속됨
	virtual void StartUsing(DIR _dir) override;

private:
	virtual void Using() override;
	void SetAngle(DIR _dir);

private:
	float m_fAngle;
	float m_fStartAngle;

};

