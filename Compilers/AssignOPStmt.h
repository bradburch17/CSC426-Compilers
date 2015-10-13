/*
* AssignOPStmt.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef AssignOPStmt_H_
#define AssignOPStmt_H_

#include <string>
#include <iosfwd>
#include <string>
#include "ASTStmt.h"

using namespace std;

class AssignOPStmt : public ASTStmt {
public:
	AssignOPStmt(string l, string i1, string o, string i2);
	string render(string indent);
private:
	string lhs;
	string id1;
	string op;
	string id2;

};
#endif /* AssignIDStmt_H_ */
