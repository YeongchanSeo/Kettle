
// MFC���ۺ���4.h : MFC���ۺ���4 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFC���ۺ���4App:
// �� Ŭ������ ������ ���ؼ��� MFC���ۺ���4.cpp�� �����Ͻʽÿ�.
//

class CMFC���ۺ���4App : public CWinApp
{
public:
	CMFC���ۺ���4App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC���ۺ���4App theApp;
