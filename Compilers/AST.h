/*       
* AST.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef AST_H_
#define AST_H_

#include <string>
#include <iosfwd>
#include <list>
#include <stack>
#include <vector>
#include <map>

using namespace std;

enum Op1 { Neg, Not };
enum Op2 { EQ, NE, LE, GE, LT, GT, Plus, Minus, Times, Div, Mod, And, Or };
enum Type { IntType, BoolType };

enum NodeTypes {Val, Expr, Item, String}; //used to check to see if node is true.

string checkOp1(Op1 op1);
string checkOp2(Op2 op2);

/*
* Abstract Syntax Tree Beginning 
*/
class ASTConstDecl;
class ASTVarDecl;
class ASTProcDecl;
class ASTStmt;
class ASTItem;
class ASTParam;
class ASTExpr;
class ASTValDecl;
class ASTProgram;
class Value;
class SymbolTable;



/**
* Block
*/
class ASTBlock {
public:
	ASTBlock(list<ASTConstDecl*> c, list<ASTVarDecl*> v, list<ASTProcDecl*> p, list<ASTStmt*> b);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	list<ASTConstDecl*> consts;
	list<ASTVarDecl*> vars;
	list<ASTProcDecl*> procs;
	list<ASTStmt*> body;

};

/*
* Constant Declaration
*/
class ASTConstDecl {
public:
	ASTConstDecl(string i, int v);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	string id;
	int value;
};

/*
* Expressions 
*/
class ASTExpr {
public:
	ASTExpr();
	virtual string render(string indent) = 0;
	virtual Value* interpret(SymbolTable t) = 0;
	NodeTypes expr;
};

class BinOp : public ASTExpr {
public:
	BinOp(ASTExpr* l, Op2 o, ASTExpr* r);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	ASTExpr* left;
	Op2 op;
	ASTExpr* right;
};

class IDExpr : public ASTExpr {
public:
	IDExpr(string i);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	string id;
};

class Num : public ASTExpr {
public:
	Num(int v);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	int value;
};

class UnOp : public ASTExpr {
public:
	UnOp(Op1 o, ASTExpr* e);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	Op1 op;
	ASTExpr* expr;

};

class True : public ASTExpr {
public:
	True();
	string render(string indent);
	Value* interpret(SymbolTable t);
private:
	bool boolean;
};

class False : public ASTExpr {
public:
	False();
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	bool boolean;
};

/*********************************
* Items
***********************************/
class ASTItem {
public:
	ASTItem();
	virtual string render(string indent) = 0;
	NodeTypes item;
};

class ExprItem : public ASTItem {
public:
	ExprItem(ASTExpr* e);
	string render(string indent);
	ASTExpr* expr;
	NodeTypes n;
};

class StringItem : public ASTItem {
public:
	StringItem(string m);
	string render(string indent);
	string message;
	NodeTypes n;
};


/***********************************
* Parameter 
*************************************/
class ASTParam {
public:
	ASTParam();
	virtual string render(string indent) = 0;
	NodeTypes val;
};

class ValParam : public ASTParam {
public:
	ValParam(string i, Type t);
	string render(string indent);
	string id;
	Type type;
	NodeTypes val;
};

class VarParam : public ASTParam {
public:
	VarParam(string i, Type t);
	string render(string indent);
	string id;
	Type type;
};

/******************
* Procedure Declaration 
********************/
class ASTProcDecl {
public:
	ASTProcDecl(string i, list<ASTParam*> p, ASTBlock* b);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	string id;
	list<ASTParam*> params;
	ASTBlock* block; 
};

/*********************
* Program
***********************/
class ASTProgram {
public:
	ASTProgram(string n, ASTBlock* b);
	string render(string indent);
	Value* interpret();

private:
	string name;
	ASTBlock* block;
};

/****************
* Statements 
******************/
class ASTStmt {  
public:
	ASTStmt();
	virtual string render(string indent) = 0;
	virtual Value* interpret(SymbolTable t) = 0;
};

class Assign : public ASTStmt {
public:
	Assign(string i, ASTExpr* e);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	string id;
	ASTExpr* expr;
};

class Call : public ASTStmt {
public:
	Call(string i, list<ASTExpr*> a);
	string render(string indent);
	Value* interpret(SymbolTable t);
	void call(list<ASTParam*> p, ASTBlock* b, list<Value*> v, SymbolTable t);
private:
	string id;
	list<ASTExpr*> args;
};


class IfThen : public ASTStmt {
public:
	IfThen(ASTExpr* t, ASTStmt* tc);
	string render(string indent);
	Value* interpret(SymbolTable t);
private:
	ASTExpr* test;
	ASTStmt* trueClause;
};

class IfThenElse : public ASTStmt {
public:
	IfThenElse(ASTExpr* t, ASTStmt* tc, ASTStmt* fc);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	ASTExpr* test;
	ASTStmt* trueClause;
	ASTStmt* falseClause;
};

class Print : public ASTStmt {
public:
	Print(list<ASTItem*> i);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	list<ASTItem*> items;

};

class Prompt : public ASTStmt {
public:
	Prompt(string m);
	string render(string indent);
	Value* interpret(SymbolTable t);
private:
	string message;

};

class Prompt2 : public ASTStmt {
public:
	Prompt2(string m, string i);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	string message;
	string id;

};

class Seq : public ASTStmt {
public:
	Seq(list<ASTStmt*> b);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	list<ASTStmt*> body;

};

class While : public ASTStmt {
public:
	While(ASTExpr* t, ASTStmt* b);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	ASTExpr* test;
	ASTStmt* body;

};

/***********************
* Variable Declarations 
************************/
class ASTVarDecl {
public:
	ASTVarDecl(string i, Type t);
	string render(string indent);
	Value* interpret(SymbolTable t);

private:
	string id;
	Type typ;
};

/***********************
* Variable Declarations
************************/
class Val {
public: 
	Val();
	virtual bool isVariable() = 0;
};
#endif /* AST_H_ */
