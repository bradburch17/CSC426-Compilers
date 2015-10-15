/*
* ASTProcDecl.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef ASTProcDecl_H_
#define ASTProcDecl_H_

#include <string>
#include <iosfwd>
#include <list>

#include "ASTParam.h"

class ASTBlock;

using namespace std;

class ASTProcDecl {
public:
	ASTProcDecl(string i, list<ASTParam*> p, ASTBlock* b);
	string render(string indent);

private:
	string id;
	list<ASTParam*> params;
	ASTBlock block; //throws an error because undefined class. 


};
#endif /* ASTProcDecl_H_ */
