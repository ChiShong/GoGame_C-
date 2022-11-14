// goDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Go.h"
#include "goDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// goDialog dialog


goDialog::goDialog(CWnd* pParent /*=NULL*/)
	: CDialog(goDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(goDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void goDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(goDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(goDialog, CDialog)
	//{{AFX_MSG_MAP(goDialog)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// goDialog message handlers

void goDialog::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	
}

void goDialog::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	
}

void goDialog::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	
}
