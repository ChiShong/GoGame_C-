// GoView.cpp : implementation of the CGoView class
//

#include "stdafx.h"
#include <iostream>
#include "Go.h"
#include "board.h"
#include "Rules.h"

#include "GoDoc.h"
#include "GoView.h"

#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  TIMER_BLACK  1 
#define  TIMER_WHITE  2
/////////////////////////////////////////////////////////////////////////////
// CGoView

IMPLEMENT_DYNCREATE(CGoView, CView)

BEGIN_MESSAGE_MAP(CGoView, CView)
	//{{AFX_MSG_MAP(CGoView)
	ON_COMMAND(IDR_MENU1, OnMenu1)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_backward_1, Onbackward1)
	ON_COMMAND(ID_backward_5, Onbackward5)
	ON_COMMAND(ID_forward_1, Onforward1)
	ON_COMMAND(ID_forward_5, Onforward5)
	ON_COMMAND(ID_to_the_begin, Ontothebegin)
	ON_COMMAND(ID_to_the_end, Ontotheend)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

	ON_BN_CLICKED(1, OnPassButton)
	ON_BN_CLICKED(2, OnResignButton)
	ON_BN_CLICKED(3, OnDoneButton)
	ON_BN_CLICKED(4, OnContinueButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoView construction/destruction

CGoView::CGoView()
{
	// TODO: add construction code here

 //current_moves_index = pDoc->board->m_moves.moves_sequence.end();
	previous_x = 1;
	previous_y = 1;
	//StartTimer(TIMER_BLACK, 1000);
}

CGoView::~CGoView()
{
}

BOOL CGoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGoView drawing

void CGoView::OnDraw(CDC* pDC)
{
 Draw_Board(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CGoView printing

BOOL CGoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGoView diagnostics

#ifdef _DEBUG
void CGoView::AssertValid() const
{
	CView::AssertValid();
}

void CGoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGoDoc* CGoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGoDoc)));
	return (CGoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGoView message handlers



void CGoView::OnMenu1() 
{
	// TODO: Add your command handler code here
	
}

void CGoView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//CString str;
	//str.Format("%s %d,%d", "座標為:", point.x, point.y);

	//if (nFlags & MK_LBUTTON) {
	//	AfxMessageBox(str,MB_OK);
	//}
	int grid, x, y, mx, my, board_size, chain_num, xt, yt;
	double x_float, y_float;
	Turn dead_color;
	CGoDoc * pDoc = GetDocument();
	vector<pair<int,int> > deads, adjacent_vacancy, vacant_chain;

	ASSERT_VALID(pDoc);

	grid = pDoc->board->m_gridsize;
	board_size = pDoc->board->m_boardsize;
	x_float = point.x;
	y_float = point.y;
	mx = (int)(x_float/grid+0.5);
	my = (int)(y_float/grid+0.5);

	CClientDC aDC(this);
	CDC dcMemory;

	aDC.BitBlt(800,600,150,150,&dcMemory,0,0,WHITENESS);

	vector<pair<int,int> >::iterator i, ite;
	if (pDoc->board->game_status == PLAYING) {
		if (pDoc->board->p_current_board_position->player == BLACK) {
			if (pDoc->board->mp_rule->move(BLACK, mx, my, pDoc->board, deads, dead_color)) {
				BlackCountDownTime = pDoc->board->m_CountDownTime;
				draw_stone(mx, my, BLACK);
				draw_mark(mx, my);
				PlaySound( MAKEINTRESOURCE(IDR_StoneClick), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE); 
				pDoc->board->p_current_board_position->player = WHITE;
				pDoc->board->num_consecutive_pass = 0;
				StopTimer(TIMER_BLACK);
				StartTimer(TIMER_WHITE, 1000);
			}
		}
		else {
			if (pDoc->board->mp_rule->move(WHITE, mx, my, pDoc->board, deads, dead_color)) {
			    WhiteCountDownTime = pDoc->board->m_CountDownTime;
				draw_stone(mx, my, WHITE);
				draw_mark(mx, my);
				PlaySound( MAKEINTRESOURCE(IDR_StoneClick), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				pDoc->board->p_current_board_position->player = BLACK;
				pDoc->board->num_consecutive_pass = 0;
				StopTimer(TIMER_WHITE);
				StartTimer(TIMER_BLACK, 1000);
			}
		}
		for(i=deads.begin(); i<deads.end(); i++) {
			x = (*i).first;
			y = (*i).second;
			draw_stone(x, y, VACANT);
		}
		deads.clear();
	}
	// enter scoring stage
	if (pDoc->board->game_status == SCORING) {
		if (mx<1 || mx>19 || my<1 || my>19) return;
		if (!pDoc->board->set_chain_dead(mx, my, &adjacent_vacancy, chain_num)) return;
		if (pDoc->board->p_Chains[chain_num]) {
			for (i=pDoc->board->p_Chains[chain_num]->chain_members.begin(); i<pDoc->board->p_Chains[chain_num]->chain_members.end(); i++) {
				x = (*i).first;
				y = (*i).second;
				if (chain_num < MAX_STONES/2) {
					draw_territory_mark(x, y, 1); // white territory
					pDoc->board->territory_mark[x-1][y-1] = 2;
				}
				else {
					draw_territory_mark(x, y, 0); // black territory
					pDoc->board->territory_mark[x-1][y-1] = 1;
				}
			}
			for(i=adjacent_vacancy.begin(); i<adjacent_vacancy.end(); i++) {
				x = (*i).first;
				y = (*i).second;
				if (pDoc->board->territory_mark[x-1][y-1] == 0) {
					if (chain_num < MAX_STONES/2) {
						pDoc->board->set_vacant_territory(x,y,'w',&vacant_chain);
						for(ite=vacant_chain.begin(); ite<vacant_chain.end(); ite++) {
							xt = (*ite).first;
							yt = (*ite).second;
							draw_territory_mark(xt, yt, 1);
						}
					}
					else {
						pDoc->board->set_vacant_territory(x,y,'b',&vacant_chain);
						for(ite=vacant_chain.begin(); ite<vacant_chain.end(); ite++) {
							xt = (*ite).first;
							yt = (*ite).second;
							draw_territory_mark(xt, yt, 0);
						}
					}
				}
				vacant_chain.clear();
			}
			adjacent_vacancy.clear();			
		}

	}
   display_prompts(pDoc->board->p_current_board_position->m_stones_on_board, pDoc->board->m_num_moves, pDoc->board->m_black_captured, pDoc->board->m_white_captured);

}


void CGoView::Draw_Board(CDC *pDC)
{
	
	int boardsize, gridsize, middle, left, right, i, j;
	CBitmap board_bitmap;
	CDC dcMemory;
	//BITMAP bm;


	CGoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	board_bitmap.LoadBitmap(IDB_board_birch);
	dcMemory.CreateCompatibleDC(pDC);
	dcMemory.SelectObject(&board_bitmap);

	boardsize = pDoc->board->m_boardsize;
	gridsize = pDoc->board->m_gridsize;
   /* Get the height and width of the bitmap */
	//board_bitmap.GetBitmap(&bm);
	for (i=0; i<boardsize; i++) {
		for (j=0; j<boardsize; j++) {
			pDC->BitBlt(gridsize/2+i*gridsize,gridsize/2+j*gridsize,gridsize,gridsize,&dcMemory,0,0,SRCCOPY);
		}
	}




	switch(boardsize) {
	case 9:
		middle = 5;
		left = 3;
		right = 7;
		break;
	case 13:
		middle = 7;
		left = 4;
		right = 10;
		break;
	case 19:
		middle = 10;
		left = 4;
		right = 16;
		break;
	default:
		exit(0);
	}
	
	CBrush aBrush(RGB(0,0,0));
	pDC->SelectObject(&aBrush);
	for (i=0;i<boardsize;i++) {
		pDC->MoveTo(gridsize+gridsize*i,gridsize);
		pDC->LineTo(gridsize+gridsize*i,gridsize*boardsize);
		pDC->MoveTo(gridsize,gridsize+gridsize*i);
		pDC->LineTo(gridsize*boardsize,gridsize+gridsize*i);
		
	}
		pDC->Ellipse(gridsize*left-3,gridsize*left-3,gridsize*left+3,gridsize*left+3);
		pDC->Ellipse(gridsize*left-3,gridsize*middle-3,gridsize*left+3,gridsize*middle+3);
		pDC->Ellipse(gridsize*left-3,gridsize*right-3,gridsize*left+3,gridsize*right+3);
			
		pDC->Ellipse(gridsize*middle-3,gridsize*left-3,gridsize*middle+3,gridsize*left+3);
		pDC->Ellipse(gridsize*middle-3,gridsize*middle-3,gridsize*middle+3,gridsize*middle+3);
		pDC->Ellipse(gridsize*middle-3,gridsize*right-3,gridsize*middle+3,gridsize*right+3);
			
		pDC->Ellipse(gridsize*right-3,gridsize*left-3,gridsize*right+3,gridsize*left+3);
		pDC->Ellipse(gridsize*right-3,gridsize*middle-3,gridsize*right+3,gridsize*middle+3);
		pDC->Ellipse(gridsize*right-3,gridsize*right-3,gridsize*right+3,gridsize*right+3);

		int pos;
		for (int x=1; x<=boardsize; x++) {
			for (int y=1; y<=boardsize; y++) {
				pos = pDoc->board->get_board_position(x, y, pDoc->board->p_current_board_position);
				switch(pos)
				{
				case 1:
					draw_stone(x, y, BLACK);
					//pDC->SelectStockObject(BLACK_BRUSH);
					//pDC->Ellipse(x*gridsize-gridsize/2, y*gridsize-gridsize/2, x*gridsize+gridsize/2, y*gridsize+gridsize/2);
					break;
				case 2:
					draw_stone(x, y, WHITE);
					//pDC->SelectStockObject(WHITE_BRUSH);
					//pDC->Ellipse(x*gridsize-gridsize/2, y*gridsize-gridsize/2, x*gridsize+gridsize/2, y*gridsize+gridsize/2);
					break;
				default :
					break;
				}
			}
		}
    display_prompts(pDoc->board->p_current_board_position->m_stones_on_board, pDoc->board->m_num_moves, pDoc->board->m_black_captured, pDoc->board->m_white_captured);
	//display_photos();
}



void CGoView::Onbackward1() 
{
	// TODO: Add your command handler code here
 int stones_on_board, num_moves, black_captured, white_captured;
 list<CMove>::iterator moves_index_tmp;
 vector<pair<int,int> >::iterator i;
 pair<int,int> move;
 CMove current_move;
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);

 moves_index_tmp = pDoc->board->m_moves.current_moves_index;
 if ((!pDoc->board->m_moves.moves_sequence.empty())&&(moves_index_tmp != pDoc->board->m_moves.moves_sequence.begin())) {
	current_move = *(--moves_index_tmp);
	switch (current_move.dead_color) {
		case BLACK :
			for(i=current_move.captured.begin(); i<current_move.captured.end(); i++) {
				move = *i;
				draw_stone(move.first, move.second, BLACK);
			}
			break;
		case WHITE :
			for(i=current_move.captured.begin(); i<current_move.captured.end(); i++) {
				move = *i;
				draw_stone(move.first, move.second, WHITE);
			}
			break;
	}
	draw_stone(current_move.x, current_move.y, VACANT);
	pDoc->board->m_moves.current_moves_index = moves_index_tmp;
	 if (moves_index_tmp != pDoc->board->m_moves.moves_sequence.begin()) {
		current_move = *(--moves_index_tmp);
		stones_on_board = current_move.m_stones_on_board;
		num_moves = current_move.m_num_moves;
		black_captured = current_move.m_black_captured;
		white_captured = current_move.m_white_captured;
		display_prompts(stones_on_board, num_moves, black_captured, white_captured);
	}
	else
		display_prompts(0, 0, 0, 0);
 }

}

