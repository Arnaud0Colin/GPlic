#if !defined(AFX_GPLIC_H__7C135B48_170C_11D2_B150_00C04F829FFD__INCLUDED_)
#define AFX_GPLIC_H__7C135B48_170C_11D2_B150_00C04F829FFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

// GPLic.h : main header file
//
//
// Copyright (c) 1998-2014 COLIN Arnaud.
// Ecrit par Arnaud COLIN 
//

class CGPLicApp : public CWinApp
{
public:
	CGPLicApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPLicApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGPLicApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPLIC_H__7C135B48_170C_11D2_B150_00C04F829FFD__INCLUDED_)
