#include "StmtIfStmt.h"
#include <iostream>

using namespace std;

StmtIfStmt::StmtIfStmt(string t, ASTStmt b) {
	test = t;
	body = b;
}

string StmtIfStmt::render(string indent)
{
	string result = indent + "IF " + test + "\n";
	result += body.render(indent + "  ");
	return result;
}

