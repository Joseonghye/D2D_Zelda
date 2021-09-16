// ObjectTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC Tool.h"
#include "ObjectTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFC ToolView.h"

// CObjectTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CObjectTool, CDialog)

CObjectTool::CObjectTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OBJECTTOOL, pParent)
	, m_tName(_T(""))
{

}

CObjectTool::~CObjectTool()
{
}

void CObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_COMBO1, m_tComboBox);
	DDX_Control(pDX, IDC_RADIO1, m_tMoveCheck[0]);
	DDX_Control(pDX, IDC_RADIO3, m_tMoveCheck[1]);
	DDX_Control(pDX, IDC_RADIO2, m_tDestroyCheck[0]);
	DDX_Control(pDX, IDC_RADIO4, m_tDestroyCheck[1]);
	DDX_Control(pDX, IDC_LIST2, m_tObjListBox);
	DDX_Text(pDX, IDC_EDIT1, m_tName);
}


BEGIN_MESSAGE_MAP(CObjectTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CObjectTool::OnLbnSelchangeTexture)
	ON_LBN_SELCHANGE(IDC_LIST2, &CObjectTool::OnLbnSelchangeObject)
	ON_BN_CLICKED(IDC_BUTTON1, &CObjectTool::OnBnClickedInitialize)
	ON_BN_CLICKED(IDC_BUTTON2, &CObjectTool::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BUTTON3, &CObjectTool::OnBnClickedListSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CObjectTool::OnBnClickedListLoad)
	ON_BN_CLICKED(IDC_BUTTON6, &CObjectTool::OnBnClickedObjSave)
	ON_BN_CLICKED(IDC_BUTTON7, &CObjectTool::OnBnClickedObjLoad)
END_MESSAGE_MAP()


// CObjectTool 메시지 처리기입니다.


void CObjectTool::OnDropFiles(HDROP hDropInfo)
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

		m_ListBox.AddString(szFileName);
	}

	m_ListBox.SetHorizontalExtent(800);
	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}

void CObjectTool::OnLbnSelchangeTexture()
{
	int iIndex = m_ListBox.GetCurSel();

	CString wstrTextureName;
	m_ListBox.GetText(iIndex, wstrTextureName);

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

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 50.f, 50.f, 0);
	D3DXMatrixTranslation(&matTrans, 700.f,500.f, 0.f);
	matWorld = matScale * matTrans;

	CGraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CGraphicDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGraphicDevice::GetInstance()->GetSprite()->End();
	CGraphicDevice::GetInstance()->EndDraw(m_Picture.m_hWnd);
}

void CObjectTool::OnLbnSelchangeObject()
{
	int iIndex = m_tObjListBox.GetCurSel();
	CString wstrName;
	m_tObjListBox.GetText(iIndex, wstrName);

	auto& iter = m_ObjInfoMap.find(wstrName);
	if (iter == m_ObjInfoMap.end()) return;

	m_tObjInfo = iter->second;


}

BOOL CObjectTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_tComboBox.AddString(L"---");
	m_tComboBox.AddString(L"Player");
	m_tComboBox.AddString(L"Monster");
	m_tComboBox.AddString(L"Interaction");
	m_tComboBox.AddString(L"Potal");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CObjectTool::OnBnClickedInitialize()
{
	//리스트에 추가 
	UpdateData(TRUE);
	auto& iter = m_ObjInfoMap.find(m_tName);
	if (iter != m_ObjInfoMap.end())
		return;

	OBJINFO* tInfo = new OBJINFO ;
	int iIndex = m_ListBox.GetCurSel();
	m_ListBox.GetText(iIndex,tInfo->strObjKey);

	tInfo->strName = m_tName;
	tInfo->eID = OBJID(m_tComboBox.GetCurSel());
	tInfo->bMove = CheckRadioBtn(m_tMoveCheck);
	tInfo->bDestroy = CheckRadioBtn(m_tDestroyCheck);
	
	m_ObjInfoMap.emplace(m_tName, tInfo);

	m_tObjListBox.AddString(tInfo->strName);

	UpdateData(FALSE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CObjectTool::OnBnClickedDelete()
{
	UpdateData(TRUE);
	int index = m_tObjListBox.GetCurSel();

	CString wstrFindName;
	m_tObjListBox.GetText(index, wstrFindName);

	auto &iter_Find = m_ObjInfoMap.find(wstrFindName);

	if (iter_Find == m_ObjInfoMap.end())
		return;

	Safe_Delete(iter_Find->second);
	m_ObjInfoMap.erase(iter_Find);
	m_tObjListBox.DeleteString(index);

	UpdateData(FALSE);
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

bool CObjectTool::CheckRadioBtn(const CButton* pBtn)
{
	if (pBtn[0].GetCheck())
		return true;
	else
		return false;
}

void CObjectTool::OnBnClickedListSave()
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
		HANDLE hFile = CreateFile(strFilePath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);;
		if (INVALID_HANDLE_VALUE == hFile)
			return;
		
		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		for (auto& rPair : m_ObjInfoMap)
		{
			//objkey값 저장
		/*	dwStrByte = (rPair.second->strObjKey.GetLength() + 1) * sizeof(wchar_t);
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, rPair.second->strObjKey.GetString(), dwStrByte, &dwByte, nullptr);*/
			
			//objName저장
			dwStrByte = (rPair.second->strName.GetLength() + 1) * sizeof(wchar_t);
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, rPair.second->strName.GetString(), dwStrByte, &dwByte, nullptr);

			WriteFile(hFile, &rPair.second->eID, sizeof(OBJID), &dwByte, nullptr);

			WriteFile(hFile, &rPair.second->bMove, sizeof(bool), &dwByte, nullptr);
			WriteFile(hFile, &rPair.second->bDestroy, sizeof(bool), &dwByte, nullptr);
	
		}
		CloseHandle(hFile);
	}
}

