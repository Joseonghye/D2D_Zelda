// MiniView.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC Tool.h"
#include "MainFrm.h"
#include "MFC ToolView.h"
#include "MiniView.h"

// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView() : m_pDevice(nullptr), m_pTexture(nullptr),m_pSprite(nullptr)
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView 그리기

void CMiniView::OnDraw(CDC* /*pDC*/)
{
	CDocument* pDoc = GetDocument();
	
	m_pDevice->BeginDraw();
	m_pDevice->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	m_MFCToolView->m_Terrain->RenderTerrain();

	m_pDevice->GetSprite()->End();
	m_pDevice->EndDraw(m_hWnd);
}


// CMiniView 진단

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView 메시지 처리기


void CMiniView::OnInitialUpdate()
{
	// CView::OnInitialUpdate();

	m_pDevice = CGraphicDevice::GetInstance();
	m_pSprite = m_pDevice->GetSprite();

	CMainFrame* mainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	m_MFCToolView = dynamic_cast<CMFCToolView*>(mainFrm->m_MainSplitter.GetPane(0,1));
}
