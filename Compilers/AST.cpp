/*
* AST.cpp
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/
#include <iostream>
#include <string>
#include <list>
#include <map>
#include "AST.h"
#include "SymbolTable.h"

using namespace std;

string checkOp1(Op1 op1)
{
	switch (op1) {
	case Neg: return "Neg";
	case Not: return "Not";
	}
}
string checkOp2(Op2 op2)
{
	switch (op2) {
	case EQ: return "EQ";
	case NE: return "NE";
	case LE: return "LE";
	case GE: return "GE";
	case LT: return "LT";
	case GT: return "GT";
	case Plus: return "Plus";
	case Minus: return "Minus";
	case Times: return "Times";
	case Div: return "Div";
	case Mod: return "Mod";
	case And: return "And";
	case Or: return "Or";
	}
}

string checkType(Type t) {
	switch (t) {
	case IntType: return "Int";
	case BoolType: return "Bool";
	}
}

string checkValueType(ValueType t) {
	switch (t) {
	case Undefined: return "Undefined Value";
	case IntegerValue: return "Integer Value";
	case BooleanValue: return "Boolean Value";
	case IntegerCell: return "Integer Cell";
	case BooleanCell: return "Boolean Cell";
	case ProcedureValue: return "Procedure Value";
	}
}

/************************
* Constructors 
*************************/
ASTBlock::ASTBlock(list<ASTConstDecl*> c, list<ASTVarDecl*> v, list<ASTProcDecl*> p, list<ASTStmt*> b)
{
	consts = c;
	vars = v;
	procs = p;
	body = b;
}


ASTConstDecl::ASTConstDecl(string i, int v)
{
	id= i;
	value = v;
}

ASTExpr::ASTExpr()
{
	expr = Expr;
}

BinOp::BinOp(ASTExpr * l, Op2 o, ASTExpr * r)
{
	left = l;
	op = o;
	right = r;
}

True::True()
{
	boolean = true;
}

False::False()
{
	boolean = false;
}

IDExpr::IDExpr(string i)
{
	id= i;
}

Num::Num(int v)
{
	value = v;
}

UnOp::UnOp(Op1 o, ASTExpr * e)
{
	op = o;
	expr = e;
}

ASTItem::ASTItem()
{
	item = Item;
}

ExprItem::ExprItem(ASTExpr * e)
{
	expr = e;
}

StringItem::StringItem(string m)
{
	message = m;
}

ASTParam::ASTParam()
{
	val = Val;
}

ValParam::ValParam(string i, Type t)
{
	id= i;
	type = t;
	val = Val;
}

VarParam::VarParam(string i, Type t)
{
	id= i;
	type = t;
}

ASTProgram::ASTProgram(string n, ASTBlock* b)
{
	name = n;
	block = b;
}

ASTStmt::ASTStmt()
{
}

ASTProcDecl::ASTProcDecl(string i, list<ASTParam*> p, ASTBlock* b)
{
	id= i;
	params = p;
	block = b;
}

Assign::Assign(string i, ASTExpr* e)
{
	id= i;
	expr = e;
}

Seq::Seq(list<ASTStmt*> b)
{
	body = b;
}

While::While(ASTExpr* t, ASTStmt * b)
{
	test = t;
	body = b;
}

IfThen::IfThen(ASTExpr * t, ASTStmt * tc)
{
	test = t;
	trueClause = tc;
}

IfThenElse::IfThenElse(ASTExpr * t, ASTStmt * tc, ASTStmt * fc)
{
	test = t;
	trueClause = tc;
	falseClause = fc;
}

Print::Print(list<ASTItem*> i)
{
	items = i;
}

Prompt::Prompt(string m)
{
	message = m;
}

Prompt2::Prompt2(string m, string i)
{
	message = m;
	id= i;
}

Call::Call(string i, list<ASTExpr*> a)
{
	id = i;
	args = a;
}

ASTVarDecl::ASTVarDecl(string i, Type t)
{
	id = i;
	typ = t;
}


/*****************
* Render 
******************/
string ASTProgram::render(string indent)
{
	string result = indent + "Program " + name + "\n";
	result += block->render(indent + "  ");
	return result;
}

string ASTBlock::render(string indent)
{
	string result = indent + "Block\n";
	for (ASTConstDecl* c : consts)
		result += c->render(indent + "  ");
	for (ASTVarDecl* v : vars)
		result += v->render(indent + "  ");
	for (ASTProcDecl* p : procs)
		result += p->render(indent + "  ");
	for (ASTStmt* b : body)
		result += b->render(indent + "  ");
	return result;
}

string ASTConstDecl::render(string indent)
{
	string result = indent + "Const " + id + " = " + to_string(value) + "\n";
	return result;
}

string ASTVarDecl::render(string indent)
{
	string result = indent + "Var " + id + " : " + checkType(typ) + "\n";
	return result;
}

string ASTProcDecl::render(string indent)
{
	string result = indent + "Proc " + id + "\n";
	for (ASTParam* p : params)
		result += p->render(indent + "  ");
	result += block->render(indent + "  ");
	return result;
}

