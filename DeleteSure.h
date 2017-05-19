#pragma once
#include "afxcmn.h"


// CDeleteSure 대화 상자입니다.

class CDeleteSure : public CDialog
{

	DECLARE_DYNAMIC(CDeleteSure)
public:
	CDeleteSure(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDeleteSure();
	CFont mFont;

	enum { IDD = IDD_DELETESURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl progress;
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
