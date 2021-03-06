/*
* Scanner.cpp
*
*  Created on: Aug 30, 2015
*      Author: Brad Burch
*/

#include "Scanner.h"

#include <iostream>
#include <cctype>
#include <map>

using namespace std;

Scanner::Scanner(istream &in) :	in(in) {
	line_num = 1;
	column_num = 1;
	getline(in, line);
}

enum States {
	INIT_ST, NUM_ST, ZERO_ST, OP_ST, SLASH1_ST, SLASH2_ST, LBRACE_ST, RBRACE_ST, ID_ST, Q1_ST, Q2_ST, LESS_ST, GREATER_ST, EQUAL_ST
};

enum Actions {
	SKIP_ACT, MARK_ACT, NEXT_ACT, NUMBER_ACT, OP_ACT, ID_ACT, EOF_ACT, ERR_ACT, Q1_ACT, Q2_ACT, LESS_ACT, GREATER_ACT, EQUAL_ACT
};

enum CharacterClass {
	LETTER_CC, ZERO_CC, DIGIT_CC, SPACE_CC, NEWLINE_CC, OP_CC, SLASH_CC, LBRACE_CC, RBRACE_CC, EOF_CC, OTHER_CC, QUOTE_CC, LESS_CC, GREATER_CC, EQUAL_CC
};

static const int CHARACTERS_CLASS = OTHER_CC + 5;

