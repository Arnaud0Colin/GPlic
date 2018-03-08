#include "stdafx.h"
#include "GPLic.h"
#include "GPLicDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
// Copyright (c) 1998-2014 COLIN Arnaud.
// Ecrit par Arnaud COLIN 
//

/////////////////////////////////////////////////////////////////////////////
// CGPLicApp

BEGIN_MESSAGE_MAP(CGPLicApp, CWinApp)
	//{{AFX_MSG_MAP(CGPLicApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGPLicApp construction

CGPLicApp::CGPLicApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGPLicApp object

CGPLicApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGPLicApp initialization

BOOL CGPLicApp::InitInstance()
{
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();			
#else
	Enable3dControlsStatic();	
#endif

	CGPLicDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	return FALSE;
}
