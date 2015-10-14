#include "ASTProcDel.h"
#include <iostream>

using namespace std;

ASTProcDecl::ASTProcDecl(string i, list<ASTParam> p, ASTBlock b)
{
	id = i;
	params = p;
	block = b;
}

string ASTProcDecl::render(string indent)
{
	return string();
}
