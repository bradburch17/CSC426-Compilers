#include <iostream>
#include <string>
#include <list>
#include <map>
#include "AST.h"

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
}

ValParam::ValParam(string i, Type t)
{
	id= i;
	type = t;
}

VarParam::VarParam(string i, Type t)
{
	id= i;
	type = t;
}

ASTProcDecl::ASTProcDecl(string i, list<ASTParam*> p, ASTBlock* b)
{
	id= i;
	params = p;
	block = b;
}

string ASTProgram::render(string indent)
{
	string result = indent + "Program " + name + "\n";
	result += block->render(indent + "  ");
	return result;
}

Value * ASTProgram::interpret()
{
	SymbolTable t = SymbolTable();
	t.enter(name);
	block->interpret(t);
	t.exit;
	return NULL;
}

ASTProgram::ASTProgram(string n, ASTBlock* b)
{
	name = n;
	block = b;
}

ASTStmt::ASTStmt()
{
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

//Render methods
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

SymbolTable::SymbolTable()
{
	scopes = stack<pair<string, map<string, Value*>*>>();
}


/*
* Enter pushes a new id onto the symbol table
*/
void SymbolTable::enter(string i)
{
	pair<string, map<string, Value*>*> symbols = make_pair(i, new map<string, Value*>());
	scopes.push(symbols);
}

/*
* Exit pops the top off of the symbol table 
*/
void SymbolTable::exit()
{
	scopes.pop();
}

void SymbolTable::bind(string id, Value * v)
{

}

/*
* Lookup returns the the binding for the id and if none found, 
* it returns a new value. 
*/
Value* SymbolTable::lookup(string id)
{
	map<string, Value*>* scope = scopes.top().second;
	if (scope->find(id) != scope->end) {
		return scope->at(id);
	}
	return new Value();
}

IntValue::IntValue(int i)
{
	integer = i;
	value = IntegerCell;
}

BoolValue::BoolValue(bool b)
{
	boolean = b;
	value = BooleanCell;
}

Value::Value()
{
	value = Undefined;
}

ProcValue::ProcValue(list<ASTParam*> p, ASTBlock * b)
{
	param = p;
	block = b;
	value = ProcedureValue;
}

IntCell::IntCell(int i)
{
	integer = i;
	value = IntegerCell;
}

void IntCell::set(int i)
{
	integer = i;
}

void BoolCell::set(bool b)
{
	boolean = b;
}

BoolCell::BoolCell(bool b)
{
	boolean = b;
	value = BooleanCell;
}
