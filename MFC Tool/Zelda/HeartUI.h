#pragma once
#include "GameObject.h"
class CHeartUI : public CGameObject
{
public:
	CHeartUI();
	virtual ~CHeartUI();

	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override{}
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override{}

	void SetHeart(int hp);

	void SetTransMat() {
		D3DXMatrixTranslation(&m_tInfo.matTrans,
			m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	}

private:
	wstring m_wstrState;
};

