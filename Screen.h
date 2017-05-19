#pragma once
#include "MFC보글보글4.h"
class CScreen
{
	
	CRect mBigBox;
	CRect mRadio;
public:
	CRect mMainBox;
	CRect mSmallBox;
	CRect mResult;
	CRect mLeftButton;
	CRect mRightButton;

	CScreen()
		: mMainBox(10, 10, 620, 330)
		, mBigBox(10, 340, 820, 480)
		, mSmallBox(95, 350, 215, 470)
		, mRadio(630, 110, 820, 200)
		, mResult(630, 210, 820, 330)
		, mLeftButton(20, 350, 85, 470)
		, mRightButton(745, 350, 810, 470)
	{
	};
	~CScreen();
	void draw(CDC* pDC)
	{
		pDC->SelectStockObject(NULL_BRUSH);
		pDC->SelectObject(CreatePen(0, 5, RGB(255, 200, 200)));
		pDC->Rectangle(mMainBox);
		pDC->Rectangle(mBigBox);		
		pDC->Rectangle(mLeftButton);
		pDC->SelectObject(CreatePen(0, 5, RGB(255, 255, 255)));

		for (int i = 0; i < 5; i++)
			pDC->Rectangle(mSmallBox.left + i * 130, mSmallBox.top, mSmallBox.right + i * 130, mSmallBox.bottom);
		pDC->SelectObject(CreatePen(0, 5, RGB(255, 200, 200)));
		pDC->Rectangle(mRightButton);
		pDC->Rectangle(mRadio);
		pDC->Rectangle(mResult);
	}
};
