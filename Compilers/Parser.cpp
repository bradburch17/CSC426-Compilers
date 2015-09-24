/*
* Created September 17, 2015
* Author: Brad Burch
*/
#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>

#include "Parser.h"
#include "Scanner.h"
#include "Wrapper.h"
#include "Token.h"

using namespace std;

Parser::Parser() {
	
}

/*
* pres is the presidence of the token types. 
*
* @params: Token 
*/
int pres(Token tok) {
	Token_Type type;
	type = tok.type;
	if (type == PRINT) {
		return 0;
	}
	else if (type == PLUS) {
		return 1;
	}
	else if (type == MINUS) {
		return 1;
	}
	else
		return 2;
}

void Parser::parser() {
	
	Wrapper wrapper(cin);
		
	while (wrapper.check(CONST)) {
		Token id = wrapper.match(ID);
		Token num = wrapper.match(NUM);
		wrapper.skip();
		pair<string, string> constant = make_pair(id.lexeme, num.lexeme);
	}

	while (wrapper.check(PRINT)) {
		wrapper.match(PRINT);
		stack<Token> s;
		Token tok;
		tok.type = PRINT;
		s.push(tok);
		Token op = wrapper.skip();

		while (!wrapper.check(SEMI)) {
			if (wrapper.check(NUM)) {
				cout << wrapper.match(NUM).lexeme << endl; 
			}
			else if (wrapper.check(ID)) {
				cout << wrapper.match(ID).lexeme << endl; 
			}
			else if (wrapper.check(PLUS)) { 
				op = wrapper.match(PLUS);
			}
			else if (wrapper.check(MINUS)) {
				op = wrapper.match(MINUS);
			}
			else if (wrapper.check(STAR)) {
				op = wrapper.match(STAR);
			}
			else if (wrapper.check(ASSIGN)) {
				op = wrapper.match(ASSIGN);
			}
			else if (wrapper.check(PERIOD)) {
				op = wrapper.match(PERIOD);
			}
			else {
				cout << "Error! Unexpected character. Expected NUM, ID, Operator";
			}

			while (pres(s.top()) >= pres(op)) {
				cout << s.top() << endl;
				s.pop();
			}
			
			s.push(op);
			
		}
		if (wrapper.check(SEMI) == true) {
			wrapper.match(SEMI);
			while (s.empty() == false) {
				cout << s.top();
				s.pop();
			}
		}
	}
}

//CONST (hashmap thing to link), pseudocode, and wrapper 
//new main (psu, maping to id+num, op stack), wrapper, 