string ValParam::render(string indent)
{
	string result = indent + "Val " + id + " : " + checkType(type) + "\n";
	return result;
}

string VarParam::render(string indent)
{
	string result = indent + "Var " + id + " : " + checkType(type) + "\n";
	return result;
}

string Assign::render(string indent)
{
	string result = indent + "Assign " + id + "\n";
	result += expr->render(indent + "  ");
	return result;
}

string Call::render(string indent)
{
	string result = indent + "Call " + id + "\n";
	for (ASTExpr* a : args)
		result += a->render(indent + "  ");
	return result;
}

string Seq::render(string indent)
{
	string result = indent + "Sequence\n";
	for (ASTStmt* b : body)
		result += b->render(indent + "  ");
	return result;
}

string IfThen::render(string indent)
{
	string result = indent + "IfThen\n";
	result += test->render(indent + "  ");
	result += trueClause->render(indent + "  ");
	return result;
}

string IfThenElse::render(string indent)
{
	string result = indent + "IfThenElse\n";
	result += test->render(indent + "  ");
	result += trueClause->render(indent + "  ");
	result += falseClause->render(indent + "  ");
	return result;
}

string While::render(string indent)
{
	string result = indent + "While\n";
	result += test->render(indent + "  ");
	result += body->render(indent + "  ");
	return result;
}

string Prompt::render(string indent)
{
	string result = indent + "Prompt " + message + "\n";
	return result;
}

string Prompt2::render(string indent)
{
	string result = indent + "Prompt2 " + message + ", " + id + "\n";
	return result;
}

string Print::render(string indent)
{
	string result = indent + "Print\n";
	for (ASTItem* i : items)
		result += i->render(indent + "  ");
	return result;
}

string ExprItem::render(string indent)
{
	string result = indent + "ExprItem\n";
	result += expr->render(indent + "  ");
	return result;
}

string StringItem::render(string indent)
{
	string result = indent + "StringItem " + message + "\n";
	return result;
}

string BinOp::render(string indent)
{
	string result = indent + "BinOp " + checkOp2(op) + "\n";
	result += left->render(indent + "  ");
	result += right->render(indent + "  ");
	return result;
}

string UnOp::render(string indent)
{
	string result = indent + "UnOp " + checkOp1(op) + "\n";
	result += expr->render(indent + "  ");
	return result;
}

string Num::render(string indent)
{
	string result = indent + "Num " + to_string(value) + "\n";
	return result;
}

string IDExpr::render(string indent)
{
	string result = indent + "Id " + id + "\n";
	return result;
}

string True::render(string indent)
{
	string result = indent + "True\n";
	return result;
}

string False::render(string indent)
{
	string result = indent + "False\n";
	return result;
}

/******************
* Interpreters 
********************/
Value * ASTProgram::interpret()
{
	SymbolTable t = SymbolTable();
	t.enter(name);
	block->interpret(t);
	t.exit();
	return NULL;
}

Value * ASTStmt::interpret(SymbolTable t)
{
	return NULL;
}

Value * ASTBlock::interpret(SymbolTable t)
{
	for (ASTConstDecl* c : consts)
		c->interpret(t);
	for (ASTVarDecl* v : vars)
		v->interpret(t);
	for (ASTProcDecl* p : procs)
		p->interpret(t);
	for (ASTStmt* s : body)
		s->interpret(t);
	return NULL;
}

Value * ASTConstDecl::interpret(SymbolTable t)
{
	t.bind(id, new IntValue(value));
	return NULL;
}

Value * ASTVarDecl::interpret(SymbolTable t)
{
	if (typ == IntType)
		t.bind(id, new IntCell(0));
	else 
		t.bind(id, new BoolCell(false));
	return NULL;
}

Value * ASTProcDecl::interpret(SymbolTable t)
{
	t.bind(id, new ProcValue(params, block));
	return NULL;
}

Value * Assign::interpret(SymbolTable t)
{
	Value* lhs = t.lookup(id);

	Value* rhs = expr->interpret(t);

	if (lhs->value == IntegerCell)
		lhs->setInt(rhs->getIntValue());
	else if (lhs->value == BooleanCell)
		lhs->setBool(rhs->getBoolValue());
	else
	{
		cout << "Error: Cannot find " << id << endl;

	}
	return NULL;
}

Value * Call::interpret(SymbolTable t)
{
	Value* look_up = t.lookup(id);

	if (look_up == NULL) {
		cout << "Error: Expected " << checkValueType(ProcedureValue) << endl;
	}

	if (look_up->value != ProcedureValue) {
		cout << "Error: Expected " << checkValueType(ProcedureValue) << endl;
	}

	ProcValue* val = dynamic_cast<ProcValue*>(t.lookup(id));
	list<Value*> arguments;

	for (ASTExpr* arg : args) {
		Value* v = arg->interpret(t);
		arguments.push_back(v);
	}


	if (val->param.size() != arguments.size()) {
		cout << "Error: Parameters do not match in " << id << endl;
	}

	t.enter(id);
	call(val->param, val->block, arguments, t);
	t.exit();
	return NULL;
}

