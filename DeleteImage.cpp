// DeleteImage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC보글보글4.h"
#include "DeleteImage.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFC보글보글4Doc.h"
#include "MFC보글보글4View.h"
#include "DeleteSure.h"

// CDeleteImage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDeleteImage, CDialog)

CDeleteImage::CDeleteImage(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteImage::IDD, pParent)
{

}

CDeleteImage::~CDeleteImage()
{
}

void CDeleteImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, mComboBox);
}


BEGIN_MESSAGE_MAP(CDeleteImage, CDialog)
	ON_BN_CLICKED(ID_DELETE, &CDeleteImage::OnBnClickedDelete)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDeleteImage 메시지 처리기입니다.

BOOL CDeleteImage::OnInitDialog()
{
	CDialog::OnInitDialog();

	CMainFrame* mainFrame = (CMainFrame*)theApp.m_pMainWnd;
	CMFC보글보글4View* pView = (CMFC보글보글4View*)mainFrame->GetActiveView();

	std::vector<CString>::iterator it;
	for (it = pView->pathNames.begin(); it != pView->pathNames.end(); ++it)
	{
		CString theString = *it;
		LPTSTR lpsz = new TCHAR[theString.GetLength() + 1];
		_tcscpy(lpsz, theString);

		mComboBox.AddString(theString);
	}

	mComboBox.SetCurSel(0);

	return TRUE;
}

void CDeleteImage::OnBnClickedDelete()
{
	CMainFrame* mainFrame = (CMainFrame*)theApp.m_pMainWnd;
	CMFC보글보글4View* pView = (CMFC보글보글4View*)mainFrame->GetActiveView();

	if (pView->pathNames.size() == 0)
	{
		MessageBox(L"삭제할 이미지가 없습니다.");
		return;
	}

	int index = mComboBox.GetCurSel();

	std::vector<CString>::iterator it;

	int i;

	for (i = 0, it = pView->pathNames.begin(); i < index; i++)
	{
		++it;
	}
	mComboBox.DeleteString(index);
	pView->pathNames.erase(it);
	mComboBox.SetCurSel(0);

	pView->Invalidate();
	if (pView->pathNames.size())
		pView->strPathName = *pView->pathNames.begin();
	else
		pView->strPathName = "";

		pView->start = pView->pathNames.size() - 5;
}


HBRUSH CDeleteImage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}


BOOL CDeleteImage::OnEraseBkgnd(CDC* pDC)
{	
	CRect rt;
	GetClientRect(&rt);  // 클라이언트 영역의 크기 계산
	pDC->FillSolidRect(&rt, RGB(235, 150, 150));  // 클라이언트 영역 크기만큼 흰색으로 채운다

	return TRUE;  // 상위 클래스의 OnEraseBkgnd 함수를 호출하지 않아야 바꾼 배경색이 적용된다

}
