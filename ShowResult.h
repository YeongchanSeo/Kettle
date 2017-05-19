#pragma once
#include "afxcmn.h"
#include "Splash.h"
#include "PictureEx.h"
// CShowResult ��ȭ �����Դϴ�.

class CShowResult : public CDialog
{
	DECLARE_DYNAMIC(CShowResult)

public:
	CShowResult(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShowResult();
	CSplash splash;
	CFont mFont;


// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SHOWRESULT };
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	
	CPictureEx mPicture, mPicture2;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
