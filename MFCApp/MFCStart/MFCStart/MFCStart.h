
// MFCStart.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCStartApp:
// See MFCStart.cpp for the implementation of this class
//

class CMFCStartApp : public CWinApp
{
public:
	CMFCStartApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCStartApp theApp;