void CGoView::Onbackward5() 
{
	// TODO: Add your command handler code here
 int stones_on_board, num_moves, black_captured, white_captured;
 list<CMove>::iterator moves_index_tmp;
 vector<pair<int,int> >::iterator i;
 pair<int,int> move;
 CMove current_move;
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);

 moves_index_tmp = pDoc->board->m_moves.current_moves_index;
 for (int j=0; j<5; j++) {
	if ((!pDoc->board->m_moves.moves_sequence.empty())&&(moves_index_tmp != pDoc->board->m_moves.moves_sequence.begin())) {
		current_move = *(--moves_index_tmp);
		switch (current_move.dead_color) {
			case BLACK :
				for(i=current_move.captured.begin(); i<current_move.captured.end(); i++) {
					move = *i;
					draw_stone(move.first, move.second, BLACK);
				}
				break;
			case WHITE :
				for(i=current_move.captured.begin(); i<current_move.captured.end(); i++) {
					move = *i;
					draw_stone(move.first, move.second, WHITE);
				}
				break;
		}
		draw_stone(current_move.x, current_move.y, VACANT);
		pDoc->board->m_moves.current_moves_index = moves_index_tmp;
	}
}
 if (moves_index_tmp != pDoc->board->m_moves.moves_sequence.begin()) {
	 current_move = *(--moves_index_tmp);
	 stones_on_board = current_move.m_stones_on_board;
	 num_moves = current_move.m_num_moves;
	 black_captured = current_move.m_black_captured;
	 white_captured = current_move.m_white_captured;
	 display_prompts(stones_on_board, num_moves, black_captured, white_captured);
 }
 else
	 display_prompts(0, 0, 0, 0);
}

