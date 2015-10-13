#include "UntilStmt.h"
#include "AssignIDStmt.h"
#include <iostream>

using namespace std;

UntilStmt::UntilStmt(string t, ASTStmt b) {
	test = t;
	body = b;
}

string UntilStmt::render(string indent)
{
	return string();
}
