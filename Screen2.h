#pragma once
#include "MFC보글보글4.h"
class CScreen2
{

	CRect mBigBox;
	CRect mRadio;
public:
	CRect mMainBox;
	CRect mSmallBox;
	CRect mResult;
	CRect mStartButton;
	CRect mStopButton;

	CScreen2()
		: mMainBox(115, 10, 715, 330)
		, mStartButton(280, 350, 400, 470)
		, mStopButton(430, 350, 550, 470)
	{
	};
	~CScreen2();
	void draw(CDC* pDC)
	{
		pDC->SelectStockObject(NULL_BRUSH);
		pDC->SelectObject(CreatePen(0, 5, RGB(255, 255, 150)));
		pDC->Rectangle(mMainBox);
		pDC->Rectangle(mStartButton);
		pDC->Rectangle(mStopButton);
		/*pDC->Rectangle(mBigBox);
		pDC->Rectangle(mLeftButton);
		pDC->SelectObject(CreatePen(0, 5, RGB(255, 255, 255)));

		for (int i = 0; i < 5; i++)
			pDC->Rectangle(mSmallBox.left + i * 130, mSmallBox.top, mSmallBox.right + i * 130, mSmallBox.bottom);
		pDC->SelectObject(CreatePen(0, 5, RGB(255, 200, 200)));
		pDC->Rectangle(mRightButton);
		pDC->Rectangle(mRadio);
		pDC->Rectangle(mResult);*/
	}
};
