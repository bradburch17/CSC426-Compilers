/*
* ASTStmt.h
*
*  Created on: October 8, 2015
*      Author: Brad Burch
*/

#ifndef ASTSTMT_H_
#define ASTSTMT_H_

#include <string>
#include <iosfwd>
#include <string>

using namespace std;

class ASTStmt {
public: 
	ASTStmt();
	virtual string render(string indent) = 0;

private:

};
#endif /* ASTStmt_H_ */
