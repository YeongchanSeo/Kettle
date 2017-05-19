#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "MFC���ۺ���4.h"
#endif
#include "MainFrm.h"
#include "MFC���ۺ���4Doc.h"
#include "MFC���ۺ���4View.h"
#include "Splash.h"
#include "Screen.h"
#include "DeleteSure.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CMFC���ۺ���4View, CView)

BEGIN_MESSAGE_MAP(CMFC���ۺ���4View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC���ۺ���4View::OnBNStart)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC���ۺ���4View::OnBNResult)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC���ۺ���4View::OnBNLeft)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFC���ۺ���4View::OnBNRight)
	ON_COMMAND(ID_DELETEIMAGE, &CMFC���ۺ���4View::OnDeleteimage)
	ON_WM_CREATE()
	ON_WM_DRAWITEM()
	ON_COMMAND(ID_ADDIMAGE, &CMFC���ۺ���4View::OnAddimage)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CMFC���ۺ���4View::CMFC���ۺ���4View()
	: mButton(IDB_BUTTON)
	, mResultButton(IDB_RESULT)
	, mLeftButton(IDB_LEFT)
	, mRightButton(IDB_RIGHT)
{
	strPathName == L"";
	showImg = nullptr;
	start = 0;
}

CMFC���ۺ���4View::~CMFC���ۺ���4View()
{
}

char* CMFC���ۺ���4View::CString2char(CString& str)
{
	long len = str.GetLength();
	len = len * 2;
	char* szTemp = new char[len + 1];
	memset(szTemp, 0, len + 1);
	USES_CONVERSION;
	strcpy(szTemp, T2A(str));

	return szTemp;
}

afx_msg void CMFC���ۺ���4View::OnBNLeft()
{
	if (start <= 0)
		return;
	start--;
	InvalidateRect(CRect(95, 350, 215, 470), FALSE);
	InvalidateRect(CRect(225, 350, 345, 470), FALSE);
	InvalidateRect(CRect(355, 350, 475, 470), FALSE);
	InvalidateRect(CRect(485, 350, 605, 470), FALSE);
	InvalidateRect(CRect(615, 350, 745, 470), FALSE);
}

afx_msg void CMFC���ۺ���4View::OnBNRight()
{
	if (start + 5 >= pathNames.size())
		return;

	start++;
	InvalidateRect(CRect(95, 350, 215, 470),FALSE);
	InvalidateRect(CRect(225, 350, 345, 470),FALSE);
	InvalidateRect(CRect(355, 350, 475, 470),FALSE);
	InvalidateRect(CRect(485, 350, 605, 470),FALSE);
	InvalidateRect(CRect(615, 350, 745, 470),FALSE);
}


