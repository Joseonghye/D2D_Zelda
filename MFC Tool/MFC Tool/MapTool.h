#pragma once
#include "afxwin.h"


// CMapTool ��ȭ �����Դϴ�.

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMapTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLbnSelchangeMapTexture();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();

	const DWORD GetDrawID() const { return m_dwDrawID; }

private:
	CListBox m_ListBox;
	CStatic m_MapPicture;

	DWORD m_dwDrawID;
	
};