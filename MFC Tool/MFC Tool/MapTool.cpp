// MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFC ToolView.h"


// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{
}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_MAP_PICTURE, m_MapPicture);
}

BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelchangeMapTexture)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON5, &CMapTool::OnBnClickedLoad)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.


void CMapTool::OnDropFiles(HDROP hDropInfo)
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


void CMapTool::OnLbnSelchangeMapTexture()
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

	wstrTextureName.Delete(0, i);
	m_dwDrawID = _ttoi(wstrTextureName.GetString());

	CGraphicDevice::getInstance()->BeginDraw();
	CGraphicDevice::getInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	const TEXINFO* pTexInfo = CTexturMgr::getInstance()->getTexture(L"Terrain", L"Tile", m_dwDrawID);
	if (pTexInfo == nullptr) return;

	float fX = WINCX / TILECX;
	float fY = WINCY / TILECY;
	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, fX, fY, 0.f);
	D3DXMatrixTranslation(&matTrans, 670.f, 360.f, 0.f);
	matWorld = matScale * matTrans;

	CGraphicDevice::getInstance()->GetSprite()->SetTransform(&matWorld);
	CGraphicDevice::getInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGraphicDevice::getInstance()->GetSprite()->End();
	CGraphicDevice::getInstance()->EndDraw(m_MapPicture.m_hWnd);
}


void CMapTool::OnBnClickedSave()
{
	CFileDialog Dlg(false, L"dat", L".dat");
	TCHAR szFilePath[MAX_PATH]{};

	GetCurrentDirectory(MAX_PATH, szFilePath);
	PathRemoveFileSpec(szFilePath);
	lstrcat(szFilePath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szFilePath;
	if (IDOK == Dlg.DoModal())
	{
		CString strFilePath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(strFilePath,GENERIC_WRITE,0,nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;

		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
		vector<TILE*>& vecTiles = pView->m_Terrain->GetTile();

		DWORD dwByte = 0;
		for (auto& pTile : vecTiles)
			WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		CloseHandle(hFile);
	}

}

void CMapTool::OnBnClickedLoad()
{
	CFileDialog Dlg(true, L"dat", L".dat");
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

		pView->m_Terrain->ReleaseTerrain();


		DWORD dwByte = 0;
		TILE* pTile = nullptr;
		while (true)
		{
			pTile = new TILE;
			ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				Safe_Delete(pTile);
				break;
			}

			pView->m_Terrain->AddTileData(pTile);
		}
		CloseHandle(hFile);

		pView->Invalidate();
	}
}
