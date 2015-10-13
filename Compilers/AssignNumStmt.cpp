#include "AssignNumStmt.h"
#include <iostream>
#include "AssignIDStmt.h"

using namespace std;

AssignNumStmt::AssignNumStmt(string l, string n) {
	lhs = l;
	num = n;
}

string AssignNumStmt::render(string indent)
{
	return string();
}
