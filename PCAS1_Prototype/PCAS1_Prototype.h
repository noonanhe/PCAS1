
// PCAS1_Prototype.h : main header file for the PCAS1_Prototype application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPCAS1PrototypeApp:
// See PCAS1_Prototype.cpp for the implementation of this class
//

class CPCAS1PrototypeApp : public CWinApp
{
public:
	CPCAS1PrototypeApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPCAS1PrototypeApp theApp;