static CharacterClass char_tbl[] = {
	OTHER_CC, OTHER_CC, OTHER_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // NUL,SOH,STX,ETX,EOT,ENQ,ACK,BEL
	OTHER_CC, SPACE_CC, NEWLINE_CC, OTHER_CC,  OTHER_CC, SPACE_CC,  OTHER_CC, OTHER_CC, // BS, TAB,LF, VT, FF, CR, SO, SI
	OTHER_CC, OTHER_CC, OTHER_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // DLE,DC1,DC2,DC3,DC4,NAK,SYN,ETB
	OTHER_CC, OTHER_CC, OTHER_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // CAN,EM, SUB,ESC,FS, GS, RS, US
	SPACE_CC, OTHER_CC, QUOTE_CC,   OTHER_CC,  OTHER_CC, OTHER_CC,  OTHER_CC, OTHER_CC, // SPC,!,  ",  #,  $,  %,  &,  '
	OP_CC, OP_CC, OP_CC,      OP_CC,     OP_CC, OP_CC,     OP_CC,    SLASH_CC, // (,  ),  *,  +,  ,,  -,  .,  /
	ZERO_CC,  DIGIT_CC, DIGIT_CC,   DIGIT_CC,  DIGIT_CC, DIGIT_CC,  DIGIT_CC, DIGIT_CC, // 0,  1,  2,  3,  4,  5,  6,  7
	DIGIT_CC, DIGIT_CC, OP_CC,       OP_CC,  LESS_CC, EQUAL_CC,   GREATER_CC, OTHER_CC, // 8,  9,  :,  ;,  <,  =,  >,  ?
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
	//  LETTER,     ZERO,      DIGIT,     SPACE,     NEWLINE,    OP,        SLASH,     LBRACE,    RBRACE,    EOF,     OTHER,     QUOTE,   <,       >,          =
	{ // INIT_ST
		ID_ST,	   ZERO_ST,   NUM_ST,    INIT_ST,   INIT_ST,    OP_ST,     SLASH1_ST,  LBRACE_ST, RBRACE_ST, INIT_ST, INIT_ST,   Q1_ST, LESS_ST, GREATER_ST, EQUAL_ST
	},
	{ // NUM_ST
		INIT_ST,   NUM_ST,    NUM_ST,    INIT_ST,   INIT_ST,    INIT_ST,   INIT_ST,    INIT_ST,   INIT_ST,   INIT_ST, INIT_ST,   INIT_ST, INIT_ST, INIT_ST, INIT_ST
	},
	{ // ZERO_ST
		INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,    INIT_ST,   INIT_ST,    INIT_ST,   INIT_ST,   INIT_ST, INIT_ST,   INIT_ST, INIT_ST, INIT_ST, INIT_ST
	},
	{ // OP_ST
		INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,    INIT_ST,   INIT_ST,   INIT_ST,    INIT_ST,   INIT_ST, INIT_ST,   INIT_ST, INIT_ST, INIT_ST, INIT_ST
	},
	{ // SLASH_ST
		INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,    INIT_ST,   SLASH2_ST, INIT_ST,    INIT_ST,   INIT_ST, INIT_ST,   INIT_ST, INIT_ST, INIT_ST, INIT_ST
	},
	{ // SLASH2_ST
		SLASH2_ST, SLASH2_ST, SLASH2_ST, SLASH2_ST, INIT_ST,    SLASH2_ST, SLASH2_ST, SLASH2_ST,  SLASH2_ST, INIT_ST, SLASH2_ST, INIT_ST, INIT_ST, INIT_ST, INIT_ST
	}, 
	{ // LRACE_ST
		LBRACE_ST,  LBRACE_ST, LBRACE_ST, LBRACE_ST, LBRACE_ST, LBRACE_ST, LBRACE_ST, LBRACE_ST,  INIT_ST,   INIT_ST, LBRACE_ST, LBRACE_ST, INIT_ST, INIT_ST, INIT_ST
	},
	{ // RBRACE_ST
		INIT_ST,    INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,    INIT_ST,   INIT_ST, INIT_ST,   INIT_ST,   INIT_ST, INIT_ST, INIT_ST
	},
	{ // ID_ST  
		ID_ST,      ID_ST,     ID_ST,     INIT_ST,  INIT_ST,    INIT_ST,   INIT_ST,   INIT_ST,    INIT_ST,   INIT_ST,  INIT_ST,  INIT_ST,   INIT_ST, INIT_ST, INIT_ST
	},  
	{ // Q1_ST
		Q1_ST,      Q1_ST,     Q1_ST,     Q1_ST,    INIT_ST,    Q1_ST,     INIT_ST,     Q1_ST,      Q1_ST,     INIT_ST,  Q1_ST,   Q2_ST,    Q1_ST,   Q1_ST,    Q1_ST
	}, 
	{ // Q2_ST
		INIT_ST,    INIT_ST,   INIT_ST,   INIT_ST,  INIT_ST,    INIT_ST,   INIT_ST,   INIT_ST,    INIT_ST,   INIT_ST,  INIT_ST,   Q1_ST,    INIT_ST, INIT_ST, INIT_ST
	}, 
	{ //LESS_ST
		INIT_ST,	INIT_ST,   INIT_ST,    INIT_ST, INIT_ST,    INIT_ST,	INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,    INIT_ST,  INIT_ST, LESS_ST, LESS_ST, LESS_ST
	}, 
	{ //GREATER_ST
		INIT_ST,	INIT_ST,   INIT_ST,    INIT_ST, INIT_ST,    INIT_ST,	INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,    INIT_ST,  INIT_ST, INIT_ST, GREATER_ST, GREATER_ST
	}, 
	{ //EQUALS_ST
		INIT_ST,	INIT_ST,   INIT_ST,    INIT_ST, INIT_ST,    INIT_ST,	INIT_ST,   INIT_ST,   INIT_ST,   INIT_ST,    INIT_ST,  INIT_ST, INIT_ST, INIT_ST,  EQUAL_ST
	}
};

