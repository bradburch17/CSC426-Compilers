/*
* AssignIDStmt.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef AssignIDStmt_H_
#define AssignIDStmt_H_

#include <string>
#include <iosfwd>
#include "ASTStmt.h"

using namespace std;

class AssignIDStmt : public ASTStmt {
public:
	AssignIDStmt(string l, string i);
	string render(string indent);
	
private:
	string lhs;
	string id;

};
#endif /* AssignIDStmt_H_ */
