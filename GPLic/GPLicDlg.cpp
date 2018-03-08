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

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGPLicDlg dialog

CGPLicDlg::CGPLicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGPLicDlg::IDD, pParent), Lic(CODEProduit)
{
	//{{AFX_DATA_INIT(CGPLicDlg)
	m_Adresse = _T("");
	m_Cle = _T("");
	m_Nom = _T("");
	m_Pass = _T("");
	m_Ville = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGPLicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGPLicDlg)
	DDX_Text(pDX, IDC_ADRESSE, m_Adresse);
	DDX_Text(pDX, IDC_CLE, m_Cle);
	DDX_Text(pDX, IDC_NOM, m_Nom);
	DDX_Text(pDX, IDC_PASS, m_Pass);
	DDX_Text(pDX, IDC_VILLE, m_Ville);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGPLicDlg, CDialog)
	//{{AFX_MSG_MAP(CGPLicDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DEREGISTRE, OnDeregistre)
	ON_BN_CLICKED(IDC_GENERE, OnGenere)
	ON_BN_CLICKED(IDC_REGISTRE, OnRegistre)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGPLicDlg message handlers

BOOL CGPLicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	Lic.m_IsRead = Lic.Read();
	Lic.m_IsRegistered = Lic.IsRegistered((WORD)Lic.m_Paye);

	Affect();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGPLicDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CGPLicDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CGPLicDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGPLicDlg::OnDeregistre() 
{
	if(!Lic.m_IsRegistered || !Lic.m_IsRead) return;
	
	Lic.Destroy();

	Lic.m_IsRegistered = FALSE;
	Lic.m_IsRead = FALSE;
	
	Affect();

}

void CGPLicDlg::OnGenere() 
{
	if(Lic.m_IsRead) return;

	Lic.m_Nom = "SITE";
	Lic.m_Prenom = "CODEPLEX";
	Lic.m_Adresse = "Project Hosting for Open Source Software";
	Lic.m_CodePostal = "75000";
	Lic.m_Ville = "PARIS";
	Lic.m_Pays = "FRANCE";
	
	Lic.m_Inst = 1;
	Lic.m_Paye = 1;

	Lic.SetVersion("1.0");

	Lic.CreateKey();

	Lic.m_IsRead = TRUE;
	
	Affect();

}

void CGPLicDlg::OnRegistre() 
{
	if(!Lic.m_IsRead) return;
	if(Lic.m_IsRegistered) return;

	WORD w = (WORD)Lic.m_Paye;

	Lic.CreatePass(w);
	Lic.Register();

	Lic.m_IsRegistered = TRUE;

	Affect();
}

void CGPLicDlg::Affect()
{

	if(Lic.m_IsRead)
	{
		m_Nom.Format("%s %s",Lic.m_Nom,Lic.m_Prenom);
		m_Adresse.Format("%s",Lic.m_Adresse);
		m_Ville.Format("%s %s %s",Lic.m_CodePostal,Lic.m_Ville,Lic.m_Pays);

		m_Cle.Format("%s-%s",Lic.m_Cle,Lic.m_CleExt);

		GetDlgItem(IDC_REGISTRE)->EnableWindow(TRUE);
		GetDlgItem(IDC_GENERE)->EnableWindow(FALSE);
	}
	else
	{
		m_Nom = _T("*********************");
		m_Adresse = m_Nom;
		m_Ville = m_Nom;

		m_Cle.Empty();
		m_Pass.Empty();

		GetDlgItem(IDC_REGISTRE)->EnableWindow(FALSE);
		GetDlgItem(IDC_GENERE)->EnableWindow(TRUE);
	}

	if(Lic.m_IsRegistered)
	{
		m_Pass = Lic.m_Pass;

		GetDlgItem(IDC_REGISTRE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DEREGISTRE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_DEREGISTRE)->EnableWindow(FALSE);
	}

	UpdateData(FALSE);


}

void CGPLicDlg::OnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
	
}
