#include "ASTParam.h"
#include "ASTExpr.h"
#include "ASTType.h"
#include <iostream>

using namespace std;


string checkType(Type t) {
	switch (t) {
	case IntType: return "Int";
	case BoolType: return "Bool";
	}
}

ASTParam::ASTParam()
{
}

ValParam::ValParam(string i, Type t)
{
	id = i;
	type = t;
}

string ValParam::render(string indent)
{
	return indent + "Val " + id + ":" + checkType(type) + "\n";
}

VarParam::VarParam(string i, Type t)
{
	id = i;
	type = t;
}

string VarParam::render(string indent)
{
	return indent + "Var " + id + ":" + checkType(type) + "\n";
}
