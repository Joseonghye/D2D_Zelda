// CollisionTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC Tool.h"
#include "CollisionTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFC ToolView.h"

// CollisionTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCollisionTool, CDialog)

CCollisionTool::CCollisionTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_COLLISIONTOOL, pParent)
{

}

CCollisionTool::~CCollisionTool()
{
}

void CCollisionTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCollisionTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CCollisionTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON8, &CCollisionTool::OnBnClickedLoad)
END_MESSAGE_MAP()


// CollisionTool 메시지 처리기입니다.


void CCollisionTool::OnBnClickedSave()
{
	CFileDialog Dlg(false, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		, NULL, NULL, 0, FALSE);

	//CFileDialog Dlg(false, L"dat", L".dat");
	TCHAR szFilePath[MAX_PATH]{};

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
		map<int,D3DXVECTOR3>& vecTiles = pView->m_Terrain->GetColl();

		DWORD dwByte = 0;
		for (auto& pColl : vecTiles) 
		{
			WriteFile(hFile, &pColl.first, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &pColl.second, sizeof(D3DXVECTOR3), &dwByte, nullptr);
		}
		CloseHandle(hFile);
	}
}


void CCollisionTool::OnBnClickedLoad()
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

		pView->m_Terrain->ReleaseColl();


		DWORD dwByte = 0;
		int iIndex = -1;
		D3DXVECTOR3 vPos;
		while (true)
		{
			ReadFile(hFile, &iIndex, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &vPos, sizeof(D3DXVECTOR3), &dwByte, nullptr);

			if (0 == dwByte)
			{
				break;
			}

			pView->m_Terrain->AddCollData(iIndex, vPos);
		}
		CloseHandle(hFile);

		pView->Invalidate();
	}
}
