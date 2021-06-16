// NetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "E_140.h"
#include "NetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetDlg dialog


CNetDlg::CNetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetDlg)
	m_port = 0;
	m_net_addr = 0;
	//}}AFX_DATA_INIT
}


void CNetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetDlg)
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDV_MinMaxUInt(pDX, m_port, 1, 9999);
	DDX_Radio(pDX, IDC_RADIO1, m_net_addr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetDlg, CDialog)
	//{{AFX_MSG_MAP(CNetDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetDlg message handlers

BOOL CNetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetPrivateProfileStruct("network","port",&m_port,4,"e140.ini");
	GetPrivateProfileStruct("network","dest",&m_net_addr,4,"e140.ini");
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNetDlg::OnOK() 
{
	UpdateData(TRUE);
	WritePrivateProfileStruct("network","port",&m_port,4,"e140.ini");
	WritePrivateProfileStruct("network","dest",&m_net_addr,4,"e140.ini");
	CDialog::OnOK();
}
