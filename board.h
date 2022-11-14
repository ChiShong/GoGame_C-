// board.h: interface for the Cboard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOARD_H__A6050BE3_82E7_4175_91EC_87E6CD8DEAE2__INCLUDED_)
#define AFX_BOARD_H__A6050BE3_82E7_4175_91EC_87E6CD8DEAE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;

template <class T>
class CountedPtr {
	private:
		T* ptr;
		long* count;

	public:
		explicit CountedPtr (T* p=0) : ptr(p), count(new long(1)) {}

		CountedPtr (const CountedPtr<T>& p) throw() : ptr(p.ptr), count(p.count) {
			++*count;
		}

		~CountedPtr () throw() {
			dispose();
		}

		CountedPtr<T>& operator= (const CountedPtr<T>& p) throw() {
			if (this != &p) {
				dispose();
				ptr = p.ptr;
				count = p.count;
				++*count;
			}
			return *this;
		}

		T& operator*() const throw() {
			return *ptr;
		}

		T* operator->() const throw() {
			return ptr;
		}

	private:
		void dispose() {
			if (--*count == 0) {
				delete count;
				delete ptr;
			}
		}
}; 

typedef enum Turn {BLACK, WHITE, VACANT};
typedef enum Rules {POSITIONAL_SUPER_KO, SITUATIONAL_SUPER_KO, NSSK, CHINESE, ING, JAPANESE};
typedef enum ChainStatus {LIVE, DEAD, UNCERTAINTY};
typedef enum GameStatus {PLAYING, SCORING, OVER};
typedef enum Rank {nine_d, eight_d, seven_d, six_d, five_d, four_d, three_d, two_d, one_d, one_k, two_k, three_k, 
				   four_k, five_k, six_k, seven_k, eight_k, nine_k, ten_k, eleven_k, twelve_k, thirteen_k, fourteen_k, 
				   fifteen_k, sixteen_k, seventeen_k, eighteen_k, nineteen_k, twenty_k};

const Board_Size = 19;

class Csituation
{
public:
	Turn player;
	int m_stones_on_board;
  __int64 *p_board_position;

public:
	Csituation() {
		player = BLACK;
		m_stones_on_board = 0;
		p_board_position = new __int64[Board_Size];
		for (int i=0; i<Board_Size; i++)
			p_board_position[i] = 0;
	}

	// Copy Constructor
	Csituation(const Csituation & rhs) throw() {
		player = rhs.player;
		m_stones_on_board = rhs.m_stones_on_board;
		p_board_position = new __int64[Board_Size];
		for (int i=0; i<Board_Size; i++)
			p_board_position[i] = rhs.p_board_position[i];
	}

	~Csituation() {
		if (p_board_position)
			delete [] p_board_position;
	}

	Csituation& operator= (const Csituation& rhs) throw() {
		if (this != &rhs) {
				player = rhs.player;
				m_stones_on_board = rhs.m_stones_on_board;
				//p_board_position = rhs.p_board_position;
				p_board_position = new __int64[Board_Size];
				for (int i=0; i<Board_Size; i++)
					p_board_position[i] = rhs.p_board_position[i];
			}
			return *this;
	}
};


const BOARD_GRID_SIZE_19 = 38;
const BOARD_GRID_SIZE_13 = 40;
const BOARD_GRID_SIZE_9 = 59;
const MAX_STONES = 360;

#include "Rules.h"
#include "Move1.h"	// Added by ClassView

class CChain
{
public:
	ChainStatus status;
	int liberties;
	vector<pair<int,int> > chain_members;
//	list<CountedPtr<vector<pair<int,int> > > > p_eyes;

public:
	CChain() {
		status = UNCERTAINTY;		
	}

	// Copy Constructor
	CChain(const CChain & rhs) throw() {
		status = rhs.status;
		liberties = rhs.liberties;
		chain_members = rhs.chain_members;
	//	p_eyes = rhs.p_eyes;
	}

	~CChain() {
		chain_members.clear();
	//	p_eyes.clear();
	}

	CChain& operator= (const CChain& rhs) throw() {
		if (this != &rhs) {
				status = rhs.status;
				liberties = rhs.liberties;
				chain_members = rhs.chain_members;
	//			p_eyes = rhs.p_eyes;
		}
		return *this;
	}
};

class CPlayer
{
public:
	CString m_player_name;
	Rank rank;

public:
	CPlayer() {		
	}

	// Copy Constructor
	CPlayer(const CPlayer & rhs) throw() {
		
	}

	~CPlayer() {
		
	}

	CPlayer& operator= (const CPlayer& rhs) throw() {
		if (this != &rhs) {
			
		}
		return *this;
	}
};

class Cboard  
{
public:
	char territory_mark[Board_Size][Board_Size]; // 1 represents black and 2 represents white
	void set_vacant_territory(int x, int y, char attribute, vector<pair<int,int> > *vacant_chain);
	bool set_chain_dead(int x, int y, vector<pair<int,int> > *adjacent_vacancy, int &chain_num);
	bool eye_detect(int x, int y, int ChainsMarks[Board_Size][Board_Size], int &id, vector<pair<int,int> > *s, char visited[Board_Size][Board_Size], int &first_nonvacant_id);
	void live_or_dead_eval(CChain *pChains[MAX_STONES]);
	// for the tracing of the number of chains
	int num_of_black_chains;
	int num_of_white_chains;

	void collect_chains();
	float komi;
	GameStatus game_status;
	int num_consecutive_pass;
	bool if_simulate_moves;
	CMoveTree m_moves;
	static void set_board_position(Turn t, int x, int y, Csituation *p);
	void collect_strings(Turn stone_color, int x, int y, Csituation *p, int &liberties, vector<pair<int,int> > &s, char visited[Board_Size][Board_Size]);
	static void clear_board_position(int x, int y, Csituation *p );
	static int get_board_position(int x, int y, Csituation *p); // return 0 representing vacancy, 1 black, 2 white
	Cboard(int bsize);
	Cboard();
	virtual ~Cboard();

	int m_gridsize;
	int m_boardsize;

	Rules m_rule;
	CRules *mp_rule;
	CPlayer white_player;
	CPlayer black_player;
	UINT m_basic_time;
	UINT m_CountDownTime;
	UINT m_NumCountDown;
	UINT m_num_moves;
	int m_black_captured; // The number of captured black stones
	int m_white_captured; // The number of captured white stones

	/* 
	 * board position represented by 19*64 bits
	 * each point occupies 2 bits
	 * 00 denotes vacancy, 01 denotes black, 10 denotes white, 11 unused
	 */
    Csituation *p_current_board_position;

	/*
	 * Store the information of chains in current board position.
	 * The index (chain id) ranging from 0 to MAX_STONES/2-1 belongs to black chain,
	 * while the index from MAX_STONES/2 to MAX_STONES-1 represents white chain.
	 */
	CChain *p_Chains[MAX_STONES];
	 
};



#endif // !defined(AFX_BOARD_H__A6050BE3_82E7_4175_91EC_87E6CD8DEAE2__INCLUDED_)