void CGoView::Onforward1() 
{
	// TODO: Add your command handler code here
 int stones_on_board, num_moves, black_captured, white_captured;
 int x, y;
 list<CMove>::iterator moves_index_tmp;
 vector<pair<int,int> >::iterator i;
 CMove current_move;
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);

 moves_index_tmp = pDoc->board->m_moves.current_moves_index;
 if ((!pDoc->board->m_moves.moves_sequence.empty())&&(moves_index_tmp != pDoc->board->m_moves.moves_sequence.end())) {
	current_move = *(moves_index_tmp++);
	for(i=current_move.captured.begin(); i<current_move.captured.end(); i++) {
		x = (*i).first;
		y = (*i).second;
		draw_stone(x, y, VACANT);
	}
	draw_stone(current_move.x, current_move.y, current_move.stone);
	pDoc->board->m_moves.current_moves_index = moves_index_tmp;
	stones_on_board = current_move.m_stones_on_board;
	num_moves = current_move.m_num_moves;
	black_captured = current_move.m_black_captured;
	white_captured = current_move.m_white_captured;
	display_prompts(stones_on_board, num_moves, black_captured, white_captured);
 }
}

void CGoView::Onforward5() 
{
	// TODO: Add your command handler code here
 int stones_on_board, num_moves, black_captured, white_captured;
 int x, y;
 list<CMove>::iterator moves_index_tmp;
 vector<pair<int,int> >::iterator i;
 CMove current_move;
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);

 moves_index_tmp = pDoc->board->m_moves.current_moves_index;
 for (int j=0; j<5; j++) {
	if ((!pDoc->board->m_moves.moves_sequence.empty())&&(moves_index_tmp != pDoc->board->m_moves.moves_sequence.end())) {
		current_move = *(moves_index_tmp++);
		for(i=current_move.captured.begin(); i<current_move.captured.end(); i++) {
			x = (*i).first;
			y = (*i).second;
			draw_stone(x, y, VACANT);
		}
		draw_stone(current_move.x, current_move.y, current_move.stone);
		pDoc->board->m_moves.current_moves_index = moves_index_tmp;
		stones_on_board = current_move.m_stones_on_board;
		num_moves = current_move.m_num_moves;
		black_captured = current_move.m_black_captured;
		white_captured = current_move.m_white_captured;
		display_prompts(stones_on_board, num_moves, black_captured, white_captured);
	}
 }
}

