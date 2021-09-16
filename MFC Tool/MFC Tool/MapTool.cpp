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
	ON_BN_CLICKED(IDC_BUTTON9, &CMapTool::OnBnClickedSetStart)
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

	CGraphicDevice::GetInstance()->BeginDraw();
	CGraphicDevice::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	const TEXINFO* pTexInfo = CTexturMgr::GetInstance()->getTexture(L"Terrain", L"Tile", m_dwDrawID);
	if (pTexInfo == nullptr) return;

	float fX = WINCX / TILECX;
	float fY = WINCY / TILECY;
	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, fX, fY, 0.f);
	D3DXMatrixTranslation(&matTrans, 670.f, 360.f, 0.f);
	matWorld = matScale * matTrans;

	CGraphicDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);
	CGraphicDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &pTexInfo->tCenter, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CGraphicDevice::GetInstance()->GetSprite()->End();
	CGraphicDevice::GetInstance()->EndDraw(m_MapPicture.m_hWnd);
}


void CMapTool::OnBnClickedSave()
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

		HANDLE hFile = CreateFile(strFilePath,GENERIC_WRITE,0,nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;

		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_MainSplitter.GetPane(0, 1));
		vector<TILE*>& vecTiles = pView->m_Terrain->GetTile();

		DWORD dwByte = 0;

		//전체타일 3360
		//int RoomTile = (ROOM_TILEX*ROOM_TILEY); //80

		//for (int totalY = 0; totalY < TOTAL_TILEY; ++totalY) //6
		//{
		//	for (int totalX = 0; totalX < TOTAL_TILEX; ++totalX) //7
		//	{
		//		for (int j = 0; j < ROOM_TILEY; ++j) //8 
		//		{
		//			for (int i = 0; i < ROOM_TILEX; ++i) //10
		//			{
		//				int index = ((RoomTile*TOTAL_TILEX)* totalY) + (ROOM_TILEX * totalX) + i + (TOTAL_TILEX * ROOM_TILEX * j);
		//				TILE tile = *vecTiles[index];
		//				
		//				WriteFile(hFile,&tile, sizeof(TILE), &dwByte, nullptr);
		//			}
		//		}
		//	}
		//}

		for (auto& pTile : vecTiles)
			WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		CloseHandle(hFile);
	}

}

void CMapTool::OnBnClickedLoad()
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

		pView->m_Terrain->ReleaseTerrain();


		DWORD dwByte = 0;
		TILE* pTile = nullptr;

	//	int i = 0;

		int totalX = 0;
		int totalY = 0;
		int x = 0;
		int y = 0;

		while (true)
		{
			
			pTile = new TILE;
			ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				Safe_Delete(pTile);
				break;
			}

		/*	++x;
			if (x == ROOM_TILEX)
			{
				y++;
				x = 0;

				if (y == ROOM_TILEY)
				{
					totalX++;
					y = 0;

					if (totalX == TOTAL_TILEX)
					{
						totalY++;
						totalX = 0;
					}

				}
			}

			int index = (((ROOM_TILEX*ROOM_TILEY)*TOTAL_TILEX)* totalY) + ((ROOM_TILEX * totalX) + x) + (TOTAL_TILEX * ROOM_TILEX * y);
*/
			pView->m_Terrain->AddTileData(pTile);
		}
		CloseHandle(hFile);

		pView->Invalidate();
	}
}


void CMapTool::OnBnClickedSetStart()
{
	m_bStart = true;
}
