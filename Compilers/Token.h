/*
* Token.h
*
*  Created on: Aug 30, 2015
*      Author: bhoward and Brad Burch
*	   Modified September 6, 2015 by Brad Burch
*/

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
#include <iosfwd>

using namespace std;

enum Token_Type {
	NUM, //Number
	SEMI, //;
	PLUS, //+
	MINUS, //-
	STAR, //*
	PERIOD, //.
	EQUALS, //=
	PROGRAM, //program
	CONST, //constant
	BEGIN, //begin
	END, //end
	PRINT, //print
	DIV, //div
	MOD, //mod
	ID, //identifer 
	EOFILE // EOF is already used in cstdio
};

// Format a Token_Type for display on an output stream
ostream& operator<<(ostream& out, Token_Type type);

struct Token {
	int line, column;
	Token_Type type;
	string lexeme;
};

// Format a Token for display on an output stream
ostream& operator<<(ostream& out, const Token& token);

#endif /* TOKEN_H_ */