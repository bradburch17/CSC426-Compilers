#include "AssignOPStmt.h"
#include <iostream>

using namespace std;

AssignOPStmt::AssignOPStmt(string l, string i1, string o, string i2) {
	lhs = l;
	id1 = i1;
	op = o;
	id2 = i2;
}

string AssignOPStmt::render(string indent)
{
	return indent + "ASSIGN_OP " + lhs + " = " + id1 + " " + op + " " + id2 + "\n";
}
