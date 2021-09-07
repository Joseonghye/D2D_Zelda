
// MFC ToolView.cpp : CMFCToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC Tool.h"
#endif

#include "MFC ToolDoc.h"
#include "MFC ToolView.h"
#include "MainFrm.h"
#include "Form.h"
#include "Mouse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCToolView

IMPLEMENT_DYNCREATE(CMFCToolView, CView)

BEGIN_MESSAGE_MAP(CMFCToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DROPFILES()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCToolView 생성/소멸
HWND g_hWnd;
CMFCToolView::CMFCToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCToolView::~CMFCToolView()
{
	Safe_Delete(m_Terrain);
	Safe_Delete(m_Mouse);
	CTexturMgr::DestoryInstacne();
	CGraphicDevice::DestoryInstacne();
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCToolView 그리기

void CMFCToolView::OnDraw(CDC* /*pDC*/)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_pDevice->BeginDraw();
	m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	m_Mouse->RenderMouse(m_hWnd);
	m_pDevice->GetSprite()->End();
	m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	m_Terrain->RenderTerrain();
	m_Terrain->RenderObject();

	m_pDevice->GetSprite()->End();
	m_pDevice->EndDraw();


	Invalidate(false);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMFCToolView 인쇄

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCToolView 진단

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView 메시지 처리기
void CMFCToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	RECT rcFrameWindow;
	pFrame->GetWindowRect(&rcFrameWindow);
	SetRect(&rcFrameWindow, 0, 0, rcFrameWindow.right - rcFrameWindow.left, rcFrameWindow.bottom - rcFrameWindow.top);

	RECT rcView;
	GetClientRect(&rcView);
	int iRow = rcFrameWindow.right - rcView.right;
	int iCol = rcFrameWindow.bottom - rcView.bottom;

	pFrame->SetWindowPos(nullptr, 0, 0, WINCX + iRow, WINCY + iCol, SWP_NOZORDER);
	g_hWnd = m_hWnd;
	if (FAILED(CGraphicDevice::getInstance()->Initialize()))
		AfxMessageBox(L"CDevice Create Fail");

	m_pDevice = CGraphicDevice::getInstance();
	
	m_Terrain = Terrain::Create();

	//텍스쳐추가
	{
		CTexturMgr::getInstance()->InsertTexture(TEXTYPE::MULTI, L"../Texture/Tile/tile0%d.png", L"Terrain", L"Tile", 9);

		CTexturMgr::getInstance()->InsertTexture(TEXTYPE::MULTI, L"../Texture/Monster/Octo/Walk/Octo0%d.png", L"Octo",L"Walk",2);
		CTexturMgr::getInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Monster/Goomba/Goomba.png", L"Goomba");
	}
	m_Mouse = Mouse::getInstance();
}

void CMFCToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CView::OnLButtonDown(nFlags, point);
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	Form* pForm = dynamic_cast<Form*>(pMain->m_SecSplitter.GetPane(1, 0));

	D3DXVECTOR3 vMouse = { float(point.x + GetScrollPos(SB_HORZ)), float(point.y + GetScrollPos(SB_VERT)) , 0.f };

	//타일 변경
	//if(pForm->m_tMapTool.IsWindowVisible())
	//	m_Terrain->ChangeTile(vMouse, pForm->m_tMapTool.GetDrawID());

	//오브젝트 배치 
//	if(pForm->m_tObjectTool.IsWindowVisible())
		m_Terrain->AddObj(vMouse, pForm->m_tObjectTool.GetObjINFO().strName);

	/*
	//오브젝트 배치?
	CString str;
	int iIndex = pForm->m_ListBox.GetCurSel();
	pForm->m_ListBox.GetText(iIndex,str);

	auto& iter = pForm->m_InfoMap.find(str);

	m_pDevice->BeginDraw();
	m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	m_Mouse->RenderObj(m_hWnd, iter->second);

	m_pDevice->GetSprite()->End();
	m_pDevice->EndDraw();

	Invalidate(false);
	*/

}
