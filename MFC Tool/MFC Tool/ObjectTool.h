#pragma once
#include "afxwin.h"

// CObjectTool 대화 상자입니다.

typedef struct tagObjInfo
{
	CString strObjKey;
	CString strName;
	OBJID eID;
	bool bMove;
	bool bDestroy;

}OBJINFO;

class CObjectTool : public CDialog
{
	DECLARE_DYNAMIC(CObjectTool)

public:
	CObjectTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CObjectTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	bool CheckRadioBtn(const CButton* pBtn);
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLbnSelchangeTexture();
	afx_msg void OnLbnSelchangeObject();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedInitialize();
	afx_msg void OnBnClickedDelete();

	afx_msg void OnBnClickedListSave();
	afx_msg void OnBnClickedListLoad();

	afx_msg void OnBnClickedObjSave();
	afx_msg void OnBnClickedObjLoad();
	
public:
	OBJINFO GetObjINFO() { return *m_tObjInfo; }

public:
	CStatic m_Picture;
	CListBox m_ListBox;
	CListBox m_tObjListBox;

	// enum값을 추가 하면 됩니다.
	CComboBox m_tComboBox;
	CButton m_tMoveCheck[2];
	CButton m_tDestroyCheck[2];
	
	CString m_tName;
	map<CString, OBJINFO*> m_ObjInfoMap;

	OBJINFO* m_tObjInfo;
};
