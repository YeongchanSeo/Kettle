// MyButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFC보글보글4.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton(UINT bmpID)
:mBmpId(bmpID)
{

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_CREATE()
END_MESSAGE_MAP()


void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	LPDRAWITEMSTRUCT di = lpDrawItemStruct;

	CDC dc;
	dc.Attach(di->hDC);

	if ((HBITMAP)mBitmap == nullptr)
	{

		mBitmap.LoadBitmap(MAKEINTRESOURCE(mBmpId));

		mMemDC.CreateCompatibleDC(&dc);
		mMemDC.SelectObject(&mBitmap);
	}
	UINT edge, offset = 1;
	if ((di->itemState & ODS_SELECTED) == ODS_SELECTED){
		edge = EDGE_SUNKEN;//들어간 모양
		offset = 2;
	}
	else{
		edge = EDGE_RAISED;//튀어나온 모양
	}

	dc.DrawEdge(&di->rcItem, edge, BF_RECT);
	dc.BitBlt(3 - offset, 3 - offset, di->rcItem.right - 5, di->rcItem.bottom - 5, &mMemDC, 0, 0, SRCCOPY);


	dc.Detach();
}

//부모한테 있으면 owner draw 나한테 있으면 selfdraw

int CMyButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
