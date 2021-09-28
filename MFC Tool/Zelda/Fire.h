#pragma once
#include "InteractionObj.h"
class CFire : public CInteractionObj
{
public:
	CFire();
	virtual ~CFire();

	// CInteractionObj��(��) ���� ��ӵ�
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Render_GameObject() override {}

public:
	static CFire* Create();

	virtual void Damaged() override {}
	virtual bool Pushed(DIR _dir) override { return false; }
};

