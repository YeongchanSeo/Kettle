// DeleteImage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFC���ۺ���4.h"
#include "DeleteImage.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFC���ۺ���4Doc.h"
#include "MFC���ۺ���4View.h"
#include "DeleteSure.h"

// CDeleteImage ��ȭ �����Դϴ�.

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


// CDeleteImage �޽��� ó�����Դϴ�.

BOOL CDeleteImage::OnInitDialog()
{
	CDialog::OnInitDialog();

	CMainFrame* mainFrame = (CMainFrame*)theApp.m_pMainWnd;
	CMFC���ۺ���4View* pView = (CMFC���ۺ���4View*)mainFrame->GetActiveView();

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
	CMFC���ۺ���4View* pView = (CMFC���ۺ���4View*)mainFrame->GetActiveView();

	if (pView->pathNames.size() == 0)
	{
		MessageBox(L"������ �̹����� �����ϴ�.");
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
	GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(235, 150, 150));  // Ŭ���̾�Ʈ ���� ũ�⸸ŭ ������� ä���

	return TRUE;  // ���� Ŭ������ OnEraseBkgnd �Լ��� ȣ������ �ʾƾ� �ٲ� ������ ����ȴ�

}
