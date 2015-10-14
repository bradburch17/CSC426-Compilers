#include <iostream>
#include "ASTBlock.h"

using namespace std;

ASTBlock::ASTBlock(list<ASTConstDecl> c, list<ASTVarDecl> v, list<ASTProcDecl> p, list<ASTStmt> b)
{
	consts = c;
	vars = v;
	procs = p;
	body = b;
}

string ASTBlock::render(string indent)
{
	return string();
}
