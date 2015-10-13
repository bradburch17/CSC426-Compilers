#include <iostream>
#include "WhileStmt.h"
#include "AssignIDStmt.h"

using namespace std;

WhileStmt::WhileStmt(string t, ASTStmt b) {
	test = t;
	body = b;
}

string WhileStmt::render(string indent)
{
	return string();
}
