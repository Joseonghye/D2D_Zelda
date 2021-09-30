#pragma once
#include "GameObject.h"
class CBottomUI :
	public CGameObject
{
public:
	CBottomUI();
	virtual ~CBottomUI();

	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;

	static CBottomUI* Create();

	void SetTransMat() {
		D3DXMatrixTranslation(&m_tInfo.matTrans,
			m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	}
};

