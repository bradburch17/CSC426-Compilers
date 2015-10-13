/*
* WhileStmt.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef WhileStmt_H_
#define WhileStmt_H_

#include <string>
#include <iosfwd>
#include <string>
#include "ASTStmt.h"

using namespace std;

class WhileStmt : public ASTStmt {
public:
	WhileStmt(string t, ASTStmt b);
	string render(string indent);

private:
	string test;
	ASTStmt body;

};
#endif /* WhileStmt_H_ */
