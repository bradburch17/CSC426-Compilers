/*
* ASTType.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef ASTType_H_
#define ASTType_H_

#include <string>
#include <iosfwd>

using namespace std;

class ASTType {
public:
	enum Type{IntType, BoolType};
	string nameCheck(Type t);
private:


};
#endif /* ASTType_H_ */
