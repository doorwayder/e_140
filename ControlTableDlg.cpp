// ControlTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "E_140.h"
#include "ControlTableDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include <stdio.h>
/////////////////////////////////////////////////////////////////////////////
// CControlTableDlg dialog
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

CControlTableDlg::CControlTableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControlTableDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControlTableDlg)
	m_bit1 = 0;
	m_bit2 = 0;
	m_bit3 = 0;
	m_bit4 = 0;
	m_bit5 = 0;
	m_bit6 = 0;
	m_bit7 = 0;
	m_bit8 = 0;
	m_currentcell = 1;
	m_chnum = 0;
	m_hex = _T("");
	m_descr = _T("");
	//}}AFX_DATA_INIT
}


void CControlTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlTableDlg)
	DDX_Text(pDX, IDC_EDIT1, m_bit1);
	DDV_MinMaxUInt(pDX, m_bit1, 0, 1);
	DDX_Text(pDX, IDC_EDIT7, m_bit2);
	DDV_MinMaxUInt(pDX, m_bit2, 0, 1);
	DDX_Text(pDX, IDC_EDIT8, m_bit3);
	DDV_MinMaxUInt(pDX, m_bit3, 0, 1);
	DDX_Text(pDX, IDC_EDIT3, m_bit4);
	DDV_MinMaxUInt(pDX, m_bit4, 0, 1);
	DDX_Text(pDX, IDC_EDIT10, m_bit5);
	DDV_MinMaxUInt(pDX, m_bit5, 0, 1);
	DDX_Text(pDX, IDC_EDIT2, m_bit6);
	DDV_MinMaxUInt(pDX, m_bit6, 0, 1);
	DDX_Text(pDX, IDC_EDIT9, m_bit7);
	DDV_MinMaxUInt(pDX, m_bit7, 0, 1);
	DDX_Text(pDX, IDC_EDIT4, m_bit8);
	DDV_MinMaxUInt(pDX, m_bit8, 0, 1);
	DDX_Text(pDX, IDC_EDIT5, m_currentcell);
	DDV_MinMaxUInt(pDX, m_currentcell, 1, 128);
	DDX_Text(pDX, IDC_EDIT6, m_chnum);
	DDV_MinMaxByte(pDX, m_chnum, 0, 128);
	DDX_Text(pDX, IDC_EDIT11, m_hex);
	DDV_MaxChars(pDX, m_hex, 3);
	DDX_Text(pDX, IDC_EDIT12, m_descr);
	DDV_MaxChars(pDX, m_descr, 50);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControlTableDlg, CDialog)
	//{{AFX_MSG_MAP(CControlTableDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnLoad)
	ON_BN_CLICKED(IDVBUTTON, OnViewTable)
	ON_BN_CLICKED(IDC_BUTTON3, OnSave)
	ON_BN_CLICKED(IDC_BUTTON4, OnNext)
	ON_BN_CLICKED(IDC_BUTTON5, OnPrevious)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeChannel)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeBit1)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeBit2)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeBit3)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeBit4)
	ON_EN_CHANGE(IDC_EDIT10, OnChangeBit5)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeBit6)
	ON_EN_CHANGE(IDC_EDIT9, OnChangeBit7)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeBit8)
	ON_EN_CHANGE(IDC_EDIT6, OnChangePortNum)
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlTableDlg message handlers

BOOL CControlTableDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	EnableToolTips();
	ReadCTRByte();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CControlTableDlg::OnLoad() 
{
	char str[50];
	BOOL read=TRUE;
	CFileDialog fileDialog(TRUE,NULL,"",NULL,"ControlTables(ControlTable.bin)|*.bin|");	
	int result = fileDialog.DoModal();
	if (result==IDOK)
	{
	lpath=fileDialog.GetPathName();
	FILE *tableFile;
	tableFile=fopen(lpath,"rb");
	for (int i=0;i<128;i++)
	{
		if (fread(&m_ControlTable[i],1,1,tableFile)!=1) {read=FALSE;break;}
	}
	if (fread(&str,50,1,tableFile)!=1) read=FALSE;
	m_descr=str;
	fclose(tableFile);
	m_currentcell=1;
	UpdateData(FALSE);
	ReadCTRByte();
	if (!read) AfxMessageBox("Incorrect File Size!");
	}
}

