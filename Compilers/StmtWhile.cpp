#include <iostream>
#include "StmtWhile.h"

using namespace std;

StmtWhile::StmtWhile(string t, ASTStmt b) {
	test = t;
	body = b;
}

string StmtWhile::render(string indent)
{
	string result = indent + "WHILE " + test + "\n";
	result += body.render(indent + "  ");
	return result;
}
