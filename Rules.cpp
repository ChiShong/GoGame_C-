// Rules.cpp: implementation of the CRules class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Go.h"
#include "board.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRules::CRules()
{

}

CRules::~CRules()
{

}

CRulePSK::CRulePSK()
{

}

CRulePSK::~CRulePSK()
{
 for (int i=0; i<MAX_STONES; i++)
	p_situation_list[i].clear();
}

bool CRulePSK::LegalMove(Turn t, int x, int y, Cboard *board)
{
 Csituation simulated_board(*(board->p_current_board_position));
 int pos;
 vector<pair<int,int> > deads;

 if (x<1 || x>board->m_boardsize || y<1 || y>board->m_boardsize) return false;

 pos = board->get_board_position(x, y, &simulated_board);
 switch(pos)
    {
    case 0: //vacancy
		board->set_board_position(t, x, y, &simulated_board);
		remove_deads(t, x, y, &simulated_board, board, deads);
		if (position_super_ko(t, x, y, &simulated_board))
			return false;
		else return true;
        break;
    case 1:
		return false;
        break;
	case 2:
		return false;
        break;
	default :
		return false;
    }
}

bool CRulePSK::position_super_ko(Turn t, int x, int y, Csituation *p)
{
 bool flag;
	if (p_situation_list[p->m_stones_on_board].empty()) {
		return false;
	}
	else {
		list<CountedPtr<Csituation> >::iterator pos;
		for(pos=p_situation_list[p->m_stones_on_board].begin(); pos!=p_situation_list[p->m_stones_on_board].end(); pos++) {
			flag=true;
			for (int i=0; i<Board_Size; i++) {
				if(((*pos)->p_board_position[i])!=(p->p_board_position[i])) {
					flag=false;
					break;
				}
			}
			if (flag) return true;
		}
		return false;
	}
}


pair<Turn,int> CRulePSK::remove_deads(Turn t, int x, int y, Csituation *p, Cboard *board, vector<pair<int,int> > &deads)
{
 int liberties, xd, yd, num_captured=0, j, k;
 vector<pair<int,int> > s;
 pair<int,int> move;
 Turn opposite, dead_color;
 char visited[Board_Size][Board_Size];

 if (t==BLACK) {
	 opposite = WHITE;
 }
 else {
	 opposite = BLACK;
 }

 vector<pair<int,int> >::iterator i;
 
 liberties = 0;
 s.clear();
 for (j=0; j<Board_Size; j++)
	for (k=0; k<Board_Size; k++)
		visited[j][k] = 0;
 board->collect_strings(opposite, x, y-1, p, liberties, s, visited);
 // capture opposite string stones
 if (!liberties) {
	num_captured += s.size();
	dead_color = opposite;
	for(i=s.begin(); i<s.end(); i++) {
		move = *i;
		deads.push_back(move);
		xd = move.first;
		yd = move.second;
		board->clear_board_position(xd, yd, p);
	}
 }
 liberties = 0;
 s.clear();
 for (j=0; j<Board_Size; j++)
	for (k=0; k<Board_Size; k++)
		visited[j][k] = 0;
 board->collect_strings(opposite, x, y+1, p, liberties, s, visited);
 // capture opposite string stones
 if (!liberties) {
	num_captured += s.size();
	dead_color = opposite;
	for(i=s.begin(); i<s.end(); i++) {
		move = *i;
		deads.push_back(move);
		xd = move.first;
		yd = move.second;
		board->clear_board_position(xd, yd, p);
	}
 }
 liberties = 0;
 s.clear();
 for (j=0; j<Board_Size; j++)
	for (k=0; k<Board_Size; k++)
		visited[j][k] = 0;
 board->collect_strings(opposite, x-1, y, p, liberties, s, visited);
 // capture opposite string stones
 if (!liberties) {
	num_captured += s.size();
	dead_color = opposite;
	for(i=s.begin(); i<s.end(); i++) {
		move = *i;
		deads.push_back(move);
		xd = move.first;
		yd = move.second;
		board->clear_board_position(xd, yd, p);
	}
 }
 liberties = 0;
 s.clear();
 for (j=0; j<Board_Size; j++)
	for (k=0; k<Board_Size; k++)
		visited[j][k] = 0;
 board->collect_strings(opposite, x+1, y, p, liberties, s, visited);
 // capture opposite string stones
 if (!liberties) {
	num_captured += s.size();
	dead_color = opposite;
	for(i=s.begin(); i<s.end(); i++) {
		move = *i;
		deads.push_back(move);
		xd = move.first;
		yd = move.second;
		board->clear_board_position(xd, yd, p);
	}
 }
 liberties = 0;
 s.clear();
 for (j=0; j<Board_Size; j++)
	for (k=0; k<Board_Size; k++)
		visited[j][k] = 0;
 board->collect_strings(t, x, y, p, liberties, s, visited);
 // suicide
 if (!liberties) {
	num_captured += s.size();
	dead_color = t;
	for(i=s.begin(); i<s.end(); i++) {
		move = *i;
		deads.push_back(move);
		xd = move.first;
		yd = move.second;
		board->clear_board_position(xd, yd, p);
	}
 }
 return(make_pair(dead_color, num_captured));
}

