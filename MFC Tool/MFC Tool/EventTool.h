#pragma once
#include "afxwin.h"
// CEventTool dialog


class CEventTool : public CDialog
{
	DECLARE_DYNAMIC(CEventTool)

public:
	CEventTool(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEventTool();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EVENTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedEventObjSave();
	afx_msg void OnBnClickedEventObjLoad();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLbnSelchangeTexture();

	EVENTINFO* GetEventInfo();

public:
	CListBox m_tPictureListBox;
	CComboBox m_tComboBox;

	CString m_tValue;
};
