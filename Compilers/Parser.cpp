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
#include "ASTParam.h"
#include "ASTExpr.h"
#include "ASTOp1.h"
#include "ASTOp2.h"

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

Wrapper wrapper(cin);

ASTProgram * Parser::parseProgram() {
	Token program = wrapper.match(PROGRAM);
	Token id = wrapper.match(ID);
	wrapper.match(SEMI);
	ASTBlock* block = parseBlock();
	wrapper.match(PERIOD);

	ASTProgram* p = new ASTProgram(id.lexeme, block);
	return p;
}

ASTBlock * Parser::parseBlock()
{
	list<ASTConstDecl*> constDecls = parseConstDecls();
	list<ASTVarDecl*> varDecls = parseVarDecls();
	list<ASTProcDecl*> procDecls = parseProcDecls();
	Token begin = wrapper.match(BEGIN);
	list<ASTStmt*> stmts = parseStmts();
	wrapper.match(END);

	ASTBlock* b = new ASTBlock(constDecls, varDecls, procDecls, stmts);
	return b;
}

ASTConstDecl * Parser::parseConstDecl()
{
	Token constant = wrapper.match(CONST);
	Token id = wrapper.match(ID);
	Token assign = wrapper.match(ASSIGN);
	string sign = parseSign();
	Token num = wrapper.match(NUM);
	wrapper.match(SEMI);

	int val = stoi(num.lexeme);
	if (sign.compare("-") == 0)
		val = -val;

	ASTConstDecl* c = new ASTConstDecl(id.lexeme, val);
	return c;
}

ASTVarDecl * Parser::parseVarDecl()
{
	Token var = wrapper.match(VAR);
	Token id = wrapper.match(ID);
	wrapper.match(COLON);
	ASTType type = parseType();
	wrapper.match(SEMI);

	ASTVarDecl* v = new ASTVarDecl(id.lexeme, type);
	return v;
}

ASTProcDecl * Parser::parseProcDecl()
{
	Token proc = wrapper.match(PROC);
	Token id = wrapper.match(ID);
	list<ASTParam*> paramList = parseParamList();
	wrapper.match(SEMI);
	ASTBlock* block = parseBlock();
	wrapper.match(SEMI);

	ASTProcDecl* p = new ASTProcDecl(id.lexeme, paramList, block);
}

ASTParam * Parser::parseParam()
{
	if (wrapper.check(ID)) {
		Token id = wrapper.match(ID);
		wrapper.match(COLON);
		ASTType type = parseType();
		ValParam* v = new ValParam(id.lexeme, type);
		return v;
	}
	else {
		Token var = wrapper.match(VAR);
		Token id = wrapper.match(ID);
		wrapper.match(COLON);
		ASTType type = parseType();

		VarParam* v = new VarParam(id.lexeme, type);
		return v;
	}
}

ASTStmt * Parser::parseStmt()
{
	if (wrapper.check(ID)) {
		Token id = wrapper.match(ID);
		ASTStmt* s = parseStmtID(id.lexeme);
		wrapper.match(SEMI);

		return s;
	}
	else if (wrapper.check(BEGIN)) {
		Token begin = wrapper.match(BEGIN);
		list<ASTStmt*> stmts = parseStmts();
		wrapper.match(END);
		wrapper.match(SEMI);

		Seq* s = new Seq(stmts);
		return s;
	}
	else if (wrapper.check(IF)) {
		Token ift = wrapper.match(IF);
		ASTExpr* expr = parseExpr();
		wrapper.match(THEN);
		ASTStmt* stmt = parseStmt();
		ASTStmt* check = parseStmtIf(expr, stmt);

		return check;
	}
	else if (wrapper.check(WHILE)) {
		Token whil = wrapper.match(WHILE);
		ASTExpr* expr = parseExpr();
		wrapper.match(DO);
		ASTStmt* stmt = parseStmt();

		While* w = new While(expr, stmt);
		return w;
	}
	else if (wrapper.check(PROMPT)) {
		Token prompt = wrapper.match(PROMPT);
		Token message = wrapper.match(STRING);
		ASTStmt* check = parseStmtPrompt(message.lexeme);
		wrapper.match(SEMI);

		return check;
	}
	else if (wrapper.check(PRINT)) {
		Token print = wrapper.match(PRINT);
		list<ASTItem*> items = parseItems();
		wrapper.match(SEMI);

		Print* p = new Print(items);
		return p;
	}
}

ASTStmt * Parser::parseStmtID(string i)
{
	if (wrapper.check(EQUAL)) {
		wrapper.match(EQUAL);
		ASTExpr* expr = parseExpr();
		Assign* a = new Assign(i, expr);
		return a;
	}
	else {
		list<ASTExpr*> args = parseArgList();
		Call* c = new Call(i, args);
		return c;
	}
}

