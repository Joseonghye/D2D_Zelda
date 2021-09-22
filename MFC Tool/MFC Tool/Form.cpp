// Form.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC Tool.h"
#include "Form.h"
#include "MainFrm.h"
#include "MFC ToolView.h"
#include "Mouse.h"

// Form

IMPLEMENT_DYNCREATE(Form, CFormView)

Form::Form()
	: CFormView(IDD_FORMVIEW)
{
	
}

Form::~Form()
{
	/*for (auto& rPair : m_InfoMap) {
		Safe_Delete(rPair.second);
	}
	m_InfoMap.clear();*/
}

void Form::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}

BEGIN_MESSAGE_MAP(Form, CFormView)
	ON_BN_CLICKED(IDC_BUTTON3, &Form::OnBnClickedMapTool)
	ON_BN_CLICKED(IDC_BUTTON1, &Form::OnBnClickedObjectTool)
//	ON_WM_DROPFILES()
//	ON_LBN_SELCHANGE(IDC_LIST1, &Form::OnLbnSelchangePickObejct)
//	ON_BN_CLICKED(IDC_BUTTON2, &Form::OnBnClickedLoad)
ON_BN_CLICKED(IDC_BUTTON8, &Form::OnBnClickedCollisionTool)
ON_BN_CLICKED(IDC_BUTTON10, &Form::OnBnClickedEventTool)
END_MESSAGE_MAP()


// Form 진단입니다.

#ifdef _DEBUG
void Form::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Form::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Form 메시지 처리기입니다.


void Form::OnBnClickedMapTool()
{
	if (nullptr == m_tMapTool.GetSafeHwnd())
		m_tMapTool.Create(IDD_MAPTOOL);
	m_tMapTool.ShowWindow(SW_SHOW);
}

void Form::OnBnClickedObjectTool()
{
	if (nullptr == m_tObjectTool.GetSafeHwnd())
		m_tObjectTool.Create(IDD_OBJECTTOOL);
	m_tObjectTool.ShowWindow(SW_SHOW);
}

/*
void Form::OnDropFiles(HDROP hDropInfo)
{
	//int iCount = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);
	//TCHAR szFilePath[MAX_PATH]{};

	//for (int i = 0; i < iCount; ++i)
	//{
	//	DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);
	//	CString wstrRelativePath = CFileInfo::ChangeRelativePath(szFilePath);
	//	TCHAR szFileName[MAX_PATH]{};
	//	CString wstrFileName = PathFindFileName(szFilePath);
	//	lstrcpy(szFileName, wstrFileName.GetString());
	//	PathRemoveExtension(szFileName);
	//	m_ListBox.AddString(szFileName);
	//}

	//m_ListBox.SetHorizontalExtent(800);
	//UpdateData(FALSE);


	CFormView::OnDropFiles(hDropInfo);
}

void Form::OnLbnSelchangePickObejct()
{
	//오브젝트 선택 
	int iIndex = m_ListBox.GetCurSel();
	CString wstrTextureName{};
	m_ListBox.GetText(iIndex, wstrTextureName);

	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 1));

	pView->m_Mouse->SetRenderObj(wstrTextureName);
}

void Form::OnBnClickedLoad()
{
	CFileDialog Dlg(true, L"dat", L"*.dat");

//	CFileDialog Dlg(true, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
//		, NULL, NULL, 0, FALSE);


	TCHAR szFilePath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szFilePath);
	PathRemoveFileSpec(szFilePath);
	lstrcat(szFilePath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;
	if (IDOK == Dlg.DoModal())
	{
		CString strFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;
		for (auto&rPair : m_InfoMap)
			Safe_Delete(rPair.second);
		m_InfoMap.clear();

		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		TCHAR* pStr = nullptr;
		OBJINFO* pInfo = nullptr;
		while (true)
		{
			pInfo = new OBJINFO;

			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			pStr = new TCHAR[dwStrByte];
			ReadFile(hFile, pStr, dwStrByte, &dwByte, nullptr);
			pInfo->strObjKey = pStr;
			delete[] pStr;
			pStr = nullptr;


			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			pStr = new TCHAR[dwStrByte];
			ReadFile(hFile, pStr, dwStrByte, &dwByte, nullptr);
			pInfo->strName = pStr;
			delete[] pStr;
			pStr = nullptr;


			ReadFile(hFile, &pInfo->bMove, sizeof(bool), &dwByte, nullptr);
			ReadFile(hFile, &pInfo->bDestroy, sizeof(bool), &dwByte, nullptr);
			ReadFile(hFile, &pInfo->eID, sizeof(OBJID), &dwByte, nullptr);

			if (0 == dwByte)
			{
				Safe_Delete(pInfo);
				break;
			}

			m_InfoMap.emplace(pInfo->strName, pInfo);
			m_ListBox.AddString(pInfo->strName);
		}
		CloseHandle(hFile);
	}
	
}
*/

void Form::OnBnClickedCollisionTool()
{
	if (nullptr == m_tCollTool.GetSafeHwnd())
		m_tCollTool.Create(IDD_COLLISIONTOOL);
	m_tCollTool.ShowWindow(SW_SHOW);
}


void Form::OnBnClickedEventTool()
{
	if (nullptr == m_tEventTool.GetSafeHwnd())
		m_tEventTool.Create(IDD_EVENTTOOL);
	m_tEventTool.ShowWindow(SW_SHOW);
}