void CControlTableDlg::OnSave() 
{
	char str[50];
	UpdateData(TRUE);
	BOOL writed=TRUE;
	CFileDialog fileDialog(FALSE,NULL,"",OFN_OVERWRITEPROMPT,"ControlTables(ControlTable.bin)|*.bin|");	
	CString path;
	int result = fileDialog.DoModal();
	if (result==IDOK)
	{
	path=fileDialog.GetPathName();
	FILE *tableFile;
	tableFile=fopen(path,"wb");
	for (int i=0;i<128;i++)
	{
		if (fwrite(&m_ControlTable[i],1,1,tableFile)!=1) {writed=FALSE;break;};
	}
	strcpy(str,m_descr.GetBuffer(0));
	m_descr.ReleaseBuffer(50);
	if (fwrite(str,50,1,tableFile)!=1) writed=FALSE;
	fclose(tableFile);
	if (!writed) AfxMessageBox("Error Writing File!");
	}
}

void CControlTableDlg::OnOK() 
{
	CDialog::OnOK();
}

void CControlTableDlg::OnViewTable() 
{
	CCTRDlg dlg;
	for (int i=0;i<128;i++) dlg.m_ControlTable[i]=m_ControlTable[i];
	dlg.DoModal();
}


void CControlTableDlg::OnNext() 
{
	if (m_currentcell<128)
	{
	UpdateData(TRUE);
	m_currentcell++;
	UpdateData(FALSE);
	ReadCTRByte();
	}
}

void CControlTableDlg::OnPrevious() 
{
	if (m_currentcell>1)
	{
	UpdateData(TRUE);
	m_currentcell--;
	UpdateData(FALSE);
	ReadCTRByte();
	}
}

void CControlTableDlg::OnChangeChannel() 
{
	UpdateData(TRUE);
	if ((m_currentcell>0)&&(m_currentcell<129))
	{
	ReadCTRByte();
	UpdateData(FALSE);
	}else {m_currentcell=1;UpdateData(FALSE);}
}

void CControlTableDlg::OnChangeBit1() 
{
	ControlByte Byte;
	UpdateData(TRUE);
	if ((m_bit1==1)||(m_bit1==0))
	{
	Byte.Bits.bit1=m_bit1;
	Byte.Bits.bit2=m_bit2;
	Byte.Bits.bit3=m_bit3;
	Byte.Bits.bit4=m_bit4;
	Byte.Bits.bit5=m_bit5;
	Byte.Bits.bit6=m_bit6;
	Byte.Bits.bit7=m_bit7;
	Byte.Bits.bit8=m_bit8;
	m_ControlTable[m_currentcell-1]=Byte.Byte;
	ReadCTRByte();
	}else {m_bit1=1;UpdateData(FALSE);}
}

void CControlTableDlg::OnChangeBit2() 
{
	ControlByte Byte;
	UpdateData(TRUE);
	if ((m_bit2==1)||(m_bit2==0))
	{
	Byte.Bits.bit1=m_bit1;
	Byte.Bits.bit2=m_bit2;
	Byte.Bits.bit3=m_bit3;
	Byte.Bits.bit4=m_bit4;
	Byte.Bits.bit5=m_bit5;
	Byte.Bits.bit6=m_bit6;
	Byte.Bits.bit7=m_bit7;
	Byte.Bits.bit8=m_bit8;
	m_ControlTable[m_currentcell-1]=Byte.Byte;
	ReadCTRByte();
	}else {m_bit2=1;UpdateData(FALSE);}
}

