//#include "ASTProcDel.h"
//#include "ASTBlock.h"
//#include <iostream>
//
//using namespace std;
//
//ASTProcDecl::ASTProcDecl(string i, list<ASTParam*> p, ASTBlock* b)
//{
//	id = i;
//	params = p;
//	block = b;
//}
//
//string ASTProcDecl::render(string indent)
//{
//	string result = indent + "Proc " + id + "\n";
//	for (ASTParam* p : params) {
//		result += p->render(indent + "  ");
//	}
//	result += block->render(indent + "  ");
//	return result;
//}
