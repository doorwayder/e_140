// E_140Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "E_140.h"
#include "E_140Dlg.h"
#include "DlgProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//ADC variables
UINT BLOCK_SIZE;
ILE140 *pE140;
ADC_PARS_E140 adc_pars;
MODULE_DESCR_E140 descr;
BYTE ctable[128];
volatile bool RunFlag;
volatile bool BlockFlags[2];
HANDLE thread,thread2;
DWORD thread_id,thread_id2;
SHORT *buffer;
int buffer_index;
BYTE write_buffer[64];//двойной буфер 

//Network variables
FILE *file;
int UDPSocket;
int DestPORT;
int DestADDR;
SOCKADDR_IN dest_sin;
UINT pack=0;
//Global variables
HWND hwnd;
//functions prototypes
void SendADCData(HWND param);
//ADC thread function
int WINAPI ADCThread(LPVOID* param)
{
hwnd=(HWND)param;
while(!RunFlag){};
if(pE140->START_ADC())
 {
	int index=0;
	DWORD size=BLOCK_SIZE, sz;
	DWORD timeout=10*BLOCK_SIZE/adc_pars.ChannelRate;
	OVERLAPPED ovr={0};
	ovr.hEvent=CreateEvent(NULL, FALSE , FALSE, NULL);

	//+net initialize
	//Allocatinf socket
	if ((UDPSocket = socket (AF_INET, SOCK_DGRAM, 0))== INVALID_SOCKET)
	{
		AfxMessageBox("Allocating socket failed. Error");
		return FALSE;
	}
	BOOL fBroadcast = TRUE;
	int err=setsockopt(UDPSocket,SOL_SOCKET,SO_BROADCAST,(CHAR*)&fBroadcast,sizeof(BOOL));
	if ( SOCKET_ERROR == err )
	{
		AfxMessageBox("Set socket options failed!"); 
		return 0;
	}
	dest_sin.sin_family = AF_INET;
	dest_sin.sin_port = htons (DestPORT);
	switch (DestADDR)
	{
		case 0:{dest_sin.sin_addr.s_addr = inet_addr ("127.0.0.1");break;}
		case 1:{dest_sin.sin_addr.s_addr = htonl (INADDR_BROADCAST);break;}
		default:{dest_sin.sin_addr.s_addr = inet_addr ("127.0.0.1");break;}
	}
	//-net initialize
	while(RunFlag)
	{
		if(!BlockFlags[index])
		{
			if(pE140->ReadData(buffer+index*BLOCK_SIZE, &size, &sz, &ovr) && WaitForSingleObject(ovr.hEvent, timeout)==WAIT_OBJECT_0)
			{
			BlockFlags[index]=TRUE;
			index=(index+1)&0x01;
			SendADCData(hwnd);
			}else RunFlag=FALSE;
		}
	}
	CancelIo(pE140->GetModuleHandle());
    CloseHandle(ovr.hEvent);
 } else RunFlag=false;
 return 0;
}

void SendADCData(HWND param)
{
	if(BlockFlags[buffer_index])
	{
	//net sending
	double *num;
	num=new double[adc_pars.ChannelsQuantity];
	for (int i=0;i<(BLOCK_SIZE/adc_pars.ChannelsQuantity);i++)
	{
		SHORT var;
		for (int j=0;j<adc_pars.ChannelsQuantity;j++) 
		{
			var=buffer[j+i*adc_pars.ChannelsQuantity+buffer_index*BLOCK_SIZE];
			num[j]=((double)var/8000)*10;
		}
		double tmp=num[0];
		if (sendto(UDPSocket,(char*)num,8*adc_pars.ChannelsQuantity,0,(struct sockaddr FAR *)&dest_sin,sizeof(dest_sin))==SOCKET_ERROR) 
		{
			char str[100];sprintf(str,"%d",WSAGetLastError());AfxMessageBox(str); 
			closesocket (UDPSocket);
			return;
		}
		pack++;
		if (pack%100==0)
		{
			char p_txt[10];
			sprintf(p_txt,"%d",pack);
			SetDlgItemText(param,IDC_PACKETS,p_txt); 
		}
	}
	BlockFlags[buffer_index]=FALSE;
    buffer_index=(buffer_index+1)&0x01;
	return; 
	} 
}