void CGoView::Ontothebegin() 
{
	// TODO: Add your command handler code here
 list<CMove>::iterator moves_index_tmp;
 CMove current_move;
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);

 if (!pDoc->board->m_moves.moves_sequence.empty()) {
	for(moves_index_tmp=pDoc->board->m_moves.moves_sequence.begin(); moves_index_tmp!=pDoc->board->m_moves.moves_sequence.end(); moves_index_tmp++) {
		current_move = *moves_index_tmp;
		draw_stone(current_move.x, current_move.y, VACANT);
	}
	pDoc->board->m_moves.current_moves_index = pDoc->board->m_moves.moves_sequence.begin();
    display_prompts(0, 0, 0, 0);
 }
}

void CGoView::Ontotheend() 
{
	// TODO: Add your command handler code here
 CGoDoc* pDoc = GetDocument();
 CClientDC aDC(this);
 ASSERT_VALID(pDoc);

 if (!pDoc->board->m_moves.moves_sequence.empty()) {
	Draw_Board(&aDC);
    display_prompts(pDoc->board->p_current_board_position->m_stones_on_board, pDoc->board->m_num_moves, pDoc->board->m_black_captured, pDoc->board->m_white_captured);
	pDoc->board->m_moves.current_moves_index = pDoc->board->m_moves.moves_sequence.end();
 }
}


void CGoView::display_prompts(int m_stones_on_board, int m_num_moves, int m_black_captured, int m_white_captured)
{
 int grid, board_size;
 CRect num_stones_on_board, num_moves, black_captured, white_captures;
 CString str_num_stones, str_num_moves, black_prinsoner, white_prinsoner;

 CClientDC aDC(this);
 CGoDoc * pDoc = GetDocument();
 ASSERT_VALID(pDoc);

	board_size = pDoc->board->m_boardsize;
	grid = pDoc->board->m_gridsize;
	aDC.FillSolidRect( (board_size+2)*grid, grid/2, (board_size+10)*grid, (board_size-8)*grid, RGB(255,255,255));
	str_num_stones.Format("%s  %d", "盤上總子數：", m_stones_on_board);

	num_stones_on_board.bottom = 380;
	num_stones_on_board.top = 340;
	num_stones_on_board.left = (board_size+2)*grid;
	num_stones_on_board.right = (board_size+10)*grid;
	aDC.DrawText(str_num_stones, &num_stones_on_board, DT_LEFT);

	str_num_moves.Format("%s  %d", "手數：", m_num_moves);

	num_moves.bottom = 430;
	num_moves.top = 390;
	num_moves.left = (board_size+2)*grid;
	num_moves.right = (board_size+10)*grid;
	aDC.DrawText(str_num_moves, &num_moves, DT_LEFT);

	black_prinsoner.Format("%s  %d", "白提子：", m_black_captured);

	black_captured.bottom = 330;
	black_captured.top = 290;
	black_captured.left = (board_size+10)*grid;
	black_captured.right = (board_size+18)*grid;
	aDC.DrawText(black_prinsoner, &black_captured, DT_LEFT);

	white_prinsoner.Format("%s  %d", "黑提子：", m_white_captured);

	white_captures.bottom = 330;
	white_captures.top = 290;
	white_captures.left = (board_size+2)*grid;
	white_captures.right = (board_size+10)*grid;
	aDC.DrawText(white_prinsoner, &white_captures, DT_LEFT);

	DisplayTime();
	display_photos();
}

void CGoView::draw_stone(int x, int y, Turn stone)
{
 int board_size, grid;
 CBitmap black_bitmap, white_bitmap, board_bitmap, mask_bitmap;
 CDC dcMemory_mask, dcMemory;
 //BITMAP bm;


 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);
 CClientDC aDC(this);

 board_size = pDoc->board->m_boardsize;
 grid = pDoc->board->m_gridsize;

 
 
 if (stone == VACANT) {
 //aDC.FillSolidRect( x*grid-grid/2, y*grid-grid/2, grid, grid, RGB(255,255,255));
	board_bitmap.LoadBitmap(IDB_board_birch);
	dcMemory.CreateCompatibleDC(&aDC);
	dcMemory.SelectObject(&board_bitmap);
	aDC.BitBlt(x*grid-grid/2,y*grid-grid/2,grid,grid,&dcMemory,0,0,SRCCOPY);

	aDC.SelectStockObject(BLACK_PEN);
	if (x==1 && y==1) {
		aDC.MoveTo(x*grid+grid/2,y*grid);
		aDC.LineTo(x*grid,y*grid);
		aDC.LineTo(x*grid,y*grid+grid/2);
	}
	else if (x==1 && y==board_size) {
		aDC.MoveTo(x*grid+grid/2,y*grid);
		aDC.LineTo(x*grid,y*grid);
		aDC.LineTo(x*grid,y*grid-grid/2);
	}
	else if (x==board_size && y==board_size) {
		aDC.MoveTo(x*grid-grid/2,y*grid);
		aDC.LineTo(x*grid,y*grid);
		aDC.LineTo(x*grid,y*grid-grid/2);
	}
	else if (x==board_size && y==1) {
		aDC.MoveTo(x*grid-grid/2,y*grid);
		aDC.LineTo(x*grid,y*grid);
		aDC.LineTo(x*grid,y*grid+grid/2);
	}
	else if (x==1) {
		aDC.MoveTo(x*grid,y*grid-grid/2);
		aDC.LineTo(x*grid,y*grid+grid/2);
		aDC.MoveTo(x*grid,y*grid);
		aDC.LineTo(x*grid+grid/2,y*grid);
	}
	else if (x==board_size) {
		aDC.MoveTo(x*grid,y*grid-grid/2);
		aDC.LineTo(x*grid,y*grid+grid/2);
		aDC.MoveTo(x*grid,y*grid);
		aDC.LineTo(x*grid-grid/2,y*grid);
	}
	else if (y==1) {
		aDC.MoveTo(x*grid-grid/2,y*grid);
		aDC.LineTo(x*grid+grid/2,y*grid);
		aDC.MoveTo(x*grid,y*grid);
		aDC.LineTo(x*grid,y*grid+grid/2);
	}
	else if (y==board_size) {
		aDC.MoveTo(x*grid-grid/2,y*grid);
		aDC.LineTo(x*grid+grid/2,y*grid);
		aDC.MoveTo(x*grid,y*grid);
		aDC.LineTo(x*grid,y*grid-grid/2);
	}
	else {
		aDC.MoveTo(x*grid-grid/2,y*grid);
		aDC.LineTo(x*grid+grid/2,y*grid);
		aDC.MoveTo(x*grid,y*grid-grid/2);
		aDC.LineTo(x*grid,y*grid+grid/2);
	}

	CBrush aBrush(RGB(0,0,0));
	aDC.SelectObject(&aBrush);
	switch (board_size) {
	case 9:
		if ((x==3 && y==3) || (x==3 && y==5) || (x==3 && y==7) || 
		    (x==5 && y==3) || (x==5 && y==5) || (x==5 && y==7) ||
		    (x==7 && y==3) || (x==7 && y==5) || (x==7 && y==7)) {
				aDC.Ellipse(grid*x-3,grid*y-3,grid*x+3,grid*y+3);
		}
		break;
	case 13:
		if ((x==4 && y==4) || (x==4 && y==7) || (x==4 && y==10) || 
		    (x==7 && y==4) || (x==7 && y==7) || (x==7 && y==10) ||
		    (x==10 && y==4) || (x==10 && y==7) || (x==10 && y==10)) {
				aDC.Ellipse(grid*x-3,grid*y-3,grid*x+3,grid*y+3);
		}
		break;
	case 19:
		if ((x==4 && y==4) || (x==4 && y==10) || (x==4 && y==16) || 
		    (x==10 && y==4) || (x==10 && y==10) || (x==10 && y==16) ||
		    (x==16 && y==4) || (x==16 && y==10) || (x==16 && y==16)) {
				aDC.Ellipse(grid*x-3,grid*y-3,grid*x+3,grid*y+3);
		}
		break;
	default:
		exit(0);
	}
 }


 
