// ShowResult.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC보글보글4.h"
#include "ShowResult.h"
#include "afxdialogex.h"


// CShowResult 대화 상자입니다.

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


// CShowResult 메시지 처리기입니다.



#include "Splash.h"
void CShowResult::OnPaint()
{
	CPaintDC dc(this);
	
	mPicture.Create(NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, CRect(190, 70, 60, 60), this, IDC_PICTURE2);

	if (mPicture.Load(MAKEINTRESOURCE(IDR_GIF2), _T("GIF"))) // 등록 된 리소스에서 로드하는 방법입니다 ~
	{
		mPicture.Draw();
	}

	Graphics grfx(dc.m_hDC);
	Image img(L"res/주전자.png");

	Image img2(L"res/불.png");

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
		DEFAULT_PITCH | FF_SWISS, L"맑은 고딕");

	GetDlgItem(IDC_STATIC)->SetFont(&mFont);

	return TRUE;  
}


int CShowResult::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