///////////
//////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CE_140Dlg dialog

IMPLEMENT_DYNAMIC(CE_140Dlg, CDialog);

CE_140Dlg::CE_140Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CE_140Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CE_140Dlg)
	m_ClcSource = FALSE;
	m_EnableClkOutput = FALSE;
	m_SAC = 1;
	m_inputmode = -1;
	m_analogsynctype = -1;
	m_analogsyncmode = -1;
	m_SAP = 0;
	m_ChQ = 1;
	m_discreet = 0.1;
	m_IKD = 1;
	m_IKDF = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CE_140Dlg::~CE_140Dlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CE_140Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CE_140Dlg)
	DDX_Control(pDX, IDC_RADIO7, m_rad3);
	DDX_Control(pDX, IDC_RADIO5, m_rad2);
	DDX_Control(pDX, IDC_EDIT1, wSAC);
	DDX_Control(pDX, IDC_SPIN1, m_spin);
	DDX_Control(pDX, IDC_LIST2, m_color);
	DDX_Control(pDX, IDC_LIST1, m_info);
	DDX_Check(pDX, IDC_CHECK1, m_ClcSource);
	DDX_Check(pDX, IDC_CHECK2, m_EnableClkOutput);
	DDX_Text(pDX, IDC_EDIT1, m_SAC);
	DDV_MinMaxUInt(pDX, m_SAC, 1, 16);
	DDX_Radio(pDX, IDC_RADIO1, m_inputmode);
	DDX_Radio(pDX, IDC_RADIO5, m_analogsynctype);
	DDX_Radio(pDX, IDC_RADIO7, m_analogsyncmode);
	DDX_Text(pDX, IDC_EDIT2, m_SAP);
	DDV_MinMaxInt(pDX, m_SAP, -8192, 8191);
	DDX_Text(pDX, IDC_EDIT3, m_ChQ);
	DDV_MinMaxUInt(pDX, m_ChQ, 1, 128);
	DDX_Text(pDX, IDC_EDIT4, m_discreet);
	DDV_MinMaxDouble(pDX, m_discreet, 0.1, 100.);
	DDX_Text(pDX, IDC_EDIT5, m_IKD);
	DDV_MinMaxUInt(pDX, m_IKD, 1, 256);
	DDX_Text(pDX, IDC_EDIT6, m_IKDF);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CE_140Dlg, CDialog)
	//{{AFX_MSG_MAP(CE_140Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, OnConnect)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_COMMAND(ID_SAVEASDEFAULT, OnSaveasdefault)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, OnControlTable)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_COMMAND(ID_OPTIONS_NETWORK, OnOptionsNetwork)
	ON_COMMAND(ID_OPTIONS_ADCDACDEVICE, OnOptionsAdcdacdevice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CE_140Dlg message handlers

BOOL CE_140Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//read default options from ini - file
	//e140.ini
	char sClkSource[2],sEnableClkOutput[2],sInputMode[2],sSynchroAdType[2],sSynchroAdMode[2],
	sSynchroAdChannel[3],sSynchroAdPorog[6],sChannelsQuantity[4],sInterKadrDelay[4];
	GetPrivateProfileString("defaults","iClkSource","0",sClkSource,2,"e140.ini");
	GetPrivateProfileString("defaults","iEnableClkOutput","0",sEnableClkOutput,2,"e140.ini");
	GetPrivateProfileString("defaults","iInputMode","0",sInputMode,2,"e140.ini");
	GetPrivateProfileString("defaults","iSynchroAdType","0",sSynchroAdType,2,"e140.ini");
	GetPrivateProfileString("defaults","iSynchroAdMode","0",sSynchroAdMode,2,"e140.ini");
	GetPrivateProfileString("defaults","iSynchroAdChannel","1",sSynchroAdChannel,3,"e140.ini");
	GetPrivateProfileString("defaults","iSynchroAdPorog","0",sSynchroAdPorog,6,"e140.ini");
	GetPrivateProfileString("defaults","iChannelsQuantity","1",sChannelsQuantity,4,"e140.ini");
	GetPrivateProfileString("defaults","iInterKadrDelay","1",sInterKadrDelay,4,"e140.ini");
	GetPrivateProfileString("lsession","lctable","",lpath,250,"e140.ini");
	GetPrivateProfileStruct("ADC","block_size",&BLOCK_SIZE,4,"e140.ini");
	GetPrivateProfileStruct("network","port",&DestPORT,4,"e140.ini");
	GetPrivateProfileStruct("network","dest",&DestADDR,4,"e140.ini");
	if (DestPORT==0) DestPORT=5010;
	//read binary parameters
	FILE *conf;
	conf=fopen("ConfData.bin","rb");
	if (fread(&m_discreet,8,1,conf)!=1) m_discreet=1;
	fclose(conf);
	//convert data
	sscanf(sClkSource,"%d",&m_ClcSource);
	sscanf(sEnableClkOutput,"%d",&m_EnableClkOutput);
	sscanf(sInputMode,"%d",&m_inputmode);
	sscanf(sSynchroAdType,"%d",&m_analogsynctype);
	sscanf(sSynchroAdMode,"%d",&m_analogsyncmode);
	sscanf(sSynchroAdChannel,"%d",&m_SAC);
	sscanf(sSynchroAdPorog,"%d",&m_SAP);
	sscanf(sChannelsQuantity,"%d",&m_ChQ);
	sscanf(sInterKadrDelay,"%d",&m_IKD);
	//init form
	UpdateData(FALSE);
	m_IKDF=m_IKD/m_discreet;
	UpdateData(FALSE);
	m_color.SetBkColor(RGB(255,0,0));
	m_spin.SetBuddy(&wSAC);
	m_spin.SetRange(1,16);
	if (m_ClcSource) GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
	else GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
	if (m_inputmode==3)
	{
		GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);	
		GetDlgItem(IDC_RADIO6)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO7)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN1)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);
	//load last ControlTable
	if (strcmp(lpath,"")!=0)
	{
		FILE *lfile;
		BOOL read=TRUE;
		if (lfile=fopen(lpath,"rb"))
		{
			for (int i=0;i<128;i++)
			{
				if (fread(&ctable[i],1,1,lfile)!=1) {read=FALSE;AfxMessageBox("Error Control Table!");break;}
			}
			fclose(lfile);
			if (!read) ::MessageBox(NULL,"Incorrect Last Session File!","ERROR!",MB_OK);
		}else AfxMessageBox("Can't open last file...");
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CE_140Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CE_140Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CE_140Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CE_140Dlg::OnClose() 
{
	if (CanExit())
		CDialog::OnClose();
}

void CE_140Dlg::OnOK() 
{
	if (CanExit())
		CDialog::OnOK();
}

void CE_140Dlg::OnCancel() 
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CE_140Dlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

void CE_140Dlg::OnConnect() 
{
	m_info.InsertString(m_info.GetCount(),"...........");
	CString cap;
	GetDlgItemText(IDC_BUTTON1,cap);
	if (cap.Compare("Connect")==0) 
	{
		if (Connect())	SetDlgItemText(IDC_BUTTON1,"Disconnect");
	}
	else 
	{
		if (Disconnect()) SetDlgItemText(IDC_BUTTON1,"Connect");
	}
}

BOOL CE_140Dlg::Connect()
{
	pE140=static_cast<ILE140*>(CreateInstance("e140"));	
	if(pE140==NULL) 
	{
    AfxMessageBox("Error...\rCan't CreateInstance");
	return FALSE;
	}
	//m_info.InsertString(m_info.GetCount(),"CreatedInstance");
	for(int i=0; i<1000; i++) if(pE140->OpenLDevice(i)) break;
	if (i<1000)
	{
		if (!pE140->OpenLDevice(i)) 
		{
			AfxMessageBox("Error opening device!");
			return FALSE;
		}
		else
		{
			m_info.InsertString(m_info.GetCount(),"Connected...");
			DWORD *lBIOS=new DWORD;
			if (!pE140->GET_LBIOS_VERSION(lBIOS)) 
			{
				AfxMessageBox("Error. Incorrect BIOS.");
				return FALSE;
			}
			else 
			{
				m_info.InsertString(m_info.GetCount(),"BIOS Checked...");
				if(pE140->GET_MODULE_DESCR(&descr) && pE140->GET_CUR_ADC_PARS(&adc_pars))
				{
					m_info.InsertString(m_info.GetCount(),descr.Name);
					m_info.InsertString(m_info.GetCount(),descr.SerialNumber);
					m_info.InsertString(m_info.GetCount(),descr.CpuType);
					if (descr.IsDacPresented)
						m_info.InsertString(m_info.GetCount(),"DAC: YES");
					else m_info.InsertString(m_info.GetCount(),"DAC: NO");
					m_color.SetBkColor(RGB(0,155,0));
					m_color.RedrawWindow();
					//параметры работы АЦП...
					UpdateData(TRUE);
					if (m_ClcSource)adc_pars.ClkSource=1; else adc_pars.ClkSource=0;
					if (m_EnableClkOutput)adc_pars.ClkSource=1; else adc_pars.EnableClkOutput=0;
					adc_pars.InputMode=m_inputmode;
					if (m_analogsynctype==0) adc_pars.SynchroAdType=0; else adc_pars.SynchroAdType=1;
					if (m_analogsyncmode==0) adc_pars.SynchroAdMode=0; else adc_pars.SynchroAdMode=1;
					adc_pars.SynchroAdChannel=m_SAC;
					adc_pars.SynchroAdPorog=m_SAP;
					adc_pars.ChannelsQuantity=m_ChQ;
					adc_pars.AdcRate=m_discreet;
					adc_pars.InterKadrDelay=m_IKD/m_discreet;
					//load last ControlTable
					for (int i=0;i<128;i++)
					{
						adc_pars.ControlTable[i]=ctable[i];
					}
					if(pE140->FILL_ADC_PARS(&adc_pars))
					{
						buffer=new SHORT[2*BLOCK_SIZE];
						if(buffer!=NULL)
						{
							thread=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ADCThread, this->GetSafeHwnd(), 0, &thread_id);
							if(thread!=INVALID_HANDLE_VALUE)
							{
								BlockFlags[0]=BlockFlags[1]=FALSE;
								RunFlag=TRUE;
								vEnableControls(FALSE);
								//thread2=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NETThread, NULL, 0, &thread_id2);
							}else {AfxMessageBox("Error Creating Thread!");return FALSE;}
						}else {AfxMessageBox("Error Buffer!");return FALSE;}
					}else {AfxMessageBox("Error ADC_PARS!");return FALSE;}
				}else {AfxMessageBox("Error GetModuleDesr!");return FALSE;}
			}
		}
	}else {AfxMessageBox("Device not connected!");return FALSE;}
	return TRUE;
}

