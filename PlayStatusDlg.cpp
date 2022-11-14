// PlayStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Go.h"
#include "PlayStatusDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayStatusDlg dialog


CPlayStatusDlg::CPlayStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayStatusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayStatusDlg)
	m_basic_time = 0;
	m_CountDownTime = 0;
	m_Handicap = 0.0f;
	m_NumCountDown = 0;
	//}}AFX_DATA_INIT
}


void CPlayStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayStatusDlg)
	DDX_Text(pDX, IDC_BasicTime, m_basic_time);
	DDV_MinMaxUInt(pDX, m_basic_time, 0, 60);
	DDX_Text(pDX, IDC_CountDownTime, m_CountDownTime);
	DDV_MinMaxUInt(pDX, m_CountDownTime, 0, 60);
	DDX_Text(pDX, IDC_Handicap, m_Handicap);
	DDV_MinMaxFloat(pDX, m_Handicap, -10.5, 10.5);
	DDX_Text(pDX, IDC_NumCountDown, m_NumCountDown);
	DDV_MinMaxUInt(pDX, m_NumCountDown, 0, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlayStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CPlayStatusDlg)
	ON_BN_CLICKED(IDC_BlackStone, OnBlackStone)
	ON_BN_CLICKED(IDC_Board13, OnBoard13)
	ON_BN_CLICKED(IDC_Board19, OnBoard19)
	ON_BN_CLICKED(IDC_Board9, OnBoard9)
	ON_BN_CLICKED(IDC_ChineseRule, OnChineseRule)
	ON_BN_CLICKED(IDC_IngRule, OnIngRule)
	ON_BN_CLICKED(IDC_JapanRule, OnJapanRule)
	ON_BN_CLICKED(IDC_PSK, OnPsk)
	ON_BN_CLICKED(IDC_SSK, OnSsk)
	ON_BN_CLICKED(IDC_SystemDetermined, OnSystemDetermined)
	ON_BN_CLICKED(IDC_WhiteStone, OnWhiteStone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayStatusDlg message handlers

void CPlayStatusDlg::OnBlackStone() 
{
	// TODO: Add your control notification handler code here
	
}

void CPlayStatusDlg::OnBoard13() 
{
	// TODO: Add your control notification handler code here
	m_board_size = 13;
}

void CPlayStatusDlg::OnBoard19() 
{
	// TODO: Add your control notification handler code here
	m_board_size = 19;
}

void CPlayStatusDlg::OnBoard9() 
{
	// TODO: Add your control notification handler code here
	m_board_size = 9;
}

void CPlayStatusDlg::OnChineseRule() 
{
	// TODO: Add your control notification handler code here
	m_rule = CHINESE;
}

void CPlayStatusDlg::OnIngRule() 
{
	// TODO: Add your control notification handler code here
	m_rule = ING;
}

void CPlayStatusDlg::OnJapanRule() 
{
	// TODO: Add your control notification handler code here
	m_rule = JAPANESE;
}

void CPlayStatusDlg::OnPsk() 
{
	// TODO: Add your control notification handler code here
	m_rule = POSITIONAL_SUPER_KO;
}

void CPlayStatusDlg::OnSsk() 
{
	// TODO: Add your control notification handler code here
	m_rule = SITUATIONAL_SUPER_KO;
}

void CPlayStatusDlg::OnSystemDetermined() 
{
	// TODO: Add your control notification handler code here
	
}

void CPlayStatusDlg::OnWhiteStone() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CPlayStatusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	switch(m_board_size)
	{
	case 19:
		CheckDlgButton(IDC_Board19,1);
		break;
	case 13:
		CheckDlgButton(IDC_Board13,1);
		break;
	case 9:
		CheckDlgButton(IDC_Board9,1);
		break;
	}

	switch(m_rule)
	{
	case POSITIONAL_SUPER_KO:
		CheckDlgButton(IDC_PSK,1);
		break;
	case SITUATIONAL_SUPER_KO:
		CheckDlgButton(IDC_SSK,1);
		break;
	case CHINESE:
		CheckDlgButton(IDC_ChineseRule,1);
		break;
	case ING:
		CheckDlgButton(IDC_IngRule,1);
		break;
	case JAPANESE:
		CheckDlgButton(IDC_JapanRule,1);
		break;
	}

	/* m_basic_time = 1;
	m_CountDownTime = 30;
	m_NumCountDown = 3;
	m_Handicap = 5.5; */

	return TRUE;
}
