#include "StmtUntil.h"
#include <iostream>

using namespace std;

StmtUntil::StmtUntil(string t, ASTStmt b) {
	test = t;
	body = b;
}

string StmtUntil::render(string indent)
{
	string result = indent + "UNTIL " + test + "\n";
	result += body.render(indent + "  ");
	return result;
}
