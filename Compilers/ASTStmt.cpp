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

ASTStmt * ASTStmt::assignIDStmt(string lhs, string id)
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
}

string AssignID::render(string indent)
{
	return string();
}

AssignNum::AssignNum(string l, string n)
{
}

string AssignNum::render(string indent)
{
	return string();
}

IfStmt::IfStmt(string t, ASTStmt* b) {

}

string IfStmt::render(string indent)
{
	return string();
}

string Seq::render(string indent)
{
	return string();
}

Until::Until(string t, ASTStmt * b)
{
}

string Until::render(string indent)
{
	return string();
}

While::While(string t, ASTStmt * b)
{
}

string While::render(string indent)
{
	return string();
}
