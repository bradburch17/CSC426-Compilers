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
#include <list>

using namespace std;

class ASTStmt { //Must use pointers when working with virtual functions! 
public: 
	virtual string render(string indent) = 0;
	ASTStmt();
	ASTStmt* assignNumStmt(string lhs, string num);
	ASTStmt* assignIDStmt(string lhs, string id);
	ASTStmt* assignOpStmt(string lhs, string id1, string op, string id2);
	ASTStmt* seqStmt(list<ASTStmt*> stmts);
	ASTStmt* whileStmt(string test, ASTStmt* body);
	ASTStmt* ifStmt(string test, ASTStmt* body);
	ASTStmt* untilStmt(string test, ASTStmt* body);

private:

};
/*
We can add the class declarations for everything that is going to use this abstract class in here, make it neat 
*/
class AssignID : public ASTStmt {
public:
	AssignID(string l, string i);
	string render(string indent);

private:
	string lhs;
	string id;

};

class AssignNum : public ASTStmt {
public:
	AssignNum(string l, string n);
	string render(string indent);
private:
	string lhs;
	string num;
};

class Call : public ASTStmt {
public: 

private: 

};

class IfStmt : public ASTStmt {
public:
	IfStmt(string t, ASTStmt* b);
	string render(string indent);

private:
	string test;
	ASTStmt* body;
};

class IfThen : public ASTStmt {
public: 

private: 

};

class IfThenElse : public ASTStmt {
public: 

private: 

};

class Print : public ASTStmt {
public: 

private: 

};

class Prompt : public ASTStmt {
public: 

private: 

};

class Prompt2 : public ASTStmt {
public: 

private: 

};

class Seq : public ASTStmt {
public:
	//ArrayList in C++?
	string render(string indent);

private:
	//ArrayList

};

class Until : public ASTStmt {
public:
	Until(string t, ASTStmt* b);
	string render(string indent);

private:
	string test;
	ASTStmt* body;
};

class While : public ASTStmt {
public:
	While(string t, ASTStmt* b);
	string render(string indent);

private:
	string test;
	ASTStmt* body;

};

#endif /* ASTStmt_H_ */


