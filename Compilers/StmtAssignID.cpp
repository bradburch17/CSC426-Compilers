#include <iostream>
#include "StmtAssignID.h"
#include "ASTStmt.h"

using namespace std;

StmtAssignID::StmtAssignID(string l, string i)
{
	lhs = l;
	id = i;
}

string StmtAssignID::render(string indent)
{
	return indent + "ASSIGN_ID " + lhs + " = " + id + "\n";
}
