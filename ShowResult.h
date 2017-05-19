#pragma once
#include "afxcmn.h"
#include "Splash.h"
#include "PictureEx.h"
// CShowResult 대화 상자입니다.

class CShowResult : public CDialog
{
	DECLARE_DYNAMIC(CShowResult)

public:
	CShowResult(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShowResult();
	CSplash splash;
	CFont mFont;


// 대화 상자 데이터입니다.
	enum { IDD = IDD_SHOWRESULT };
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	
	CPictureEx mPicture, mPicture2;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