afx_msg void CMFC���ۺ���4View::OnBNStart()
{
	if (strPathName == L"")
	{
		MessageBox(L"�̹����� ������ �ּ���.", L"���");
		return;
	}

	CDeleteSure dlg;
	dlg.DoModal();

	char* path = CString2char(strPathName);

	IplImage* src = cvLoadImage(path, CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* binary = cvLoadImage(path, CV_LOAD_IMAGE_GRAYSCALE);
	

	showImg = cvLoadImage(path, CV_WINDOW_AUTOSIZE);
	IplImage* eig_image = cvCreateImage(cvGetSize(src), IPL_DEPTH_32F, 1);
	IplImage* temp_image = cvCreateImage(cvGetSize(src), IPL_DEPTH_32F, 1);

	CvPoint2D32f* corners = new CvPoint2D32f[MAX_CORNERS];
	int corner_count = MAX_CORNERS;

	cvDilate(src, src, nullptr, 7);
	cvErode(src, src);
	cvDilate(src, src, nullptr, 3);
	cvErode(src, src);


	cvSmooth(src, src, CV_MEDIAN, 1);
	cvSmooth(src, src, CV_GAUSSIAN, 1);

	cvGoodFeaturesToTrack(src, eig_image, temp_image, corners, &corner_count,
		0.05, 5.0, 0, 3, 0, 0.04);

	int* rectX = new int[corner_count];
	int* rectY = new int[corner_count];

	CvRect rect;
	int Xmax = 0, Xmin = 1000, Xmin2 = 1001, Ymax = 0, Ymin = 1000;

	for (int i = 0; i < corner_count; i++) {
		cvCircle(showImg, cvPoint((int)corners[i].x, (int)corners[i].y), 3, CV_RGB(255, 255, 100), -1, 8);
		rectX[i] = (int)corners[i].x;
		rectY[i] = (int)corners[i].y;
	}

	std::sort(rectX, rectX + corner_count);
	std::sort(rectY, rectY + corner_count);

	for (int i = 0; i < corner_count; i++)
	{
		Xmin = rectX[i];
		if (rectX[i] + 50 >= rectX[i + 1])
			break;
	}
	for (int i = 0; i < corner_count; i++)
	{
		Ymin = rectY[i];
		if (rectY[i] + 50 >= rectY[i + 1])
			break;
	}
	for (int i = corner_count - 1; i >= 0; i++)
	{
		Xmax = rectX[i];
		if (rectX[i] - 50 <= rectX[i - 1])
			break;
	}
	for (int i = corner_count - 1; i >= 0; i++)
	{
		Ymax = rectY[i];
		if (rectY[i] - 50 <= rectY[i - 1])
			break;
	}
	int width = Xmax - Xmin;
	int height = Ymax - Ymin;

	rect.x = (int)(Xmin - width*0.1);
	rect.y = (int)(Ymin - height*0.2);
	rect.width = (int)(width*1.2);
	rect.height = (int)(height*1.4);

	cvRectangle(showImg, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), cvScalar(150, 255, 0, 100), 2);

	int num;

	CClientDC dc(this);

	CFont font;
	font.CreatePointFont(120, _T("���� ���"));	
	BOOL m_bTransparent = TRUE;	
	COLORREF m_colorText = RGB(250, 230, 230);
	COLORREF m_colorBk = RGB(0, 0, 0);

	CFont *oldFont;
	COLORREF oldText;
	COLORREF oldBk;
	oldFont = (CFont *)dc.SelectObject(&font);
	oldText = (COLORREF)dc.SetTextColor(m_colorText);
	oldBk = (COLORREF)dc.SetBkColor(m_colorBk);
	if (m_bTransparent) dc.SetBkMode(TRANSPARENT);
	else				dc.SetBkMode(OPAQUE);

	if (rect.x <= showImg->width / 8.0)
	{
		dc.DrawText(L"������ ��ġ : ����", CRect(640, 220, 820, 330), DT_LEFT);
		printf("������ ��ġ : ����\n");
		num = PixelCount(binary, showImg, rect.x + rect.width, binary->width, binary->width, rect.y + rect.height / 2);
	}
	else if (rect.x + rect.width >= showImg->width * 7 / 8.0)
	{
		dc.DrawText(L"������ ��ġ : ������", CRect(640, 220, 820, 330), DT_LEFT);
		printf("������ ��ġ : ������\n");
		num = PixelCount(binary, showImg, 0, binary->width, rect.x, rect.y + rect.height / 2);
	}
	else
	{
		dc.DrawText(L"������ ��ġ : ���", CRect(640, 220, 820, 330), DT_LEFT);
		num = PixelCount(binary, showImg, rect.x + rect.width, binary->width, binary->width, rect.y + rect.height / 2);
		num = PixelCount(binary, showImg, 0, binary->width, rect.x, rect.y + rect.height / 2);
	}

	if (num>1000)
	{
		dc.DrawText(L"���� �����ϴ�.", CRect(640, 240, 820, 330), DT_LEFT);
		//printf("%d", num);
	}
	else
	{
		dc.DrawText(L"���� ���� �ʽ��ϴ�.", CRect(640, 240, 820, 330), DT_LEFT);
	}

	dc.SelectObject(oldFont);
	dc.SetTextColor(oldText);
	dc.SetBkColor(oldBk);
	font.DeleteObject();
	cvReleaseImage(&src);
	delete[] rectX;
	delete[] rectY;
}

afx_msg void CMFC���ۺ���4View::OnBNResult()
{
	if (strPathName == L"")
	{
		MessageBox(L"�̹����� ������ �ּ���.", L"���");
		return;
	}
	if (showImg == nullptr)
	{
		MessageBox(L"���� ��ư�� ���� �ּ���.", L"���");
		return;
	}
	cvNamedWindow("RESULT", CV_WINDOW_AUTOSIZE);
	cvShowImage("RESULT", showImg);
	cvWaitKey(0);
	cvDestroyWindow("RESULT");
}

BOOL CMFC���ۺ���4View::PreCreateWindow(CREATESTRUCT& cs)
{

	return CView::PreCreateWindow(cs);
}

void CMFC���ۺ���4View::OnDraw(CDC* pDC)
{
	CMFC���ۺ���4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	CRect window;
	CBrush brush;
	GetClientRect(window);

	pDoc->mImage.Load(L"");
	Graphics grfx(pDC->m_hDC);
	Image img(L"res/2.jpg");

	grfx.SetInterpolationMode(InterpolationModeHighQualityBilinear);
	grfx.DrawImage(&img, 0, 0, window.right, window.bottom);

	CScreen mainBox;
	mainBox.draw(pDC);

	Graphics graphics(pDC->m_hDC);
	LPWSTR bstr = strPathName.AllocSysString();
	Image image(bstr);
	::SysFreeString(bstr);

	graphics.SetInterpolationMode(InterpolationModeHighQualityBilinear);
	graphics.DrawImage(&image, 15, 15, 600, 310);

	std::vector<CString>::iterator it;
	int i;
	for (it = pathNames.begin(), i = 0; i < start; i++)
	{
		++it;

	}
	for (i = 0; it != pathNames.end() && i < 5; ++it, i++)
	{
		LPWSTR bstr = it->AllocSysString();
		Image image(bstr);
		::SysFreeString(bstr);

		Point points[] = { Point(100 + i * 130, 355), Point(210 + i * 130, 355), Point(100 + i * 130, 465) };
		graphics.DrawImage(&image, points, 3);
	}
}

