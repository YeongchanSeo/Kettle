// DeleteSure.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC보글보글4.h"
#include "DeleteSure.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFC보글보글4View.h"
#include "DeleteImage.h"

// CDeleteSure 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDeleteSure, CDialog)

CDeleteSure::CDeleteSure(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteSure::IDD, pParent)
{
	
	//progress.SetBarColor(RGB(0, 0, 255));
}

CDeleteSure::~CDeleteSure()
{
}

void CDeleteSure::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS1, progress);
}


BEGIN_MESSAGE_MAP(CDeleteSure, CDialog)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


void CDeleteSure::OnPaint()
{
	CPaintDC dc(this);	
}

BOOL CDeleteSure::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	mFont.CreateFont(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, L"Cre초코쿠키 M");

	GetDlgItem(IDC_STATIC)->SetFont(&mFont);

	progress.SetRange(0, 100);  //진행폭을 결정
	progress.SetStep(10);          //얼마씩 진행할 것인지를 결정
	progress.SetBarColor(RGB(255, 70, 70));

	SetWindowTheme(GetDlgItem(IDC_PROGRESS1)->GetSafeHwnd(), L"", L"");

	SetTimer(1, 200, nullptr);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CDeleteSure::OnEraseBkgnd(CDC* pDC)
{
	CRect rt;
	GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(225, 150, 150));  // 클라이언트 영역 크기만큼 흰색으로 채운다

	return TRUE;  // 상위 클래스의 OnEraseBkgnd 함수를 호출하지 않아야 바꾼 배경색이 적용된다
}


void CDeleteSure::OnTimer(UINT_PTR nIDEvent)
{
	progress.StepIt();  //SetStep에서 결정한 값대로 진행

	if (progress.GetPos() == 100)
	{
		KillTimer(1);
		::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
	}
	CDialog::OnTimer(nIDEvent);
}


HBRUSH CDeleteSure::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC)
		{
			pDC->SetTextColor(RGB(255, 10, 10));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
	}
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;

}
