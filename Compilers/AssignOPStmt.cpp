#include "AssignOPStmt.h"
#include <iostream>
#include "AssignIDStmt.h"

using namespace std;

AssignOPStmt::AssignOPStmt(string l, string i1, string o, string i2) {
	lhs = l;
	id1 = i1;
	op = o;
	id2 = i2;
}

string AssignOPStmt::render(string indent)
{
	return string();
}
