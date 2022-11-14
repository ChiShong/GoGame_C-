// board.cpp: implementation of the Cboard class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Go.h"
//#include "Rules.h"
#include "board.h"

//class CRulePSK;


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cboard::Cboard()
{
 m_boardsize = 19;
 komi = 0;
 m_gridsize = BOARD_GRID_SIZE_19;
 m_rule = POSITIONAL_SUPER_KO;
 num_consecutive_pass = 0;
 m_num_moves = 0;
 m_black_captured = 0;
 m_white_captured = 0;
 if_simulate_moves = false;
 game_status = PLAYING;
 m_basic_time = 30;
 m_CountDownTime = 30;
 m_NumCountDown = 3;
 if (m_rule == POSITIONAL_SUPER_KO)
	mp_rule = new CRulePSK;
 p_current_board_position = new Csituation;
 for (int i=0; i<MAX_STONES; i++)
	p_Chains[i] = 0;

 for (i=0; i<Board_Size; i++)
	for (int j=0; j<Board_Size; j++)
		territory_mark[i][j] = 0;
 
}

Cboard::~Cboard()
{
	delete mp_rule;
	delete p_current_board_position;
	for (int i=0; i<MAX_STONES; i++)
		delete p_Chains[i];
}

Cboard::Cboard(int bsize)
{
 m_boardsize = bsize;
 switch (m_boardsize)
 {
  case 9 :
 	 m_gridsize = BOARD_GRID_SIZE_9;
 	 break;
  case 13 :
 	 m_gridsize = BOARD_GRID_SIZE_13;
 	 break;
  case 19 :
 	 m_gridsize = BOARD_GRID_SIZE_19;
 	 break;
 }
 komi = 0;
 m_rule = POSITIONAL_SUPER_KO;
 num_consecutive_pass = 0;
 m_num_moves = 0;
 m_black_captured = 0;
 m_white_captured = 0;
 if_simulate_moves = false;
 game_status = PLAYING;
 m_basic_time = 30;
 m_CountDownTime = 30;
 m_NumCountDown = 3;
 if (m_rule == POSITIONAL_SUPER_KO)
	mp_rule = new CRulePSK;
 p_current_board_position = new Csituation;
 for (int i=0; i<MAX_STONES; i++)
	p_Chains[i] = 0;

 for (i=0; i<Board_Size; i++)
	for (int j=0; j<Board_Size; j++)
		territory_mark[i][j] = 0;
}



// returned value 0 representing vacancy, 1 black, and 2 white
int Cboard::get_board_position(int x, int y, Csituation *p)
{
 __int64 tmp=3;
 tmp <<= 2*(y-1);
 tmp &= p->p_board_position[x-1];
 tmp >>= 2*(y-1);
 return (int)tmp;
}

void Cboard::clear_board_position(int x, int y, Csituation *p)
{
 __int64 tmp=3;
 p->m_stones_on_board--;
 tmp <<= 2*(y-1);
 tmp = ~tmp;
 p->p_board_position[x-1] &= tmp;
}


void Cboard::collect_strings(Turn stone_color, int x, int y, Csituation *p, int &liberties, vector<pair<int,int> > &s, char visited[Board_Size][Board_Size])
// int &liberties : liberties of chain extented from (x, y)
// vector<pair<int,int> > &s : chain extended from (x, y)
{
 int pos;
 pair<int,int> move;

	if (x<1 || x>m_boardsize || y<1 || y>m_boardsize) return;
	if (visited[x-1][y-1]) return;

	pos = get_board_position(x, y, p);
	
	move.first = x;
	move.second = y;

	switch(pos)
    {
    case 0: //vacancy : liberties plus 1
        if (!visited[x-1][y-1]) {
			liberties++;
			visited[x-1][y-1] = 1;
		}
		return;
        break;
    case 1:
		if (stone_color==BLACK) {
			if (!visited[x-1][y-1]) {
				s.push_back(move);
				visited[x-1][y-1] = 1;
			}
			collect_strings(stone_color, x, y-1, p, liberties, s, visited);
			collect_strings(stone_color, x, y+1, p, liberties, s, visited);
			collect_strings(stone_color, x-1, y, p, liberties, s, visited);
			collect_strings(stone_color, x+1, y, p, liberties, s, visited);	
		}
		else {
			visited[x-1][y-1] = 1;
			return;
		}
        break;
	case 2:
		if (stone_color==WHITE) {
			if (!visited[x-1][y-1]) {
				s.push_back(move);
				visited[x-1][y-1] = 1;
			}
			collect_strings(stone_color, x, y-1, p, liberties, s, visited);
			collect_strings(stone_color, x, y+1, p, liberties, s, visited);
			collect_strings(stone_color, x-1, y, p, liberties, s, visited);
			collect_strings(stone_color, x+1, y, p, liberties, s, visited);
		}
		else {
			visited[x-1][y-1] = 1;
			return;
		}
        break;
	default :
		return;
    }

}

