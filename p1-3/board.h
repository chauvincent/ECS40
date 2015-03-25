
#include <cctype>
#include <cerrno>
#include <climits>
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

typedef unsigned char byte;

struct move {
        
        short move;
        
        unsigned short prescore;
};


// 	WILL COMPILE AND BUILD BUT CMD_NEW GIVES SEG FAULT AFTER MOVING A CERTAIN AMOUNT OF STEPS
//	THE COMPUTER ALSO DOES NOT MAKE MOVES, PLAYER WHITE CAN KEEP MAKING MOVES  
//
//THESE EXTERNED ARE DECLARED IN mscp.cpp

extern unsigned long zobrist[12][64]; 

extern signed char undo_stack[6*1024], *undo_sp; /* Move undo administration */

extern unsigned long hash_stack[1024]; /* History of hashes, for repetition */

extern move move_stack[1024], *move_sp; /* History of moves */

//below moved to mscp.cpp
//unsigned long hash_stack[1024]; /* History of hashes, for repetition */
//unsigned long zobrist[12][64]; 
//move move_stack[1024], *move_sp;
//signed char undo_stack[6*1024], *undo_sp;


// declarations are in mscp
extern byte castle[64]; /* Which pieces may participate in castling */
extern int computer[2]; /* Which side is played by the computer */
extern int xboard_mode; /* XBoard protocol, surpresses prompt */	
extern unsigned long nodes; /* Node counter */


/* attacks */
const int ATKB_NORTH = 0;

const int ATKB_NORTHEAST = 1;

const int ATKB_EAST = 2;

const int ATKB_SOUTHEAST = 3;

const int ATKB_SOUTH = 4;

const int ATKB_SOUTHWEST = 5;

const int ATKB_WEST = 6;

const int ATKB_NORTHWEST = 7;

const int ATK_NORTH          =     (1 << ATKB_NORTH);

const int ATK_NORTHEAST      =     (1 << ATKB_NORTHEAST);

const int ATK_EAST           =     (1 << ATKB_EAST);

const int ATK_SOUTHEAST      =     (1 << ATKB_SOUTHEAST);

const int ATK_SOUTH          =     (1 << ATKB_SOUTH);

const int ATK_SOUTHWEST      =     (1 << ATKB_SOUTHWEST);

const int ATK_WEST           =     (1 << ATKB_WEST);

const int ATK_NORTHWEST      =     (1 << ATKB_NORTHWEST);

const int ATK_ORTHOGONAL     =     ( ATK_NORTH | ATK_SOUTH | \
                                  ATK_WEST  | ATK_EAST  );
const int ATK_DIAGONAL       =     ( ATK_NORTHEAST | ATK_NORTHWEST | \
                                  ATK_SOUTHEAST | ATK_SOUTHWEST );
const int ATK_SLIDER         =     ( ATK_ORTHOGONAL | ATK_DIAGONAL );

enum {
        EMPTY,
        WHITE_KING, WHITE_QUEEN, WHITE_ROOK,
        WHITE_BISHOP, WHITE_KNIGHT, WHITE_PAWN,
        BLACK_KING, BLACK_QUEEN, BLACK_ROOK,
        BLACK_BISHOP, BLACK_KNIGHT, BLACK_PAWN
};
inline int PIECE_COLOR(int pc) { return ( (pc) < BLACK_KING ); } /* White or black */

const int DIR_N = +1;              /* Offset to step one square up (north) */

const int DIR_E = +8;              /* Offset to step one square right (east) */

enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H };

enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8 };

inline int RANK2CHAR(int r)       { return    ('1'+(r));           }  /* rank to text */

inline int CHAR2RANK(int c)       { return    ((c)-'1');           }    /* text to rank */

inline char FILE2CHAR(int f)       { return    ('a'+(f));           }   /* file to text */

inline int CHAR2FILE(int c)       { return   ((c)-'a');            }   /* text to file */

inline int PIECE2CHAR(int p)      { return   ("-KQRBNPkqrbnp"[p]); }  /* piece to text */

inline int F(int square)           { return   ( (square) >> 3 );    }    /* file */

inline int R(int square)           { return ( (square) & 7 );       }    /* rank */

inline int SQ(int f, int r)        { return ( ((f) << 3) | (r) );  }    /* compose square */

inline int FLIP(int square)        { return  ((square)^7);          } /* flip board */

inline int MOVE(int fr, int to)             { return ( ((fr) << 6) | (to) );  }   /* compose move */

inline int FR(int move)               { return ( ((move) & 07700) >> 6 ); } /* from square */

inline int TO(int move)               { return ( (move) & 00077 );}        /* target square */

const int SPECIAL = (1<<12);                /* for special moves */
	
const int CASTLE_WHITE_KING  = 1;

const int CASTLE_WHITE_QUEEN = 2;

const int CASTLE_BLACK_KING  = 4;

const int CASTLE_BLACK_QUEEN = 8;	

// DECLARED AS EXTERN TESTING, USE TO BE STATIC
extern int ply;         /* Number of half-moves made in game and search */

inline int WTM() { return (~ply & 1); }  /* White-to-move predicate */	
	
const int INF = 32000;

inline int MAX(const int a, const int b) { return ( ((a)>(b) ? (a) : (b)) ); }

inline int MIN(const int a, const int b) { return ( ((a)<(b) ? (a) : (b)) ); }

inline bool xisspace(const char c) { return ( isspace((int)(c)) ); } /* Prevent warnings on crappy Solaris */

inline bool xisalpha(const char c) { return ( isalpha((int)(c)) ); }

enum {                  /* 64 squares */
        A1, A2, A3, A4, A5, A6, A7, A8,
        B1, B2, B3, B4, B5, B6, B7, B8,
        C1, C2, C3, C4, C5, C6, C7, C8,
        D1, D2, D3, D4, D5, D6, D7, D8,
        E1, E2, E3, E4, E5, E6, E7, E8,
        F1, F2, F3, F4, F5, F6, F7, F8,
        G1, G2, G3, G4, G5, G6, G7, G8,
        H1, H2, H3, H4, H5, H6, H7, H8,
        CASTLE,         /* Castling rights */
        EP,             /* En-passant square */
        LAST            /* Ply number of last capture or pawn push */
};





class Board{
	
	public:
		
		byte *board;
		
		Board(){board= new byte[boardSize];};
		
		byte &operator[](int subscript){
			return board[subscript];};

		void setup_board(const char *fen);
		
		void print_board(void);
		
		unsigned long compute_hash(void);
		
		void reset(void);



		
		~Board(){delete []board;};
	
	private:
		static const int boardSize = 67;
};

