#if !defined(AFX_CONTROLTABLEDLG_H__9115A87A_5174_4E52_A18A_DFCF594C4818__INCLUDED_)
#define AFX_CONTROLTABLEDLG_H__9115A87A_5174_4E52_A18A_DFCF594C4818__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControlTableDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CControlTableDlg dialog

#include <iostream>
#include "CTRDlg.h"

class CControlTableDlg : public CDialog
{
// Construction
public:
	CString lpath;
	void ReadCTRByte();
	BYTE m_ControlTable[128];
	CControlTableDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CControlTableDlg)
	enum { IDD = IDD_CTABLEDLG };
	UINT	m_bit1;
	UINT	m_bit2;
	UINT	m_bit3;
	UINT	m_bit4;
	UINT	m_bit5;
	UINT	m_bit6;
	UINT	m_bit7;
	UINT	m_bit8;
	UINT	m_currentcell;
	BYTE	m_chnum;
	CString	m_hex;
	CString	m_descr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlTableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CControlTableDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLoad();
	afx_msg void OnViewTable();
	virtual void OnOK();
	afx_msg void OnSave();
	afx_msg void OnNext();
	afx_msg void OnPrevious();
	afx_msg void OnChangeChannel();
	afx_msg void OnChangeBit1();
	afx_msg void OnChangeBit2();
	afx_msg void OnChangeBit3();
	afx_msg void OnChangeBit4();
	afx_msg void OnChangeBit5();
	afx_msg void OnChangeBit6();
	afx_msg void OnChangeBit7();
	afx_msg void OnChangeBit8();
	afx_msg void OnChangePortNum();
	afx_msg BOOL OnToolTipNotify(UINT id,NMHDR* pNMHDR,LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLTABLEDLG_H__9115A87A_5174_4E52_A18A_DFCF594C4818__INCLUDED_)
