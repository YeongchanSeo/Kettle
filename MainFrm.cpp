#include "stdafx.h"
#include "MFC���ۺ���4.h"

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
	m_nViewFlag = FIRSTVIEW;        // ó���� FIRSTVIEW (�� ��)�� ����.

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
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
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

	cs.lpszName = L"���ۺ���";

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
	if (m_nViewFlag == SECONDVIEW)         // �䰡 �Ϲ� �� �� ���¿��� [����/�� ��ȯ]
	{                    // �޴��� �����ϸ� FirstView( ) ȣ��
		FirstView();
		m_nViewFlag = FIRSTVIEW;
	}
	else if (m_nViewFlag == FIRSTVIEW)      // �䰡 �� �� �� ���¿��� [����/�� ��ȯ]
	{                    // �޴��� �����ϸ� SecondView( ) ȣ��
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

	m_pFirstView->ShowWindow(SW_SHOW);        // ���並 ȭ�鿡 ���̰� �Ѵ�
	m_pSecondView->ShowWindow(SW_HIDE);        // ����Ʈ �並 �����

	m_pFirstView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);  // �޼����� �߻��� ��� 
	m_pSecondView->SetDlgCtrlID(AFX_IDW_PANE_FIRST + 1);  // �޼����� �߻��� ��� 

	SetActiveView(m_pFirstView);                     // ���並 Ȱ��ȭ ��Ų��
	pDoc->RemoveView(m_pSecondView);
	RecalcLayout();                                     // �� �信�� ó���ϵ��� ����
}

void CMainFrame::SecondView()
{
	CDocument* pDoc = GetActiveDocument();

	if (m_pSecondView == NULL)    // ��ü�� ���� ���������� ���ٸ� if������
	{
		m_pFirstView = (CMFC���ۺ���4View *)GetActiveView();// ���� Ȱ��ȭ �Ǿ��ִ� 
		// �並 ��´�
		m_pSecondView = new CMFC���ۺ���4View2;  // ��ü ����
		//        CCreateContext context;  // ��ť��Ʈ�� ���� ������ ������ �ִ� ��ü ����
		//        context.m_pCurrentDoc = pDoc;
		//        context.m_pCurrentDoc = m_pFirstView->GetDocument(); //��ť��Ʈ�� ��´�
		m_pSecondView->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, rectDefault, this, AFX_IDW_PANE_FIRST + 1);
		//            &context);                   // �並 ����
		m_pSecondView->OnInitialUpdate();      // �� ������Ʈ
	}

	pDoc->AddView(m_pSecondView);

	m_pFirstView->SetDlgCtrlID(AFX_IDW_PANE_FIRST + 1);
	m_pSecondView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);

	m_pFirstView->ShowWindow(SW_HIDE);     // ù ��° �並 �����
	m_pSecondView->ShowWindow(SW_SHOW); // Ȱ��ȭ ��Ų �� ��° �並 ȭ�鿡 ��Ÿ����

	SetActiveView(m_pSecondView);           // �ι�° �並 Ȱ��ȭ ��Ų��.
	pDoc->RemoveView(m_pFirstView);
	RecalcLayout();

	//    m_nViewFlag = SECONDVIEW;           // �䰡 ����Ʈ ��� �ٲ� ���� �̹Ƿ� 
	// SECONDVIEW�� �� ����
}

void CMainFrame::OnImagemode()
{
	if (m_nViewFlag == FIRSTVIEW)      // �䰡 �� �� �� ���¿��� [����/�� ��ȯ]
		return;
	// �޴��� �����ϸ� FirstView( ) ȣ��
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