void CControlTableDlg::OnChangeBit3() 
{
	ControlByte Byte;
	UpdateData(TRUE);
	if ((m_bit3==1)||(m_bit3==0))
	{
	Byte.Bits.bit1=m_bit1;
	Byte.Bits.bit2=m_bit2;
	Byte.Bits.bit3=m_bit3;
	Byte.Bits.bit4=m_bit4;
	Byte.Bits.bit5=m_bit5;
	Byte.Bits.bit6=m_bit6;
	Byte.Bits.bit7=m_bit7;
	Byte.Bits.bit8=m_bit8;
	m_ControlTable[m_currentcell-1]=Byte.Byte;
	ReadCTRByte();
	}else {m_bit3=1;UpdateData(FALSE);}
}

void CControlTableDlg::OnChangeBit4() 
{
	ControlByte Byte;
	UpdateData(TRUE);
	if ((m_bit4==1)||(m_bit4==0))
	{
	Byte.Bits.bit1=m_bit1;
	Byte.Bits.bit2=m_bit2;
	Byte.Bits.bit3=m_bit3;
	Byte.Bits.bit4=m_bit4;
	Byte.Bits.bit5=m_bit5;
	Byte.Bits.bit6=m_bit6;
	Byte.Bits.bit7=m_bit7;
	Byte.Bits.bit8=m_bit8;
	m_ControlTable[m_currentcell-1]=Byte.Byte;
	ReadCTRByte();
	}else {m_bit4=1;UpdateData(FALSE);}
}

void CControlTableDlg::OnChangeBit5() 
{
	ControlByte Byte;
	UpdateData(TRUE);
	if ((m_bit5==1)||(m_bit5==0))
	{
	Byte.Bits.bit1=m_bit1;
	Byte.Bits.bit2=m_bit2;
	Byte.Bits.bit3=m_bit3;
	Byte.Bits.bit4=m_bit4;
	Byte.Bits.bit5=m_bit5;
	Byte.Bits.bit6=m_bit6;
	Byte.Bits.bit7=m_bit7;
	Byte.Bits.bit8=m_bit8;
	m_ControlTable[m_currentcell-1]=Byte.Byte;
	ReadCTRByte();
	}else {m_bit5=1;UpdateData(FALSE);}
}

void CControlTableDlg::OnChangeBit6() 
{
	ControlByte Byte;
	UpdateData(TRUE);
	if ((m_bit6==1)||(m_bit6==0))
	{
	Byte.Bits.bit1=m_bit1;
	Byte.Bits.bit2=m_bit2;
	Byte.Bits.bit3=m_bit3;
	Byte.Bits.bit4=m_bit4;
	Byte.Bits.bit5=m_bit5;
	Byte.Bits.bit6=m_bit6;
	Byte.Bits.bit7=m_bit7;
	Byte.Bits.bit8=m_bit8;
	m_ControlTable[m_currentcell-1]=Byte.Byte;
	ReadCTRByte();
	}else {m_bit6=1;UpdateData(FALSE);}
}

void CControlTableDlg::OnChangeBit7() 
{
	ControlByte Byte;
	UpdateData(TRUE);
	if ((m_bit7==1)||(m_bit7==0))
	{
	Byte.Bits.bit1=m_bit1;
	Byte.Bits.bit2=m_bit2;
	Byte.Bits.bit3=m_bit3;
	Byte.Bits.bit4=m_bit4;
	Byte.Bits.bit5=m_bit5;
	Byte.Bits.bit6=m_bit6;
	Byte.Bits.bit7=m_bit7;
	Byte.Bits.bit8=m_bit8;
	m_ControlTable[m_currentcell-1]=Byte.Byte;
	ReadCTRByte();
	}else {m_bit7=1;UpdateData(FALSE);}
}

