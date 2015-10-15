#include <iostream>
#include "ASTConstDecl.h"

using namespace std;

ASTConstDecl::ASTConstDecl(string i, int v)
{
	id = i;
	value = v;
}

string ASTConstDecl::render(string indent)
{
	return indent + "Const " + id + " = " + to_string(value) +"\n";
}
