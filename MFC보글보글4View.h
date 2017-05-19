#pragma once
#include "Splash.h"
#include "MyButton.h"
#include <vector>
#include "MFC보글보글4Doc.h"


class CMFC보글보글4View : public CView
{
	CSplash splash;
	
public:
	CString strPathName;
	CMFC보글보글4View();
	
	virtual ~CMFC보글보글4View();
	std::vector<CString> pathNames;
	CMyButton mButton, mResultButton, mLeftButton, mRightButton;

	int start;
	CPoint mPoint;

	IplImage* showImg;

	DECLARE_DYNCREATE(CMFC보글보글4View)

	CMFC보글보글4Doc* GetDocument() const;
		
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void OnInitialUpdate();
	afx_msg void OnAddimage();
	afx_msg void OnBNStart();
	afx_msg void OnBNResult();
	afx_msg void OnBNLeft();
	afx_msg void OnBNRight();
	afx_msg void OnDeleteimage();
	int PixelCount(IplImage *gray, IplImage *origin, int start, int finish, int imgw, int imgh);
	const int MAX_CORNERS = 50;
	char* CString2char(CString& str);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CProgressCtrl progress;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // MFC보글보글2View.cpp의 디버그 버전
inline CMFC보글보글2Doc* CMFC보글보글4View::GetDocument() const
{
	return reinterpret_cast<CMFC보글보글2Doc*>(m_pDocument);
}
#endif