if (stone == BLACK) {
	switch (board_size) {
	case 19:
		mask_bitmap.LoadBitmap(IDB_Mask_38);
		black_bitmap.LoadBitmap(IDB_Black_38);
		break;
	case 13:
		mask_bitmap.LoadBitmap(IDB_Mask_40);
		black_bitmap.LoadBitmap(IDB_Black_40);
		break;
	case 9:
		mask_bitmap.LoadBitmap(IDB_Mask_59);
		black_bitmap.LoadBitmap(IDB_Black_59);
		break;
	}
	dcMemory_mask.CreateCompatibleDC(&aDC);
	dcMemory_mask.SelectObject(&mask_bitmap);
	aDC.BitBlt(x*grid-grid/2,y*grid-grid/2,grid,grid,&dcMemory_mask,0,0,SRCAND);
	//black_bitmap.LoadBitmap(IDB_Black_30);
	dcMemory.CreateCompatibleDC(&aDC);
	dcMemory.SelectObject(&black_bitmap);
	aDC.BitBlt(x*grid-grid/2,y*grid-grid/2,grid,grid,&dcMemory,0,0,SRCPAINT);
	//aDC.SelectStockObject(BLACK_BRUSH);
    //aDC.Ellipse(x*grid-grid/2, y*grid-grid/2, x*grid+grid/2, y*grid+grid/2);
 }
 else if (stone == WHITE) {
	switch (board_size) {
	case 19:
		mask_bitmap.LoadBitmap(IDB_Mask_38);
		white_bitmap.LoadBitmap(IDB_White_38);
		break;
	case 13:
		mask_bitmap.LoadBitmap(IDB_Mask_40);
		white_bitmap.LoadBitmap(IDB_White_40);
		break;
	case 9:
		mask_bitmap.LoadBitmap(IDB_Mask_59);
		white_bitmap.LoadBitmap(IDB_White_59);
		break;
	}
	//mask_bitmap.LoadBitmap(IDB_Mask_30);
	dcMemory_mask.CreateCompatibleDC(&aDC);
	dcMemory_mask.SelectObject(&mask_bitmap);
	aDC.BitBlt(x*grid-grid/2,y*grid-grid/2,grid,grid,&dcMemory_mask,0,0,SRCAND);
	//white_bitmap.LoadBitmap(IDB_White_30);
	dcMemory.CreateCompatibleDC(&aDC);
	dcMemory.SelectObject(&white_bitmap);
	aDC.BitBlt(x*grid-grid/2,y*grid-grid/2,grid,grid,&dcMemory,0,0,SRCPAINT);
	//aDC.SelectStockObject(WHITE_BRUSH);
    //aDC.Ellipse(x*grid-grid/2, y*grid-grid/2, x*grid+grid/2, y*grid+grid/2);
 }
}

