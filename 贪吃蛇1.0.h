
// ̰����1.0.h : ̰����1.0 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// C̰����10App:
// �йش����ʵ�֣������ ̰����1.0.cpp
//

class C̰����10App : public CWinAppEx
{
public:
	C̰����10App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern C̰����10App theApp;
