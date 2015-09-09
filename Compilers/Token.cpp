/*
* Token.cpp
*
*  Created on: Aug 30, 2015
*      Author: Brad Burch
*/

#include "Token.h"

#include <ostream>

std::ostream& operator<<(std::ostream& out, Token_Type type) {
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
	case EQUALS:
		out << "EQUALS";
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
		//Identifier 
	case ID:
		out << "ID ";
		break;
		//End of File
	case EOFILE:
		out << "EOF";
		break;
		// TODO add cases for the other Token_Types
	default:
		out << "ERROR";
		break;
	}

	return out;
}

std::ostream& operator<<(std::ostream& out, const Token& token) {
	out << token.type;

	if (token.lexeme != "") {
		out << " " << token.lexeme;
	}

	out << " " << token.line << ":" << token.column;

	return out;
}