void Cboard::set_board_position(Turn t, int x, int y, Csituation *p)
{
 //__int64 tmp;

 /*switch(t)
    {
	p->player = t;
	p->m_stones_on_board++;
    case BLACK:
        tmp = 1;
		tmp <<= 2*(y-1);
		p->p_board_position[x-1] |= tmp;
        break;
    case WHITE:
		tmp = 2;
		tmp <<= 2*(y-1);
		p->p_board_position[x-1] |= tmp;
        break;	
    }*/
  __int64 tmp=1; 
	p->player = t;
	p->m_stones_on_board++;
	if (t == BLACK) {
		tmp <<= (2*y-2);
		p->p_board_position[x-1] |= tmp;
	}
	else {
		tmp <<= (2*y-1);
		p->p_board_position[x-1] |= tmp;
	}
}

void Cboard::collect_chains()
{
 char visited[Board_Size][Board_Size], chains_visited[Board_Size][Board_Size];
 int x, y, liberties, pos, i, j;
 Turn stone;
 vector<pair<int,int> > s;
 vector<pair<int,int> >::iterator ite;

 // clear the chains collected in previous run
 for (i=0; i<MAX_STONES; i++) {
	 if (p_Chains[i]) {
		 delete p_Chains[i];
		 p_Chains[i] = 0;
	 }
 }

 num_of_black_chains = 0;
 num_of_white_chains = 0;
 for (i=0; i<m_boardsize; i++) 
	 for (j=0; j<m_boardsize; j++) {
		chains_visited[i][j] = 0;
		territory_mark[i][j] = 0;
	 }

 for (i=0; i<m_boardsize; i++) {
	 for (j=0; j<m_boardsize; j++) {
		if (chains_visited[i][j] == 1)
			continue;
		pos = get_board_position(i+1, j+1, p_current_board_position);
		switch(pos)
		{
			case 0: //vacancy
				break;
			case 1:
				num_of_black_chains++;
				stone = BLACK;
				liberties = 0;
				s.clear();
				for (x=0; x<m_boardsize; x++) 
					for (y=0; y<m_boardsize; y++)
						visited[x][y] = 0;
				collect_strings(stone, i+1, j+1, p_current_board_position, liberties, s, visited);
				p_Chains[num_of_black_chains] = new CChain;
				p_Chains[num_of_black_chains] -> liberties = liberties;
				for(ite=s.begin(); ite<s.end(); ite++) {
					chains_visited[(*ite).first-1][(*ite).second-1] = 1;
					//p_Chains[num_of_black_chains] -> chain_members.push_back((*ite));
				}
				p_Chains[num_of_black_chains] -> chain_members = s;
				break;
			case 2:
				num_of_white_chains++;
				stone = WHITE;
				liberties = 0;
				s.clear();
				for (x=0; x<m_boardsize; x++) 
					for (y=0; y<m_boardsize; y++)
						visited[x][y] = 0;
				collect_strings(stone, i+1, j+1, p_current_board_position, liberties, s, visited);
				p_Chains[MAX_STONES-num_of_white_chains-1] = new CChain;
				p_Chains[MAX_STONES-num_of_white_chains-1] -> liberties = liberties;
				for (ite=s.begin(); ite<s.end(); ite++) {
					chains_visited[(*ite).first-1][(*ite).second-1] = 1;
					//p_Chains[MAX_STONES-num_of_white_chains-1] -> chain_members.push_back((*ite));
				}
				p_Chains[MAX_STONES-num_of_white_chains-1] -> chain_members = s;
		}
	 }
 }
}