BOOL CE_140Dlg::Disconnect()
{
	RunFlag=FALSE;
	DWORD j;
	while(!GetExitCodeThread(thread, &j) || j);
	CloseHandle(thread);
	delete []buffer;
	pE140->CloseLDevice();
	pE140->ReleaseLDevice();
	m_color.SetBkColor(RGB(255,0,0));
	vEnableControls(TRUE);
	m_color.RedrawWindow();
	m_info.InsertString(m_info.GetCount(),"Disconnected...");
	return TRUE;
}

void CE_140Dlg::OnRadio4() 
{
	GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);	
	GetDlgItem(IDC_RADIO6)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN1)->EnableWindow(TRUE);
}

void CE_140Dlg::OnRadio1() 
{
	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);	
	GetDlgItem(IDC_RADIO6)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN1)->EnableWindow(FALSE);
}

void CE_140Dlg::OnRadio2() 
{
	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);	
	GetDlgItem(IDC_RADIO6)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN1)->EnableWindow(FALSE);
}

void CE_140Dlg::OnRadio3() 
{
	GetDlgItem(IDC_RADIO5)->EnableWindow(FALSE);	
	GetDlgItem(IDC_RADIO6)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_SPIN1)->EnableWindow(FALSE);
}

void CE_140Dlg::OnChangeEdit2() 
{
	UpdateData(TRUE);
}
void CE_140Dlg::OnChangeEdit5() 
{
	UpdateData(TRUE);
	m_IKDF=m_IKD/m_discreet;
	UpdateData(FALSE);
}

