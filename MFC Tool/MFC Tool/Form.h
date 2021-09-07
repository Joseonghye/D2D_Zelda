#pragma once

#include "ObjectTool.h"
#include "MapTool.h"

// Form 폼 뷰입니다.
class Form : public CFormView
{
	DECLARE_DYNCREATE(Form)

protected:
	Form();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~Form();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMapTool();
	afx_msg void OnBnClickedObjectTool();

	/*
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLbnSelchangePickObejct();
	afx_msg void OnBnClickedLoad();
	*/

public:
	CMapTool m_tMapTool;
	CObjectTool m_tObjectTool;

	//CListBox m_ListBox;
	//map<CString, OBJINFO*> m_InfoMap;
	
};


