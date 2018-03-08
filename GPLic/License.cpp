#include "stdafx.h"
#include "License.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//
// Copyright (c) 1998-2014 COLIN Arnaud.
// Ecrit par Arnaud COLIN 
//


#include "Registry.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CString GetLRC(CString Str);

static char *pKEYu[] = {"Utilisateur",
							"Nom",
							"Prenom",
							"Adresse",
							"Code Postal",
							"Ville",
							"Pays"
						};

static char *pKEYo[] = {"Options",
							"Install",
							"Licence"
						};

static char *pKEYi[] = {"IDProduit",
							"Clef",
							"ClefExt",
							"Id"
						};

static char *pKEYv[] = {"Ver"};

static char *pKEY[] = {	"COLIN", 
						"Ver",
					};



#define VerifCRC if( GetLRC(m_ProduitID) != CRCProduit) return FALSE;



CLicense::CLicense(CString ProduitID) : CLicOption()
{
	m_ProduitID = ProduitID;
	m_IsRegistered = FALSE;
	m_IsRead = FALSE;
}

CLicense::~CLicense()
{

}

BOOL CLicense::Read()
{
	CString strTop;
	CRegistry Registry(HKEY_CURRENT_USER);

	VerifCRC

	strTop.Format("SOFTWARE\\%s\\%s\\",pKEY[0],m_ProduitID);

	CString Path;
	CString sAux;

	Path = strTop + pKEYu[0];

	if(!Registry.VerifyKey(HKEY_CURRENT_USER, Path))
		return FALSE;

	Registry.Open(HKEY_CURRENT_USER, Path);  
	Registry.Read(pKEYu[1], m_Nom);
	Registry.Read(pKEYu[2], m_Prenom);
	Registry.Read(pKEYu[3], m_Adresse);
	Registry.Read(pKEYu[4], m_CodePostal);
	Registry.Read(pKEYu[5], m_Ville);
	Registry.Read(pKEYu[6], m_Pays);
	Registry.Close();  

	Path = strTop;

	if(!Registry.VerifyKey(HKEY_CURRENT_USER, Path))
		return FALSE;

	Registry.Open(HKEY_CURRENT_USER, Path);  
	Registry.Read(pKEYv[0], sAux);
	Registry.Close();  

	SetVersion(sAux);

	Path = strTop + pKEYo[0];

	if(!Registry.VerifyKey(HKEY_CURRENT_USER, Path))
		return FALSE;

	Registry.Open(HKEY_CURRENT_USER, Path);  
	Registry.Read(pKEYo[1], sAux);
	SetInstaller(sAux);
	Registry.Read(pKEYo[2], sAux);
	SetPayer(sAux);
	Registry.Close();  


	Path = strTop + pKEYi[0];

	if(!Registry.VerifyKey(HKEY_CURRENT_USER, Path))
		return FALSE;

	Registry.Open(HKEY_CURRENT_USER, Path);  
	Registry.Read(pKEYi[1], m_Cle);
	Registry.Read(pKEYi[2], m_CleExt);
	Registry.Read(pKEYi[3], m_Pass);
	Registry.Close();  

	return TRUE;
}

BOOL CLicense::Register( )
{

	CString strTop;
	CRegistry Registry(HKEY_CURRENT_USER);

	VerifCRC

	if(m_Pass.GetLength() == 13 )
		m_Paye = CHAR2HDIGIT(m_Pass[9])*16 + CHAR2HDIGIT(m_Pass[10]);
	else
		m_Paye = 0;

	strTop.Format("SOFTWARE\\%s\\%s\\",pKEY[0],m_ProduitID);

	CString Path;

	Path = strTop + pKEYu[0];

	if(!Registry.VerifyKey(HKEY_CURRENT_USER, Path))
		Registry.CreateKey(HKEY_CURRENT_USER, Path);  

	if (Registry.Open(HKEY_CURRENT_USER, Path))
	{
		Registry.Write(pKEYu[1], m_Nom);
		Registry.Write(pKEYu[2], m_Prenom);
		Registry.Write(pKEYu[3], m_Adresse);
		Registry.Write(pKEYu[4], m_CodePostal);
		Registry.Write(pKEYu[5], m_Ville);
		Registry.Write(pKEYu[6], m_Pays);
		Registry.Close();  
	}
	Path = strTop;

	if(!Registry.VerifyKey(HKEY_CURRENT_USER, Path))
		Registry.CreateKey(HKEY_CURRENT_USER, Path);  

	Registry.Open(HKEY_CURRENT_USER, Path);  
	Registry.Write(pKEYv[0], GetVersion());
	Registry.Close();  


	Path = strTop + pKEYo[0];

	if(!Registry.VerifyKey(HKEY_CURRENT_USER, Path))
		Registry.CreateKey(HKEY_CURRENT_USER, Path);  

	if(Registry.Open(HKEY_CURRENT_USER, Path))
	{
		Registry.Write(pKEYo[1], GetInstaller());
		Registry.Write(pKEYo[2], GetPayer());
		Registry.Close();  
	}


	Path = strTop + pKEYi[0];

	if(!Registry.VerifyKey(HKEY_CURRENT_USER, Path))
		Registry.CreateKey(HKEY_CURRENT_USER, Path);  

	if(Registry.Open(HKEY_CURRENT_USER, Path))
	{
		Registry.Write(pKEYi[1], m_Cle);
		Registry.Write(pKEYi[2], m_CleExt);	
		Registry.Write(pKEYi[3], m_Pass);
		Registry.Close();  
	}

	return TRUE;
}

