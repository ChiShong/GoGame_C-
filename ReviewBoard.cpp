// ReviewBoard.cpp : implementation file
//

#include "stdafx.h"
#include "Go.h"
#include "ReviewBoard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReviewBoard dialog


ReviewBoard::ReviewBoard(CWnd* pParent /*=NULL*/)
	: CDialog(ReviewBoard::IDD, pParent)
{
	//{{AFX_DATA_INIT(ReviewBoard)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ReviewBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ReviewBoard)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ReviewBoard, CDialog)
	//{{AFX_MSG_MAP(ReviewBoard)
	ON_BN_CLICKED(IDC_back_move1, Onbackmove1)
	ON_BN_CLICKED(IDC_back_move5, Onbackmove5)
	ON_BN_CLICKED(IDC_forward_move1, Onforwardmove1)
	ON_BN_CLICKED(IDC_forward_move5, Onforwardmove5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ReviewBoard message handlers

void ReviewBoard::Onbackmove1() 
{
	// TODO: Add your control notification handler code here
	
}

void ReviewBoard::Onbackmove5() 
{
	// TODO: Add your control notification handler code here
	
}

void ReviewBoard::Onforwardmove1() 
{
	// TODO: Add your control notification handler code here
	
}

void ReviewBoard::Onforwardmove5() 
{
	// TODO: Add your control notification handler code here
	
}
