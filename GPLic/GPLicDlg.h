#if !defined(AFX_GPLICDLG_H__7C135B4A_170C_11D2_B150_00C04F829FFD__INCLUDED_)
#define AFX_GPLICDLG_H__7C135B4A_170C_11D2_B150_00C04F829FFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// GPLicDlg.h : header file
//
//
// Copyright (c) 1998-2014 COLIN Arnaud.
// Ecrit par Arnaud COLIN 
//

#include "License.h"
/////////////////////////////////////////////////////////////////////////////
// CGPLicDlg dialog

class CGPLicDlg : public CDialog
{
// Construction
public:
	void Affect();
	CGPLicDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGPLicDlg)
	enum { IDD = IDD_GPLIC_DIALOG };
	CString	m_Adresse;
	CString	m_Cle;
	CString	m_Nom;
	CString	m_Pass;
	CString	m_Ville;
	//}}AFX_DATA

	CLicense Lic;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPLicDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGPLicDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDeregistre();
	afx_msg void OnGenere();
	afx_msg void OnRegistre();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPLICDLG_H__7C135B4A_170C_11D2_B150_00C04F829FFD__INCLUDED_)
