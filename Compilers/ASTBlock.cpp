#include <iostream>
#include "ASTBlock.h"

using namespace std;

ASTBlock::ASTBlock(list<ASTConstDecl*> c, list<ASTVarDecl*> v, list<ASTProcDecl*> p, list<ASTStmt*> b)
{
	consts = c;
	vars = v;
	procs = p;
	body = b;
}

string ASTBlock::render(string indent)
{
	string result = indent + "Block\n";
	for (ASTConstDecl* c : consts)
		result += c->render(indent + "  ");
	for (ASTVarDecl* v : vars)
		result += v->render(indent + "  ");
	for (ASTProcDecl* p : procs)
		result += p->render(indent + "  ");
	for (ASTStmt* b : body)
		result += b->render(indent + "  ");
	return result;
}
