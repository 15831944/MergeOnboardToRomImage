
// MergeOnboardToRomImage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMergeOnboardToRomImageApp:
// �йش����ʵ�֣������ MergeOnboardToRomImage.cpp
//

class CMergeOnboardToRomImageApp : public CWinApp
{
public:
	CMergeOnboardToRomImageApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMergeOnboardToRomImageApp theApp;