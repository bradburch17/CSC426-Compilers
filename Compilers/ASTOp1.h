/*
* ASTOp1.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef ASTOp1_H_
#define ASTOp1_H_

#include <string>
#include <iosfwd>

using namespace std;

class ASTOp1 {
public:
	enum Op1 {Neg, Not};
	string nameCheck(Op1 op1);

private:


};
#endif /* ASTOp1_H_ */
