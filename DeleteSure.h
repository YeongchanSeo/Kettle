#pragma once
#include "afxcmn.h"


// CDeleteSure ��ȭ �����Դϴ�.

class CDeleteSure : public CDialog
{

	DECLARE_DYNAMIC(CDeleteSure)
public:
	CDeleteSure(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDeleteSure();
	CFont mFont;

	enum { IDD = IDD_DELETESURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl progress;
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
