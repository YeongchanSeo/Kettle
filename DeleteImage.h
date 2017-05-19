#pragma once
#include "afxwin.h"

class CDeleteImage : public CDialog
{
	DECLARE_DYNAMIC(CDeleteImage)

public:
	CComboBox mComboBox;
	CDeleteImage(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDeleteImage();
private:
	enum { IDD = IDD_DELETEIMAGE };
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDelete();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
