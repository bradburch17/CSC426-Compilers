/*
* Scanner.cpp
*
*  Created on: Aug 30, 2015
*      Author: bhoward
*/

#include "Scanner.h"

#include <iostream>
#include <cctype>
#include <map>

using namespace std;

Scanner::Scanner(istream& in) :
	in(in) {
	line_num = 1;
	column_num = 1;
	getline(in, line);
}

enum States {
	INIT_ST, NUM_ST, ZERO_ST, OP_ST, SLASH1_ST, SLASH2_ST, RBRACE_ST, LBRACE_ST, ID_ST
};

enum Actions {
	SKIP_ACT, MARK_ACT, NEXT_ACT, NUMBER_ACT, OP_ACT, ID_ACT, EOF_ACT, ERR_ACT, 
};

enum CharacterClass {
	LETTER_CC, ZERO_CC, DIGIT_CC, SPACE_CC, NEWLINE_CC, OP_CC, SLASH_CC, LBRACE_CC, RBRACE_CC, EOF_CC, OTHER_CC
};

static const int CHARACTERS_CLASS = OTHER_CC + 1;

static CharacterClass char_tbl[] = {
	OTHER_CC, OTHER_CC, OTHER_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // NUL,SOH,STX,ETX,EOT,ENQ,ACK,BEL
	OTHER_CC, SPACE_CC, NEWLINE_CC, OTHER_CC,  OTHER_CC, SPACE_CC,  OTHER_CC, OTHER_CC, // BS, TAB,LF, VT, FF, CR, SO, SI
	OTHER_CC, OTHER_CC, OTHER_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // DLE,DC1,DC2,DC3,DC4,NAK,SYN,ETB
	OTHER_CC, OTHER_CC, OTHER_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // CAN,EM, SUB,ESC,FS, GS, RS, US
	SPACE_CC, OTHER_CC, OTHER_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // SPC,!,  ",  #,  $,  %,  &,  '
	OTHER_CC, OTHER_CC, OP_CC,      OP_CC,     OTHER_CC, OP_CC,     OP_CC,    SLASH_CC, // (,  ),  *,  +,  ,,  -,  .,  /
	ZERO_CC,  DIGIT_CC, DIGIT_CC,   DIGIT_CC,  DIGIT_CC, DIGIT_CC,  DIGIT_CC, DIGIT_CC, // 0,  1,  2,  3,  4,  5,  6,  7
	DIGIT_CC, DIGIT_CC, OTHER_CC,   OP_CC,     OTHER_CC, OP_CC,     OTHER_CC, OTHER_CC, // 8,  9,  :,  ;,  <,  =,  >,  ?
	OTHER_CC, LETTER_CC, LETTER_CC,   LETTER_CC,  LETTER_CC, LETTER_CC,  LETTER_CC, LETTER_CC, // @,  A,  B,  C,  D,  E,  F,  G
	LETTER_CC, LETTER_CC, LETTER_CC,   LETTER_CC,  LETTER_CC, LETTER_CC,  LETTER_CC, LETTER_CC, // H,  I,  J,  K,  L,  M,  N,  O
	LETTER_CC, LETTER_CC, LETTER_CC,   LETTER_CC,  LETTER_CC, LETTER_CC,  LETTER_CC, LETTER_CC, // P,  Q,  R,  S,  T,  U,  V,  W
	LETTER_CC, LETTER_CC, LETTER_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // X,  Y,  Z,  [,  \,  ],  ^,  _
	OTHER_CC, LETTER_CC, LETTER_CC,   LETTER_CC,  LETTER_CC, LETTER_CC,  LETTER_CC, LETTER_CC, // `,  a,  b,  c,  d,  e,  f,  g
	LETTER_CC, LETTER_CC, LETTER_CC,   LETTER_CC,  LETTER_CC, LETTER_CC,  LETTER_CC, LETTER_CC, // h,  i,  j,  k,  l,  m,  n,  o
	LETTER_CC, LETTER_CC, LETTER_CC,   LETTER_CC,  LETTER_CC, LETTER_CC,  LETTER_CC, LETTER_CC, // p,  q,  r,  s,  t,  u,  v,  w
	LETTER_CC, LETTER_CC, LETTER_CC,   LBRACE_CC, OTHER_CC, RBRACE_CC, OTHER_CC, OTHER_CC  // x,  y,  z,  {,  |,  },  ~,  DEL
};