ASTStmt * Parser::parseStmtIf(ASTExpr * t, ASTStmt * tr)
{
	if (wrapper.check(ELSE)) {
		wrapper.match(ELSE);
		ASTStmt* stmt = parseStmt();
		IfThenElse* i = new IfThenElse(t, tr, stmt);
		return i;
	}
	else {
		IfThen* i = new IfThen(t, tr);
		return i;
	}
}

ASTStmt * Parser::parseStmtPrompt(string m)
{
	if (wrapper.check(COMMA)) {
		wrapper.match(COMMA);
		Token id = wrapper.match(ID);
		Prompt2* p = new Prompt2(m, id.lexeme);
		return p;
	}
	else {
		Prompt* p = new Prompt(m);
		return p;
	}
}

ASTExpr * Parser::parseExpr()
{
	ASTExpr* expr = parseSimpleExpr();
	ASTExpr* e = parseExprRest(expr);
	return e;
}

ASTExpr * Parser::parseExprRest(ASTExpr * e)
{
	if (wrapper.check(EQUAL) || wrapper.check(NOTEQUAL) || wrapper.check(LESS) || wrapper.check(GREATER) || wrapper.check(LESSEQUAL) || wrapper.check(GREATEREQUAL)) {
		ASTOp2 relOp = parseRelOp();
		ASTExpr* expr = parseSimpleExpr();

		BinOp* b = new BinOp(e, relOp, expr);
		return b;
	}
}

ASTExpr * Parser::parseSimpleExpr()
{
	ASTExpr* term = parseTerm();
	ASTExpr* e = parseSimpleExprRest(term);

	return e;
}

ASTExpr * Parser::parseSimpleExprRest(ASTExpr * e)
{
	if (wrapper.check(PLUS) || wrapper.check(MINUS) || wrapper.check(OR)) {
		ASTOp2 addOp = parseAddOp();
		ASTExpr* term = parseTerm();
		BinOp* binOp = new BinOp(e, addOp, term);
		ASTExpr* n = parseSimpleExprRest(binOp);
		return n;
	}
	else
		return e;
}

ASTExpr * Parser::parseTerm()
{
	ASTExpr* factor = parseFactor();
	ASTExpr* n = parseTermRest(factor);
	return n;
}

ASTExpr * Parser::parseTermRest(ASTExpr * e)
{
	if (wrapper.check(STAR) || wrapper.check(DIV) || wrapper.check(MOD) || wrapper.check(AND)) {
		ASTOp2 mulOp = parseMulOp();
		ASTExpr* factor = parseFactor();
		BinOp* binOp = new BinOp(e, mulOp, factor);
		ASTExpr* n = parseTermRest(binOp);

		return n;
	}
	else
		return e;
}

ASTExpr * Parser::parseFactor()
{
	if (wrapper.check(NUM))
	{
		Token num = wrapper.match(NUM);
		Num* n = new Num(stoi(num.lexeme));

		return n;
	}
	else if (wrapper.check(ID))
	{
		Token id = wrapper.match(ID);
		IDExpr* n = new IDExpr(id.lexeme);

		return n;
	}
	else if (wrapper.check(TRUE))
	{
		Token trueToken = wrapper.match(TRUE);
		True* n = new True();

		return n;
	}
	else if (wrapper.check(FALSE))
	{
		Token falseToken = wrapper.match(FALSE);
		False* n = new False();

		return n;
	}
	else if (wrapper.check(MINUS))
	{
		Token unOp = wrapper.match(MINUS);
		ASTExpr* factor = parseFactor();
		ASTOp1 Neg; //This will probably need to be fixed. 
		UnOp* n = new UnOp(Neg, factor);

		return n;
	}
	else if (wrapper.check(NOT))
	{
		Token unOp = wrapper.match(NOT);
		ASTExpr* factor = parseFactor();
		ASTOp1 Not; //This will probably need to be fixed.
		UnOp* n = new UnOp(Not, factor);

		return n;
	}
	else
	{
		Token leftParen = wrapper.match(LPAREN);
		ASTExpr* n = parseExpr();
		wrapper.match(RPAREN);

		return n;
	}
}

ASTItem * Parser::parseItem()
{
	if (wrapper.check(STRING)) {
		Token stringToken = wrapper.match(STRING);
		StringItem* node = new StringItem(stringToken.lexeme);

		return node;
	}
	else
	{
		ASTExpr* expr = parseExpr();
		ExprItem* n = new ExprItem(expr);

		return n;
	}
}

ASTOp2 Parser::parseRelOp()
{
	if (wrapper.check(EQUAL))
	{
		wrapper.match(EQUAL);
		return EQ;
	}
	else if (wrapper.check(NOTEQUAL))
	{
		wrapper.match(NOTEQUAL);
		return NE;
	}
	else if (wrapper.check(LESS))
	{
		wrapper.match(LESS);
		return LT;
	}
	else if (wrapper.check(GREATER))
	{
		wrapper.match(GREATER);
		return GT;
	}
	else if (wrapper.check(LESSEQUAL))
	{
		wrapper.match(LESSEQUAL);
		return LE;
	}
	else
	{
		wrapper.match(GREATEREQUAL);
		return GE;
	}
}

