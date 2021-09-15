#pragma once
#include "InteractionObj.h"
class CWeed : public CInteractionObj
{
private:
	CWeed();
public:
	~CWeed();

	// CInteractionObj��(��) ���� ��ӵ�
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

	virtual void Damaged() override;
	virtual bool Pushed(DIR _dir) override;
public:
	static CWeed* Create();
};