static CharacterClass char_class(char c) {
	if (c == char_traits<char>::eof()) {
		return EOF_CC;
	}
	else {
		return char_tbl[c & 127];
	}
}

static States next_state[][CHARACTERS_CLASS] = {
	//  ALPHA,     ZERO,      DIGIT,     SPACE,     NEWLINE,  OP,        SLASH,     LBRACE,    RBRACE,    EOF,     OTHER
	{ // INIT_ST
		ID_ST,   ZERO_ST,   NUM_ST,    INIT_ST,   INIT_ST,  OP_ST,     SLASH1_ST,  LBRACE_ST,   RBRACE_ST,   INIT_ST, INIT_ST
	},
	{ // NUM_ST
		INIT_ST,   NUM_ST,    NUM_ST,    INIT_ST,   INIT_ST,  INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST, INIT_ST
	},
	{ // ZERO_ST
		INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,  INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST, INIT_ST
	},
	{ // OP_ST
		INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,  INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST, INIT_ST
	},
	{ // SLASH_ST
		INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,  INIT_ST,   SLASH2_ST, INIT_ST,   INIT_ST,   INIT_ST, INIT_ST
	},
	{ // SLASH2_ST
		SLASH2_ST, SLASH2_ST, SLASH2_ST, SLASH2_ST, INIT_ST,  SLASH2_ST, SLASH2_ST, SLASH2_ST, SLASH2_ST, INIT_ST, SLASH2_ST
	}, //********NO IDEA IF THESE ARE CORRECT*********
	{ // BRACE_ST
		RBRACE_ST,  RBRACE_ST,  RBRACE_ST,  RBRACE_ST,  RBRACE_ST, RBRACE_ST,  RBRACE_ST,  LBRACE_ST,  RBRACE_ST,  INIT_ST, RBRACE_ST
	},
	{ // LBRACE_ST
		INIT_ST,    INIT_ST,     INIT_ST,    INIT_ST,    INIT_ST,   INIT_ST,     INIT_ST,    RBRACE_ST,   INIT_ST,    INIT_ST, INIT_ST
	},
	{ // ID_ST  
		ID_ST,     ID_ST,     ID_ST,     INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,  INIT_ST
	}
};

static Actions action[][CHARACTERS_CLASS] = {
	//  ALPHA,     ZERO,      DIGIT,     SPACE,     NEWLINE,  OP,        SLASH,     LBRACE,    RBRACE,    EOF,     OTHER
	{ // INIT_ST
		MARK_ACT,  MARK_ACT,  MARK_ACT,  SKIP_ACT,  SKIP_ACT, MARK_ACT,  SKIP_ACT,  SKIP_ACT,  ERR_ACT,   EOF_ACT, ERR_ACT
	},
	{ // NUM_ST
		NUMBER_ACT,   NEXT_ACT,  NEXT_ACT,  NUMBER_ACT,   NUMBER_ACT,  NUMBER_ACT,   NUMBER_ACT,   NUMBER_ACT,   NUMBER_ACT,   NUMBER_ACT, NUMBER_ACT
	},
	{ // ZERO_ST
		NUMBER_ACT,   NUMBER_ACT,   NUMBER_ACT,   NUMBER_ACT,   NUMBER_ACT,  NUMBER_ACT,   NUMBER_ACT,   NUMBER_ACT,   NUMBER_ACT,   NUMBER_ACT, NUMBER_ACT
	},
	{ // OP_ST
		OP_ACT,    OP_ACT,    OP_ACT,    OP_ACT,    OP_ACT,   OP_ACT,    OP_ACT,    OP_ACT,    OP_ACT,    OP_ACT,  OP_ACT
	},
	{ // SLASH_ST
		ERR_ACT,   ERR_ACT,   ERR_ACT,   ERR_ACT,   ERR_ACT,  ERR_ACT,   SKIP_ACT,  ERR_ACT,   ERR_ACT,   ERR_ACT, ERR_ACT
	},
	{ // SLASH2_ST
		SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT, SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  EOF_ACT, SKIP_ACT
	},
	{ // BRACES_ST
		SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT, SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT, SKIP_ACT
	},
	{
		SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT, SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT, SKIP_ACT
	},
	{ // ID_ST
		NEXT_ACT,  NEXT_ACT,  NEXT_ACT,   ID_ACT,  ID_ACT,    ID_ACT,    ID_ACT,    ID_ACT,    ID_ACT,     ID_ACT,  ID_ACT
	}
};

