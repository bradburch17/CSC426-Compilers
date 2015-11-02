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
//
//
//using namespace std;
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
//	string checkOp1(Op1 op1);
//	string checkOp2(Op2 op2);
//	virtual string render(string indent) = 0;
//
//private:
//
//};
//
//class BinOp : public ASTExpr {
//public:
//	BinOp(ASTExpr* l, Op2 o, ASTExpr* r);
//	string render(string indent);
//
//private:
//	ASTExpr* left;
//	Op2 op;
//	ASTExpr* right;
//};
//
//class IDExpr : public ASTExpr {
//public:
//	IDExpr(string i);
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
//	UnOp(Op1 o, ASTExpr* e);
//	string render(string indent);
//
//private:
//	Op1 op;
//	ASTExpr* expr;
//
//};
//
//class True : public ASTExpr {
//public:
//	True();
//	string render(string indent);
//private:
//	bool boolean;
//};
//
//class False : public ASTExpr {
//public:
//	False();
//	string render(string indent);
//
//private:
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
//class StringItem : public ASTItem {
//public:
//	StringItem(string m);
//	string render(string indent);
//private:
//	string message;
//
//};
/////////////////////////////////////////////////////////////////////////////////////////
//enum Op1 { Neg, Not };
//
//enum Op2 { EQ, NE, LE, GE, LT, GT, Plus, Minus, Times, Div, Mod, And, Or };
//
//enum Type { IntType, BoolType };
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
//	ValParam(string i, Type t);
//	string render(string indent);
//
//private:
//	string id;
//	Type type;
//
//};
//
//class VarParam : public ASTParam {
//public:
//	VarParam(string i, Type t);
//	string render(string indent);
//
//private:
//	string id;
//	Type type;
//
//};
//
////class ASTBlock;
//
//
//class ASTProcDecl {
//public:
//	ASTProcDecl(string i, list<ASTParam*> p, ASTBlock* b);
//	string render(string indent);
//
//private:
//	string id;
//	list<ASTParam*> params;
//	ASTBlock* block; 
//};
//
//class ASTProgram {
//public:
//	ASTProgram(string n, ASTBlock* b);
//	string render(string indent);
//
//private:
//	string name;
//	ASTBlock* block;
//
//
//};
//
//class ASTStmt { //Must use pointers when working with virtual functions! 
//public:
//	virtual string render(string indent) = 0;
//	ASTStmt();
//
//};
//
//class Assign : public ASTStmt {
//public:
//	Assign(string i, ASTExpr* e);
//	string render(string indent);
//
//private:
//	string id;
//	ASTExpr* expr;
//};
//
//class Call : public ASTStmt {
//public:
//	Call(string i, list<ASTExpr*> a);
//	string render(string indent);
//
//private:
//	string id;
//	list<ASTExpr*> args;
//};
//
//
//class IfThen : public ASTStmt {
//public:
//	IfThen(ASTExpr* t, ASTStmt* tc);
//	string render(string indent);
//private:
//	ASTExpr* test;
//	ASTStmt* trueClause;
//};
//
//class IfThenElse : public ASTStmt {
//public:
//	IfThenElse(ASTExpr* t, ASTStmt* tc, ASTStmt* fc);
//	string render(string indent);
//
//private:
//	ASTExpr* test;
//	ASTStmt* trueClause;
//	ASTStmt* falseClause;
//};
//
//class Print : public ASTStmt {
//public:
//	Print(list<ASTItem*> i);
//	string render(string indent);
//
//private:
//	list<ASTItem*> items;
//
//};
//
//class Prompt : public ASTStmt {
//public:
//	Prompt(string m);
//	string render(string indent);
//private:
//	string message;
//
//};
//
//class Prompt2 : public ASTStmt {
//public:
//	Prompt2(string m, string i);
//	string render(string indent);
//
//private:
//	string message;
//	string id;
//
//};
//
//class Seq : public ASTStmt {
//public:
//	Seq(list<ASTStmt*> b);
//	string render(string indent);
//
//private:
//	list<ASTStmt*> body;
//
//};
//
//class While : public ASTStmt {
//public:
//	While(ASTExpr* t, ASTStmt* b);
//	string render(string indent);
//
//private:
//	ASTExpr* test;
//	ASTStmt* body;
//
//};
//
//class ASTVarDecl {
//public:
//	ASTVarDecl(string i, Type t);
//	string render(string indent);
//
//private:
//	string id;
//	Type typ;
//
//
//};
//
//#endif /* ASTBlock_H_ */
