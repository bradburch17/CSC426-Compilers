#include <iostream>
#include "ASTProgram.h"

using namespace std;

ASTProgram::ASTProgram(string n, ASTBlock b)
{
	name = n;
	block = b;
}

string ASTProgram::render(string indent)
{
	return string();
}
