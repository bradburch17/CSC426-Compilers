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
#include "SymbolTable.h"

using namespace std;

enum Op1 { Neg, Not };
enum Op2 { EQ, NE, LE, GE, LT, GT, Plus, Minus, Times, Div, Mod, And, Or };
enum Type { IntType, BoolType };
enum InfoType { Undefined_Info, ConstInfo_Info, VarInfo_Info, RefInfo_Info, ProcInfo_Info }; 
enum ValType { Undefined_Val, IntVal_Val, BoolVal_Val, IntVar_Val, BoolVar_Val, ProcVal_Val };

enum NodeTypes {
	UndefinedNode, 
	ProgramNode, 
	BlockNode, 
	ConstDeclNode, 
	VarDeclNode, 
	ProcDeclNode, 
	ValParamNode, 
	VarParamNode, 
	AssignNode, 
	CallNode, 
	SeqNode, 
	IfThenNode, 
	IfThenElseNode, 
	WhileNode, 
	PromptNode, 
	Prompt2NOde, 
	PrintNode,
	BinOpNode, 
	UnOpNode, 
	NumNode, 
	IDNode,
	TrueNode, 
	FalseNode, 
	ValuesNode, 
	ExprNode, 
	ItemNode, 
	StringNode
}; 

string checkOp1(Op1 op1);
string checkOp2(Op2 op2);
string checkValType(ValType valType);

/******************
* Abstract Syntax Tree Beginning 
*******************/
class ASTConstDecl;
class ASTVarDecl;
class ASTProcDecl;
class ASTStmt;
class ASTItem;
class ASTParam;
class ASTExpr;
class ASTValDecl;
class ASTProgram;
template <typename T>
class SymbolTable;
class Info;
class Val;

void lvalue(string id, SymbolTable<Info>* t);
void printChar(string str);

/*****************
* Block
******************/
class ASTBlock {
public:
	ASTBlock(list<ASTConstDecl*> c, list<ASTVarDecl*> v, list<ASTProcDecl*> p, list<ASTStmt*> b);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);

	list<ASTConstDecl*> consts;
	list<ASTVarDecl*> vars;
	list<ASTProcDecl*> procs;
	list<ASTStmt*> body;
	NodeTypes node;
};

/*****************
* Constant Declaration
*******************/
class ASTConstDecl {
public:
	ASTConstDecl(string i, int v);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);

	string id;
	int value;
	NodeTypes node;
};

/**************
* Expressions 
****************/
class ASTExpr {
public:
	ASTExpr();
	virtual string render(string indent) = 0;
	virtual Value* interpret(SymbolTable<Value>* t) = 0;
	virtual Val* typecheck(SymbolTable<Val>* t) = 0;
	virtual Info* generate(SymbolTable<Info>* t) = 0;
	virtual Info* generate(SymbolTable<Info>* t, string y, string n) = 0;
	NodeTypes node;
};

class BinOp : public ASTExpr {
public:
	BinOp(ASTExpr* l, Op2 o, ASTExpr* r);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);
	Info* generate(SymbolTable<Info>* t, string y, string n);
	ASTExpr* left;
	Op2 op;
	ASTExpr* right;
};

class IDExpr : public ASTExpr {
public:
	IDExpr(string i);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);
	Info* generate(SymbolTable<Info>* t, string y, string n);
	string id;
};

class Num : public ASTExpr {
public:
	Num(int v);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);
	Info* generate(SymbolTable<Info>* t, string y, string n);
	int value;
};

class UnOp : public ASTExpr {
public:
	UnOp(Op1 o, ASTExpr* e);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);
	Info* generate(SymbolTable<Info>* t, string y, string n);
	Op1 op;
	ASTExpr* expr;

};

class True : public ASTExpr {
public:
	True();
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);
	Info* generate(SymbolTable<Info>* t, string y, string n);
	bool boolean;
};

class False : public ASTExpr {
public:
	False();
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);
	Info* generate(SymbolTable<Info>* t, string y, string n);
	bool boolean;
};

/*********************************
* Items
***********************************/
class ASTItem {
public:
	ASTItem();
	virtual string render(string indent) = 0;
	NodeTypes node;
};

class ExprItem : public ASTItem {
public:
	ExprItem(ASTExpr* e);
	string render(string indent);
	ASTExpr* expr;
};

class StringItem : public ASTItem {
public:
	StringItem(string m);
	string render(string indent);
	string message;
};


/***********************************
* Parameter 
*************************************/
class ASTParam {
public:
	ASTParam();
	virtual string render(string indent) = 0;
	virtual Info* generate(SymbolTable<Info>* t) = 0;
	string id;
	NodeTypes node;
	Type type;
};

