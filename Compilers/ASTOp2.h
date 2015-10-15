/*
* ASTOp2.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef ASTOp2_H_
#define ASTOp2_H_

#include <string>
#include <iosfwd>

using namespace std;

class ASTOp2 {
public:
	enum Op2 {EQ, NE, LE, GE, LT, GT, Plus, Minus, Times, Div, Mod, And, Or};
	string nameCheck(Op2 op2);
private:


};
#endif /* ASTOp2_H_ */
