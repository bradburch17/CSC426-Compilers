/*
* StmtAssignNum.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef StmtAssignNum_H_
#define StmtAssignNum_H_

#include <iosfwd>
#include <string>
#include "ASTStmt.h"

using namespace std;

class StmtAssignNum : public ASTStmt {
public:
	StmtAssignNum(string l, string n);
	string render(string indent);
private:
	string lhs;
	string num;
};
#endif /* AssignNumStmt_H_ */