BOOL CMFC���ۺ���4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CMFC���ۺ���4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CMFC���ۺ���4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CMFC���ۺ���4View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC���ۺ���4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC���ۺ���4Doc* CMFC���ۺ���4View::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC���ۺ���4Doc)));
	return (CMFC���ۺ���4Doc*)m_pDocument;
}
#endif

int CMFC���ۺ���4View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	splash.Create(IDB_SPLASH, this);
	return 0;
}

#include "MyButton.h"
void CMFC���ۺ���4View::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CView::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CMFC���ۺ���4View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	mButton.Create(L"��  ��", BS_NOTIFY | WS_CHILD | BS_OWNERDRAW | WS_VISIBLE | WS_TABSTOP, CRect(630, 10, 820, 100), this, IDC_BUTTON1);
	mResultButton.Create(L"�� �� �� ��", BS_NOTIFY | WS_CHILD | BS_OWNERDRAW | WS_VISIBLE | WS_TABSTOP, CRect(630, 110, 820, 200), this, IDC_BUTTON2);
	mLeftButton.Create(L"��", BS_NOTIFY | WS_CHILD | BS_OWNERDRAW | WS_VISIBLE | WS_TABSTOP, CRect(20, 350, 85, 470), this, IDC_BUTTON3);
	mRightButton.Create(L"��", BS_NOTIFY | WS_CHILD | BS_OWNERDRAW | WS_VISIBLE | WS_TABSTOP, CRect(745, 350, 810, 470), this, IDC_BUTTON4);
	}

void CMFC���ۺ���4View::OnAddimage()
{
	CMFC���ۺ���4Doc* pDoc = GetDocument();
	
	pDoc->mImage.Destroy();
	char szFilter[] = "Image (*.BMP, *.GIF, *.JPG, *JPEG) | *.BMP; *.GIF;*.JPG; *JPEG | All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, (CString)szFilter);
	if (IDOK == dlg.DoModal())
	{
		strPathName = dlg.GetPathName();

		pDoc->mImage.Load(strPathName);
		pathNames.push_back(strPathName);
		Invalidate(FALSE);
		if (start + 5 >= pathNames.size())
			return;

		start = pathNames.size() - 5;
	}	
}

#include "DeleteImage.h"

void CMFC���ۺ���4View::OnDeleteimage()
{
	CDeleteImage dlg;
	dlg.DoModal();
}

int CMFC���ۺ���4View::PixelCount(IplImage *gray, IplImage *origin, int start, int finish, int imgw, int imgh)
{
	CvScalar v;
	register int i, j;

	cvThreshold(gray, gray, 100, 255, CV_THRESH_BINARY);
	int cnt = 0;

	for (j = 0; j < imgh; j++)
	{
		for (i = start; i < imgw; i++)
		{
			v = cvGet2D(gray, j, i);
			if (v.val[0])
			{

				cnt++;
			}
		}
	}
	cvRectangle(origin, cvPoint(start, 0), cvPoint(imgw, imgh), cvScalar(150, 255, 255, 100), 2);
	return cnt;
}

void CMFC���ۺ���4View::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMFC���ۺ���4Doc* pDoc = GetDocument();

	CScreen config;
	mPoint = point;
	pDoc->mImage.Destroy();

	for (int i = 0, j; i < 7; i++)
	{
		if (i >= pathNames.size())
			return;
		if (PtInRect(CRect(95+i*130, 355, 205+i*130, 465), point))
		{
			std::vector<CString>::iterator it;
			for (it = pathNames.begin(),j = 0; j < start; j++)
			{
				++it;
			}
			for (j = 0; it != pathNames.end(), j<i; ++it, j++)
			{
			}
			strPathName = *it;
			pDoc->mImage.Load(strPathName);
			InvalidateRect(config.mMainBox, FALSE);
			InvalidateRect(config.mResult);

			break;
		}
	}

	CView::OnLButtonDown(nFlags, point);
}


BOOL CMFC���ۺ���4View::OnEraseBkgnd(CDC* pDC)
{
	CRect rt;
	GetClientRect(&rt);  // Ŭ���̾�Ʈ ������ ũ�� ���
	pDC->FillSolidRect(&rt, RGB(155, 70, 70));  // Ŭ���̾�Ʈ ���� ũ�⸸ŭ ������� ä���

	return TRUE;  // ���� Ŭ������ OnEraseBkgnd �Լ��� ȣ������ �ʾƾ� �ٲ� ������ ����ȴ�
}
