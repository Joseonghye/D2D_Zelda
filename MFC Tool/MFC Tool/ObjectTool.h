#pragma once
#include "afxwin.h"

// CObjectTool ��ȭ �����Դϴ�.

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
	CObjectTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CObjectTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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

	// enum���� �߰� �ϸ� �˴ϴ�.
	CComboBox m_tComboBox;
	CButton m_tMoveCheck[2];
	CButton m_tDestroyCheck[2];
	
	CString m_tName;
	map<CString, OBJINFO*> m_ObjInfoMap;

	OBJINFO* m_tObjInfo;
};
