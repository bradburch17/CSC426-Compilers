#include <iostream>
#include "AssignIDStmt.h"
#include "ASTStmt.h"

using namespace std;

AssignIDStmt::AssignIDStmt(string l, string i) {
	lhs = l;
	id = i;
}

string AssignIDStmt::render(string indent)
{
	return string();
}


