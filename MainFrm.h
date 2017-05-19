#pragma once
#include "MFC���ۺ���4View.h"
#include "MFC���ۺ���4View2.h"

class CMainFrame : public CFrameWnd
{
	
protected:
	CMainFrame();
	virtual ~CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	void OnViewChange();
	int m_nViewFlag;

	enum { FIRSTVIEW = 1, SECONDVIEW };

	void SecondView();
	void FirstView();
	CMFC���ۺ���4View *m_pFirstView;        // �ΰ��� �� Ŭ���� �� ���� 
	CMFC���ۺ���4View2 *m_pSecondView;                // ��ü�� ����Ѵ�
	int mViewFlag;
	afx_msg void OnVideomode();
	afx_msg void OnImagemode();
	afx_msg void OnUpdateImagemode(CCmdUI *pCmdUI);
	afx_msg void OnUpdateVideomode(CCmdUI *pCmdUI);
};