void CGoView::draw_mark(int x, int y)
{
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);
 CClientDC aDC(this);
 int pos, grid;
 CBrush mark_brush;

 grid = pDoc->board->m_gridsize;
 pos = pDoc->board->get_board_position(previous_x, previous_y, pDoc->board->p_current_board_position);
 switch(pos)
 {
	case 1:
		draw_stone(previous_x, previous_y, BLACK);
		break;
	case 2:
		draw_stone(previous_x, previous_y, WHITE);
		break;
	default :
		draw_stone(previous_x, previous_y, VACANT);
		break;
 }

 mark_brush.CreateSolidBrush(RGB(255,0,0));
 aDC.SelectObject(&mark_brush);
 aDC.Ellipse(x*grid-grid/4, y*grid-grid/4, x*grid+grid/4, y*grid+grid/4);

 previous_x = x;
 previous_y = y;
}

void CGoView::OnPassButton()
{
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);

 if (pDoc->board->game_status == PLAYING) {
	pDoc->board->num_consecutive_pass++;
	if (pDoc->board->p_current_board_position->player == BLACK) {
		pDoc->board->p_current_board_position->player = WHITE;
		StopTimer(TIMER_BLACK);
		StartTimer(TIMER_WHITE, 1000);
	}
	else {
		pDoc->board->p_current_board_position->player = BLACK;
		StopTimer(TIMER_WHITE);
		StartTimer(TIMER_BLACK, 1000);
	}

	CClientDC aDC(this);
	int pos;
	pos = pDoc->board->get_board_position(previous_x, previous_y, pDoc->board->p_current_board_position);
	switch(pos)
	{
		case 1:
			draw_stone(previous_x, previous_y, BLACK);
			break;
		case 2:
			draw_stone(previous_x, previous_y, WHITE);
			break;
		default :
			draw_stone(previous_x, previous_y, VACANT);
			break;
	}
	if (pDoc->board->num_consecutive_pass==2) {
		pDoc->board->game_status = SCORING;
		if (pDoc->board->p_current_board_position->player == BLACK) {
				StopTimer(TIMER_BLACK);
		}
		else {
				StopTimer(TIMER_WHITE);
		}
		pDoc->board->collect_chains();
		AfxMessageBox("兩虛終局，請將死子移除，無爭議時請按(結束)鈕，否則請按(繼續)鈕...",MB_OK);
	}
 }
}

int CGoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	IniCountDownTime();
	StartTimer(TIMER_BLACK, 1000);
	// TODO: Add your specialized creation code here
    PassButton.Create(_T("虛手"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect(23*BOARD_GRID_SIZE_19,500,23*BOARD_GRID_SIZE_19+100,540), this, 1);
	ResignButton.Create(_T("認輸"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect(23*BOARD_GRID_SIZE_19,560,23*BOARD_GRID_SIZE_19+100,600), this, 2);
	DoneButton.Create(_T("結束"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect(28*BOARD_GRID_SIZE_19,500,28*BOARD_GRID_SIZE_19+100,540), this, 3);
	ContinueButton.Create(_T("繼續"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, CRect(28*BOARD_GRID_SIZE_19,560,28*BOARD_GRID_SIZE_19+100,600), this, 4);
	return 0;
}

void CGoView::OnResignButton()
{
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);

 pDoc->board->game_status = OVER;
 if (pDoc->board->p_current_board_position->player == BLACK) {
	StopTimer(TIMER_BLACK);
	AfxMessageBox("白方中盤勝",MB_OK);
 }
 else {
	StopTimer(TIMER_WHITE);
	AfxMessageBox("黑方中盤勝",MB_OK);
 }
}


void CGoView::OnDoneButton()
{
 float black_points, white_points;
 CString scoring_message;
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);

 if (pDoc->board->game_status == SCORING) {
	pDoc->board->game_status = OVER;
	pDoc->board->mp_rule->scoring(black_points, white_points, pDoc->board);
	CClientDC aDC(this);
	int pos, i, j;
	for (i=0; i<pDoc->board->m_boardsize; i++) {
		for (j=0; j<pDoc->board->m_boardsize; j++) {
			pos = pDoc->board->get_board_position(i+1, j+1, pDoc->board->p_current_board_position);
			switch(pos)
			{
			case 0:
				if (pDoc->board->territory_mark[i][j]==1)
					draw_territory_mark(i+1, j+1, 0);
				else if (pDoc->board->territory_mark[i][j]==2)
					draw_territory_mark(i+1, j+1, 1);
				break;
			case 1:
				if (pDoc->board->territory_mark[i][j]==2)
					draw_territory_mark(i+1, j+1, 1);
				break;
			case 2:
				if (pDoc->board->territory_mark[i][j]==1)
					draw_territory_mark(i+1, j+1, 0);
				break;
			}
		}
	}

	if (black_points > white_points) {
		scoring_message.Format("%s %.1f %s %.1f\n%s %.1f %s", "黑方地域：",  black_points, "白方地域：",  white_points, "黑方勝：", black_points-white_points, "點");
		AfxMessageBox(scoring_message,MB_OK);
	}
	if (black_points < white_points) {
		scoring_message.Format("%s %.1f %s %.1f\n%s %.1f %s", "黑方地域：",  black_points, "白方地域：",  white_points, "白方勝：", white_points-black_points, "點");
		AfxMessageBox(scoring_message,MB_OK);
	}
	if (black_points == white_points) {
		scoring_message.Format("%s", "本局不分勝負");
		AfxMessageBox(scoring_message,MB_OK);
	}
 }
}

void CGoView::OnContinueButton()
{
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);
 int i, j;

 if (pDoc->board->game_status == SCORING) {
	for (i=0; i<pDoc->board->m_boardsize; i++) {
		for (j=0; j<pDoc->board->m_boardsize; j++) {
			pDoc->board->territory_mark[i][j] = 0;
		}
	}

	pDoc->board->game_status = PLAYING;
	if (pDoc->board->p_current_board_position->player == BLACK) {
		StartTimer(TIMER_BLACK, 1000);
	}
	else {
		StartTimer(TIMER_WHITE, 1000);
	}

	OnUpdate(NULL,0,NULL);
 }
}

