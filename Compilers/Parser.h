/*
* Parser.h
*
* Created September 17, 2015
* Author: Brad Burch
*/
#ifndef PARSER_H_
#define PARSER_H_

#include <iosfwd>
#include <unordered_map>
#include <string>

#include "Scanner.h"
#include "ASTStmt.h"
#include "ASTParam.h"
#include "ASTProgram.h"
#include "ASTBlock.h"
#include "ASTConstDecl.h"
#include "ASTExpr.h"
#include "ASTItem.h"
#include "ASTOp1.h"

using namespace std;

class Parser {
public:
	Parser();
	void parser();

	//Parsers (easier to read than ParseS, etc.)
	ASTProgram* parseProgram();
	ASTBlock* parseBlock();
	ASTConstDecl* parseConstDecl();
	ASTVarDecl* parseVarDecl();
	ASTProcDecl* parseProcDecl();
	ASTParam* parseParam();
	ASTStmt* parseStmt();
	ASTStmt* parseStmtID(string i); 
	ASTStmt* parseStmtIf(ASTExpr* t, ASTStmt* tr); 
	ASTStmt* parseStmtPrompt(string m); 
	ASTExpr* parseExpr();
	ASTExpr* parseExprRest(ASTExpr* e);
	ASTExpr* parseSimpleExpr();
	ASTExpr* parseSimpleExprRest(ASTExpr* e); 
	ASTExpr* parseTerm();
	ASTExpr* parseTermRest(ASTExpr* e); 
	ASTExpr* parseFactor();
	ASTItem* parseItem();

	//The Operators
	ASTOp2 parseRelOp();
	ASTOp2 parseAddOp();
	ASTOp2 parseMulOp();

	//The smaller traits
	string parseSign();
	ASTType parseType();

	//All the lists
	list<ASTConstDecl*> parseConstDecls();
	list<ASTVarDecl*> parseVarDecls();
	list<ASTProcDecl*> parseProcDecls();
	list<ASTStmt*> parseStmts();
	list<ASTParam*> parseParamList();
	list<ASTParam*> parseParams();
	list<ASTParam*> parseParamRest();
	list<ASTExpr*> parseArgList();
	list<ASTExpr*> parseArgs();
	list<ASTExpr*> parseArgsRest();
	list<ASTItem*> parseItems();
	list<ASTItem*> parseItemsRest();

private:
	pair<string, string> constant; //This sets up the pairing for constants. It is not the actual hashmap.
	unordered_map<string, string> con; //This is the actual hashmap that takes in constant. 
};

#endif /* PARSER_H_ */