// not yet finished
void Cboard::live_or_dead_eval(CChain *pChains[])
{
 int ChainsMarks[Board_Size][Board_Size];
 char visited[Board_Size][Board_Size];
 int chain_id;
 int i, j, first_nonvacant_id;
 //bool same_color_and_different_chains;
 vector<pair<int,int> > s;
 vector<pair<int,int> >::iterator ite;

 for (i=0; i<Board_Size; i++) {
	 for (j=0; j<Board_Size; j++) {
		ChainsMarks[i][j] = 0; // it indicates an unoccupied point
		visited[i][j] = 0;
	 }
 }

 for (i=0; i<MAX_STONES; i++) {
	 if (pChains[i]) {
		 for (ite=pChains[i]->chain_members.begin(); ite<pChains[i]->chain_members.end(); ite++) {
			 ChainsMarks[(*ite).first-1][(*ite).second-1] = i;
		 }
	 }
 }

 for (i=0; i<Board_Size; i++) {
	 for (j=0; j<Board_Size; j++) {
		 if (ChainsMarks[i][j] == 0 && visited[i][j] == 0) {
			 s.clear();
			 if (eye_detect(i+1,j+1,ChainsMarks,chain_id,&s,visited,first_nonvacant_id)) {
				CountedPtr<vector<pair<int,int> > > ptr(new vector<pair<int,int> >(s));
//				pChains[chain_id]->p_eyes.push_back(ptr);
				for (ite=s.begin(); ite<s.end(); ite++) {
					visited[(*ite).first-1][(*ite).second-1] = 1;
				}
			 }
		 }
	 }
 }

 for (i=0; i<MAX_STONES; i++) {
	 if (pChains[i]) {
//		 if (pChains[i]->p_eyes.size() > 1)
			 pChains[i]->status = LIVE; // write to here
	 }
 }

}


// if the space extended from (x,y) is truely an eye, return true, list of points of the eye and the chain id it belongs to, otherwise return false.
bool Cboard::eye_detect(int x, int y, int ChainsMarks[][Board_Size], int &id, vector<pair<int,int> > *s, char visited[Board_Size][Board_Size], int &first_nonvacant_id)
{
 int current_id;
 pair<int,int> p;

 if (x<1 || x>m_boardsize || y<1 || y>m_boardsize) return true;
 if (visited[x-1][y-1]) return true;
 else visited[x-1][y-1] = 1;

 p.first = x;
 p.second = y;

 current_id = ChainsMarks[x-1][y-1];

 if (current_id == 0) {
	 s->push_back(p);
 }
 else {
	 if (first_nonvacant_id == -2) { // first meets the stone
		first_nonvacant_id = current_id;
		return true;
	 }
	 else {
		 if (current_id != first_nonvacant_id) {
			 if (!(((current_id < MAX_STONES/2) && (first_nonvacant_id < MAX_STONES/2)) || 
				 ((current_id > MAX_STONES/2) && (first_nonvacant_id > MAX_STONES/2)))) { // different color of stone around the vacant area
				s->clear();
				return false;
			 }
			 else {
				//same_color_and_different_chains=true;
				return true; //true or false eye to here
			 }
		 }
		 else
			 return true;
	 }
 }
 

 if (!eye_detect(x, y-1, ChainsMarks, id, s, visited, first_nonvacant_id)) {return false;}
 if (!eye_detect(x, y+1, ChainsMarks, id, s, visited, first_nonvacant_id)) {return false;}
 if (!eye_detect(x-1, y, ChainsMarks, id, s, visited, first_nonvacant_id)) {return false;}
 if (!eye_detect(x+1, y, ChainsMarks, id, s, visited, first_nonvacant_id)) {return false;}

 id = first_nonvacant_id;
 /*if (same_color_and_different_chains)
	return false;
 else*/
	return true;
 
}