ASTOp2 Parser::parseAddOp()
{
	if (wrapper.check(PLUS))
	{
		wrapper.match(PLUS);
		return Plus;
	}
	else if (wrapper.check(MINUS))
	{
		wrapper.match(MINUS);
		return Minus;
	}
	else
	{
		wrapper.match(OR);
		return Or;
	}
}

ASTOp2 Parser::parseMulOp()
{
	if (wrapper.check(STAR))
	{
		wrapper.match(STAR);
		return Times;
	}
	else if (wrapper.check(DIV))
	{
		wrapper.match(DIV);
		return Div;
	}
	else if (wrapper.check(MOD))
	{
		wrapper.match(MOD);
		return Mod;
	}
	else
	{
		wrapper.match(AND);
		return And;
	}
}

string Parser::parseSign()
{
	if (wrapper.check(MINUS))
	{
		wrapper.match(MINUS);
		return "-";
	}
	else
		return "";
}

ASTType Parser::parseType()
{
	if (wrapper.check(NUM))
	{
		wrapper.match(NUM);
		return IntType;
	}
	else
	{
		wrapper.match(BOOL);
		return BoolType;
	}
}

list<ASTConstDecl*> Parser::parseConstDecls()
{
	if (wrapper.check(CONST)) {
		ASTConstDecl* constDecl = parseConstDecl();
		list<ASTConstDecl*> constDecls = parseConstDecls();
		constDecls.push_front(constDecl);
		return constDecls;
	}
	else
		return list<ASTConstDecl*>();
}

list<ASTVarDecl*> Parser::parseVarDecls()
{
	if (wrapper.check(VAR))	{
		ASTVarDecl* varDecl = parseVarDecl();
		list<ASTVarDecl*> varDecls = parseVarDecls();
		varDecls.push_front(varDecl);
		return varDecls;
	}
	else
		return list<ASTVarDecl*>();
}

list<ASTProcDecl*> Parser::parseProcDecls()
{
	if (wrapper.check(PROC))
	{
		ASTProcDecl* procDecl = parseProcDecl();
		list<ASTProcDecl*> procDecls = parseProcDecls();
		procDecls.push_front(procDecl);
		return procDecls;
	}
	else
		return list<ASTProcDecl*>();
}

list<ASTStmt*> Parser::parseStmts()
{
	if (wrapper.check(ID) || wrapper.check(BEGIN) || wrapper.check(IF) || wrapper.check(WHILE) || wrapper.check(PROMPT) || wrapper.check(PRINT))
	{
		ASTStmt* stmt = parseStmt();
		list<ASTStmt*> stmts = parseStmts();
		stmts.push_front(stmt);
		return stmts;
	}
	else
		return list<ASTStmt*>();
}

list<ASTParam*> Parser::parseParamList()
{
	if (wrapper.check(LPAREN))
	{
		wrapper.match(LPAREN);
		list<ASTParam*> params = parseParams();
		wrapper.match(RPAREN);
		return params;
	}
	else
		return list<ASTParam*>();
}

list<ASTParam*> Parser::parseParams()
{
	ASTParam* param = parseParam();
	list<ASTParam*> paramRest = parseParamRest();
	paramRest.push_front(param);
	return paramRest;
}

list<ASTParam*> Parser::parseParamRest()
{
	if (wrapper.check(COMMA))
	{
		wrapper.match(COMMA);
		list<ASTParam*> params = parseParams();
		return params;
	}
	else
		return list<ASTParam*>();
}

list<ASTExpr*> Parser::parseArgList()
{
	if (wrapper.check(LPAREN))
	{
		wrapper.match(LPAREN);
		list<ASTExpr*> args = parseArgs();
		wrapper.match(RPAREN);
		return args;
	}
	else
		return list<ASTExpr*>();
}

list<ASTExpr*> Parser::parseArgs()
{
	ASTExpr* expr = parseExpr();
	list<ASTExpr*> argsRest = parseArgsRest();
	argsRest.push_front(expr);
	return argsRest;
}

list<ASTExpr*> Parser::parseArgsRest()
{
	if (wrapper.check(COMMA))
	{
		wrapper.match(COMMA);
		list<ASTExpr*> args = parseArgs();
		return args;
	}
	else
		return list<ASTExpr*>();
}

list<ASTItem*> Parser::parseItems()
{
	ASTItem* item = parseItem();
	list<ASTItem*> itemRest = parseItemsRest();
	itemRest.push_front(item);
	return itemRest;
}

list<ASTItem*> Parser::parseItemsRest()
{
	if (wrapper.check(COMMA))
	{
		wrapper.match(COMMA);
		list<ASTItem*> items = parseItems();
		return items;
	}
	else
		return list<ASTItem*>();
}
