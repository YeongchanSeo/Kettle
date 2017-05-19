// ShowResult.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFC���ۺ���4.h"
#include "ShowResult.h"
#include "afxdialogex.h"


// CShowResult ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShowResult, CDialog)

CShowResult::CShowResult(CWnd* pParent /*=NULL*/)
	: CDialog(CShowResult::IDD, pParent)
{
	/*HBITMAP hbit;
	hbit = (HBITMAP)LoadImage(NULL, L"res\\fire.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	mPicture.SetBitmap(hbit);*/
}

CShowResult::~CShowResult()
{
}

void CShowResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowResult, CDialog)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CShowResult �޽��� ó�����Դϴ�.



#include "Splash.h"
void CShowResult::OnPaint()
{
	CPaintDC dc(this);
	
	mPicture.Create(NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, CRect(190, 70, 60, 60), this, IDC_PICTURE2);

	if (mPicture.Load(MAKEINTRESOURCE(IDR_GIF2), _T("GIF"))) // ��� �� ���ҽ����� �ε��ϴ� ����Դϴ� ~
	{
		mPicture.Draw();
	}

	Graphics grfx(dc.m_hDC);
	Image img(L"res/������.png");

	Image img2(L"res/��.png");

	grfx.SetInterpolationMode(InterpolationModeHighQualityBilinear);
	grfx.DrawImage(&img, 30, 20, 120, 120);
	grfx.SetInterpolationMode(InterpolationModeHighQualityBilinear);

	grfx.DrawImage(&img2, 30, 80, 120, 120);
}


BOOL CShowResult::OnInitDialog()
{
	CDialog::OnInitDialog();

	mFont.CreateFont(18, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, L"���� ���");

	GetDlgItem(IDC_STATIC)->SetFont(&mFont);

	return TRUE;  
}


int CShowResult::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
