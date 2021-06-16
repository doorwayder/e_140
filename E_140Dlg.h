// E_140Dlg.h : header file
//

#if !defined(AFX_E_140DLG_H__656932F1_22D0_4CB2_9B5F_0C0E85C79195__INCLUDED_)
#define AFX_E_140DLG_H__656932F1_22D0_4CB2_9B5F_0C0E85C79195__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CE_140DlgAutoProxy;

#include "ControlTableDlg.h"
#include "NetDlg.h"
#include "ADCOptions.h"
/////////////////////////////////////////////////////////////////////////////
// CE_140Dlg dialog

class CE_140Dlg : public CDialog
{
	DECLARE_DYNAMIC(CE_140Dlg);
	friend class CE_140DlgAutoProxy;

// Construction
public:
	char lpath[250];
	BOOL Connect();
	void vEnableControls(BOOL enable);
	BYTE m_ControlTable[128];
	BOOL Disconnect();
	CE_140Dlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CE_140Dlg();

// Dialog Data
	//{{AFX_DATA(CE_140Dlg)
	enum { IDD = IDD_E_140_DIALOG };
	CButton	m_rad3;
	CButton	m_rad2;
	CEdit	wSAC;
	CSpinButtonCtrl	m_spin;
	CListCtrl	m_color;
	CListBox	m_info;
	BOOL	m_ClcSource;
	BOOL	m_EnableClkOutput;
	UINT	m_SAC;
	int		m_inputmode;
	int		m_analogsynctype;
	int		m_analogsyncmode;
	int		m_SAP;
	UINT	m_ChQ;
	double	m_discreet;
	UINT	m_IKD;
	double	m_IKDF;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CE_140Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CE_140DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CE_140Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnConnect();
	afx_msg void OnRadio4();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnChangeEdit2();
	afx_msg void OnSaveasdefault();
	afx_msg void OnCheck1();
	afx_msg void OnControlTable();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit4();
	afx_msg void OnOptionsNetwork();
	afx_msg void OnOptionsAdcdacdevice();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_E_140DLG_H__656932F1_22D0_4CB2_9B5F_0C0E85C79195__INCLUDED_)
