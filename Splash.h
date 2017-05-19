#ifndef _SPLASH_SCRN_
#define _SPLASH_SCRN_


class CSplash : public CWnd
{
	CBitmap m_bitmap;

public:
	CSplash();
	~CSplash();

	static void EnableSplashScreen(BOOL bEnable = TRUE);
	static void ShowSplashScreen(int bmpID, CWnd* pParentWnd = NULL);
	static BOOL PreTranslateAppMessage(MSG* pMsg);

	virtual void PostNcDestroy();
	BOOL Create(int bmpID, CWnd* pParentWnd = NULL);
	void HideSplashScreen();
	static BOOL c_bShowSplashWnd;
	static CSplash* c_pSplashWnd;
	
protected:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};


#endif
