///*      TOO LATE TO TRY AND IMPLEMENT THIS - MAYBE LATER 
//* AST.h
//*
//*  Created on: October 12, 2015
//*      Author: Brad Burch
//*/
//
//#ifndef AST_H_
//#define AST_H_
//
//#include <string>
//#include <iosfwd>
//#include <list>
//#include "ASTStmt.h"
//
//using namespace std;
//
//class ASTBlock {
//public:
//	ASTBlock(list<ASTConstDecl*> c, list<ASTVarDecl*> v, list<ASTProcDecl*> p, list<ASTStmt*> b);
//	string render(string indent);
//
//private:
//	list<ASTConstDecl*> consts;
//	list<ASTVarDecl*> vars;
//	list<ASTProcDecl*> procs;
//	list<ASTStmt*> body;
//
//};
//
//class ASTConstDecl {
//public:
//	ASTConstDecl(string i, int v);
//	string render(string indent);
//
//private:
//	string id;
//	int value;
//
//};
//
//class ASTExpr {
//public:
//	ASTExpr();
//	virtual string render(string indent) = 0;
//
//private:
//
//};
//
//class BinOp : public ASTExpr {
//public:
//	BinOp(ASTExpr* l, ASTOp2* o, ASTExpr* r);
//	string render(string indent);
//
//private:
//	ASTExpr* left;
//	ASTOp2* op;
//	ASTExpr* right;
//};
//
//class ID : public ASTExpr {
//public:
//	ID(string i);
//	string render(string indent);
//
//private:
//	string id;
//
//};
//
//class Num : public ASTExpr {
//public:
//	Num(int v);
//	string render(string indent);
//
//private:
//	int value;
//
//};
//
//class UnOp : public ASTExpr {
//public:
//	UnOp(ASTOp1* o, ASTExpr* e);
//	string render(string indent);
//
//private:
//	ASTOp1* op;
//	ASTExpr* expr;
//
//};
//
//class True : public ASTExpr {
//public:
//	True(int l, int c);
//	string render(string indent);
//private:
//	int line;
//	int column;
//	bool boolean;
//};
//
//class False : public ASTExpr {
//public:
//	False(int l, int c);
//	string render(string indent);
//
//private:
//	int line;
//	int column;
//	bool boolean;
//};
//
//class ASTItem {
//public:
//	ASTItem();
//	virtual string render(string indent) = 0;
//
//private:
//
//
//};
//
//class ExprItem : public ASTItem {
//public:
//	ExprItem(ASTExpr* e);
//	string render(string indent);
//
//private:
//	ASTExpr* expr;
//
//};
//
//class StringItem : public ASTItem {
//public:
//	StringItem(string m);
//	string render(string indent);
//private:
//	string message;
//
//};
//
//class ASTOp1 {
//public:
//	enum Op1 { Neg, Not };
//	string nameCheck(Op1 op1);
//
//private:
//
//};
//
//class ASTOp2 {
//public:
//	enum Op2 { EQ, NE, LE, GE, LT, GT, Plus, Minus, Times, Div, Mod, And, Or };
//	string nameCheck(Op2 op2);
//private:
//
//
//};
//
//class ASTParam {
//public:
//	ASTParam();
//	virtual string render(string indent) = 0;
//
//private:
//
//};
//
//class ValParam : public ASTParam {
//public:
//	ValParam(string i, ASTType* t);
//	string render(string indent);
//
//private:
//	string id;
//	ASTType* type;
//
//};
//
//class VarParam : public ASTParam {
//public:
//	VarParam(string i, ASTType* t);
//	string render(string indent);
//
//private:
//	string id;
//	ASTType* type;
//
//};
//
//class ASTBlock;
//
//using namespace std;
//
//class ASTProcDecl {
//public:
//	ASTProcDecl(string i, list<ASTParam> p, ASTBlock b);
//	string render(string indent);
//
//private:
//	string id;
//	list<ASTParam> params;
//	ASTBlock block;
//
//
//};
//#endif /* ASTBlock_H_ */
