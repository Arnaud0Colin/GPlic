#if !defined(AFX_REGISTRY_H__0A6FA073_1818_11D2_B152_00C04F829FFD__INCLUDED_)
#define AFX_REGISTRY_H__0A6FA073_1818_11D2_B152_00C04F829FFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//
// Copyright (c) 1998-2014 COLIN Arnaud.
// Ecrit par Arnaud COLIN 
//

#include <winreg.h>

class CRegistry : public CObject
{
// Construction
public:
	CRegistry(HKEY hKeyRoot = HKEY_CURRENT_USER);
	virtual ~CRegistry();

	struct REGINFO
	{
		LONG lMessage;
		DWORD dwType;
		DWORD dwSize;
	} m_Info;
// Operations
public:
	BOOL VerifyKey (HKEY hKeyRoot, LPCTSTR pszPath);
	BOOL VerifyKey (LPCTSTR pszPath);
	BOOL VerifyValue (LPCTSTR pszValue);
	BOOL CreateKey (HKEY hKeyRoot, LPCTSTR pszPath);
	BOOL Open (HKEY hKeyRoot, LPCTSTR pszPath);
	void Close();

	BOOL DeleteValue (LPCTSTR pszValue);
	BOOL DeleteValueKey (HKEY hKeyRoot, LPCTSTR pszPath);

	BOOL Write (LPCTSTR pszKey, int iVal);
	BOOL Write (LPCTSTR pszKey, DWORD dwVal);
	BOOL Write (LPCTSTR pszKey, LPCTSTR pszVal);
	BOOL Write (LPCTSTR pszKey, CStringList& scStringList);
	BOOL Write (LPCTSTR pszKey, CByteArray& bcArray);
	BOOL Write (LPCTSTR pszKey, CStringArray& scArray);
	BOOL Write (LPCTSTR pszKey, CDWordArray& dwcArray);
	BOOL Write (LPCTSTR pszKey, CWordArray& wcArray);

	BOOL Read (LPCTSTR pszKey, int& iVal);
	BOOL Read (LPCTSTR pszKey, DWORD& dwVal);
	BOOL Read (LPCTSTR pszKey, CString& sVal);
	BOOL Read (LPCTSTR pszKey, CStringList& scStringList);
	BOOL Read (LPCTSTR pszKey, CStringArray& scArray);
	BOOL Read (LPCTSTR pszKey, CDWordArray& dwcArray);
	BOOL Read (LPCTSTR pszKey, CWordArray& wcArray);
	BOOL Read (LPCTSTR pszKey, CByteArray& bcArray);

protected:	
	HKEY 	m_hKey;
	CString m_sPath;
};

#endif // !defined(AFX_REGISTRY_H__0A6FA073_1818_11D2_B152_00C04F829FFD__INCLUDED_)