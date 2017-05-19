#include "stdafx.h"
#include "MFC보글보글4.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_VIEW_CHANGE, OnViewChange)
	ON_COMMAND(ID_VIDEOMODE, &CMainFrame::OnVideomode)
	ON_COMMAND(ID_IMAGEMODE, &CMainFrame::OnImagemode)
	ON_UPDATE_COMMAND_UI(ID_IMAGEMODE, &CMainFrame::OnUpdateImagemode)
	ON_UPDATE_COMMAND_UI(ID_VIDEOMODE, &CMainFrame::OnUpdateVideomode)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
	m_nViewFlag = FIRSTVIEW;        // 처음에 FIRSTVIEW (폼 뷰)로 설정.

	m_pFirstView = NULL;
	m_pSecondView = NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	cs.cx = 850;
	cs.cy = 551;
	cs.style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX | FWS_ADDTOTITLE);

	cs.lpszName = L"보글보글";

	return TRUE;
}


#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif



void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{

	lpMMI->ptMinTrackSize.x = 850;
	lpMMI->ptMinTrackSize.y = 551;
	lpMMI->ptMaxTrackSize.x = 850;
	lpMMI->ptMaxTrackSize.y = 551;

	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnViewChange()
{
	// TODO: Add your command handler code here
	if (m_nViewFlag == SECONDVIEW)         // 뷰가 일반 뷰 인 상태에서 [보기/뷰 전환]
	{                    // 메뉴를 선택하면 FirstView( ) 호출
		FirstView();
		m_nViewFlag = FIRSTVIEW;
	}
	else if (m_nViewFlag == FIRSTVIEW)      // 뷰가 폼 뷰 인 상태에서 [보기/뷰 전환]
	{                    // 메뉴를 선택하면 SecondView( ) 호출
		SecondView();
		m_nViewFlag = SECONDVIEW;
	}
}

void CMainFrame::FirstView()
{
	CDocument* pDoc = GetActiveDocument();

	ASSERT(m_pFirstView != 0);
	ASSERT(m_pSecondView != 0);

	pDoc->AddView(m_pFirstView);

	m_pFirstView->ShowWindow(SW_SHOW);        // 폼뷰를 화면에 보이게 한다
	m_pSecondView->ShowWindow(SW_HIDE);        // 에디트 뷰를 숨긴다

	m_pFirstView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);  // 메세지가 발생할 경우 
	m_pSecondView->SetDlgCtrlID(AFX_IDW_PANE_FIRST + 1);  // 메세지가 발생할 경우 

	SetActiveView(m_pFirstView);                     // 폼뷰를 활성화 시킨다
	pDoc->RemoveView(m_pSecondView);
	RecalcLayout();                                     // 폼 뷰에서 처리하도록 설정
}

void CMainFrame::SecondView()
{
	CDocument* pDoc = GetActiveDocument();

	if (m_pSecondView == NULL)    // 객체가 아직 생성된적이 없다면 if블럭실행
	{
		m_pFirstView = (CMFC보글보글4View *)GetActiveView();// 현재 활성화 되어있는 
		// 뷰를 얻는다
		m_pSecondView = new CMFC보글보글4View2;  // 객체 생성
		//        CCreateContext context;  // 도큐먼트에 대한 정보를 가지고 있는 객체 생성
		//        context.m_pCurrentDoc = pDoc;
		//        context.m_pCurrentDoc = m_pFirstView->GetDocument(); //도큐먼트를 얻는다
		m_pSecondView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, rectDefault, this, AFX_IDW_PANE_FIRST + 1);
		//            &context);                   // 뷰를 생성
		m_pSecondView->OnInitialUpdate();      // 뷰 업데이트
	}

	pDoc->AddView(m_pSecondView);

	m_pFirstView->SetDlgCtrlID(AFX_IDW_PANE_FIRST + 1);
	m_pSecondView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);

	m_pFirstView->ShowWindow(SW_HIDE);     // 첫 번째 뷰를 숨긴다
	m_pSecondView->ShowWindow(SW_SHOW); // 활성화 시킨 두 번째 뷰를 화면에 나타낸다

	SetActiveView(m_pSecondView);           // 두번째 뷰를 활성화 시킨다.
	pDoc->RemoveView(m_pFirstView);
	RecalcLayout();

	//    m_nViewFlag = SECONDVIEW;           // 뷰가 에디트 뷰로 바뀐 상태 이므로 
	// SECONDVIEW로 재 설정
}

void CMainFrame::OnImagemode()
{
	if (m_nViewFlag == FIRSTVIEW)      // 뷰가 폼 뷰 인 상태에서 [보기/뷰 전환]
		return;
	// 메뉴를 선택하면 FirstView( ) 호출
	FirstView();
	m_nViewFlag = FIRSTVIEW;
}

void CMainFrame::OnVideomode()
{
	if (m_nViewFlag == SECONDVIEW)
		return;
	
	SecondView();
	m_nViewFlag = SECONDVIEW;
}





void CMainFrame::OnUpdateImagemode(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nViewFlag == FIRSTVIEW);
}


void CMainFrame::OnUpdateVideomode(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_nViewFlag == SECONDVIEW);
}
