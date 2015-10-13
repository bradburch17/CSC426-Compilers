/*
* IfStmt.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef IfStmt_H_
#define IfStmt_H_

#include <string>
#include <iosfwd>
#include <string>
#include "ASTStmt.h"

using namespace std;

class IfStmt : public ASTStmt {
public:
	IfStmt(string t, ASTStmt b);
	string render(string indent);

private:
	string test;
	ASTStmt body;
};
#endif /* IfStmt_H_ */