BOOL CLicense::CreateKey()
{
	return CreateKey(m_Cle,m_CleExt);
}


BOOL CLicense::CreateKey(CString& Key,CString& KeyExt)
{
	CString strReg;

	HRESULT hres = (HRESULT)0;

	strReg = m_ProduitID;
	strReg += GetVersion();
	strReg += GetInstaller();
	strReg += GetConcat();

	BYTE Reg5LRC[5] = {0,0,0,0,0};

	for( int i =0; i < strReg.GetLength(); i++)
	{
		Reg5LRC[i % 5] += (BYTE) (strReg[i]) + Reg5LRC[(i+4) % 5];
	};

	for( int i =0; i < 5; i++)
	{
		Reg5LRC[i] %= 16;
	};

	CString str;

	str.Format("%01hX%01hX%01hX%01hX%01hX",Reg5LRC[0],Reg5LRC[1],Reg5LRC[2],Reg5LRC[3],Reg5LRC[4]);

	Key = str;

	GUID thisID;

	hres = CoInitialize(NULL);
	if ((hres == S_OK) || (hres == (HRESULT)S_FALSE))
	{

		hres = CoCreateGuid((GUID FAR*)&thisID);
		CoUninitialize();
	};

	if (hres == S_OK)
	{
		DWORD RegSysLRC = 0;
		for (int i = 0; i < 6; i++)
		{
			RegSysLRC += ((DWORD)(thisID.Data4[i+2])) << (i<<1);
		};

		str.Format("%05lX", (RegSysLRC & 0xFFFFF));
		Key += str;
	}
	else
		Key += str;


	KeyExt.Format(HEXFORM,(((m_verMaj % 16) << 4) | (m_verMin % 16)));
	str.Format("%02lX", (m_Inst & 0xFF));
	KeyExt += str;

	str = Key;
	str += KeyExt;

	KeyExt += GetLRC(str);

	return TRUE;
}

#define PASSVECT 8
#define KEYVECT 14

#define PASSINXMIN_TYPE0 0
#define PASSINXMAX_TYPE0 4
#define PASSINXMIN_TYPE1 5
#define PASSINXMAX_TYPE1 9


BOOL CLicense::CreatePass(WORD& PassType,CString &Pass)
{
	BYTE PassMat[KEYVECT][PASSVECT];
	char PassMatText[(KEYVECT*PASSVECT)+1] =  
		"This note describes simplified DLL support that assumes "
		"interfaces between the application and the DLL and other";

	CString str;

	#define PMTC 0x9053E	
	DWORD dwPmtc = 0;

	BYTE KeyVect[KEYVECT];
	DWORD PassDigit;
	int inx, iny;

	for (inx = 0; inx < KEYVECT*PASSVECT; inx++) 
		dwPmtc += (inx+1) * (BYTE)PassMatText[inx];

	if (dwPmtc != PMTC)
	{	// une erreur d'integrité
		m_Pass.Empty();
		return FALSE;
	};

	if(m_Cle.GetLength() != 10) 
	{
		m_Pass.Empty();
		return FALSE;
	}

	if(m_CleExt.GetLength() != 6) 
	{
		m_Pass.Empty();
		return FALSE;
	}
	

	// création du vector KeyVect
	for (inx = 0; inx < 10; inx++) KeyVect[inx] = CHAR2HDIGIT(m_Cle[inx]);
	for (inx = 0; inx < 2; inx++) KeyVect[10+inx] = CHAR2HDIGIT(m_CleExt[inx]);
	str.Format("%02lX", m_Paye);
	for (inx = 0; inx < 2; inx++) KeyVect[12+inx] = CHAR2HDIGIT(str[inx]);
	// initialiser la matrice de conversion
	for (iny = 0; iny < PASSVECT; iny++) 
		for (inx = 0; inx < KEYVECT; inx++)
	{
		PassMat[inx][iny] = (BYTE)PassMatText[iny*KEYVECT + inx];
		PassMat[inx][iny] ^= (PassMat[inx][iny] >> 4);
		PassMat[inx][iny] &= 0x0F;
	};
	// calculer mot de passe
	Pass.Format("%01hu", PassType);
	for (iny = 0; iny < PASSVECT; iny++)
	{
		PassDigit = 0;
		for (inx = 0; inx < KEYVECT; inx++)
		{
			switch (PassType)
			{
			case 0:
				if ( (inx >= PASSINXMIN_TYPE0) && (inx <= PASSINXMAX_TYPE0) )
					PassDigit += (DWORD)PassMat[inx][iny] * (DWORD)KeyVect[inx];
				break;
			case 1:
				if ( (inx >= PASSINXMIN_TYPE1) && (inx <= PASSINXMAX_TYPE1) )
					PassDigit += (DWORD)PassMat[inx][iny] * (DWORD)KeyVect[inx];
				break;
			case 2:
			default:
				PassDigit += (DWORD)PassMat[inx][iny] * (DWORD)KeyVect[inx];
				break;
			};
		};
		PassDigit &= 0x0F;
		str.Format("%01lX", PassDigit);
		Pass += str;
	};

	// ajouter des options payées
	str.Format("%02lX", m_Paye);
	Pass += str;

	// callule LRC
	Pass += GetLRC(Pass);

	return TRUE;
}

