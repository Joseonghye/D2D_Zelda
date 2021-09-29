#pragma once
#ifndef __THREEOFONE_H__
#define __THREEOFONE_H__

#include "Monster.h"
class CKind;
class CThreeOfOne : public CMonster
{
public:
	CThreeOfOne();
	virtual ~CThreeOfOne();

	// CMonster을(를) 통해 상속됨
	virtual HRESULT Initialized_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Damaged(int Att) override {}
	virtual void Attack() override {}

public:
	static CThreeOfOne* Create(MONSTERID eID);

	void SetKind(CKind* pKind) { if (m_vecKind.size() > 3) return; m_vecKind.push_back(pKind); }
	int GetSize() { return m_vecKind.size(); }

private:
	vector<CKind*> m_vecKind;
};
#endif // !__THREEOFONE_H__