void CE_140Dlg::OnChangeEdit4() 
{
	UpdateData(TRUE);
	m_IKDF=m_IKD/m_discreet;
	UpdateData(FALSE);
}

void CE_140Dlg::OnCheck1() 
{
	UpdateData(TRUE);	
	if (m_ClcSource) GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
	else GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
}
void CE_140Dlg::OnControlTable() 
{
	CControlTableDlg dlg;
	for (int i=0;i<128;i++)	dlg.m_ControlTable[i]=ctable[i];
	if (dlg.DoModal()==IDOK)
	{
		for (int i=0;i<128;i++)
		{
			ctable[i]=dlg.m_ControlTable[i];
		}
		if (dlg.lpath.Compare("")!=0) WritePrivateProfileString("lsession","lctable",dlg.lpath,"e140.ini");
	}
}
void CE_140Dlg::OnSaveasdefault() 
{
	char sClkSource[2],sEnableClkOutput[2],sInputMode[2],sSynchroAdType[2],sSynchroAdMode[2],
	sSynchroAdChannel[3],sSynchroAdPorog[6],sChannelsQuantity[4],sInterKadrDelay[4];
	//convert data
	UpdateData(TRUE);
	sprintf(sClkSource,"%d",m_ClcSource);
	sprintf(sEnableClkOutput,"%d",m_EnableClkOutput);
	sprintf(sInputMode,"%d",m_inputmode);
	sprintf(sSynchroAdType,"%d",m_analogsynctype);
	sprintf(sSynchroAdMode,"%d",m_analogsyncmode);
	sprintf(sSynchroAdChannel,"%d",m_SAC);
	sprintf(sSynchroAdPorog,"%d",m_SAP);
	sprintf(sChannelsQuantity,"%d",m_ChQ);
	sprintf(sInterKadrDelay,"%d",m_IKD);
	WritePrivateProfileString("defaults","iClkSource",sClkSource,"e140.ini");
	WritePrivateProfileString("defaults","iEnableClkOutput",sEnableClkOutput,"e140.ini");
	WritePrivateProfileString("defaults","iInputMode",sInputMode,"e140.ini");
	WritePrivateProfileString("defaults","iSynchroAdType",sSynchroAdType,"e140.ini");
	WritePrivateProfileString("defaults","iSynchroAdMode",sSynchroAdMode,"e140.ini");
	WritePrivateProfileString("defaults","iSynchroAdChannel",sSynchroAdChannel,"e140.ini");
	WritePrivateProfileString("defaults","iSynchroAdPorog",sSynchroAdPorog,"e140.ini");
	WritePrivateProfileString("defaults","iChannelsQuantity",sChannelsQuantity,"e140.ini");
	WritePrivateProfileString("defaults","iInterKadrDelay",sInterKadrDelay,"e140.ini");
	//read binary parameters
	FILE *conf;
	conf=fopen("ConfData.bin","wb");
	if (fwrite(&m_discreet,8,1,conf)!=8) m_discreet=1;
	fclose(conf);
	AfxMessageBox("All Parameters Saved.");
}
void CE_140Dlg::OnOptionsNetwork() 
{
	CNetDlg dlg;
	if (dlg.DoModal()==IDOK)
	{
		DestPORT=dlg.m_port;
		DestADDR=dlg.m_net_addr;
	}
}

void CE_140Dlg::OnOptionsAdcdacdevice() 
{
	CADCOptions dlg;
	if (dlg.DoModal()==IDOK)
	{
		BLOCK_SIZE=dlg.m_blocksize;
	}
}

void CE_140Dlg::vEnableControls(BOOL enable)
{
	GetDlgItem(IDC_RADIO1)->EnableWindow(enable);
	GetDlgItem(IDC_RADIO2)->EnableWindow(enable);
	GetDlgItem(IDC_RADIO3)->EnableWindow(enable);
	GetDlgItem(IDC_RADIO4)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT3)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT4)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT5)->EnableWindow(enable);
	GetDlgItem(IDC_EDIT6)->EnableWindow(enable);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(enable);
}

