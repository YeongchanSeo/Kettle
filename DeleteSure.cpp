// DeleteSure.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFC���ۺ���4.h"
#include "DeleteSure.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFC���ۺ���4View.h"
#include "DeleteImage.h"

// CDeleteSure ��ȭ �����Դϴ�.

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
		DEFAULT_PITCH | FF_SWISS, L"Cre������Ű M");

	GetDlgItem(IDC_STATIC)->SetFont(&mFont);

	progress.SetRange(0, 100);  //�������� ����
	progress.SetStep(10);          //�󸶾� ������ �������� ����
	progress.SetBarColor(RGB(255, 70, 70));

	SetWindowTheme(GetDlgItem(IDC_PROGRESS1)->GetSafeHwnd(), L"", L"");

	SetTimer(1, 200, nullptr);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


BOOL CDeleteSure::OnEraseBkgnd(CDC* pDC)
{
	CRect rt;
	GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(225, 150, 150));  // Ŭ���̾�Ʈ ���� ũ�⸸ŭ ������� ä���

	return TRUE;  // ���� Ŭ������ OnEraseBkgnd �Լ��� ȣ������ �ʾƾ� �ٲ� ������ ����ȴ�
}


void CDeleteSure::OnTimer(UINT_PTR nIDEvent)
{
	progress.StepIt();  //SetStep���� ������ ����� ����

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
