// MFC보글보글4View2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC보글보글4.h"
#include "MFC보글보글4Doc.h"
#include "MFC보글보글4View2.h"
#include "CvvImage.h"
#include "Screen2.h"
#include <string>
#include "ShowResult.h"
using namespace cv;

IplImage *img;

IMPLEMENT_DYNCREATE(CMFC보글보글4View2, CView)

CMFC보글보글4View2::CMFC보글보글4View2()
: mStartButton(IDB_START)
, mStopButton(IDB_STOP)
, stop(true)
, video(115, 10, 715, 330)
{
	capture = nullptr;
	resize_image = cvCreateImage(cvSize(610, 320),
		IPL_DEPTH_8U,
		3);
}

CMFC보글보글4View2::~CMFC보글보글4View2()
{
}

BEGIN_MESSAGE_MAP(CMFC보글보글4View2, CView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC보글보글4View2::OnBNStart)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC보글보글4View2::OnBNStop)
	ON_COMMAND(ID_ADDVIDEO, &CMFC보글보글4View2::OnAddvideo)
	ON_COMMAND(ID_DELETEVIDEO, &CMFC보글보글4View2::OnDeletevideo)
END_MESSAGE_MAP()

afx_msg void CMFC보글보글4View2::OnBNStop()
{
	stop = true;
}

struct PARAM
{
	CMFC보글보글4View2* view;
	CvCapture* capture;

	PARAM(CMFC보글보글4View2* view_, CvCapture* capture_)
		:view(view_), capture(capture_)
	{
	}
};

UINT AFX_CDECL playingVideo(void* p)
{
	PARAM param = *(PARAM*)p;
	delete p;
	CClientDC dc(param.view);
	static int FirstWhite, CompareWhite;
	static IplImage* FirstImg;
	static IplImage* CompareImg;
	static IplImage* FirstGray;
	static IplImage* CompareGray;

	CvRect steam = { 0, 0, 370, 170 };

	if (param.capture)
	{
		while (1)
		{
			if (param.view->stop)
			{
				InvalidateRect(param.view->m_hWnd, CRect(360, 120, 450, 220), FALSE);
				break;
			}
			img = cvQueryFrame(param.capture);
			if (!img) break;
			 

			cvResize(img, param.view->resize_image, CV_INTER_CUBIC);
			CvRect rect = { 10, 10, 620, 330 };
			char s_output_result[100];
			CvFont font;
			int sec = param.view->count / 60;
			int secsec = param.view->count % 60;
			sprintf(s_output_result, "%02d : %02d", sec, secsec);    //우선 sprintf로 문자열 생성
			cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, 0.5, 0.5, 0, 1);  //이런 저런 설정.
			cvPutText(param.view->resize_image, s_output_result, cvPoint(15, 20), &font, cvScalar(0, 255, 0));   //cvPoint로 글자 시작 위치 설정(uv)

			param.view->vvImage.CopyOf(param.view->resize_image, 8);
			param.view->vvImage.Show(dc.m_hDC, param.view->video.left, param.view->video.top,
					   	param.view->video.Width(), param.view->video.Height());

			if (param.view->count == 0)
			{
				FirstImg = img;
				FirstGray = cvCreateImage(cvGetSize(FirstImg), IPL_DEPTH_8U, 1);
				cvCvtColor(FirstImg, FirstGray, CV_BGR2GRAY);
				cvThreshold(FirstGray, FirstGray, 50, 255, THRESH_BINARY);
				FirstWhite = calculateHisto(FirstGray, steam, 1);
			}

			string filename;
			if (param.view->count % 100 == 0)
			{
				CompareImg = img;

				CompareGray = cvCreateImage(cvGetSize(CompareImg), IPL_DEPTH_8U, 1);
				cvCvtColor(CompareImg, CompareGray, CV_BGR2GRAY);

				cvThreshold(CompareGray, CompareGray, 50, 255, THRESH_BINARY);

				cvRectangle(FirstImg, cvPoint(0, 0), cvPoint(370, 170), cvScalar(255, 0, 0, 0), 2);
				cvRectangle(CompareImg, cvPoint(0, 0), cvPoint(370, 170), cvScalar(255, 0, 0, 0), 2);

				CompareWhite = calculateHisto(CompareGray, steam, 1);
				if (CompareWhite - FirstWhite > 3000)
				{
					Sleep(100);
					wchar_t buf[256];
					wsprintf(buf, L"물이 끓습니다! [F:%d, C : %d] \n", FirstWhite, CompareWhite);
					/*vvImage.CopyOf(0, 0);
					vvImage.Show(dc.m_hDC, param.view->video.left, param.view->video.top,
						param.view->video.Width(), param.view->video.Height(), 1, 1);*/
					for (int i = 0; i < 3; i++)
					{
						dc.Rectangle(115, 10, 715, 330);
						Sleep(250);
						param.view->vvImage.Show(dc.m_hDC, param.view->video.left, param.view->video.top,
							param.view->video.Width(), param.view->video.Height(), 1, 1);
						Sleep(250);
					}
					param.view->stop = true;
					//MessageBox(param.view->m_hWnd, buf, L"작동", MB_OK);
					CShowResult dlg;
					dlg.DoModal();
					sndPlaySound(NULL, SND_ASYNC);
					break;
				}
				else if (CompareWhite - FirstWhite > 1000)
				{
					PlaySound(L"res/끓는소리.wav", NULL, SND_ASYNC);
				}
			}

			cvWaitKey(1);
			param.view->count++;
		}
	}

	return 0;
}

