#include <iostream>
#include "ASTOp1.h"
#include "ASTExpr.h"
#include "ASTType.h"
#include <string>

using namespace std;

ASTExpr::ASTExpr()
{
}

string ASTExpr::checkOp1(Op1 op1)
{
	switch (op1) {
	case Neg: return "Neg";
	case Not: return "Not";
	}
}
string ASTExpr::checkOp2(Op2 op2)
{
	switch (op2) {
	case EQ: return "EQ";
	case NE: return "NE";
	case LE: return "LE";
	case GE: return "GE";
	case LT: return "LT";
	case GT: return "GT";
	case Plus: return "Plus";
	case Minus: return "Minus";
	case Times: return "Times";
	case Div: return "Div";
	case Mod: return "Mod";
	case And: return "And";
	case Or: return "Or";
	}
}

False::False()
{
	boolean = false;
}

string False::render(string indent)
{
	return indent + "False\n";
}

True::True()
{
	boolean = true;
}

string True::render(string indent)
{
	return indent + "True\n";
}

BinOp::BinOp(ASTExpr * l, ASTOp2 o, ASTExpr * r)
{
	left = l;
	op = o;
	right = r;
}

string BinOp::render(string indent)
{
	string result = indent + "BinOp " + checkOp2(op) + "\n";
	result += left->render(indent + "  ");
	result += right->render(indent + "  ");
	return result;
}

IDExpr::IDExpr(string i)
{
	id = i;
}

string IDExpr::render(string indent)
{
	return indent + "ID " + id + "\n";
}

Num::Num(int v)
{
	value = v;
}

string Num::render(string indent)
{
	return indent + "Num " + to_string(value) + "\n";
}

UnOp::UnOp(ASTOp1 o, ASTExpr * e)
{
	op = o;
	expr = e;
}

string UnOp::render(string indent)
{
	string result = indent + "Num " + checkOp1(op) + "\n";
	result += expr->render(indent + "  ");
	return result;
}
