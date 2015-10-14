#include "ASTVarDecl.h"

ASTVarDecl::ASTVarDecl(string i, ASTType t)
{
	id = i;
	typ = t;
}

string ASTVarDecl::render(string indent)
{
	return string();
}
