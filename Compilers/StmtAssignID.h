/*
* StmtAssignID.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef StmtAssignID_H_
#define StmtAssignID_H_

#include <string>
#include <iosfwd>
#include "ASTStmt.h"

using namespace std;

class StmtAssignID : public ASTStmt {
public:
	StmtAssignID(string l, string i);
	string render(string indent);
	
private:
	string lhs;
	string id;

};
#endif /* StmtAssignID_H_ */
