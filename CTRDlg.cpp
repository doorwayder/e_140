// CTRDlg.cpp : implementation file
//

#include "stdafx.h"
#include "E_140.h"
#include "CTRDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCTRDlg dialog
struct ControlBits
	{
		UINT bit1:1;
		UINT bit2:1;
		UINT bit3:1;
		UINT bit4:1;
		UINT bit5:1;
		UINT bit6:1;
		UINT bit7:1;
		UINT bit8:1;
	};
	
	union ControlByte
	{
		ControlBits Bits;
		BYTE Byte;
	};

CCTRDlg::CCTRDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCTRDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCTRDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCTRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCTRDlg)
	DDX_Control(pDX, IDC_LIST1, m_controltable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCTRDlg, CDialog)
	//{{AFX_MSG_MAP(CCTRDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCTRDlg message handlers

BOOL CCTRDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_controltable.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	LV_COLUMN Col;
    Col.mask=LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	Col.fmt=LVCFMT_LEFT;
    Col.cx=80;
	Col.iSubItem=0;
	Col.pszText="bitVOL";
	m_controltable.InsertColumn(0,&Col);
	Col.iSubItem=1;
	Col.cx=20;
	m_controltable.InsertColumn(1,&Col);
	Col.iSubItem=2;
	Col.cx=20;
	m_controltable.InsertColumn(2,&Col);
	Col.iSubItem=3;
	Col.cx=20;
	m_controltable.InsertColumn(3,&Col);
	Col.iSubItem=4;
	Col.cx=20;
	m_controltable.InsertColumn(4,&Col);
	Col.iSubItem=5;
	Col.cx=20;
	m_controltable.InsertColumn(5,&Col);
	Col.iSubItem=6;
	Col.cx=20;
	m_controltable.InsertColumn(6,&Col);
	Col.iSubItem=7;
	Col.cx=20;
	m_controltable.InsertColumn(7,&Col);
	Col.iSubItem=8;
	Col.cx=20;
	m_controltable.InsertColumn(8,&Col);
	Col.iSubItem=9;
	Col.cx=40;
	m_controltable.InsertColumn(9,&Col);
	//insert items
	for (int i=0;i<128;i++)
	{
	LV_ITEM it;
	it.mask=LVIF_TEXT;
	it.state=0;
	it.stateMask=0;
	it.iItem=i;//number
	it.iSubItem=0;
	it.pszText="1";
	m_controltable.InsertItem(&it);
	CString num,txt="Channel_";
	num.Format("%d",(i+1));
	txt+=num;
	txt+=":";
	m_controltable.SetItemText(i,0,txt);
	ControlByte Byte;
	Byte.Byte=m_ControlTable[i];

	CString tmp;
		tmp.Format("%d",Byte.Bits.bit1);
	m_controltable.SetItemText(i,1,tmp);
		tmp.Format("%d",Byte.Bits.bit2);
	m_controltable.SetItemText(i,2,tmp);
		tmp.Format("%d",Byte.Bits.bit3);
	m_controltable.SetItemText(i,3,tmp);
		tmp.Format("%d",Byte.Bits.bit4);
	m_controltable.SetItemText(i,4,tmp);
		tmp.Format("%d",Byte.Bits.bit5);
	m_controltable.SetItemText(i,5,tmp);
		tmp.Format("%d",Byte.Bits.bit6);
	m_controltable.SetItemText(i,6,tmp);
		tmp.Format("%d",Byte.Bits.bit7);
	m_controltable.SetItemText(i,7,tmp);
		tmp.Format("%d",Byte.Bits.bit8);
	m_controltable.SetItemText(i,8,tmp);
	
	num.Format("%02x",Byte.Byte);
	num.MakeUpper();
	num+="h";
	m_controltable.SetItemText(i,9,num);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
