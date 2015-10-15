/*
* ASTExpr.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef ASTExpr_H_
#define ASTExpr_H_

#include <string>
#include <iosfwd>
#include "ASTOp2.h"
#include "ASTOp1.h"
#include "ASTType.h"

using namespace std;

class ASTExpr {
public:
	ASTExpr();
	//enum Type{ IntType, BoolType };
	//enum Op1 { Neg, Not };
	//enum Op2 { EQ, NE, LE, GE, LT, GT, Plus, Minus, Times, Div, Mod, And, Or };

	//string checkType(Type type);
	string checkOp1(Op1 op1);
	string checkOp2(Op2 op2);
	virtual string render(string indent) = 0;

private:

};

class BinOp : public ASTExpr {
public: 
	BinOp(ASTExpr* l, Op2 o, ASTExpr* r);
	string render(string indent);

private: 
	ASTExpr* left;
	Op2 op;
	ASTExpr* right;
};

class IDExpr : public ASTExpr {
public:
	IDExpr(string i);
	string render(string indent);

private:
	string id;

};

class Num : public ASTExpr {
public:
	Num(int v);
	string render(string indent);

private:
	int value;

};

class UnOp : public ASTExpr {
public:
	UnOp(Op1 o, ASTExpr* e);
	string render(string indent);

private:
	Op1 op;
	ASTExpr* expr;

};

class True : public ASTExpr {
public: 
	True();
	string render(string indent);
private:
	bool boolean;
};

class False : public ASTExpr {
public: 
	False();
	string render(string indent);

private:
	bool boolean;
};
#endif /* ASTExpr_H_ */
