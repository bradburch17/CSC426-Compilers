#include "IfStmt.h"
#include "AssignIDStmt.h"
#include <iostream>

using namespace std;

IfStmt::IfStmt(string t, ASTStmt b) {
	test = t;
	body = b;
}

string IfStmt::render(string indent)
{
	return string();
}
