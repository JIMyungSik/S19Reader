
// SRecordizer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSRecordizerApp:
// �� Ŭ������ ������ ���ؼ��� SRecordizer.cpp�� �����Ͻʽÿ�.
//

class CSRecordizerApp : public CWinApp
{
public:
	CSRecordizerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSRecordizerApp theApp;