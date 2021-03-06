#pragma once


// CollisionTool 대화 상자입니다.

class CCollisionTool : public CDialog
{
	DECLARE_DYNAMIC(CCollisionTool)

public:
	CCollisionTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCollisionTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLISIONTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();

	afx_msg void OnBnClickedReset();
};
