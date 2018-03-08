#if !defined(AFX_LICENSE_H__9D3EB2F2_127C_11D2_B14A_00C04F829FFD__INCLUDED_)
#define AFX_LICENSE_H__9D3EB2F2_127C_11D2_B14A_00C04F829FFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// License.h: interface for the CLicense class.
//
//
// Copyright (c) 1998-2014 COLIN Arnaud.
// Ecrit par Arnaud COLIN 
//

#include "SpApp.h"


#define CHAR2HDIGIT(c) ((((BYTE)(c)>0x2F)&&((BYTE)(c)<0x3A))?((BYTE)(c)-0x30):(((((BYTE)(c)>0x40)&&((BYTE)(c)<0x47))?((BYTE)(c)-0x37):0)))
#define CHAR2DDIGIT(c) ( (((BYTE)(c)>0x2F)&&((BYTE)(c)<0x3A)) ? ((BYTE)(c)-0x30) : 0 )

const char HEXFORM[5] = _T("%02X");

class CLicUser
{
public:
	CString m_Nom;
	CString m_Prenom;
	CString m_Adresse;
	CString m_CodePostal;
	CString m_Ville;
	CString m_Pays;

	CString GetConcat()
	{
		CString sAux;
		sAux = m_Nom;
		sAux += m_Prenom;
		sAux += m_Adresse;
		sAux += m_CodePostal;
		sAux += m_Ville;
		sAux += m_Pays;
		return sAux;
	}
};

class CLicOption
{
public:
	DWORD m_Inst;
	DWORD m_Paye;
	
	CLicOption() { m_Inst = 0; m_Paye = 0; }

	void SetInstaller(CString sAux) { m_Inst = CHAR2HDIGIT(sAux[0])*16 + CHAR2HDIGIT(sAux[1]); }
	void SetPayer(CString sAux) { m_Paye = CHAR2HDIGIT(sAux[0])*16 + CHAR2HDIGIT(sAux[1]); }

	CString GetInstaller() 
	{
		CString sAux;
		sAux.Format(HEXFORM,m_Inst);
		return sAux;
	}

	CString GetPayer() 
	{
		CString sAux;
		sAux.Format(HEXFORM,m_Paye);
		return sAux;
	}
};


class CLicVer
{
public:
	short m_verMaj;
	short m_verMin;

	CLicVer() { m_verMaj = 1; m_verMin = 0; }

	void SetVersion(CString sAux)
	{
		m_verMaj = CHAR2DDIGIT(sAux[0]);
		m_verMin = CHAR2DDIGIT(sAux[2]);
	}

	CString GetVersion()
	{
		CString sAux;
		sAux.Format("%01hu.%01hu",m_verMaj,m_verMin);
		return sAux;
	}
};

class CLicense : public CLicUser,public CLicVer, public CLicOption
{

public:
	CString m_Cle;
	CString m_CleExt;
	CString m_Pass;

	CString m_ProduitID;

	BOOL m_IsRegistered;
	BOOL m_IsRead;

public:
	void Destroy();
	CLicense(CString ProduitID);
	virtual ~CLicense();

	BOOL Register();
	BOOL Read();
	BOOL CreateKey();
	BOOL CreateKey(CString& Key,CString& KeyExt);
	BOOL CreatePass(WORD& PassType);
	BOOL CreatePass(WORD& PassType,CString &Pass);
	

	BOOL IsRegistered(WORD OpID);

	void Lecture(WORD OpID)
	{
		m_IsRead = Read();
		m_IsRegistered = IsRegistered(OpID);
	}


	
	BOOL IsCleValide();
	BOOL IsPassValide();

};





#endif // !defined(AFX_LICENSE_H__9D3EB2F2_127C_11D2_B14A_00C04F829FFD__INCLUDED_)
