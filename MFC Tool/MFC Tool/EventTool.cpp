// EventTool.cpp : implementation file
//

#include "stdafx.h"
#include "MFC Tool.h"
#include "EventTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFC ToolView.h"

// CEventTool dialog

IMPLEMENT_DYNAMIC(CEventTool, CDialog)

CEventTool::CEventTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_EVENTTOOL, pParent)
	, m_tValue(_T(""))
{

}

CEventTool::~CEventTool()
{
}

void CEventTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_tPictureListBox);
	DDX_Control(pDX, IDC_COMBO1, m_tComboBox);
	DDX_Text(pDX, IDC_EDIT2, m_tValue);
}

BOOL CEventTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_tComboBox.AddString(L"Button");
	m_tComboBox.AddString(L"Check");
	m_tComboBox.AddString(L"Open");
	m_tComboBox.AddString(L"Close");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BEGIN_MESSAGE_MAP(CEventTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON13, &CEventTool::OnBnClickedEventObjSave)
	ON_BN_CLICKED(IDC_BUTTON14, &CEventTool::OnBnClickedEventObjLoad)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CEventTool::OnLbnSelchangeTexture)
END_MESSAGE_MAP()

void CEventTool::OnBnClickedEventObjSave()
{
	CFileDialog Dlg(false, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		, NULL, NULL, 0, FALSE);

	//CFileDialog Dlg(false, L"dat", L"*.dat");
	TCHAR szFilePath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szFilePath);
	PathRemoveFileSpec(szFilePath);
	lstrcat(szFilePath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;
	if (IDOK == Dlg.DoModal())
	{
		CString strFilePath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(strFilePath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;

		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
		map<int, EVENTINFO*>& objList = pView->m_Terrain->GetEvent();


		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		for (auto& pObj : objList)
		{
			WriteFile(hFile, &pObj.first, sizeof(int), &dwByte, nullptr);

			WriteFile(hFile, &pObj.second->iEventID, sizeof(int), &dwByte, nullptr);

			dwStrByte = (lstrlen(pObj.second->strValue) + 1) * sizeof(wchar_t);
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, pObj.second->strValue, dwStrByte, &dwByte, nullptr);


			WriteFile(hFile, &pObj.second->vPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
		}
		CloseHandle(hFile);
	}
}


void CEventTool::OnBnClickedEventObjLoad()
{
	CFileDialog Dlg(true, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		, NULL, NULL, 0, FALSE);

	//CFileDialog Dlg(true, L"dat", L".dat");
	TCHAR szFilePath[MAX_PATH]{};

	GetCurrentDirectory(MAX_PATH, szFilePath);
	PathRemoveFileSpec(szFilePath);
	lstrcat(szFilePath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;
	if (IDOK == Dlg.DoModal())
	{
		CString strFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);;
		if (INVALID_HANDLE_VALUE == hFile)
			return;

		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 1));

		pView->m_Terrain->ReleaseEvent();

		DWORD dwByte = 0;
		DWORD dwStrByte = 0;

		int index = 0;
		TCHAR* pStr = nullptr;
	
		while (true)
		{
			ReadFile(hFile, &index, sizeof(int), &dwByte, nullptr);

			EVENTINFO* pInfo = new EVENTINFO;
			ReadFile(hFile, &pInfo->iEventID, sizeof(int), &dwByte, nullptr);

			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			pStr = new TCHAR[dwStrByte];
			ReadFile(hFile, pStr, dwStrByte, &dwByte, nullptr);

		
			ReadFile(hFile, pInfo->vPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);

			if (0 == dwByte)
			{
				Safe_Delete(pInfo);
				break;
			}
			pInfo->strValue = pStr;
			pView->m_Terrain->AddEventData(index, pInfo);

			delete[] pStr;
			pStr = nullptr;
		}
		CloseHandle(hFile);

		pView->Invalidate();
	}
}


void CEventTool::OnDropFiles(HDROP hDropInfo)
{
	int iCount = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);
	TCHAR szFilePath[MAX_PATH]{};

	for (int i = 0; i < iCount; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);
		CString wstrRelativePath = CFileInfo::ChangeRelativePath(szFilePath);

		TCHAR szFileName[MAX_PATH]{};
		CString wstrFileName = PathFindFileName(szFilePath);
		lstrcpy(szFileName, wstrFileName.GetString());
		PathRemoveExtension(szFileName);

		m_tPictureListBox.AddString(szFileName);
	}

	m_tPictureListBox.SetHorizontalExtent(800);
	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}

void CEventTool::OnLbnSelchangeTexture()
{
	int iIndex = m_tPictureListBox.GetCurSel();

	CString wstrTextureName;
	m_tPictureListBox.GetText(iIndex, wstrTextureName);

	int iTextureNameSize = wstrTextureName.GetLength();

	int i = 0;

	for (; i < iTextureNameSize; ++i)
	{
		if (isdigit(wstrTextureName[i]))
			break;
	}
	if (i != 0)
		wstrTextureName.Delete(i, iTextureNameSize - 1);

	CGraphicDevice::GetInstance()->BeginDraw();
	CGraphicDevice::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	const TEXINFO* pTexInfo = CTexturMgr::GetInstance()->getTexture(wstrTextureName.GetString(), L"Walk");
	if (nullptr == pTexInfo)
		return;

}

EVENTINFO * CEventTool::GetEventInfo()
{
	UpdateData(TRUE);
	EVENTINFO* pInfo = new EVENTINFO;

	pInfo->iEventID = int(m_tComboBox.GetCurSel());
	pInfo->strValue = m_tValue;

	UpdateData(FALSE);
	return pInfo;
}



