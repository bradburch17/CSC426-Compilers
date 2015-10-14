/*
* ASTExpr.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef ASTExpr_H_
#define ASTExpr_H_

#include <string>
#include <iosfwd>

using namespace std;

class ASTExpr {
public:
	ASTExpr();
	virtual string render(string indent) = 0;

private:


};
#endif /* ASTExpr_H_ */
