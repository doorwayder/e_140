#if !defined(AFX_ADCOPTIONS_H__4D52A932_D4FC_44BF_BB70_754846908C36__INCLUDED_)
#define AFX_ADCOPTIONS_H__4D52A932_D4FC_44BF_BB70_754846908C36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ADCOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CADCOptions dialog

class CADCOptions : public CDialog
{
// Construction
public:
	CADCOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CADCOptions)
	enum { IDD = IDD_ADCDLG };
	UINT	m_blocksize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADCOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CADCOptions)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADCOPTIONS_H__4D52A932_D4FC_44BF_BB70_754846908C36__INCLUDED_)
