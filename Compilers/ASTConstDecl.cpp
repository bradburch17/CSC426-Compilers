#include "ASTConstDecl.h"

ASTConstDecl::ASTConstDecl(string i, int v)
{
	id = i;
	value = v;
}

string ASTConstDecl::render(string indent)
{
	return string();
}
