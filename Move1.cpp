// Move1.cpp: implementation of the CMove class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Go.h"
#include "board.h"
#include "Move1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMove::CMove()
{
 	//p_board_position = new __int64[Board_Size];
	//for (int i=0; i<Board_Size; i++)
		//p_board_position[i] = 0;
}

CMove::CMove(const CMove & rhs) throw() {
		stone = rhs.stone;
		m_num_moves = rhs.m_num_moves;
		m_black_captured = rhs.m_black_captured;
		m_white_captured = rhs.m_white_captured;
		m_stones_on_board = rhs.m_stones_on_board;
		x = rhs.x;
		y = rhs.y;
		dead_color = rhs.dead_color;
		captured = rhs.captured;
 		//p_board_position = new __int64[Board_Size];
		//for (int i=0; i<Board_Size; i++)
			//p_board_position[i] = rhs.p_board_position[i];
		alt_moves.assign(rhs.alt_moves.begin(),rhs.alt_moves.end());
}

CMove& CMove::operator= (const CMove & rhs) throw() {
	if (this != &rhs) {
		stone = rhs.stone;
		m_num_moves = rhs.m_num_moves;
		m_black_captured = rhs.m_black_captured;
		m_white_captured = rhs.m_white_captured;
		m_stones_on_board = rhs.m_stones_on_board;
		x = rhs.x;
		y = rhs.y;
		dead_color = rhs.dead_color;
		captured = rhs.captured;
 		//p_board_position = new __int64[Board_Size];
		//for (int i=0; i<Board_Size; i++)
			//p_board_position[i] = rhs.p_board_position[i];
		alt_moves.assign(rhs.alt_moves.begin(),rhs.alt_moves.end());
	}
	return *this;
}

CMoveTree::CMoveTree()
{

}

CMoveTree::CMoveTree(const CMoveTree & rhs) throw() {
	moves_sequence = rhs.moves_sequence;
	current_moves_index = rhs.current_moves_index;
}

CMoveTree& CMoveTree::operator= (const CMoveTree & rhs) throw() {
	if (this != &rhs) {
		moves_sequence = rhs.moves_sequence;
		current_moves_index = rhs.current_moves_index;
	}
	return *this;
}

CMoveTree::~CMoveTree()
{
 moves_sequence.clear();
}