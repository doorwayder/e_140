// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "E_140.h"
#include "DlgProxy.h"
#include "E_140Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CE_140DlgAutoProxy

IMPLEMENT_DYNCREATE(CE_140DlgAutoProxy, CCmdTarget)

CE_140DlgAutoProxy::CE_140DlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CE_140Dlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CE_140Dlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CE_140DlgAutoProxy::~CE_140DlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CE_140DlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CE_140DlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CE_140DlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CE_140DlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CE_140DlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IE_140 to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {841A8391-1DD3-4489-A769-137DED0A6A0F}
static const IID IID_IE_140 =
{ 0x841a8391, 0x1dd3, 0x4489, { 0xa7, 0x69, 0x13, 0x7d, 0xed, 0xa, 0x6a, 0xf } };

BEGIN_INTERFACE_MAP(CE_140DlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CE_140DlgAutoProxy, IID_IE_140, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {683C16D3-3CC0-4900-BC99-9E65CF133039}
IMPLEMENT_OLECREATE2(CE_140DlgAutoProxy, "E_140.Application", 0x683c16d3, 0x3cc0, 0x4900, 0xbc, 0x99, 0x9e, 0x65, 0xcf, 0x13, 0x30, 0x39)

/////////////////////////////////////////////////////////////////////////////
// CE_140DlgAutoProxy message handlers
