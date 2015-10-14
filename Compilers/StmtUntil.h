/*
* StmtUntil.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef StmtUntil_H_
#define StmtUntil_H_

#include <string>
#include <iosfwd>

#include "ASTStmt.h"

using namespace std;

class StmtUntil : public ASTStmt {
public:
	StmtUntil(string t, ASTStmt b);
	string render(string indent);

private:
	string test;
	ASTStmt body;

};
#endif /* StmtUntil_H_ */
