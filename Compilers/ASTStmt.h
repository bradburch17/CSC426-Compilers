///*
//* ASTStmt.h
//*
//*  Created on: October 8, 2015
//*      Author: Brad Burch
//*/
//
//#ifndef ASTSTMT_H_
//#define ASTSTMT_H_
//
//#include <string>
//#include <iosfwd>
//#include <list>
//#include "ASTExpr.h"
//#include "ASTItem.h"
//
//using namespace std;
//
//class ASTStmt { //Must use pointers when working with virtual functions! 
//public: 
//	virtual string render(string indent) = 0;
//	ASTStmt();
//
//};
//
//class Assign : public ASTStmt {
//public:
//	Assign(string i, ASTExpr* e);
//	string render(string indent);
//
//private:
//	string id;
//	ASTExpr* expr;
//};
//
//class Call : public ASTStmt {
//public: 
//	Call(string i, list<ASTExpr*> a);
//	string render(string indent);
//
//private: 
//	string id;
//	list<ASTExpr*> args;
//};
//
//
//class IfThen : public ASTStmt {
//public: 
//	IfThen(ASTExpr* t, ASTStmt* tc);
//	string render(string indent);
//private: 
//	ASTExpr* test;
//	ASTStmt* trueClause;
//};
//
//class IfThenElse : public ASTStmt {
//public: 
//	IfThenElse(ASTExpr* t, ASTStmt* tc, ASTStmt* fc);
//	string render(string indent);
//
//private: 
//	ASTExpr* test;
//	ASTStmt* trueClause;
//	ASTStmt* falseClause;
//};
//
//class Print : public ASTStmt {
//public: 
//	Print(list<ASTItem*> i);
//	string render(string indent);
//
//private: 
//	list<ASTItem*> items;
//
//};
//
//class Prompt : public ASTStmt {
//public: 
//	Prompt(string m);
//	string render(string indent);
//private: 
//	string message;
//
//};
//
//class Prompt2 : public ASTStmt {
//public: 
//	Prompt2(string m, string i);
//	string render(string indent);
//
//private: 
//	string message;
//	string id;
//
//};
//
//class Seq : public ASTStmt {
//public:
//	Seq(list<ASTStmt*> b);
//	string render(string indent);
//
//private:
//	list<ASTStmt*> body;
//
//};
//
//class While : public ASTStmt {
//public:
//	While(ASTExpr* t, ASTStmt* b);
//	string render(string indent);
//
//private:
//	ASTExpr* test;
//	ASTStmt* body;
//
//};
//
//#endif /* ASTStmt_H_ */
//
//
