// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__A763E50C_0018_4C5F_8610_4D9BA71EE547__INCLUDED_)
#define AFX_DLGPROXY_H__A763E50C_0018_4C5F_8610_4D9BA71EE547__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CE_140Dlg;

/////////////////////////////////////////////////////////////////////////////
// CE_140DlgAutoProxy command target

class CE_140DlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CE_140DlgAutoProxy)

	CE_140DlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CE_140Dlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CE_140DlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CE_140DlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CE_140DlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CE_140DlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CE_140DlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__A763E50C_0018_4C5F_8610_4D9BA71EE547__INCLUDED_)
