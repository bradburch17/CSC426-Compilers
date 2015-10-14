/*
* ASTStmt.h
*
*  Created on: October 8, 2015
*      Author: Brad Burch
*/

#ifndef ASTSTMT_H_
#define ASTSTMT_H_

#include <string>
#include <iosfwd>

using namespace std;

class ASTStmt {
public: 
	virtual string render(string indent) = 0;
	ASTStmt();
//	ASTStmt assignNumStmt(string lhs, string num);

private:

};
#endif /* ASTStmt_H_ */