class ValParam : public ASTParam {
public:
	ValParam(string i, Type t);
	string render(string indent);
	Info* generate(SymbolTable<Info>* t);
};

class VarParam : public ASTParam {
public:
	VarParam(string i, Type t);
	string render(string indent);
	Info* generate(SymbolTable<Info>* t);
};

/******************
* Procedure Declaration 
********************/
class ASTProcDecl {
public:
	ASTProcDecl(string i, list<ASTParam*> p, ASTBlock* b);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);
	string id;
	list<ASTParam*> params;
	ASTBlock* block; 
	NodeTypes node;
};

/*********************
* Program
***********************/
class ASTProgram {
public:
	ASTProgram(string n, ASTBlock* b);
	string render(string indent);
	Value* interpret();
	Val* typecheck();
	Info* generate();
	string name;
	ASTBlock* block;
	NodeTypes node;
};

/****************
* Statements 
******************/
class ASTStmt {  
public:
	ASTStmt();
	virtual string render(string indent) = 0;
	virtual Value* interpret(SymbolTable<Value>* t) = 0;
	virtual Val* typecheck(SymbolTable<Val>* t) = 0;
	virtual Info* generate(SymbolTable<Info>* t) = 0;
};

class Assign : public ASTStmt {
public:
	Assign(string i, ASTExpr* e);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);
	string id;
	ASTExpr* expr;
	NodeTypes node;
};

class Call : public ASTStmt {
public:
	Call(string i, list<ASTExpr*> a);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	void call(list<ASTParam*> p, ASTBlock* b, list<Value*> v, SymbolTable<Value>* t);
	void match(list<ASTParam*> params, list<Val*> args);
	void setup(list<ASTParam*> params, list<ASTExpr*> args, SymbolTable<Info>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);

	string id;
	list<ASTExpr*> args;
};


class IfThen : public ASTStmt {
public:
	IfThen(ASTExpr* t, ASTStmt* tc);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);
	ASTExpr* test;
	ASTStmt* trueClause;
	NodeTypes node;
};

class IfThenElse : public ASTStmt {
public:
	IfThenElse(ASTExpr* t, ASTStmt* tc, ASTStmt* fc);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);

	ASTExpr* test;
	ASTStmt* trueClause;
	ASTStmt* falseClause;
	NodeTypes node;
};

class Print : public ASTStmt {
public:
	Print(list<ASTItem*> i);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);
	list<ASTItem*> items;
	NodeTypes node;
};

class Prompt : public ASTStmt {
public:
	Prompt(string m);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);
	string message;
	NodeTypes node;

};

class Prompt2 : public ASTStmt {
public:
	Prompt2(string m, string i);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);
	string message;
	string id;
	NodeTypes node;

};

class Seq : public ASTStmt {
public:
	Seq(list<ASTStmt*> b);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);

	list<ASTStmt*> body;
	NodeTypes node;

};

class While : public ASTStmt {
public:
	While(ASTExpr* t, ASTStmt* b);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);

	ASTExpr* test;
	ASTStmt* body;
	NodeTypes node;

};

/***********************
* Variable Declarations 
************************/
class ASTVarDecl {
public:
	ASTVarDecl(string i, Type t);
	string render(string indent);
	Value* interpret(SymbolTable<Value>* t);
	Val* typecheck(SymbolTable<Val>* t);
	Info* generate(SymbolTable<Info>* t);

	string id;
	Type typ;
	NodeTypes node;
};

/***********************
* Variable Declarations
************************/
class Val {
public: 
	Val();
	virtual bool isVariable() = 0;
	ValType valtype;
};

class IntVal : public Val {
public:
	IntVal();
	bool isVariable();
};

class BoolVal : public Val {
public:
	BoolVal();
	bool isVariable();
};

class IntVar : public Val {
public:
	IntVar();
	bool isVariable();
};

class BoolVar : public Val {
public:
	BoolVar();
	bool isVariable();
};

class ProcVal : public Val {
public:
	ProcVal(list<ASTParam*>	p);
	bool isVariable();
	list<ASTParam*> params;
};

/***********************
* Info Declarations
************************/
class Info {
public:
	Info();
	InfoType infotype;
	virtual ~Info();
};

class ConstInfo : public Info {
public: 
	ConstInfo(int cnst);
	int constant;
};

class VarInfo : public Info {
public:
	VarInfo(int l, int o);
	int level;
	int offset;
};

class RefInfo : public Info {
public: 
	RefInfo(int l, int o);
	int level;
	int offset;
};

class ProcInfo : public Info {
public:
	ProcInfo(string l, list<ASTParam*> p);
	string label;
	list<ASTParam*> params;
};
#endif /* AST_H_ */
