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
	else if (type == STAR) {
		return 2;
	} 
	else if (type == DIV) {
		return 2;
	}
	else if (type == MOD) {
		return 2;
	} 
}
/*
* parser() is the main parser function. It sets up the syntax for a YASL program. 
*/
void Parser::parser() {
	
	Wrapper wrapper(cin);

	wrapper.match(PROGRAM);
	wrapper.match(ID);
	wrapper.match(SEMI);

	while (wrapper.check(CONST)) {
		wrapper.skip();
		Token id = wrapper.match(ID);
		wrapper.match(ASSIGN);
		Token num = wrapper.match(NUM);
		wrapper.match(SEMI);
		constant = make_pair(id.lexeme, num.lexeme);
		con.insert(constant);
	}

	wrapper.match(BEGIN);

	while (wrapper.check(PRINT)) {
		wrapper.match(PRINT);
		stack<Token> s;
		Token tok;
		tok.type = PRINT;
		s.push(tok);
		Token op;

		while (!wrapper.check(SEMI)) {
			if (wrapper.check(NUM)) {
				cout << wrapper.match(NUM).lexeme << endl; 
				continue;
			}
			else if (wrapper.check(ID)) {
				Token id = wrapper.match(ID);
				cout << con.at(id.lexeme) << endl;
				continue;
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
			else if (wrapper.check(MOD)) {
				op = wrapper.match(MOD);
			}
			else if (wrapper.check(DIV)) {
				op = wrapper.match(DIV);
			}
			else if (wrapper.check(ASSIGN)) {
				op = wrapper.match(ASSIGN);
			}
			else if (wrapper.check(PERIOD)) {
				op = wrapper.match(PERIOD);
			}
			else {
				cout << "Error! Unexpected character. Expected NUM, ID, Operator";
				wrapper.skip();
			}
			while (pres(s.top()) >= pres(op)) {
				cout << s.top().lexeme << endl;
				s.pop();
			}
			s.push(op);
		}
		if (wrapper.check(SEMI) == true) {
			wrapper.match(SEMI);
			while (!s.empty()) {
				if (s.top().type != PRINT) {
					cout << s.top().lexeme << endl;
				}
				if (s.top().type == PRINT) {
					cout << "PRINT" << endl;
				}
				s.pop();
			}
		}
	}
	wrapper.match(END);
	wrapper.match(PERIOD);
}

ASTStmt Parser::parseProgram()
{
	Wrapper wrapper(cin);
	ASTStmt stmt = parseS();
	wrapper.match(EOFILE);
	return stmt;
}

/*
ASTStmt parseS() {
	Wrapper wrapper(cin);
	if (wrapper.check(ID)) {
		string lhs = wrapper.match(ID);
		wrapper.match(ASSIGN);
		return parseU(lhs);
		} 
	else if (wrapper.check(BEGIN)) {
		wrapper.match(BEGIN);
		list<Stmt> stmts = parseT(new ArrayList<Stmt>());
		wrapper.match(END);
		return Stmt.seqStmt(stmts);
		} 
	else if (wrapper.check(WHILE)) {
		wrapper.match(WHILE);
		string test = wrapper.match(ID);
		Stmt body = parseS();
		return Stmt.whileStmt(test, body);
		} 
	else if (wrapper.check(IF)) {
		wrapper.match(IF);
		string test = wrapper.match(ID);
		Stmt body = parseS();
		return Stmt.ifStmt(test, body);
		} 
	else {
		wrapper.match(DO);
		Stmt body = parseS();
		wrapper.match(UNTIL);
		string test = wrapper.match(ID);
		return Stmt.untilStmt(test, body);
	if (wrapper.check(ID)) {
		string lhs = wrapper.match(ID);
		wrapper.match(ASSIGN);
		return parseU(lhs);
	}
	else if (wrapper.check(BEGIN)) {
		wrapper.match(BEGIN);
		list<Stmt> stmts = parseT(ArrayList<Stmt>());
		wrapper.match(END);
		return Stmt.seqStmt(stmts);
	}
	else if (wrapper.check(WHILE)) {
		wrapper.match(WHILE);
		string test = wrapper.match(ID);
		Stmt body = parseS();
		return Stmt.whileStmt(test, body);
	}
	else if (wrapper.check(IF)) {
		wrapper.match(IF);
		string test = wrapper.match(ID);
		Stmt body = parseS();
		return Stmt.ifStmt(test, body);
	}
	else {
		wrapper.match(DO);
		Stmt body = parseS();
		wrapper.match(UNTIL);
		string test = wrapper.match(ID);
		return Stmt.untilStmt(test, body);
	}
	*/