BOOL CLicense::CreatePass(WORD& PassType)
{
	return CreatePass(PassType,m_Pass);
}

BOOL CLicense::IsCleValide()
{
	CString str;
	str = m_Cle;
	str += m_CleExt.Left(m_CleExt.GetLength()-1);

	CString LRC =  GetLRC(str);
	if (LRC = m_CleExt[4])
		return TRUE;
	else
		return FALSE;
}

BOOL CLicense::IsPassValide()
{
	CString str;
	str = m_Pass;

	CString LRC =  GetLRC(str);
	if (LRC = m_Pass[11])
		return TRUE;
	else
		return FALSE;
}

BOOL CLicense::IsRegistered(WORD OpID)
{

	WORD wPassType;

	if( m_Pass.GetLength() != 13 )  return FALSE;
	if( m_Cle.GetLength() != 10 )  return FALSE;
	if( m_CleExt.GetLength() != 6 )  return FALSE;

	VerifCRC

	if ( (m_Paye & (OpID)) != (OpID) ) return FALSE;

	if(!IsCleValide()) return FALSE;

	CString Key;
	CString KeyExt;

	if(!CreateKey(Key,KeyExt)) return FALSE;

	wPassType = (WORD)CHAR2HDIGIT(m_Pass[0]);

	switch (wPassType)
	{
	case 0:	// type user - verification du code à partir de données d'utilisateur
		if ( ( Key.Left(5) !=  m_Cle.Left(5) )
			|| ( KeyExt.Left(4) != m_CleExt.Left(4)) ) return FALSE;
		break;
	case 1:	// type machine - verification du code à partir de code machine
		if ( (Key.Right(Key.GetLength()-5) != m_Cle.Right(m_Cle.GetLength()-5)  )
			|| (KeyExt.Right(KeyExt.GetLength()-4) != m_CleExt.Right(m_CleExt.GetLength()-4)) ) return FALSE;
		break;
	case 2:
	default:
		if (( Key != m_Cle)
			|| (KeyExt != m_CleExt) ) return FALSE;
		break;
	};
	
	CString Pass;

	if(!CreatePass(wPassType,Pass)) return FALSE;


	if (m_Pass != Pass) return FALSE;


	return TRUE;
}


CString GetLRC(CString Str)
{
	int inx;
	int len;
	BYTE byLRC;
	CString sAux;

	len = Str.GetLength();

	byLRC = 0;
	for (inx = 0; inx < len; inx++) 
		byLRC ^= ((BYTE)(Str[inx]) % 0x30)*(inx+1);

	sAux.Format(HEXFORM,byLRC);

	return sAux;
}


void CLicense::Destroy()
{
	CString strTop;
	CRegistry Registry(HKEY_CURRENT_USER);

	strTop.Format("SOFTWARE\\%s\\%s\\",pKEY[0],m_ProduitID);

	CString Path;

	Path = strTop + pKEYu[0];

	Registry.Open(HKEY_CURRENT_USER, Path);  
	Registry.DeleteValueKey (HKEY_CURRENT_USER, Path);
	Registry.Close();  

	Path = strTop;

	Registry.Open(HKEY_CURRENT_USER, Path);  
	Registry.DeleteValueKey (HKEY_CURRENT_USER, Path);
	Registry.Close();  


	Path = strTop + pKEYo[0];

	Registry.Open(HKEY_CURRENT_USER, Path);  
	Registry.DeleteValueKey (HKEY_CURRENT_USER, Path);
	Registry.Close();  


	Path = strTop + pKEYi[0];

	Registry.Open(HKEY_CURRENT_USER, Path);  
	Registry.DeleteValueKey (HKEY_CURRENT_USER, Path);
	Registry.Close();  


	Path = strTop;

	Registry.Open(HKEY_CURRENT_USER, Path);  
	Registry.DeleteValueKey (HKEY_CURRENT_USER, Path);
	Registry.Close();


}
