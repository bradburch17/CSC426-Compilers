#include <iostream>
#include <string>
#include "ASTStmt.h"

using namespace std;

ASTStmt::ASTStmt()
{
}

ASTStmt * ASTStmt::assignNumStmt(string lhs, string num)
{

	return nullptr;
}

ASTStmt * ASTStmt::assignIDStmt(string l, string i)
{
	return nullptr;
}

ASTStmt * ASTStmt::assignOpStmt(string lhs, string id1, string op, string id2)
{
	return nullptr;
}

ASTStmt * ASTStmt::seqStmt(list<ASTStmt*> stmts)
{
	return nullptr;
}

ASTStmt * ASTStmt::whileStmt(string test, ASTStmt * body)
{
	return nullptr;
}

ASTStmt * ASTStmt::ifStmt(string test, ASTStmt * body)
{
	return nullptr;
}

ASTStmt * ASTStmt::untilStmt(string test, ASTStmt * body)
{
	return nullptr;
}

AssignID::AssignID(string l, string i)
{
	lhs = l;
	id = i;
}

string AssignID::render(string indent)
{
	return indent + "ASSIGN_ID " + lhs + " = " + id + "\n";
}

AssignNum::AssignNum(string l, string n)
{
	lhs = l;
	num = n;
}

string AssignNum::render(string indent)
{
	return indent + "ASSIGN_NUM " + lhs + " = " + num + "\n";
}

IfStmt::IfStmt(string t, ASTStmt* b) {
	test = t;
	body = b;
}

string IfStmt::render(string indent)
{
	string result = indent + "IF " + test + "\n";
	result += body.render(indent + "  ");
	return result;
}

string Seq::render(string indent)
{
	string result = indent + "SEQ\n";
	for (ASTStmt* stmt : stmts) {
		result += stmt.render(indent + "  ");
	}
	return result;
}

Until::Until(string t, ASTStmt * b)
{
	test = t;
	body = b;
}

string Until::render(string indent)
{
	string result = indent + "UNTIL " + test + "\n";
	result += body.render(indent + "  ");
	return result;
}

While::While(string t, ASTStmt * b)
{
	test = t;
	body = b;
}

string While::render(string indent)
{
	string result = indent + "WHILE " + test + "\n";
	result += body.render(indent + "  ");
	return result;
}