bool CRulePSK::move(Turn t, int x, int y, Cboard *b, vector<pair<int,int> > &deads, Turn &dead_color)
{
 pair<Turn,int> dead_stones;
 CMove move;

	if (LegalMove(t, x, y, b)) {
		b->set_board_position(t, x, y, b->p_current_board_position);
		b->m_num_moves++;
		dead_stones = remove_deads(t, x, y, b->p_current_board_position, b, deads);
		if (dead_stones.first==BLACK && dead_stones.second) {
			b->m_black_captured += dead_stones.second;
		}
		else if (dead_stones.first==WHITE && dead_stones.second) {
			b->m_white_captured += dead_stones.second;
		}
		dead_color = dead_stones.first;

		CountedPtr<Csituation> ptr(new Csituation(*(b->p_current_board_position)));
		p_situation_list[b->p_current_board_position->m_stones_on_board].push_back(ptr);
		
		move.stone = t;
		move.x = x;
		move.y = y;
		move.dead_color = dead_color;
		move.captured = deads;
		move.m_black_captured = b->m_black_captured;
		move.m_white_captured = b->m_white_captured;
		move.m_num_moves = b->m_num_moves;
		move.m_stones_on_board = b->p_current_board_position->m_stones_on_board;
//		for (int i=0; i<Board_Size; i++)
			//move.p_board_position[i] = b->p_current_board_position->p_board_position[i];
		b->m_moves.moves_sequence.push_back(move);
	    b->m_moves.current_moves_index = b->m_moves.moves_sequence.end();
		return true;
	}
	else {
		return false;
	}
}

void CRulePSK::scoring(float &black_points, float &white_points, Cboard *b)
{
 int i, j, iv, jv;
 int chain_id;
 vector<pair<int,int> > s;
 vector<pair<int,int> >::iterator ite;
 int ChainsMarks[Board_Size][Board_Size];
 char visited[Board_Size][Board_Size];
 int first_nonvacant_id;
 //bool same_color_and_different_chains;

 for (i=0; i<b->m_boardsize; i++) {
	 for (j=0; j<b->m_boardsize; j++) {
		ChainsMarks[i][j] = 0; // it indicates an unoccupied point
	 }
 }

 for (i=0; i<MAX_STONES; i++) {
	 if (b->p_Chains[i]) {
		 for (ite=b->p_Chains[i]->chain_members.begin(); ite<b->p_Chains[i]->chain_members.end(); ite++) {
			 ChainsMarks[(*ite).first-1][(*ite).second-1] = i;
		 }
	 }
 }

 for (i=0; i<b->m_boardsize; i++) {
	 for (j=0; j<b->m_boardsize; j++) {
		 if (b->territory_mark[i][j]==0) {
			 if (b->p_Chains[ChainsMarks[i][j]]) { // for stone position
				 if (b->p_Chains[ChainsMarks[i][j]]->status != DEAD) {
					for (ite=b->p_Chains[ChainsMarks[i][j]]->chain_members.begin(); ite<b->p_Chains[ChainsMarks[i][j]]->chain_members.end(); ite++) {
						if (ChainsMarks[i][j] < MAX_STONES/2) {
							b->territory_mark[(*ite).first-1][(*ite).second-1] = 1; // black territory
						}
						else {
							b->territory_mark[(*ite).first-1][(*ite).second-1] = 2; // white territory
						}
					}
				 }
			 }
			 else { // for vacant position
				s.clear();
				for (iv=0; iv<b->m_boardsize; iv++)
					for (jv=0; jv<b->m_boardsize; jv++)
						visited[iv][jv] = 0;
				first_nonvacant_id=-2;
				//same_color_and_different_chains=false;
				b->eye_detect(i+1,j+1,ChainsMarks,chain_id,&s,visited,first_nonvacant_id);
				//CountedPtr<vector<pair<int,int> > > ptr(new vector<pair<int,int> >(s));
				//pChains[chain_id]->p_eyes.push_back(ptr);
				for (ite=s.begin(); ite<s.end(); ite++) {
					if (chain_id < MAX_STONES/2)
						b->territory_mark[(*ite).first-1][(*ite).second-1] = 1;
					else
						b->territory_mark[(*ite).first-1][(*ite).second-1] = 2;
				}
			 } 
		 }
	 }
 }

 black_points=0;
 white_points=0;
 // scoring ...
 for (i=0; i<b->m_boardsize; i++) {
	 for (j=0; j<b->m_boardsize; j++) {
		 if (b->territory_mark[i][j] == 1) black_points = black_points + 1;
		 else
			if (b->territory_mark[i][j] == 2) white_points = white_points + 1;
	 }
 }
 white_points += b->komi;
 
}
