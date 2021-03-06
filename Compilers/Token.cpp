/*
* Token.cpp
*
*  Created on: Aug 30, 2015
*      Author: Brad Burch
*/

#include "Token.h"

#include <ostream>

using namespace std;

ostream& operator<<(ostream& out, Token_Type type) {
	switch (type) {
	// Numbers 
	case NUM:
		out << "NUM";
		break;
	// Operators/Punctuation 
	case SEMI:
		out << "SEMI";
		break;
	case PERIOD:
		out << "PERIOD";
		break;
	case PLUS:
		out << "PLUS";
		break;
	case MINUS:
		out << "MINUS";
		break;
	case STAR:
		out << "STAR";
		break;
	case ASSIGN:
		out << "ASSIGN";
		break;
	//Keywords
	case PROGRAM:
		out << "PROGRAM";
		break;
	case CONST:
		out << "CONST";
		break;
	case BEGIN:
		out << "BEGIN";
		break;
	case END:
		out << "END";
		break;
	case PRINT:
		out << "PRINT";
		break;
	case DIV:
		out << "DIV";
		break;
	case MOD:
		out << "MOD";
		break;

	case VAR:
		out << "VAR";
		break;
	case INT: 
		out << "INT";
		break;
	case BOOL:
		out << "BOOLEAN";
		break;
	case PROC:
		out << "PROC";
		break;
	case IF:
		out << "IF";
		break;
	case THEN:
		out << "THEN";
		break;
	case ELSE:
		out << "ELSE";
		break;
	case WHILE:
		out << "WHILE";
		break;
	case DO:
		out << "DO";
		break;
	case PROMPT:
		out << "PROMPT";
		break;
	case AND:
		out << "AND";
		break;
	case OR:
		out << "OR";
		break;
	case NOT:
		out << "NOT";
		break;
	case TRUE:
		out << "TRUE";
		break;
	case FALSE:
		out << "FALSE";
		break;
	case ID:
		out << "ID";
		break;
	//End of File
	case EOFILE:
		out << "EOF";
		break;
	default:
		out << "ERROR";
		break;
	}

	return out;
}

ostream& operator<<(ostream& out, const Token& token) {
	out << token.type;

	if (token.type == ID) {
		out << " " << token.lexeme;
	}
	else if (token.type == NUM) {
		out << " " << token.lexeme;
	}
	else if (token.type != ID) {

	}
	else if (token.lexeme != "") {
		out << " " << token.lexeme;
	}

	out << " " << token.line << ":" << token.column;

	return out;
}
