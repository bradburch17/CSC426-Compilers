/*
* AssignNumStmt.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef AssignNumStmt_H_
#define AssignNumStmt_H_

#include <string>
#include <iosfwd>
#include <string>
#include "ASTStmt.h"

using namespace std;

class AssignNumStmt : public ASTStmt {
public:
	AssignNumStmt(string l, string n);
	string render(string indent);
private:
	string lhs;
	string num;
};
#endif /* AssignNumStmt_H_ */
