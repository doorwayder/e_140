// E_140.h : main header file for the E_140 application
//

#if !defined(AFX_E_140_H__A1166E52_14CE_4A4F_B99A_06D1A46501D3__INCLUDED_)
#define AFX_E_140_H__A1166E52_14CE_4A4F_B99A_06D1A46501D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CE_140App:
// See E_140.cpp for the implementation of this class
//

class CE_140App : public CWinApp
{
public:
	CE_140App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CE_140App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CE_140App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_E_140_H__A1166E52_14CE_4A4F_B99A_06D1A46501D3__INCLUDED_)


