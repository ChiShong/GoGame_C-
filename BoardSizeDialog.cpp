// BoardSizeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Go.h"
#include "BoardSizeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoardSizeDialog dialog


CBoardSizeDialog::CBoardSizeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBoardSizeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBoardSizeDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBoardSizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBoardSizeDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBoardSizeDialog, CDialog)
	//{{AFX_MSG_MAP(CBoardSizeDialog)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoardSizeDialog message handlers


BOOL CBoardSizeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	switch(m_board_size)
	{
	case 19:
		CheckDlgButton(IDC_RADIO1,1);
		break;
	case 13:
		CheckDlgButton(IDC_RADIO2,1);
		break;
	case 9:
		CheckDlgButton(IDC_RADIO3,1);
		break;
	}
	return TRUE;
}

void CBoardSizeDialog::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	m_board_size = 19;
}

void CBoardSizeDialog::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	m_board_size = 13;
}

void CBoardSizeDialog::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	m_board_size = 9;
}
