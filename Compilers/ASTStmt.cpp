//#include <iostream>
//#include <string>
//#include "ASTStmt.h"
//
//using namespace std;
//
//ASTStmt::ASTStmt()
//{
//}
//
//Assign::Assign(string i, ASTExpr* e)
//{
//	id = i;
//	expr = e;
//}
//
//string Assign::render(string indent)
//{
//	string result = indent + "Assign " + id + "\n";
//	result += expr->render(indent + "  ");
//	return result;
//}
//
//Seq::Seq(list<ASTStmt*> b)
//{
//	body = b;
//}
//
//string Seq::render(string indent)
//{
//	string result = indent + "Sequence\n";
//	for (ASTStmt* b : body)
//		result += b->render(indent + "  ");
//	return result;
//}
//
//While::While(ASTExpr* t, ASTStmt * b)
//{
//	test = t;
//	body = b;
//}
//
//string While::render(string indent)
//{
//	string result = indent + "While\n";
//	result += test->render(indent + "  ");
//	result += body->render(indent + "  ");
//	return result;
//}
//
//IfThen::IfThen(ASTExpr * t, ASTStmt * tc)
//{
//	test = t;
//	trueClause = tc;
//}
//
//string IfThen::render(string indent)
//{
//	string result = indent + "IfThen\n";
//	result += test->render(indent + "  ");
//	result += trueClause->render(indent + "  ");
//	return result;
//}
//
//IfThenElse::IfThenElse(ASTExpr * t, ASTStmt * tc, ASTStmt * fc)
//{
//	test = t;
//	trueClause = tc;
//	falseClause = fc;
//}
//
//string IfThenElse::render(string indent)
//{
//	string result = indent + "IfThenElse\n";
//	result += test->render(indent + "  ");
//	result += trueClause->render(indent + "  ");
//	result += falseClause->render(indent + "  ");
//	return result;
//}
//
//Print::Print(list<ASTItem*> i)
//{
//	items = i;
//}
//
//string Print::render(string indent)
//{
//	string result = indent + "Print\n";
//	for (ASTItem* i : items)
//		result += i->render(indent + "  ");
//	return result;
//}
//
//Prompt::Prompt(string m)
//{
//	message = m;
//}
//
//string Prompt::render(string indent)
//{
//	return indent + "Prompt " + message + "/n";
//}
//
//Prompt2::Prompt2(string m, string i)
//{
//	message = m;
//	id = i;
//}
//
//string Prompt2::render(string indent)
//{
//	return indent + "Prompt 2 " + message + ", " + id + "\n";
//}
//
//Call::Call(string i, list<ASTExpr*> a)
//{
//	id = i;
//	args = a;
//}
//
//string Call::render(string indent)
//{
//	string result = indent + "Call " + id + "\n";
//	for (ASTExpr * a : args)
//		result += a->render(indent + "  ");
//	return result;
//}
