// Elevator.h : Elevator main header file
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       


// CElevatorApp:
// About the implemention of it, please review Elevator.cpp
//

class CElevatorApp : public CWinApp
{
public:
	CElevatorApp();


// override
public:
	virtual BOOL InitInstance();

// implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CElevatorApp theApp;