/*
* SeqStmt.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef SeqStmt_H_
#define SeqStmt_H_

#include <string>
#include <iosfwd>
#include <string>
#include "ASTStmt.h"

using namespace std;

class SeqStmt : public ASTStmt {
public:
	//ArrayList in C++?
	string render(string indent);

private:
	//ArrayList

};
#endif /* SeqStmt_H_ */
