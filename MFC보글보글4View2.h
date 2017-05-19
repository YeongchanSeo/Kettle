#pragma once
#include "MFC���ۺ���4View2.h"
#include "MyButton.h"
#include "CvvImage.h"
#include "Splash.h"
// CMFC���ۺ���4View2 ���Դϴ�.



class CMFC���ۺ���4View2 : public CView
{
	DECLARE_DYNCREATE(CMFC���ۺ���4View2)

public:
	CSplash splash;
	CMFC���ۺ���4View2();     
	CvvImage vvImage;// ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMFC���ۺ���4View2();
	CMyButton mStartButton, mStopButton;
	CvCapture *capture;
	char* CString2char(CString& str);
	int count;
	bool stop;
	CRect video;
	IplImage *resize_image;
public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	CMFC���ۺ���4Doc* GetDocument() const;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBNStart();
	afx_msg void OnBNStop();
	
	afx_msg void OnAddvideo();
	afx_msg void OnDeletevideo();
};

UINT AFX_CDECL playingVideo(void* p);
int calculateHisto(IplImage * src, CvRect rect, int colors);
