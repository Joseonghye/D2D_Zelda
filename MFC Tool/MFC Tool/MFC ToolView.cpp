
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCToolView

IMPLEMENT_DYNCREATE(CMFCToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMFCToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_DROPFILES()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
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
	CTexturMgr::DestoryInstacne();
	CGraphicDevice::DestoryInstacne();
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
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
	m_Terrain->RenderTerrain();
	m_Terrain->RenderObject();
	m_Terrain->RenderEvent();

	m_pDevice->GetSprite()->End();

	m_pDevice->getLine()->Begin();
	m_Terrain->RenderColl();
	m_pDevice->getLine()->End();

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
	CScrollView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
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
	CScrollView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize((TOTAL_TILEX *ROOM_TILEX)* TILECX, TILECY* (TOTAL_TILEY*ROOM_TILEY)));

	CMainFrame* pFrame = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	RECT rcFrameWindow;
	pFrame->GetWindowRect(&rcFrameWindow);
	SetRect(&rcFrameWindow, 0, 0, rcFrameWindow.right - rcFrameWindow.left, rcFrameWindow.bottom - rcFrameWindow.top);

	RECT rcView;
	GetClientRect(&rcView);
	int iRow = rcFrameWindow.right - rcView.right;
	int iCol = rcFrameWindow.bottom - rcView.bottom;

	pFrame->SetWindowPos(nullptr, 0, 0, WINCX + iRow, WINCY + iCol, SWP_NOMOVE);
	g_hWnd = m_hWnd;
	if (FAILED(CGraphicDevice::GetInstance()->Initialize()))
		AfxMessageBox(L"CDevice Create Fail");

	m_pDevice = CGraphicDevice::GetInstance();
	m_Terrain = Terrain::Create();
	m_Terrain->Set_View(this);

	//텍스쳐추가
	{
		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::MULTI, L"../Texture/Tile/tile%d.png", L"Terrain", L"Tile", 28);

		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::MULTI, L"../Texture/Monster/Octo/Walk/Octo0%d.png", L"Octo",L"Walk",2);
		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Monster/Goomba/Goomba.png", L"Goomba");
		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::MULTI, L"../Texture/Monster/HardHat/HardHat0%d.png", L"HardHat", L"Walk", 2);

		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/weed.png", L"Weed");
		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/Black.png", L"BlackStone");

		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/Up.png", L"Up");
		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/Down.png", L"Down");
		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/Left.png", L"Left");
		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/Right.png", L"Right");

		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Event/Check.png", L"Check");
		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Event/Button.png", L"Button");
		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Event/Open.png", L"Open");
		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Event/Close.png", L"Close");

		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/Door/Door00.png", L"Door_FORNT");
		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/Door/Door_Left00.png", L"Door_LEFT");
		CTexturMgr::GetInstance()->InsertTexture(TEXTYPE::SINGLE, L"../Texture/Object/Door/Door_Right00.png", L"Door_RIGHT");
	}
}

void CMFCToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	Form* pForm = dynamic_cast<Form*>(pMain->m_SecSplitter.GetPane(1, 0));

	D3DXVECTOR3 vMouse = { float(point.x + GetScrollPos(SB_HORZ)), float(point.y + GetScrollPos(SB_VERT)) , 0.f };

	//타일 변경
	if(pForm->m_tMapTool.GetSafeHwnd())
		if (pForm->m_tMapTool.IsWindowVisible()) {
			if (pForm->m_tMapTool.GetStart()) 
			{
				pForm->m_tMapTool.SetStartFalse();
				m_Terrain->SetStartPos(vMouse);
			}
			else
				m_Terrain->ChangeTile(vMouse, pForm->m_tMapTool.GetDrawID());
		}
	//오브젝트 배치 
	if(pForm->m_tObjectTool.GetSafeHwnd())
		if(pForm->m_tObjectTool.IsWindowVisible())
			m_Terrain->AddObj(vMouse, pForm->m_tObjectTool.GetObjINFO().strName);

	//충돌박스 설치 
	if (pForm->m_tCollTool.GetSafeHwnd())
		if (pForm->m_tCollTool.IsWindowVisible())
			m_Terrain->AddCollision(vMouse);

	if (pForm->m_tEventTool.GetSafeHwnd())
		if (pForm->m_tEventTool.IsWindowVisible()) {
			m_Terrain->AddEvent(vMouse, pForm->m_tEventTool.GetEventInfo());
		}

	CScrollView::OnLButtonDown(nFlags, point);
}


void CMFCToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	Form* pForm = dynamic_cast<Form*>(pMain->m_SecSplitter.GetPane(1, 0));

	D3DXVECTOR3 vMouse = { float(point.x + GetScrollPos(SB_HORZ)), float(point.y + GetScrollPos(SB_VERT)) , 0.f };

	//오브젝트 삭제
	if (pForm->m_tObjectTool.GetSafeHwnd())
		if (pForm->m_tObjectTool.IsWindowVisible())
			m_Terrain->DeleteObject(vMouse);

	//충돌박스 삭제  
	if (pForm->m_tCollTool.GetSafeHwnd())
		if (pForm->m_tCollTool.IsWindowVisible())
			m_Terrain->DeleteColl(vMouse);

	//이벤트 삭제
	if (pForm->m_tEventTool.GetSafeHwnd())
		if (pForm->m_tEventTool.IsWindowVisible())
			m_Terrain->DeleteEvent(vMouse);

	CScrollView::OnRButtonDown(nFlags, point);
}
