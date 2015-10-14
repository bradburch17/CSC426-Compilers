#include "ASTProgram.h"

ASTProgram::ASTProgram(string n, ASTBlock b)
{
	name = n;
	block = b;
}

string ASTProgram::render(string indent)
{
	return string();
}