Value * Seq::interpret(SymbolTable t)
{
	for (ASTStmt* b : body)
		b->interpret(t);
	return NULL;
}

Value * IfThen::interpret(SymbolTable t)
{
	Value* val = test->interpret(t);
	if (val->getBoolValue())
		trueClause->interpret(t);
	return NULL;
}

Value * IfThenElse::interpret(SymbolTable t)
{
	Value* value = test->interpret(t);
	if (value->getBoolValue())
		trueClause->interpret(t);
	else
		falseClause->interpret(t);
	return NULL;
}

Value * While::interpret(SymbolTable t) {
	Value* value = test->interpret(t);
	while (value->getBoolValue())
	{
		body->interpret(t);
		value = test->interpret(t);
	}
	return NULL;
}

Value * Prompt::interpret(SymbolTable t)
{
	string input;
	cout << message;
	getline(cin, input);
	return NULL;
}

Value * Prompt2::interpret(SymbolTable t)
{
	Value* lhs = t.lookup(id);
	string input;

	cout << message << " ";
	getline(cin, input);
	try	{
		lhs->setInt(stoi(input));
	}
	catch (invalid_argument)
	{
		cout << "Error: Input is not an interger" << endl;
		exit(1);
	}
	return NULL;
}

Value * Print::interpret(SymbolTable t)
{
	for (ASTItem* i : items) {
		if (i->item == Item) {
			ExprItem* item = dynamic_cast<ExprItem*>(i);
			Value* value = item->expr->interpret(t);
			cout << value->getIntValue();
			delete item;
		}
		else {
			StringItem* item = dynamic_cast<StringItem*>(i);
			cout << item->message;
		}
	}
	cout << endl;
	return NULL;
}

Value * BinOp::interpret(SymbolTable t)
{
	Value* lhs = left->interpret(t);
	Value* rhs = right->interpret(t);

	switch (op) {
	case And:	return new BoolValue(lhs->getBoolValue() && rhs->getBoolValue());
	case Or:	return new BoolValue(lhs->getBoolValue() || rhs->getBoolValue());
	case EQ:	return new BoolValue(lhs->getIntValue() == rhs->getIntValue());
	case NE:	return new BoolValue(lhs->getIntValue() != rhs->getIntValue());
	case LE:	return new BoolValue(lhs->getIntValue() <= rhs->getIntValue());
	case LT:	return new BoolValue(lhs->getIntValue() < rhs->getIntValue());
	case GE:	return new BoolValue(lhs->getIntValue() >= rhs->getIntValue());
	case GT:	return new BoolValue(lhs->getIntValue() > rhs->getIntValue());
	case Plus:	return new IntValue(lhs->getIntValue() + rhs->getIntValue());
	case Minus:	return new IntValue(lhs->getIntValue() - rhs->getIntValue());
	case Times:	return new IntValue(lhs->getIntValue() * rhs->getIntValue());
	case Div:	return new IntValue(lhs->getIntValue() / rhs->getIntValue());
	case Mod:	return new IntValue(lhs->getIntValue() % rhs->getIntValue());
	}
}

Value * UnOp::interpret(SymbolTable t)
{
	Value* value = expr->interpret(t);

	switch (op)
	{
	case Neg:
		return new IntValue(-value->getIntValue());
	case Not:
		return new BoolValue(!value->getBoolValue());
	}
}

Value * Num::interpret(SymbolTable t)
{
	return new IntValue(value);
}

Value * IDExpr::interpret(SymbolTable t)
{
	Value* val = t.lookup(id);
	if (val != NULL)
		return val;
	else {
		cout << "Error: Undefined" << id << endl;
		exit(1);
	}
}

Value * True::interpret(SymbolTable t)
{
	return new BoolValue(boolean);
}

Value * False::interpret(SymbolTable t)
{
	return new BoolValue(boolean);
}

/******************
* Call 
******************/
void Call::call(list<ASTParam*> param, ASTBlock * block, list<Value*> value, SymbolTable t)
{
	if (param.empty() && args.empty())
		block->interpret(t);
	else
	{
		ASTParam* par = param.front();
		Value* arg = value.front();
		param.pop_front();
		args.pop_front();

		if (par->val == Val)
		{
			ValParam* param = dynamic_cast<ValParam*>(par);

			if (param->type == IntType)
				t.bind(param->id, new IntCell(arg->getIntValue()));
			else
				t.bind(param->id, new BoolCell(arg->getBoolValue()));
		}
		else
		{
			VarParam* param = dynamic_cast<VarParam*>(par);

			if (param->type == IntType && arg->value == IntegerCell)
				t.bind(param->id, dynamic_cast<IntCell*>(arg));
			else if (param->type == BoolType && arg->value == BooleanCell)
				t.bind(param->id, dynamic_cast<BoolCell*>(arg));
			else
			{
				cout << "Error: Cannot pass " << checkValueType(arg->value) << endl;
			}
		}
		call(param, block, value, t);
	}
}


