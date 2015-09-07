/*
* Scanner.cpp
*
*  Created on: Aug 30, 2015
*	   Author: bhoward and Brad Burch
*	   Modified September 6, 2015 by Brad Burch
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

enum State {
	INIT_ST, NUM_ST, ZERO_ST, OP_ST, SLASH_ST, SLASH2_ST, BRACE_ST, ID_ST
};

enum Action {
	SKIP_ACT, MARK_ACT, NEXT_ACT, NUM_ACT, OP_ACT, EOF_ACT, ERR_ACT, ID_ACT
};

enum Char_Class {
	ALPHA_CC,
	ZERO_CC,
	DIGIT_CC,
	SPACE_CC,
	NEWLINE_CC,
	OP_CC,
	SLASH_CC,
	LBRACE_CC,
	RBRACE_CC,
	EOF_CC,
	OTHER_CC
};

static const int NUM_CHAR_CLASS = OTHER_CC + 1;

static Char_Class char_table[] = {
	OTHER_CC, OTHER_CC, OTHER_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // NUL,SOH,STX,ETX,EOT,ENQ,ACK,BEL
	OTHER_CC, SPACE_CC, NEWLINE_CC, OTHER_CC,  OTHER_CC, SPACE_CC,  OTHER_CC, OTHER_CC, // BS, TAB,LF, VT, FF, CR, SO, SI
	OTHER_CC, OTHER_CC, OTHER_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // DLE,DC1,DC2,DC3,DC4,NAK,SYN,ETB
	OTHER_CC, OTHER_CC, OTHER_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // CAN,EM, SUB,ESC,FS, GS, RS, US
	SPACE_CC, OTHER_CC, OTHER_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // SPC,!,  ",  #,  $,  %,  &,  '
	OTHER_CC, OTHER_CC, OP_CC,      OP_CC,     OTHER_CC, OP_CC,     OP_CC,    SLASH_CC, // (,  ),  *,  +,  ,,  -,  .,  /
	ZERO_CC,  DIGIT_CC, DIGIT_CC,   DIGIT_CC,  DIGIT_CC, DIGIT_CC,  DIGIT_CC, DIGIT_CC, // 0,  1,  2,  3,  4,  5,  6,  7
	DIGIT_CC, DIGIT_CC, OTHER_CC,   OP_CC,     OTHER_CC, OP_CC,     OTHER_CC, OTHER_CC, // 8,  9,  :,  ;,  <,  =,  >,  ?
	OTHER_CC, ALPHA_CC, ALPHA_CC,   ALPHA_CC,  ALPHA_CC, ALPHA_CC,  ALPHA_CC, ALPHA_CC, // @,  A,  B,  C,  D,  E,  F,  G
	ALPHA_CC, ALPHA_CC, ALPHA_CC,   ALPHA_CC,  ALPHA_CC, ALPHA_CC,  ALPHA_CC, ALPHA_CC, // H,  I,  J,  K,  L,  M,  N,  O
	ALPHA_CC, ALPHA_CC, ALPHA_CC,   ALPHA_CC,  ALPHA_CC, ALPHA_CC,  ALPHA_CC, ALPHA_CC, // P,  Q,  R,  S,  T,  U,  V,  W
	ALPHA_CC, ALPHA_CC, ALPHA_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // X,  Y,  Z,  [,  \,  ],  ^,  _
	OTHER_CC, ALPHA_CC, ALPHA_CC,   ALPHA_CC,  ALPHA_CC, ALPHA_CC,  ALPHA_CC, ALPHA_CC, // `,  a,  b,  c,  d,  e,  f,  g
	ALPHA_CC, ALPHA_CC, ALPHA_CC,   ALPHA_CC,  ALPHA_CC, ALPHA_CC,  ALPHA_CC, ALPHA_CC, // h,  i,  j,  k,  l,  m,  n,  o
	ALPHA_CC, ALPHA_CC, ALPHA_CC,   ALPHA_CC,  ALPHA_CC, ALPHA_CC,  ALPHA_CC, ALPHA_CC, // p,  q,  r,  s,  t,  u,  v,  w
	ALPHA_CC, ALPHA_CC, ALPHA_CC,   LBRACE_CC, OTHER_CC, RBRACE_CC, OTHER_CC, OTHER_CC  // x,  y,  z,  {,  |,  },  ~,  DEL
};

static Char_Class char_class(char c) {
	if (c == char_traits<char>::eof()) {
		return EOF_CC;
	}
	else {
		return char_table[c & 127];
	}
}

static State next_state[][NUM_CHAR_CLASS] = {
	//  ALPHA,     ZERO,      DIGIT,     SPACE,     NEWLINE,  OP,        SLASH,     LBRACE,    RBRACE,    EOF,     OTHER
	{ // INIT_ST
		INIT_ST,   ZERO_ST,   NUM_ST,    INIT_ST,   INIT_ST,  OP_ST,     SLASH_ST,  INIT_ST,   INIT_ST,   INIT_ST, INIT_ST
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
	{ //BRACE_ST
		BRACE_ST,  BRACE_ST,  BRACE_ST,  BRACE_ST,  BRACE_ST,  BRACE_ST,  BRACE_ST,  BRACE_ST,  BRACE_ST,  BRACE_ST, BRACE_ST
	}, 
	{ //ID_ST
		ID_ST,     INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,  INIT_ST
	}
};

static Action action[][NUM_CHAR_CLASS] = {
	//  ALPHA,     ZERO,      DIGIT,     SPACE,     NEWLINE,  OP,        SLASH,     LBRACE,    RBRACE,    EOF,     OTHER
	{ // INIT_ST
		MARK_ACT,  MARK_ACT,  MARK_ACT,  SKIP_ACT,  SKIP_ACT, MARK_ACT,  SKIP_ACT,  SKIP_ACT,  ERR_ACT,   EOF_ACT, ERR_ACT
	},
	{ // NUM_ST
		NUM_ACT,   NEXT_ACT,  NEXT_ACT,  NUM_ACT,   NUM_ACT,  NUM_ACT,   NUM_ACT,   NUM_ACT,   NUM_ACT,   NUM_ACT, NUM_ACT
	},
	{ // ZERO_ST
		NUM_ACT,   NUM_ACT,   NUM_ACT,   NUM_ACT,   NUM_ACT,  NUM_ACT,   NUM_ACT,   NUM_ACT,   NUM_ACT,   NUM_ACT, NUM_ACT
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
		SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  SKIP_ACT, SKIP_ACT,  SKIP_ACT,  SKIP_ACT,  NEXT_ACT,  SKIP_ACT, SKIP_ACT
	}
};

typedef map<string, Token_Type> map_t;

static map_t create_token_map()
{
	map_t m;
	m[";"] = SEMI;
	m["."] = PERIOD;
	m["+"] = PLUS;
	m["-"] = MINUS;
	m["*"] = STAR;
	m["="] = EQUALS;
	m["program"] = PROGRAM;
	m["const"] = CONST;
	m["begin"] = BEGIN;
	m["end"] = END;
	m["print"] = PRINT;
	m["div"] = DIV;
	m["mod"] = MOD;
	return m;
}

static map_t token_map = create_token_map();

Token Scanner::next() {
	Token token;
	State state = INIT_ST;
	bool done = false;

	while (!done) {
		char current = current_char();
		Char_Class cc = char_class(current);
		Action act = action[state][cc];
		state = next_state[state][cc];

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

		case NUM_ACT:
			token.type = NUM;
			done = true;
			break;

		case OP_ACT:
			token.type = token_map[token.lexeme];
			done = true;
			break;

		case EOF_ACT:
			token.line = line_num;
			token.column = column_num;
			token.type = EOFILE;
			done = true;
			break;

		case ERR_ACT:
			if (cc == EOF_CC) {
				cerr << "Error: Unexpected end of file ";
			}
			else {
				cerr << "Error: Unexpected character (" << current << ") ";
			}
			cerr << "at line " << line_num << ", column " << column_num;
			cerr << endl;
			advance();
			break;
		}
	}

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
