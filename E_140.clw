; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CControlTableDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "E_140.h"
ODLFile=E_140.odl

ClassCount=8
Class1=CE_140App
Class2=CE_140Dlg
Class3=CAboutDlg
Class4=CE_140DlgAutoProxy

ResourceCount=8
Resource1=IDD_ADCDLG
Resource2=IDR_MAINFRAME
Resource3=IDD_NETDLG
Resource4=IDD_CTDLG
Class5=CControlTableDlg
Resource5=IDD_ABOUTBOX
Class6=CNetDlg
Resource6=IDD_CTABLEDLG
Class7=CCTRDlg
Resource7=IDD_E_140_DIALOG
Class8=CADCOptions
Resource8=IDR_MENU

[CLS:CE_140App]
Type=0
HeaderFile=E_140.h
ImplementationFile=E_140.cpp
Filter=N

[CLS:CE_140Dlg]
Type=0
HeaderFile=E_140Dlg.h
ImplementationFile=E_140Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT3

[CLS:CAboutDlg]
Type=0
HeaderFile=E_140Dlg.h
ImplementationFile=E_140Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CE_140DlgAutoProxy]
Type=0
HeaderFile=DlgProxy.h
ImplementationFile=DlgProxy.cpp
BaseClass=CCmdTarget
Filter=N

[DLG:IDD_E_140_DIALOG]
Type=1
Class=CE_140Dlg
ControlCount=35
Control1=IDC_RADIO1,button,1342341129
Control2=IDC_RADIO2,button,1342210057
Control3=IDC_RADIO3,button,1342210057
Control4=IDC_RADIO4,button,1342210057
Control5=IDC_BUTTON1,button,1342242816
Control6=IDC_LIST1,listbox,1352728835
Control7=IDC_CHECK1,button,1342275587
Control8=IDC_LIST2,SysListView32,1350631424
Control9=IDC_CHECK2,button,1476493315
Control10=IDC_STATIC,button,1342177799
Control11=IDC_STATIC,button,1342177799
Control12=IDC_STATIC,button,1342177799
Control13=IDC_SPIN1,msctls_updown32,1476395042
Control14=IDC_EDIT1,edit,1484857473
Control15=IDC_STATIC,static,1342308352
Control16=IDC_RADIO5,button,1476558857
Control17=IDC_RADIO6,button,1476427785
Control18=IDC_RADIO7,button,1476558857
Control19=IDC_RADIO8,button,1476427785
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT2,edit,1484857473
Control22=IDC_STATIC,button,1342177799
Control23=IDC_EDIT3,edit,1350639745
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,button,1342177799
Control26=IDC_EDIT4,edit,1350631553
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EDIT5,edit,1350639745
Control29=IDC_STATIC,static,1342308352
Control30=IDC_EDIT6,edit,1350641793
Control31=IDC_STATIC,static,1342308352
Control32=IDC_BUTTON2,button,1342275584
Control33=IDC_STATIC,static,1342308352
Control34=IDC_PACKETS,edit,1350631552
Control35=IDC_STATIC,static,1342308352

[MNU:IDR_MENU]
Type=1
Class=CE_140Dlg
Command1=ID_OPTIONS_NETWORK
Command2=ID_OPTIONS_ADCDACDEVICE
Command3=ID_OPTIONS_PROGRAMM
Command4=ID_SAVEASDEFAULT
CommandCount=4

[DLG:IDD_CTABLEDLG]
Type=1
Class=CControlTableDlg
ControlCount=24
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_EDIT1,edit,1350639744
Control5=IDVBUTTON,button,1342275584
Control6=IDC_EDIT7,edit,1350639744
Control7=IDC_EDIT8,edit,1350639744
Control8=IDC_EDIT9,edit,1350639744
Control9=IDC_EDIT10,edit,1350639744
Control10=IDC_EDIT2,edit,1350639744
Control11=IDC_EDIT3,edit,1350639744
Control12=IDC_EDIT4,edit,1350639744
Control13=IDC_EDIT5,edit,1350639745
Control14=IDC_EDIT6,edit,1350639745
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,static,1342308352
Control17=IDC_BUTTON3,button,1342242816
Control18=IDC_EDIT11,edit,1350633600
Control19=IDC_BUTTON4,button,1342275584
Control20=IDC_BUTTON5,button,1342275584
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDIT12,edit,1350631556
Control24=IDC_STATIC,static,1342308352

[CLS:CControlTableDlg]
Type=0
HeaderFile=ControlTableDlg.h
ImplementationFile=ControlTableDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT12

[DLG:IDD_NETDLG]
Type=1
Class=CNetDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350639744
Control5=IDC_STATIC,button,1342177287
Control6=IDC_RADIO1,button,1342308361
Control7=IDC_RADIO2,button,1342177289
Control8=IDC_STATIC,static,1342308352

[CLS:CNetDlg]
Type=0
HeaderFile=NetDlg.h
ImplementationFile=NetDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RADIO1
VirtualFilter=dWC

[DLG:IDD_CTDLG]
Type=1
Class=CCTRDlg
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350647809

[CLS:CCTRDlg]
Type=0
HeaderFile=CTRDlg.h
ImplementationFile=CTRDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST1
VirtualFilter=dWC

[DLG:IDD_ADCDLG]
Type=1
Class=CADCOptions
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350639744
Control5=IDC_STATIC,button,1342177287

[CLS:CADCOptions]
Type=0
HeaderFile=ADCOptions.h
ImplementationFile=ADCOptions.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

