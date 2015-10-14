/*
* ASTBlock.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef ASTBlock_H_
#define ASTBlock_H_

#include <string>
#include <iosfwd>
#include <list>
#include "ASTStmt.h"
#include "ASTConstDecl.h"
#include "ASTVarDecl.h"
#include "ASTProcDel.h"

using namespace std;

class ASTBlock {
public:
	ASTBlock(list<ASTConstDecl> c, list<ASTVarDecl> v, list<ASTProcDecl> p, list<ASTStmt> b);
	string render(string indent);

private:
	list<ASTConstDecl> consts;
	list<ASTVarDecl> vars;
	list<ASTProcDecl> procs;
	list<ASTStmt> body;

};
#endif /* ASTBlock_H_ */
