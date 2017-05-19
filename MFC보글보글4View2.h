#pragma once
#include "MFC보글보글4View2.h"
#include "MyButton.h"
#include "CvvImage.h"
#include "Splash.h"
// CMFC보글보글4View2 뷰입니다.



class CMFC보글보글4View2 : public CView
{
	DECLARE_DYNCREATE(CMFC보글보글4View2)

public:
	CSplash splash;
	CMFC보글보글4View2();     
	CvvImage vvImage;// 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMFC보글보글4View2();
	CMyButton mStartButton, mStopButton;
	CvCapture *capture;
	char* CString2char(CString& str);
	int count;
	bool stop;
	CRect video;
	IplImage *resize_image;
public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	CMFC보글보글4Doc* GetDocument() const;
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
