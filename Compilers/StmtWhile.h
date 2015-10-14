/*
* StmtWhile.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef StmtWhile_H_
#define StmtWhile_H_

#include <string>
#include <iosfwd>

#include "ASTStmt.h"

using namespace std;

class StmtWhile : public ASTStmt {
public:
	StmtWhile(string t, ASTStmt b);
	string render(string indent);

private:
	string test;
	ASTStmt body;

};
#endif /* StmtWhile_H_ */