typedef map<string, Token_Type> yymap;

static yymap create_keyword_map() {
	yymap m;
	m["program "] = PROGRAM;
	m["begin "] = BEGIN;
	m["end"] = END;
	m["const "] = CONST;
	m["mod "] = MOD;
	m["div "] = DIV;
	m["print "] = PRINT;
	return m;
}

static yymap keyword_map = create_keyword_map();

typedef map<string, Token_Type> map_t;

static map_t create_token_map()
{
	map_t m;
	m[";"] = SEMI;
	m["."] = PERIOD;
	m["+"] = PLUS;
	m["-"] = MINUS;
	m["*"] = STAR;
	m["="] = EQUALS; //are we counting this as an OP?
	return m;
}

static map_t token_map = create_token_map();

Token Scanner::next() {
	Token token;
	States state = INIT_ST;
	bool done = false;

	while (!done) {
		char current = current_char();
		CharacterClass c = char_class(current);
		Actions act = action[state][c];
		state = next_state[state][c];

		switch (act) {
		case SKIP_ACT:
			advance();
			break;
		case MARK_ACT:
			token.line = line_num;
			token.column = column_num;
			token.lexeme = current;
			advance();
			break;
		case NEXT_ACT:
			token.lexeme += current;
			advance();
			break;
		case NUMBER_ACT:
			token.type = NUM;
			done = true;
			break;
		case OP_ACT:
			token.type = token_map[token.lexeme];
			done = true;
			break;			
		case ID_ACT:
			cout << "hey";
			token.type = ID;
			done = true;
			break;
		case EOF_ACT:
			token.line = line_num;
			token.column = column_num;
			token.type = EOFILE;
			done = true;
			break;		
		case ERR_ACT:
			if (c == EOF_CC) {
				cerr << "ERROR! Unexpected end of file ";
			}
			else
				cerr << "ERROR! Unexpected character " << current;
			cerr << "at line " << line_num << ", column " << column_num;
			cerr << endl;
			advance();
			break;

		}


	}


	// TODO implement the state machine here:
	// - have a "state" variable start in the initial state
	// - repeatedly look at current_char() (the current character),
	//   perform an appropriate action based on them, and assign
	//   a new state until the end of a token is seen
	// - call advance() on each state transition, until you
	//   see the first character after the token
	// - if at_EOF() is true, then return an EOF token:
	//     token.line = line_num;
	//     token.column = column_num;
	//     token.type = EOFILE;
	//     token.lexeme = "";

	return token;
}

char Scanner::current_char() {
	if (column_num <= line.size()) {
		// still within the current line
		return line[column_num - 1];
	}
	else if (in) {
		// at end of current line, but input still valid
		return '\n';
	}
	else {
		// past end of input
		return char_traits<char>::eof();
	}
}

bool Scanner::at_EOF() {
	return current_char() == char_traits<char>::eof();
}

void Scanner::advance() {
	if (column_num <= line.size()) {
		// still within current line
		++column_num;
	}
	else if (in) {
		// attempt to read another line
		line.clear();
		getline(in, line);
		++line_num;
		column_num = 1;
	}
	else {
		// do nothing -- at EOF
	}
}
