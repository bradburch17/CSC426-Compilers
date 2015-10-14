/*
* StmtIfStmt.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef StmtIfStmt_H_
#define StmtIfStmt_H_

#include <string>
#include <iosfwd>

#include "ASTStmt.h"

using namespace std;

class StmtIfStmt : public ASTStmt {
public:
	StmtIfStmt(string t, ASTStmt b);
	string render(string indent);

private:
	string test;
	ASTStmt body;
};
#endif /* StmtIfStmt_H_ */
