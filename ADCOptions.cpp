// ADCOptions.cpp : implementation file
//

#include "stdafx.h"
#include "E_140.h"
#include "ADCOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CADCOptions dialog


CADCOptions::CADCOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CADCOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CADCOptions)
	m_blocksize = 32;
	//}}AFX_DATA_INIT
}


void CADCOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CADCOptions)
	DDX_Text(pDX, IDC_EDIT1, m_blocksize);
	DDV_MinMaxUInt(pDX, m_blocksize, 2, 1024);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CADCOptions, CDialog)
	//{{AFX_MSG_MAP(CADCOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADCOptions message handlers

BOOL CADCOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetPrivateProfileStruct("ADC","block_size",&m_blocksize,4,"e140.ini");
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CADCOptions::OnOK() 
{
	UpdateData(TRUE);
	WritePrivateProfileStruct("adc","block_size",&m_blocksize,4,"e140.ini");
	CDialog::OnOK();
}
