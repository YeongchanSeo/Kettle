#pragma once

class CMyButton : public CBitmapButton
{
	DECLARE_DYNAMIC(CMyButton)

	UINT    mBmpId;
	CBitmap mBitmap;
	CDC     mMemDC;
public:
	CMyButton(UINT bmpId);
	virtual ~CMyButton();

	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};