/*
* AssignIDStmt.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef UntilStmt_H_
#define UntilStmt_H_

#include <string>
#include <iosfwd>
#include <string>
#include "ASTStmt.h"

using namespace std;

class UntilStmt : public ASTStmt {
public:
	UntilStmt(string t, ASTStmt b);
	string render(string indent);

private:
	string test;
	ASTStmt body;

};
#endif /* UntilStmt_H_ */
