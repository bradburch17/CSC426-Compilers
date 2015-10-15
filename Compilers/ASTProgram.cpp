#include <iostream>
#include "ASTProgram.h"

using namespace std;

ASTProgram::ASTProgram(string n, ASTBlock* b)
{
	name = n;
	block = b;
}

string ASTProgram::render(string indent)
{
	string result = indent + "Program " + name + "\n";
	result += block->render(indent + "  ");
	return result;
}