void CControlTableDlg::OnChangeBit8() 
{
	ControlByte Byte;
	UpdateData(TRUE);
	if ((m_bit8==1)||(m_bit8==0))
	{
	Byte.Bits.bit1=m_bit1;
	Byte.Bits.bit2=m_bit2;
	Byte.Bits.bit3=m_bit3;
	Byte.Bits.bit4=m_bit4;
	Byte.Bits.bit5=m_bit5;
	Byte.Bits.bit6=m_bit6;
	Byte.Bits.bit7=m_bit7;
	Byte.Bits.bit8=m_bit8;
	m_ControlTable[m_currentcell-1]=Byte.Byte;
	ReadCTRByte();
	}else {m_bit8=1;UpdateData(FALSE);}
}

void CControlTableDlg::OnChangePortNum() 
{
	ControlByte Byte1,Byte2;
	UpdateData(TRUE);
	if ((m_chnum>=0)&&(m_chnum<=32))
	{
	Byte1.Byte=m_ControlTable[m_currentcell-1];
	Byte2.Byte=m_chnum;
	Byte1.Bits.bit1=Byte2.Bits.bit1;Byte1.Bits.bit2=Byte2.Bits.bit2;
	Byte1.Bits.bit3=Byte2.Bits.bit3;Byte1.Bits.bit4=Byte2.Bits.bit4;
	if (m_bit6==1) Byte1.Bits.bit5=Byte2.Bits.bit5;
	m_bit1=Byte1.Bits.bit1;m_bit2=Byte1.Bits.bit2;m_bit3=Byte1.Bits.bit3;m_bit4=Byte1.Bits.bit4;
	m_bit5=Byte1.Bits.bit5;m_bit6=Byte1.Bits.bit6;m_bit7=Byte1.Bits.bit7;m_bit8=Byte1.Bits.bit8;
	m_ControlTable[m_currentcell-1]=Byte1.Byte;
	UpdateData(FALSE);
	}else {m_chnum=0;UpdateData(FALSE);}
}

void CControlTableDlg::ReadCTRByte()
{
	UpdateData(TRUE);
	ControlByte Byte;
	Byte.Byte=m_ControlTable[m_currentcell-1];
	m_bit1=Byte.Bits.bit1;
	m_bit2=Byte.Bits.bit2;
	m_bit3=Byte.Bits.bit3;
	m_bit4=Byte.Bits.bit4;
	m_bit5=Byte.Bits.bit5;
	m_bit6=Byte.Bits.bit6;
	m_bit7=Byte.Bits.bit7;
	m_bit8=Byte.Bits.bit8;
	if (m_bit6==0) m_chnum=(Byte.Bits.bit1<<0 |Byte.Bits.bit2<<1 | Byte.Bits.bit3<<2 | Byte.Bits.bit4<<3);
	else m_chnum=(Byte.Bits.bit1<<0 |Byte.Bits.bit2<<1 | Byte.Bits.bit3<<2 | Byte.Bits.bit4<<3 | Byte.Bits.bit5<<4);
	m_hex.Format("%02x",Byte.Byte);
	m_hex.MakeUpper();
	m_hex+="h";
	UpdateData(FALSE);
}

BOOL CControlTableDlg::OnToolTipNotify(UINT id,NMHDR* pNMHDR,LRESULT* pResult)
{
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
    UINT nID =pNMHDR->idFrom;
    if (pTTT->uFlags & TTF_IDISHWND)
    {
    // TTF_IDISHWND означает, что idFrom - это и есть HWND эл-та управления
    //проверяем класс
    TCHAR szClsName[100];
    GetClassName((HWND)nID,szClsName,100);
    nID = ::GetDlgCtrlID((HWND)nID);
        if(nID)
        {
            pTTT->lpszText = MAKEINTRESOURCE(nID);
            pTTT->hinst = AfxGetResourceHandle();
            return(TRUE);
        }
    }
    return(FALSE);
}