char* CMFC보글보글4View2::CString2char(CString& str)
{
	long len = str.GetLength();
	len = len * 2;
	char* szTemp = new char[len + 1];
	memset(szTemp, 0, len + 1);
	USES_CONVERSION;
	strcpy(szTemp, T2A(str));

	return szTemp;
}

afx_msg void CMFC보글보글4View2::OnBNStart()
{
	if (capture == nullptr)
	{
		MessageBox(L"동영상을 추가해주세요.", L"경고");
		return;
	}
	if (stop == false)
	{
		return;
	}
	stop = false;
	AfxBeginThread(playingVideo, new PARAM(this, capture));
}


void CMFC보글보글4View2::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	
	CRect window;
	CBrush brush;
	GetClientRect(window);

	Graphics grfx(pDC->m_hDC);
	Image image(L"res/1.jpg");

	grfx.SetInterpolationMode(InterpolationModeHighQualityBilinear);
	grfx.DrawImage(&image, 0, 0, window.right, window.bottom);

	CScreen2 screen;
	screen.draw(pDC);

	if (stop == true && capture != nullptr)
	{
		img = cvQueryFrame(capture);
		cvResize(img, resize_image, CV_INTER_CUBIC);

		vvImage.CopyOf(resize_image, 8);
		vvImage.Show(pDC->m_hDC, video.left, video.top, video.Width(), video.Height());
		CRect play = { 400, 170, 400, 170 };
		play.InflateRect(50, 50);
		CBrush brush;
		Graphics grfx(pDC->m_hDC);
		if (count == 0)
		{
			Image image(L"res/2.png");
			grfx.SetInterpolationMode(InterpolationModeHighQualityBilinear);
			grfx.DrawImage(&image, play.left, play.top, play.Width(), play.Height());
		}
		else
		{
			Image image(L"res/1.png");
			grfx.SetInterpolationMode(InterpolationModeHighQualityBilinear);
			grfx.DrawImage(&image, play.left, play.top, play.Width(), play.Height());
		}
	}
}

int calculateHisto(IplImage * src, CvRect rect, int colors) //영역별 히스토그램저장
{
	CvScalar v;
	int black, white;
	black = white = 0;

	int B, G, R;

	for (int i = rect.x; i < rect.x + rect.width; i++)
	{
		for (int j = rect.y; j < rect.y + rect.height; j++)
		{
			v = cvGet2D(src, j, i);
			B = (int)v.val[0];
			G = (int)v.val[1];
			R = (int)v.val[2];
			if (B > 0)
			{
				white++;
			}
			else
			{
				black++;
			}
		}
	}

	if (colors == 0)
		return black;
	else
		return white;
}

#ifdef _DEBUG
void CMFC보글보글4View2::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMFC보글보글4View2::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

CMFC보글보글4Doc* CMFC보글보글4View2::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC보글보글4Doc)));
	return (CMFC보글보글4Doc*)m_pDocument;
}


void CMFC보글보글4View2::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	mStartButton.Create(L"시  작", BS_NOTIFY | WS_CHILD | BS_OWNERDRAW | WS_VISIBLE | WS_TABSTOP, CRect(280, 350, 400, 470), this, IDC_BUTTON1);
	mStopButton.Create(L"결 과 보 기", BS_NOTIFY | WS_CHILD | BS_OWNERDRAW | WS_VISIBLE | WS_TABSTOP, CRect(430, 350, 550, 470), this, IDC_BUTTON2);
}


void CMFC보글보글4View2::OnAddvideo()
{
	if (capture != nullptr)
	{
		MessageBox(L"이미 동영상이 추가되어 있습니다.", L"경고");
		return;
	}
	CMFC보글보글4Doc* pDoc = GetDocument();

	CString pathName;
	pDoc->mImage.Destroy();
	char szFilter[] = "Image (*.avi, *.mp4) | *.AVI; *.mp4 | All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, (CString)szFilter);
	if (IDOK == dlg.DoModal())
	{
		pathName = dlg.GetPathName();
		char* str = CString2char(pathName);
		capture = cvCaptureFromFile(str);

		count = 0;
		InvalidateRect(CRect(115, 10, 715, 330),FALSE);
	}
}


void CMFC보글보글4View2::OnDeletevideo()
{
	if (capture == nullptr)
	{
		MessageBox(L"삭제할 동영상이 없습니다.", L"경고");
		return;
	}
	cvReleaseCapture(&capture);
	capture = nullptr;
	stop = true;

	InvalidateRect(CRect(115, 10, 715, 330), FALSE);
}