static Actions action[][CHARACTERS_CLASS] = {
	//  LETTER,     ZERO,       DIGIT,      SPACE,      NEWLINE,      OP,        SLASH,      LBRACE,    RBRACE,     EOF,         OTHER,       QUOTE,       <,          >,        =
	{ // INIT_ST
		MARK_ACT,   MARK_ACT,   MARK_ACT,   SKIP_ACT,   SKIP_ACT,   MARK_ACT,   SKIP_ACT,   SKIP_ACT,   ERR_ACT,    EOF_ACT,    ERR_ACT,    MARK_ACT,   MARK_ACT,  MARK_ACT,   MARK_ACT
	},
	{ // NUM_ST
		NUMBER_ACT, NEXT_ACT,   NEXT_ACT,   NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT
	},
	{ // ZERO_ST
		NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT, NUMBER_ACT
	},
	{ // OP_ST
		OP_ACT,     OP_ACT,     OP_ACT,     OP_ACT,     OP_ACT,     OP_ACT,      OP_ACT,    OP_ACT,     OP_ACT,    OP_ACT,      OP_ACT,     OP_ACT,       OP_ACT,    OP_ACT,     OP_ACT
	},
	{ // SLASH_ST
		ERR_ACT,    ERR_ACT,    ERR_ACT,    ERR_ACT,    ERR_ACT,    ERR_ACT,     SKIP_ACT,  ERR_ACT,    ERR_ACT,   ERR_ACT,     ERR_ACT,    ERR_ACT, ERR_ACT,     ERR_ACT,     ERR_ACT
	},
	{ // SLASH2_ST
		SKIP_ACT,   SKIP_ACT,   SKIP_ACT,   SKIP_ACT,   SKIP_ACT,   SKIP_ACT,    SKIP_ACT,  SKIP_ACT,   SKIP_ACT,  EOF_ACT,     SKIP_ACT,   SKIP_ACT,  SKIP_ACT,   SKIP_ACT,   SKIP_ACT
	},
	{ // LBRACES_ST
		SKIP_ACT,   SKIP_ACT,   SKIP_ACT,   SKIP_ACT,   SKIP_ACT,   SKIP_ACT,    SKIP_ACT,  SKIP_ACT,   SKIP_ACT,  ERR_ACT,     SKIP_ACT,   SKIP_ACT,  SKIP_ACT,   SKIP_ACT,  SKIP_ACT
	},
	{ // RBRACES_ST
		SKIP_ACT,   SKIP_ACT,   SKIP_ACT,   SKIP_ACT,   SKIP_ACT,   SKIP_ACT,    SKIP_ACT,  SKIP_ACT,   SKIP_ACT,  EOF_ACT,     SKIP_ACT,   SKIP_ACT, SKIP_ACT,   SKIP_ACT,   SKIP_ACT
	},
	{ // ID_ST
		NEXT_ACT,   NEXT_ACT,   NEXT_ACT,   ID_ACT,     ID_ACT,     ID_ACT,      ID_ACT,    ID_ACT,     ID_ACT,    ID_ACT,      ID_ACT,     ID_ACT, ID_ACT,       ID_ACT,      ID_ACT
	}, 
	{ // Q1_ST
		Q1_ACT,     Q1_ACT,     Q1_ACT,		Q1_ACT,     ERR_ACT,    Q1_ACT,      Q1_ACT,	Q1_ACT,     Q1_ACT,    ERR_ACT,     Q1_ACT,     SKIP_ACT,  Q1_ACT,     Q1_ACT,     Q1_ACT
	}, 
	{ // Q2_ST
		Q2_ACT,     Q2_ACT,     Q2_ACT,		Q2_ACT,     Q2_ACT,     Q2_ACT,      Q2_ACT,	Q2_ACT,     Q2_ACT,    Q2_ACT,      Q2_ACT,     Q1_ACT,    Q2_ACT,     Q2_ACT,     Q2_ACT
	},  
	{ //LESS_ST
		LESS_ACT,  LESS_ACT,  LESS_ACT,   LESS_ACT,    LESS_ACT,    LESS_ACT,   LESS_ACT,   LESS_ACT, LESS_ACT, LESS_ACT,     LESS_ACT,    LESS_ACT,  LESS_ACT,   NEXT_ACT,   NEXT_ACT  
	}, 
	{ //GREATER_ST
		GREATER_ACT, GREATER_ACT, GREATER_ACT,  GREATER_ACT, GREATER_ACT, GREATER_ACT, GREATER_ACT, GREATER_ACT, GREATER_ACT, GREATER_ACT, GREATER_ACT, GREATER_ACT, GREATER_ACT,  GREATER_ACT, NEXT_ACT
	}, 
	{ //EQUALS_ST
		EQUAL_ACT,  EQUAL_ACT,  EQUAL_ACT, EQUAL_ACT, EQUAL_ACT, EQUAL_ACT,   EQUAL_ACT,  EQUAL_ACT,   EQUAL_ACT,   EQUAL_ACT,  EQUAL_ACT, EQUAL_ACT,   EQUAL_ACT,   EQUAL_ACT,    NEXT_ACT
	}
};

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
			if (token.lexeme == "*") {
				token.type = STAR;
			}
			else if (token.lexeme == "+") {
				token.type = PLUS;
			}
			else if (token.lexeme == "-") {
				token.type = MINUS;
			}
			else if (token.lexeme == ";") {
				token.type = SEMI;
			}
			else if (token.lexeme == ".") {
				token.type = PERIOD;
			}
			else if (token.lexeme == ":") {
				token.type = COLON;
			}
			else if (token.lexeme == ",") {
				token.type = COMMA;
			}
			else if (token.lexeme == "(") {
				token.type = LPAREN;
			}
			else if (token.lexeme == ")") {
				token.type = RPAREN;
			}
			done = true;
			break;		
		case LESS_ACT:
			if (token.lexeme == "<=") {
				token.type = LESSEQUAL;
			}
			else if (token.lexeme == "<") {
				token.type = LESS;
			}
			else if (token.lexeme == "<>") {
				token.type = NOTEQUAL;
			}
			done = true;
			break;
		case GREATER_ACT:
			if (token.lexeme == ">=") {
				token.type = GREATEREQUAL;
			}
			else if (token.lexeme == ">") {
				token.type = GREATER;
			}
			done = true;
			break;
		case EQUAL_ACT:
			if (token.lexeme == "==") {
				token.type = EQUAL;
			}
			else {
				token.type = ASSIGN;
			}
			done = true;
			break;
		case ID_ACT:
			if (token.lexeme == "program") {
				token.type = PROGRAM;
			}
			else if (token.lexeme == "begin") {
				token.type = BEGIN;
			}
			else if (token.lexeme == "end") {
				token.type = END;
			}
			else if (token.lexeme == "print") {
				token.type = PRINT;
			}
			else if (token.lexeme == "mod") {
				token.type = MOD;
			}
			else if (token.lexeme == "div") {
				token.type = DIV;
			}
			else if (token.lexeme == "const") {
				token.type = CONST;
			}
			else if (token.lexeme == "var") {
				token.type = VAR;
			}
			else if (token.lexeme == "int") {
				token.type = INT;
			}
			else if (token.lexeme == "bool") {
				token.type = BOOL;
			}
			else if (token.lexeme == "proc") {
				token.type = PROC;
			}
			else if (token.lexeme == "if") {
				token.type = IF;
			}
			else if (token.lexeme == "then") {
				token.type = THEN;
			}
			else if (token.lexeme == "else") {
				token.type = ELSE;
			}
			else if (token.lexeme == "while") {
				token.type = WHILE;
			}
			else if (token.lexeme == "do") {
				token.type = DO;
			}
			else if (token.lexeme == "prompt") {
				token.type = PROMPT;
			}
			else if (token.lexeme == "and") {
				token.type = AND;
			}
			else if (token.lexeme == "or") {
				token.type = OR;
			}
			else if (token.lexeme == "not") {
				token.type = NOT;
			}
			else if (token.lexeme == "true") {
				token.type = TRUE;
			}
			else if (token.lexeme == "false") {
				token.type = FALSE;
			}
			else 
				token.type = ID;
			done = true;
			break;
		case Q1_ACT: 
			token.lexeme += current;
			advance();
			break;
		case Q2_ACT: 
			token.type = STRING;
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
			cerr << " at line " << line_num << ", column " << column_num;
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
