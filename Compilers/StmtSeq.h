/*
* StmtSeq.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef StmtSeq_H_
#define StmtSeq_H_

#include <string>
#include <iosfwd>
#include "ASTStmt.h"

using namespace std;

class StmtSeq : public ASTStmt {
public:
	//ArrayList in C++?
	string render(string indent);

private:
	//ArrayList

};
#endif /* StmtSeq_H_ */