void CObjectTool::OnBnClickedListLoad()
{
	CFileDialog Dlg(true, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
			, NULL, NULL, 0, FALSE);
	//CFileDialog Dlg(true, L"dat", L"*.dat");

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

		m_ListBox.ResetContent();
		m_tObjListBox.ResetContent();

		for (auto&rPair : m_ObjInfoMap)
			Safe_Delete(rPair.second);

		m_ObjInfoMap.clear();

		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		TCHAR* pStr = nullptr;
		OBJINFO* pInfo = nullptr;

		while (true)
		{
			pInfo = new OBJINFO;

	/*		ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			pStr = new TCHAR[dwStrByte];
			ReadFile(hFile, pStr, dwStrByte, &dwByte, nullptr);
			pInfo->strObjKey = pStr;

			delete[] pStr;
			pStr = nullptr;*/


			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			pStr = new TCHAR[dwStrByte];
			ReadFile(hFile, pStr, dwStrByte, &dwByte, nullptr);
			pInfo->strName = pStr;

			delete[] pStr;
			pStr = nullptr;

			ReadFile(hFile, &pInfo->eID, sizeof(OBJID), &dwByte, nullptr);

			ReadFile(hFile, &pInfo->bMove, sizeof(bool), &dwByte, nullptr);
			ReadFile(hFile, &pInfo->bDestroy, sizeof(bool), &dwByte, nullptr);
		

			if (0 == dwByte)
			{
				Safe_Delete(pInfo);
				break;
			}

			m_ObjInfoMap.emplace(pInfo->strName, pInfo);
			m_tObjListBox.AddString(pInfo->strName);
		}
		CloseHandle(hFile);
	}

}


void CObjectTool::OnBnClickedObjSave()
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
		map<int,OBJDATA*>& objList = pView->m_Terrain->GetObj();


		DWORD dwByte = 0;
		DWORD dwStrByte = 0;
		for (auto& pObj : objList) 
		{
			WriteFile(hFile, &pObj.first, sizeof(int), &dwByte, nullptr);

			dwStrByte = (lstrlen(pObj.second->szName) + 1) * sizeof(wchar_t);
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, pObj.second->szName, dwStrByte, &dwByte, nullptr);

			WriteFile(hFile, &pObj.second->m_tInfo, sizeof(INFO), &dwByte, nullptr);
		}
		CloseHandle(hFile);
	}
}

void CObjectTool::OnBnClickedObjLoad()
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

		pView->m_Terrain->ReleaseObject();

		DWORD dwByte = 0;
		DWORD dwStrByte = 0;

		int index = 0;
		TCHAR* pStr = nullptr;
		INFO* pInfo = nullptr;
		while (true)
		{
			ReadFile(hFile, &index, sizeof(int), &dwByte, nullptr);

			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			pStr = new TCHAR[dwStrByte];
			ReadFile(hFile, pStr, dwStrByte, &dwByte, nullptr);

			pInfo = new INFO;
			ReadFile(hFile, pInfo, sizeof(INFO), &dwByte, nullptr);

			if (0 == dwByte)
			{
				Safe_Delete(pInfo);
				break;
			}
			OBJDATA* data = new OBJDATA;
			lstrcpy(data->szName, pStr);

			data->m_tInfo = *pInfo;

			pView->m_Terrain->AddObjData(index,data);

			delete[] pStr;
			pStr = nullptr;
		}
		CloseHandle(hFile);

		pView->Invalidate();
	}
}