void CGoView::draw_territory_mark(int x, int y, int color)
{
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);
 CClientDC aDC(this);
 int grid;
 CBrush mark_brush;

 grid = pDoc->board->m_gridsize;
 
 if (color==0) 
	 mark_brush.CreateSolidBrush(RGB(0,0,0));
 else 
	 mark_brush.CreateSolidBrush(RGB(255,255,255));
 aDC.SelectObject(&mark_brush);
 aDC.Rectangle(x*grid-grid/4, y*grid-grid/4, x*grid+grid/4, y*grid+grid/4);
}

void CGoView::OnTimer(UINT nIDEvent) 
{
 static bool soundFlagBlack=true, soundFlagWhite=true;
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);
 CBitmap cursor_bitmap;
 CDC dcMemory;
 CClientDC aDC(this);

	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == TIMER_BLACK) {
		if (black_base_time == 0) {
			// 黑方讀秒
			//AfxMessageBox("黑方開始讀秒",MB_OK);
			black_time = BlackCountDownTime;

			if ((BlackNumCountDown==pDoc->board->m_NumCountDown) && soundFlagBlack) {
				PlaySound( MAKEINTRESOURCE(IDR_StartCountDown), AfxGetInstanceHandle(), SND_RESOURCE);
				soundFlagBlack = false;
			}
			if (soundFlagBlack) {
				switch(BlackNumCountDown)
				{
				case 3:
					PlaySound( MAKEINTRESOURCE(IDR_RemainThreeCountDown), AfxGetInstanceHandle(), SND_RESOURCE);
					soundFlagBlack = false;
					break;
				case 2:
					PlaySound( MAKEINTRESOURCE(IDR_RemainTwoCountDown), AfxGetInstanceHandle(), SND_RESOURCE);
					soundFlagBlack = false;
					break;
				case 1:
					PlaySound( MAKEINTRESOURCE(IDR_FinalCountDown), AfxGetInstanceHandle(), SND_RESOURCE);
					soundFlagBlack = false;
					break;
				case 0:
					StopTimer(TIMER_BLACK);
					AfxMessageBox("黑方超時敗!",MB_OK);
					break;
				}
			}


			switch(BlackCountDownTime)
			{
			case 10:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown10), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				//SetCursor(LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR10)));
				//SetCursorPos(800,800);
				//ShowCursor(true);
				//cursor_bitmap.Attach((HBITMAP)LoadImage(NULL, MAKEINTRESOURCE(IDC_CURSOR10),2,32,32,LR_DEFAULTCOLOR)); 
				//cursor_bitmap.FromHandle((HBITMAP)LoadImage(NULL, MAKEINTRESOURCE(IDC_CURSOR10),2,32,32,LR_DEFAULTCOLOR));
				break;
			case 9:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown9), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number9);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 8:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown8), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number8);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 7:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown7), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number7);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 6:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown6), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number6);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 5:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown5), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number5);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 4:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown4), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number4);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 3:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown3), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number3);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 2:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown2), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number2);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 1:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown1), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number1);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY );
				break;
			case 0:
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,WHITENESS);
				BlackCountDownTime = pDoc->board->m_CountDownTime;
				BlackNumCountDown--;
				soundFlagBlack = true;
				break;
			}
			BlackCountDownTime--;

		}
		else {
			black_base_time = black_base_time - 1;
			black_time--;
		}
    }

    if(nIDEvent == TIMER_WHITE) {
		if (white_base_time == 0) {
			// 白方讀秒
			//AfxMessageBox("白方開始讀秒",MB_OK);
			white_time = WhiteCountDownTime;
			if ((WhiteNumCountDown==pDoc->board->m_NumCountDown) && soundFlagWhite) {
				PlaySound( MAKEINTRESOURCE(IDR_StartCountDown), AfxGetInstanceHandle(), SND_RESOURCE);
				soundFlagWhite = false;
			}

			if (soundFlagWhite) {
				switch(WhiteNumCountDown)
				{
				case 3:
					PlaySound( MAKEINTRESOURCE(IDR_RemainThreeCountDown), AfxGetInstanceHandle(), SND_RESOURCE);
					soundFlagWhite = false;
					break;
				case 2:
					PlaySound( MAKEINTRESOURCE(IDR_RemainTwoCountDown), AfxGetInstanceHandle(), SND_RESOURCE);
					soundFlagWhite = false;
					break;
				case 1:
					PlaySound( MAKEINTRESOURCE(IDR_FinalCountDown), AfxGetInstanceHandle(), SND_RESOURCE);
					soundFlagWhite = false;
					break;
				case 0:
					StopTimer(TIMER_WHITE);
					AfxMessageBox("白方超時敗!",MB_OK);
					break;
				}
			}

			switch(WhiteCountDownTime)
			{
			case 10:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown10), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				break;
			case 9:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown9), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number9);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 8:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown8), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number8);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 7:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown7), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number7);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 6:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown6), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number6);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 5:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown5), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number5);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 4:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown4), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number4);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 3:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown3), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number3);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 2:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown2), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number2);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 1:
				PlaySound( MAKEINTRESOURCE(IDR_CountDown1), AfxGetInstanceHandle(), SND_ASYNC |SND_RESOURCE);
				dcMemory.CreateCompatibleDC(&aDC);
				cursor_bitmap.LoadBitmap(IDB_Number1);
				dcMemory.SelectObject(&cursor_bitmap);
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,SRCCOPY);
				break;
			case 0:
				aDC.BitBlt(800,600,150,150,&dcMemory,0,0,WHITENESS);
				WhiteCountDownTime = pDoc->board->m_CountDownTime;
				WhiteNumCountDown--;
				soundFlagWhite = true;
				break;
			}
			WhiteCountDownTime--;
		}
		else {
			white_base_time = white_base_time - 1;
			white_time--;
		}
     }
	DisplayTime();
	CView::OnTimer(nIDEvent);
}

