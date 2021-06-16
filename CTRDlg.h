#if !defined(AFX_CTRDLG_H__B594483B_80C1_4609_A7C8_557E284DCAAA__INCLUDED_)
#define AFX_CTRDLG_H__B594483B_80C1_4609_A7C8_557E284DCAAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CTRDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCTRDlg dialog

class CCTRDlg : public CDialog
{
// Construction
public:
	BYTE m_ControlTable[128];
	CCTRDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCTRDlg)
	enum { IDD = IDD_CTDLG };
	CListCtrl	m_controltable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCTRDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCTRDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRDLG_H__B594483B_80C1_4609_A7C8_557E284DCAAA__INCLUDED_)
