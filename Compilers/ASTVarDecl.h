/*
* ASTVarDecl.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef ASTVarDecl_H_
#define ASTVarDecl_H_

#include <string>
#include <iosfwd>

#include "ASTType.h"

using namespace std;

class ASTVarDecl {
public:
	ASTVarDecl(string i, ASTType t);
	string render(string indent);

private:
	string id;
	ASTType typ;


};
#endif /* ASTVarDecl_H_ */
