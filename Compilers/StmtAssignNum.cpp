#include "StmtAssignNum.h"
#include <iostream>

using namespace std;

StmtAssignNum::StmtAssignNum(string l, string n) {
	lhs = l;
	num = n;
}

string StmtAssignNum::render(string indent)
{
	return indent + "ASSIGN_NUM " + lhs + " = " + num + "\n";
}