UINT CGoView::StartTimer(UINT TimerID, UINT TimerDuration)
{
	UINT    TimerVal;

    TimerVal = SetTimer (TimerID, TimerDuration, NULL);  // Starting the Timer

    if (TimerVal == 0) {
       AfxMessageBox("Unable to obtain timer");
    }

    return TimerVal;

}

BOOL CGoView::StopTimer(UINT TimerVal)
{
	if (!KillTimer (TimerVal)) {
       return FALSE;
	}

    //    Place clean-up code following this point.

    return TRUE;

}

void CGoView::IniCountDownTime()
{
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);

 black_time = white_time = black_base_time = white_base_time = pDoc->board->m_basic_time * 60;
 BlackCountDownTime = WhiteCountDownTime = pDoc->board->m_CountDownTime;
 BlackNumCountDown = WhiteNumCountDown = pDoc->board->m_NumCountDown;
}

void CGoView::DisplayTime()
{
 int grid, board_size;
 int hours, minutes, seconds;
 CString black_time_display, white_time_display;
 CRect black_time_display_area, white_time_display_area;

 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);
 CClientDC aDC(this);
 board_size = pDoc->board->m_boardsize;
 grid = pDoc->board->m_gridsize;

 hours = (int)(black_time/3600);
 minutes = (int)(black_time/60 - hours*60);
 seconds = black_time % 60;
 black_time_display.Format("(%2d) %s %2d:%2d:%2d ", BlackNumCountDown, "黑方時間：", hours, minutes, seconds);
 hours = (int)(white_time/3600);
 minutes = (int)(white_time/60 - hours*60);
 seconds = white_time % 60;
 white_time_display.Format("(%2d) %s %2d:%2d:%2d ", WhiteNumCountDown, "白方時間：", hours, minutes, seconds);

 black_time_display_area.bottom = 290;
 black_time_display_area.top = 250;
 black_time_display_area.left = (board_size+4)*grid;
 black_time_display_area.right = (board_size+10)*grid;
 aDC.DrawText(black_time_display, &black_time_display_area, DT_LEFT);

 white_time_display_area.bottom = 290;
 white_time_display_area.top = 250;
 white_time_display_area.left = (board_size+12)*grid;
 white_time_display_area.right = (board_size+18)*grid;
 aDC.DrawText(white_time_display, &white_time_display_area, DT_LEFT);
}

void CGoView::display_photos()
{
 int  grid, board_size;
 CBitmap black_player_bitmap, white_player_bitmap;
 CBitmap black_bitmap, white_bitmap, mask_bitmap;
 CDC dcMemory;

 CClientDC aDC(this);
 CGoDoc* pDoc = GetDocument();
 ASSERT_VALID(pDoc);
 board_size = pDoc->board->m_boardsize;
 grid = pDoc->board->m_gridsize;

 black_player_bitmap.LoadBitmap(IDB_cswang1);
 white_player_bitmap.LoadBitmap(IDB_cswang2);
 black_bitmap.LoadBitmap(IDB_Black_30);
 white_bitmap.LoadBitmap(IDB_White_30);
 mask_bitmap.LoadBitmap(IDB_Mask_30);

 dcMemory.CreateCompatibleDC(&aDC);

 dcMemory.SelectObject(&mask_bitmap);
 aDC.BitBlt((board_size+2)*grid,240,(board_size+10)*grid,240,&dcMemory,0,0,SRCAND);
 dcMemory.SelectObject(&black_bitmap);
 aDC.BitBlt((board_size+2)*grid,240,(board_size+10)*grid,240,&dcMemory,0,0,SRCPAINT);
 dcMemory.SelectObject(&black_player_bitmap);
 aDC.StretchBlt((board_size+2)*grid,0,200,220,&dcMemory,0,0,402,531,SRCCOPY);
 
 //aDC.BitBlt((board_size+2)*grid,0,(board_size+10)*grid,240,&dcMemory,0,0,SRCCOPY);
 dcMemory.SelectObject(&mask_bitmap);
 aDC.BitBlt((board_size+10)*grid,240,(board_size+10)*grid,240,&dcMemory,0,0,SRCAND);
 dcMemory.SelectObject(&white_bitmap);
 aDC.BitBlt((board_size+10)*grid,240,(board_size+10)*grid,240,&dcMemory,0,0,SRCPAINT);
 dcMemory.SelectObject(&white_player_bitmap);
 aDC.StretchBlt((board_size+10)*grid,0,200,220,&dcMemory,0,0,402,531,SRCCOPY);
 //aDC.BitBlt((board_size+12)*grid,0,(board_size+20)*grid,240,&dcMemory,0,0,SRCCOPY);
}

void CGoView::OnFileNew() 
{
	// TODO: Add your command handler code here
	IniCountDownTime();
}