// set the chain extending from (x, y) dead and return the vacant points adjacent to the chain
bool Cboard::set_chain_dead(int x, int y, vector<pair<int,int> > *adjacent_vacancy, int &chain_num)
{
 int ChainsMarks[Board_Size][Board_Size];
 char visited[Board_Size][Board_Size];
 int i, j, x_t, y_t;
 pair<int,int> p;
 vector<pair<int,int> >::iterator ite;

 for (i=0; i<Board_Size; i++) {
	 for (j=0; j<Board_Size; j++) {
		ChainsMarks[i][j] = 0; // it indicates an unoccupied point
		visited[i][j] = 0;
	 }
 }

 for (i=0; i<MAX_STONES; i++) {
	 if (p_Chains[i]) {
		 for (ite=p_Chains[i]->chain_members.begin(); ite<p_Chains[i]->chain_members.end(); ite++) {
			 ChainsMarks[(*ite).first-1][(*ite).second-1] = i;
		 }
	 }
 }

 if (p_Chains[ChainsMarks[x-1][y-1]]) {
	p_Chains[ChainsMarks[x-1][y-1]]->status = DEAD;
	chain_num = ChainsMarks[x-1][y-1];
	for (ite=p_Chains[chain_num]->chain_members.begin(); ite<p_Chains[chain_num]->chain_members.end(); ite++) {
		x_t = (*ite).first;
		y_t = (*ite).second-1;
		if (y_t != 0)
			if (ChainsMarks[x_t-1][y_t-1] == 0 && visited[x_t-1][y_t-1] == 0) {
				p.first = x_t;
				p.second = y_t;
				adjacent_vacancy->push_back(p);
				visited[x_t-1][y_t-1] = 1;
			}
		x_t = (*ite).first;
		y_t = (*ite).second+1;
		if (y_t != m_boardsize+1)
			if (ChainsMarks[x_t-1][y_t-1] == 0 && visited[x_t-1][y_t-1] == 0) {
				p.first = x_t;
				p.second = y_t;
				adjacent_vacancy->push_back(p);
				visited[x_t-1][y_t-1] = 1;
			}
		x_t = (*ite).first-1;
		y_t = (*ite).second;
		if (x_t != 0)
			if (ChainsMarks[x_t-1][y_t-1] == 0 && visited[x_t-1][y_t-1] == 0) {
				p.first = x_t;
				p.second = y_t;
				adjacent_vacancy->push_back(p);
				visited[x_t-1][y_t-1] = 1;
			}
		x_t = (*ite).first+1;
		y_t = (*ite).second;
		if (x_t != m_boardsize+1)
			if (ChainsMarks[x_t-1][y_t-1] == 0 && visited[x_t-1][y_t-1] == 0) {
				p.first = x_t;
				p.second = y_t;
				adjacent_vacancy->push_back(p);
				visited[x_t-1][y_t-1] = 1;
			}
	}
	return true;
 }
 else {
	 return false;
 }

}

// In the TerritoryMarks, attributes 'b' represents black, 'w' represents white and 'c' represents the share point
void Cboard::set_vacant_territory(int x, int y, char attribute, vector<pair<int,int> > *vacant_chain)
{
 int pos;
 pair<int,int> p;

 if (x<1 || x>m_boardsize || y<1 || y>m_boardsize) return;
 if (territory_mark[x-1][y-1]) return;

 pos = get_board_position(x, y, p_current_board_position);
 switch(pos)
 {
	case 0: //vacancy
		switch (attribute)
		{
		case 'b':
			territory_mark[x-1][y-1] = 1;
			break;
		case 'w':
			territory_mark[x-1][y-1] = 2;
			break;
		}
		p.first = x;
		p.second = y;
		vacant_chain->push_back(p);
		break;
	case 1:
		return;
	case 2:
		return;
 }
 set_vacant_territory(x-1, y, attribute, vacant_chain);
 set_vacant_territory(x+1, y, attribute, vacant_chain);
 set_vacant_territory(x, y-1, attribute, vacant_chain);
 set_vacant_territory(x, y+1, attribute, vacant_chain);
}
