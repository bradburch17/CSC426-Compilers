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
	node = BlockNode;
}


ASTConstDecl::ASTConstDecl(string i, int v)
{
	id= i;
	value = v;
	node = ConstDeclNode;
}

ASTExpr::ASTExpr()
{
	node = ExprNode;
}

BinOp::BinOp(ASTExpr * l, Op2 o, ASTExpr * r)
{
	left = l;
	op = o;
	right = r;
	node = BinOpNode;
}

True::True()
{
	boolean = true;
	node = TrueNode;
}

False::False()
{
	boolean = false;
	node = FalseNode;
}

IDExpr::IDExpr(string i)
{
	id= i;
	node = IDNode;
}

Num::Num(int v)
{
	value = v;
	node = NumNode;
}

UnOp::UnOp(Op1 o, ASTExpr * e)
{
	op = o;
	expr = e;
	node = UnOpNode;
}

ASTItem::ASTItem()
{
	node = ItemNode;
}

ExprItem::ExprItem(ASTExpr * e)
{
	expr = e;
	node = ExprNode;
}

StringItem::StringItem(string m)
{
	message = m;
	node = StringNode;
}

ASTParam::ASTParam()
{
	node = ValParamNode;
}

ValParam::ValParam(string i, Type t)
{
	id= i;
	type = t;
	node = ValParamNode;
}

VarParam::VarParam(string i, Type t)
{
	id= i;
	type = t;
	node = VarParamNode;
}

ASTProgram::ASTProgram(string n, ASTBlock* b)
{
	name = n;
	block = b;
	node = ProgramNode;
}

ASTStmt::ASTStmt()
{
}

ASTProcDecl::ASTProcDecl(string i, list<ASTParam*> p, ASTBlock* b)
{
	id= i;
	params = p;
	block = b;
	node = ProcDeclNode;
}

Assign::Assign(string i, ASTExpr* e)
{
	id= i;
	expr = e;
	node = AssignNode;
}

Seq::Seq(list<ASTStmt*> b)
{
	body = b;
	node = SeqNode;
}

While::While(ASTExpr* t, ASTStmt * b)
{
	test = t;
	body = b;
	node = WhileNode;
}

IfThen::IfThen(ASTExpr * t, ASTStmt * tc)
{
	test = t;
	trueClause = tc;
	node = IfThenNode;
}

IfThenElse::IfThenElse(ASTExpr * t, ASTStmt * tc, ASTStmt * fc)
{
	test = t;
	trueClause = tc;
	falseClause = fc;
	node = IfThenElseNode;
}

Print::Print(list<ASTItem*> i)
{
	items = i;
	node = PrintNode;
}

Prompt::Prompt(string m)
{
	message = m;
	node = PromptNode;
}

Prompt2::Prompt2(string m, string i)
{
	message = m;
	id= i;
	node = Prompt2NOde;
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
	node = VarDeclNode;
}

Val::Val() {
	valtype = Undefined_Val;
}

BoolVal::BoolVal() {
	valtype = BoolVal_Val;
}

IntVar::IntVar() {
	valtype = IntVar_Val;
}

BoolVar::BoolVar() {
	valtype = BoolVar_Val;
}

ProcVal::ProcVal(list<ASTParam*> p) {
	params = p;
	valtype = ProcVal_Val;
}

IntVal::IntVal() {
	valtype = IntVal_Val;
}

Info::Info() {
	infotype = Undefined_Info;
}

ConstInfo::ConstInfo(int cnst) {
	constant = cnst;
	infotype = ConstInfo_Info;
}

VarInfo::VarInfo(int l, int o) {
	level = l;
	offset = o;
	infotype = VarInfo_Info;
}

RefInfo::RefInfo(int l, int o) {
	level = l;
	offset = o;
	infotype = RefInfo_Info;
}

ProcInfo::ProcInfo(string l, list<ASTParam*> p) {
	params = p;
	label = l;
	infotype = ProcInfo_Info;
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
	SymbolTable<Value>* t = new SymbolTable<Value>();
	t->entertbl(name);
	block->interpret(t);
	t->exittbl();

	return NULL;
}

Value * ASTBlock::interpret(SymbolTable<Value>* t)
{
	for (ASTConstDecl* c : consts)
		c->interpret(t);
	for (ASTVarDecl* v : vars)
		v->interpret(t);
	for (ASTProcDecl* p : procs)
		p->interpret(t);
	for (ASTStmt* b : body) {
		b->interpret(t);
	}
	return NULL;
}

Value * ASTConstDecl::interpret(SymbolTable<Value>* t)
{
	t->bind(id, new IntValue(value));
	return NULL;
}

Value * ASTVarDecl::interpret(SymbolTable<Value>* t)
{
	if (typ == IntType)
		t->bind(id, new IntCell(0));
	else
		t->bind(id, new BoolCell(false));
	return NULL;
}

Value * ASTProcDecl::interpret(SymbolTable<Value>* t)
{
	t->bind(id, new ProcValue(params, block));
	return NULL;
}

Value * Assign::interpret(SymbolTable<Value>* t)
{
	cout << "1" << endl;
	Value* lhs = t->lookup(id);
	cout << "2" << endl;
	Value* rhs = expr->interpret(t);
	cout << "3" << endl;

	if (lhs->value == IntegerCell)
		lhs->setInt(rhs->getIntValue());
	else if (lhs->value == BooleanCell)
		lhs->setBool(rhs->getBoolValue());
	else
	{
		cout << "Error: " << id << "is not " << checkValueType(lhs->value) << endl;
		exit(1);
	}
	return NULL;
}

Value * Call::interpret(SymbolTable<Value>* t)
{
	Value* lkup = t->lookup(id);
	
	ProcValue* value = dynamic_cast<ProcValue*>(lkup);
	list<Value*> arguments;

	if (lkup == NULL) {
		cout << "Error: Expected " << checkValueType(ProcedureValue) << " but found " << checkValueType(Undefined) << endl;
		exit(1);
	}
	if (lkup->value != ProcedureValue) {
		cout << "Error: Expected " << checkValueType(ProcedureValue) << " but found " << checkValueType(lkup->value) << endl;
		exit(1);
	}
	
	for (ASTExpr* arg : args) {
		Value* v = arg->interpret(t);
		arguments.push_back(v);
	}

	if (value->param.size() != arguments.size()) {
		cout << "Error: Number of parameters does not match " << id << " number of arguments." << endl;
		exit(1);
	}

	t.entertbl(id);
	call(value->param, value->block, arguments, t);
	t.exittbl();
	return NULL;
}

Value * Seq::interpret(SymbolTable<Value>* t)
{
	for (ASTStmt* b : body)
		b->interpret(t);
	return NULL;
}

Value * IfThen::interpret(SymbolTable<Value>* t)
{
	Value* value = test->interpret(t);
	if (value->getBoolValue())
		trueClause->interpret(t);
	return NULL;
}

Value * IfThenElse::interpret(SymbolTable<Value>* t)
{
	Value* value = test->interpret(t);
	if (value->getBoolValue())
		trueClause->interpret(t);
	else
		falseClause->interpret(t);
	return NULL;
}

Value * While::interpret(SymbolTable<Value>* t) {
	Value* value = test->interpret(t);
	while (!value->getBoolValue())/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		body->interpret(t);
		value = test->interpret(t);
	}
	return NULL;
}

Value * Prompt::interpret(SymbolTable<Value>* t)
{
	string input;
	cout << message;
	getline(cin, input);
	return NULL;
}

Value * Prompt2::interpret(SymbolTable<Value>* t)
{
	Value* lhs = t.lookup(id);
	string input;

	cout << message << " ";
	cin >> input;
	//getline(cin, input);

	try {
		int n = stoi(input);
		lhs->setInt(n);
		}
	catch (invalid_argument) {
		cout << "Error: Input is not an interger." << endl;
		exit(1);
	}
	return NULL;
}

Value * Print::interpret(SymbolTable<Value>* t)
{
	for (ASTItem* i : items) {
		if (i->node == ItemNode) {
			
			ExprItem* j = dynamic_cast<ExprItem*>(i);
			Value* value = j->expr->interpret(t); 
			cout << value->getIntValue();
			delete j;
		}
		else {
			StringItem* item = dynamic_cast<StringItem*>(i);
			cout << item->message;
		}
	}
	cout << endl;
	return NULL;
}

Value * BinOp::interpret(SymbolTable<Value>* t)
{
	Value* lhs = left->interpret(t);
	Value* rhs = right->interpret(t);

	switch (op)
	{
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

Value * UnOp::interpret(SymbolTable<Value>* t)
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

Value * Num::interpret(SymbolTable<Value>* t)
{
	return new IntValue(value);
}

Value * IDExpr::interpret(SymbolTable<Value>* t)
{
	Value* value = t->lookup(id);
	if (value != NULL)
		return value;
	else
	{
		cout << "Error: Undefined " << id << endl;
		exit(1);
	}
}

Value * True::interpret(SymbolTable<Value>* t)
{
	return new BoolValue(boolean);
}

Value * False::interpret(SymbolTable<Value>* t)
{
	return new BoolValue(boolean);
}

/******************
* Call 
******************/
void Call::call(list<ASTParam*> params, ASTBlock* block, list<Value*> args, SymbolTable<Value>* t)
{
	if (params.empty() && args.empty())
		block->interpret(t);
	else {
		ASTParam* par = params.front();
		Value* arg = args.front();
		params.pop_front();
		args.pop_front();

		if (par->node == ValParamNode) {
			ValParam* param = dynamic_cast<ValParam*>(par);

			if (param->type == IntType)
				t->bind(param->id, new IntCell(arg->getIntValue()));
			else
				t->bind(param->id, new BoolCell(arg->getBoolValue()));
		}
		else {
			VarParam* param = dynamic_cast<VarParam*>(par);

			if (param->type == IntType && arg->value == IntegerCell)
				t->bind(param->id, dynamic_cast<IntCell*>(arg));
			else if (param->type == BoolType && arg->value == BooleanCell)
				t->bind(param->id, dynamic_cast<BoolCell*>(arg));
			else {
				cout << "Error: Cannot pass " << checkValueType(arg->value)	<< " " << id << " to a parameter of type " << checkType(param->type) << endl;
				exit(1);
			}
		}
		call(params, block, args, t);
	}
}

/*****************
* Typecheckers 
******************/
Val* ASTProgram::typecheck() {
	SymbolTable<Val>* t = new SymbolTable<Val>;
	t->entertbl(name);
	block->typecheck(t);
	t->exittbl();
	return NULL;
}

Val* ASTBlock::typecheck(SymbolTable<Val>* t) {
	for (ASTConstDecl* c : consts)
		c->typecheck(t);
	for (ASTVarDecl* v : vars)
		v->typecheck(t);
	for (ASTProcDecl* p : procs)
		t->bind(p->id, new ProcVal(p->params));
	for (ASTProcDecl* p : procs)
		p->typecheck(t);
	for (ASTStmt* b : body)
		b->typecheck(t);
	return NULL;
}

Val* ASTConstDecl::typecheck(SymbolTable<Val>* t) {
	t->bind(id, new IntVal());
	return  NULL;
}


Val* ASTVarDecl::typecheck(SymbolTable<Val>* t) {
	if (typ == IntType)
		t->bind(id, new IntVar());
	else
		t->bind(id, new BoolVar());
	return NULL;
}


Val* ASTProcDecl::typecheck(SymbolTable<Val>* t)
{
	t->entertbl(id);
	for (ASTParam* p : params)
	{
		if (p->val == IntType) //////////////////////////////////////
			t->bind(p->id, new IntVar());//////////////////////////////////////////////////////////////////////////////////////
		else
			t->bind(p->id, new BoolVar());
	}

	block->typecheck(t);
	t->exittbl();
	return NULL;
}


Val* Assign::typecheck(SymbolTable<Val>* t)
{
	Val* lhs = t->lookup(id);
	Val* rhs = expr->typecheck(t);

	if (!lhs->isVariable())
	{
		cout << "Error: Expected " << id << endl;
		exit(1);
	}
	if (checkValueType(lhs->valtype).compare(checkValueType(rhs->valtype)) != 0)
	{
		cout << "Error: Cannot assign a value typed " << checkValueType(rhs->valtype) << " to " << id << endl;
		exit(1);
	}
	return NULL;
}


Val* Call::typecheck(SymbolTable<Val>* t)
{
	Val* look_up = t->lookup(id);


	if (look_up == NULL || look_up->valtype != ProcedureValue)
	{
		cout << "Error: No procedure identified" << endl;
		exit(1);
	}

	ProcVal* proc_val = dynamic_cast<ProcVal*>(look_up);
	list<Val*> arguments;


	for (ASTExpr* arg : args)
	{
		Val* v = arg->typecheck(t);
		arguments.push_back(v);
	}
	if (proc_val->params.size() != arguments.size())
	{
		cout << "(!) The number of parameters does not match the number of arguments of " << id << endl;
		exit(1);
	}


	match(proc_val->params, arguments);
	return NULL;
}

Val* Seq::typecheck(SymbolTable<Val>* t) {
	for (ASTStmt* b : body)
		b->typecheck(t);
	return NULL;
}

Val* IfThen::typecheck(SymbolTable<Val>* t) {
	Val* value = test->typecheck(t);
	if (checkValType(value->valtype).compare("bool") != 0) {
		cout << "Error: Expected boolean" << endl;
		exit(1);
	}
	trueClause->typecheck(t);
	return NULL;
}

Val* IfThenElse::typecheck(SymbolTable<Val>* t) {
	Val* value = test->typecheck(t);
	if (checkValType(value->valtype).compare("bool") != 0) {
		cout << "Error: Expected boolean" << endl;
		exit(1);
	}
	trueClause->typecheck(t);
	falseClause->typecheck(t);
	return NULL;
}

Val* While::typecheck(SymbolTable<Val>* t)
{
	Val* value = test->typecheck(t);
	if (checkValType(value->valtype).compare("bool") != 0) {
		cout << "Error: Expected boolean" << endl;
		exit(1);
	}
	body->typecheck(t);
	return NULL;
}

Val* Prompt::typecheck(SymbolTable<Val>* t) {
	return NULL;
}


Val* Prompt2::typecheck(SymbolTable<Val>* t) {
	Val* lhs = t->lookup(id);
	if (lhs->valtype != IntVar_Val) {
		cout << "(!) Expected an integer variable at " << line << ":" << column << endl;
		exit(1);
	}
	return NULL;
}

Val* Print::typecheck(SymbolTable<Val>* t) {
	for (ASTItem* i : items) {
		if (i->node == ItemNode) {
			ExprItem* item = dynamic_cast<ExprItem*>(i);
			Val* value = item->expr->typecheck(t);
			if (checkValueType(value->valtype).compare("int") != 0)
			{
				cout << "Error: Expected integer" << endl;
				exit(1);
			}
		}
		else {}
	}
	return NULL;
}

Val* BinOp::typecheck(SymbolTable<Val>* t) {
	Val* lhs = left->typecheck(t);
	Val* rhs = right->typecheck(t);

	switch (op)	{
	case And:
		if (checkValType(lhs->valtype).compare("bool") == 0 && checkValType(rhs->valtype).compare("bool") == 0) {}
		else {
			cout << "Error: Expected boolean" << endl;
			exit(1);
		}
		return new BoolVal();
	case Or:
		if (checkValType(lhs->valtype).compare("bool") == 0 && checkValType(rhs->valtype).compare("bool") == 0) {}
		else {
			cout << "Error: Expected boolean" << endl;
			exit(1);
		}
		return new BoolVal();
	case EQ:
		if (checkValType(lhs->valtype).compare("int") == 0 && checkValType(rhs->valtype).compare("int") == 0) {}
		else {
			cout << "Error: Expected integer" << endl;
			exit(1);
		}
		return new BoolVal();
	case NE:
		if (checkValType(lhs->valtype).compare("int") == 0 && checkValType(rhs->valtype).compare("int") == 0) {}
		else {
			cout << "Error: Expected integer" << endl;
			exit(1);
		}
		return new BoolVal();
	case LE:
		if (checkValType(lhs->valtype).compare("int") == 0 && checkValType(rhs->valtype).compare("int") == 0) {}
		else {
			cout << "Error: Expected integer" << endl;
			exit(1);
		}
		return new BoolVal();
	case LT:
		if (checkValType(lhs->valtype).compare("int") == 0 && checkValType(rhs->valtype).compare("int") == 0) {}
		else {
			cout << "Error: Expected integer" << endl;
			exit(1);
		}
		return new BoolVal();
	case GE:
		if (checkValType(lhs->valtype).compare("int") == 0 && checkValType(rhs->valtype).compare("int") == 0) {}
		else {
			cout << "Error: Expected integer" << endl;
			exit(1);
		}
		return new BoolVal();
	case GT:
		if (checkValType(lhs->valtype).compare("int") == 0 && checkValType(rhs->valtype).compare("int") == 0) {}
		else {
			cout << "Error: Expected integer" << endl;
			exit(1);
		}
		return new BoolVal();
	case Plus:
		if (checkValType(lhs->valtype).compare("int") == 0 && checkValType(rhs->valtype).compare("int") == 0) {}
		else {
			cout << "Error: Expected integer" << endl;
			exit(1);
		}
		return new IntVal();
	case Minus:
		if (checkValType(lhs->valtype).compare("int") == 0 && checkValType(rhs->valtype).compare("int") == 0) {}
		else {
			cout << "Error: Expected integer" << endl;
			exit(1);
		}
		return new IntVal();
	case Times:
		if (checkValType(lhs->valtype).compare("int") == 0 && checkValType(rhs->valtype).compare("int") == 0) {}
		else {
			cout << "Error: Expected integer" << endl;
			exit(1);
		}
		return new IntVal();
	case Div:
		if (checkValType(lhs->valtype).compare("int") == 0 && checkValType(rhs->valtype).compare("int") == 0) {}
		else {
			cout << "Error: Expected integer" << endl;
			exit(1);
		}
		return new IntVal();
	case Mod:
		if (checkValType(lhs->valtype).compare("int") == 0 && checkValType(rhs->valtype).compare("int") == 0) {}
		else {
			cout << "Error: Expected integer" << endl;
			exit(1);
		}
		return new IntVal();
	}
}

Val* UnOp::typecheck(SymbolTable<Val>* t) {
	Val* value = expr->typecheck(t);

	switch (op)	{
	case Neg:
		if (checkValType(value->valtype).compare("int") != 0)	{
			cout << "Error: Expected integer" << endl;
			exit(1);
		}
		return new IntVal();
	case Not:
		if (checkValType(value->valtype).compare("bool") != 0) {
			cout << "Error: Expected boolean" << endl;
			exit(1);
		}
		return new BoolVal();
	}
}

Val* Num::typecheck(SymbolTable<Val>* t) {
	return new IntVal();
}


Val* IDExpr::typecheck(SymbolTable<Val>* t) {
	return t->lookup(id);
}


Val* True::typecheck(SymbolTable<Val>* t) {
	return new BoolVal();
}


Val* False::typecheck(SymbolTable<Val>* t) {
	return new BoolVal();
}


/*****************
* Call Match
*******************/
void Call::match(list<ASTParam*> params, list<Val*> args) {
	if (params.empty() && args.empty()) {}
	else
	{
		ASTParam* par = params.front();
		Val* arg = args.front();
		params.pop_front();
		args.pop_front();

		if (par->node == ValParamNode)
		{
			if (checkValType(arg->valtype).compare("int") == 0 || checkValType(arg->valtype).compare("bool") == 0) {}
			else
			{
				cout << "Error: Expected either an integer or a boolean" << endl;
				exit(1);
			}
		}
		else // Node_VarParam
		{
			if (arg->valtype == IntVar_Val || arg->valtype == BoolVar_Val) {}
			else
			{
				cout << "Error: Expected integer variable or a boolean variable" << endl;
				exit(1);
			}
		}
		match(params, args);
	}
}

/***************
* isVariable() checcks variable types
*****************/
bool IntVal::isVariable() {
	return false;
}

bool BoolVal::isVariable() {
	return false;
}

bool IntVar::isVariable() {
	return true;
}

bool BoolVar::isVariable() {
	return true;
}

bool ProcVal::isVariable() {
	return false;
}

/**************
* Generate 
***************/
Info* ASTProgram::generate() {
	SymbolTable<Info>* t = new SymbolTable<Info>();
	t->entertbl(name);
	block->generate(t);
	t->exittbl();
	cout << "HALT" << endl;
	return NULL;
}

Info* ASTBlock::generate(SymbolTable<Info>* t) {
	string s = t->newLabel();
	cout << "BRANCH " << s << endl;

	for (ASTConstDecl* c : consts)
		c->generate(t);

	t->offset = 0;

	for (ASTVarDecl* v : vars)
		v->generate(t);
	for (ASTProcDecl* p : procs)
		t->bind(p->id, new ProcInfo(t->newLabel(), p->params));
	for (ASTProcDecl* p : procs)
		p->generate(t);

	cout << "LABEL " << s << endl;
	int n = (int)vars.size();
	int l = t->level;
	cout << "ENTER " << l << endl;
	cout << "RESERVE " << n << endl;

	for (ASTStmt* b : body)
		b->generate(t);

	cout << "DROP " << n << endl;
	cout << "EXIT " << l << endl;
	return NULL;
}

Info* ASTConstDecl::generate(SymbolTable<Info>* t) {
	t->bind(id, new ConstInfo(value));
	return NULL;
}

Info* ASTVarDecl::generate(SymbolTable<Info>* t) {
	t->offset -= 1;
	t->bind(id, new VarInfo(t->level, t->offset));
	return NULL;
}

Info* ASTProcDecl::generate(SymbolTable<Info>* t)
{
	ProcInfo* proc_info = dynamic_cast<ProcInfo*>(t->lookup (id));
	t->entertbl(id);
	t->param = 1;

	params.reverse();
	for (ASTParam* p : params)
		p->generate(t);

	cout << "LABEL " << proc_info->label << endl;
	block->generate(t);
	cout << "RETURN" << endl;
	t->exittbl();
	return NULL;
}

Info* ValParam::generate(SymbolTable<Info>* t) {
	t->param += 1;
	t->bind(id, new VarInfo(t->level, t->param));
	return NULL;
}

Info* VarParam::generate(SymbolTable<Info>* t) {
	t->param += 1;
	t->bind(id, new RefInfo(t->level, t->param));
	return NULL;
}

Info* Assign::generate(SymbolTable<Info>* t) {
	expr->generate(t);
	lvalue(id, t);
	cout << "STORE" << endl;
	return NULL;
}

Info* Call::generate(SymbolTable<Info>* t) {
	ProcInfo* proc_info = dynamic_cast<ProcInfo*>(t->lookup(id));
	setup(proc_info->params, args, t);
	cout << "CALL " << proc_info->label << endl;
	cout << "DROP " << proc_info->params.size() << endl;
	return NULL;
}

void Call::setup(list<ASTParam*> params, list<ASTExpr*> args, SymbolTable<Info>* t) {
	if (params.empty() && args.empty()) {}
	else {
		ASTParam* par = params.front();
		Expr* arg = args.front();
		params.pop_front();
		args.pop_front();

		if (par->node_type == Node_ValParam)
			arg->generate(t);
		else // Node_VarParam == reference parameter
		{
			IDExpr* ID2 = dynamic_cast<IDExpr*>(arg);
			lvalue(ID2->id, t);
		}
		setup(params, args, t);
	}
}

Info* Seq::generate(SymbolTable<Info>* t) {
	for (ASTStmt* b : body)
		b->generate(t);
	return NULL;
}

Info* IfThen::generate(SymbolTable<Info>* t) {
	string y = t->newLabel();
	string n = t->newLabel();
	test->generate(t, y, n);
	cout << "LABEL " << y << endl;
	trueClause->generate(t);
	cout << "LABEL " << n << endl;
	return NULL;
}

Info* IfThenElse::generate(SymbolTable<Info>* t) {
	string y = t->newLabel();
	string n = t->newLabel();
	string s = t->newLabel();
	test->generate(t, y, n);
	cout << "LABEL " << y << endl;
	trueClause->generate(t);
	cout << "BRANCH " << s << endl;
	cout << "LABEL " << n << endl;
	falseClause->generate(t);
	cout << "LABEL " << s << endl;
	return NULL;
}

Info* While::generate(SymbolTable<Info>* t) {
	string y = t->newLabel();
	string n = t->newLabel();
	string s = t->newLabel();
	cout << "LABEL " << s << endl;
	test->generate(t, y, n);
	cout << "LABEL " << y << endl;
	body->generate(t);
	cout << "BRANCH " << s << endl;
	cout << "LABEL " << n << endl;
	return NULL;
}

Info* Prompt::generate(SymbolTable<Info>* t) {
	printChar(message);
	cout << "READLINE" << endl;
	return NULL;
}

Info* Prompt2::generate(SymbolTable<Info>* t) {
	printChar(message + " ");
	cout << "READINT" << endl;
	lvalue(id, t);
	cout << "STORE" << endl;
	return NULL;
}

Info* Print::generate(SymbolTable<Info>* t) {
	for (ASTItem* i : items) {
		if (i->node_type == Node_ExprItem)
		{
			ExprItem* item = dynamic_cast<ExprItem*>(i);
			item->expr->generate(t);
			cout << "WRITEINT" << endl;
		}
		else // Node_StringItem
		{
			StringItem* item = dynamic_cast<StringItem*>(i);
			printChar(item->message);
		}
	}
	cout << "WRITELINE" << endl;
	return NULL;
}

Info* BinOp::generate(SymbolTable<Info>* t) {
	string y, n, s;
	switch (op)	{
	case Plus:
		left->generate(t);
		right->generate(t);
		cout << "ADD" << endl;
		break;
	case Minus:
		left->generate(t);
		right->generate(t);
		cout << "SUB" << endl;
		break;
	case Times:
		left->generate(t);
		right->generate(t);
		cout << "MUL" << endl;
		break;
	case Div:
		left->generate(t);
		right->generate(t);
		cout << "DIV" << endl;
		break;
	case Mod:
		left->generate(t);
		right->generate(t);
		cout << "MOD" << endl;
		break;
	default:
		y = t->newLabel();
		n = t->newLabel();
		s = t->newLabel();
		this->generate(t, y, n);
		cout << "LABEL " << y << endl;
		cout << "CONSTANT 1" << endl;
		cout << "BRANCH " << s << endl;
		cout << "LABEL " << n << endl;
		cout << "CONSTANT 0" << endl;
		cout << "LABEL " << s << endl;
		break;
	}
	return NULL;
}

Info* BinOp::generate(SymbolTable<Info>* t, string y, string n) {
	string s;
	switch (op) {
	case And:
		s = t->newLabel();
		left->generate(t, s, n);
		cout << "LABEL " << s << endl;
		right->generate(t, y, n);
		break;
	case Or:
		s = t->newLabel();
		left->generate(t, y, s);
		cout << "LABEL " << s << endl;
		right->generate(t, y, n);
		break;
	case EQ:
		left->generate(t);
		right->generate(t);
		cout << "SUB" << endl;
		cout << "BRANCHZERO " << y << endl;
		cout << "BRANCH " << n << endl;
		break;
	case NE:
		left->generate(t);
		right->generate(t);
		cout << "SUB" << endl;
		cout << "BRANCHZERO " << n << endl;
		cout << "BRANCH " << y << endl;
		break;
	case LT:
		left->generate(t);
		right->generate(t);
		cout << "SUB" << endl;
		cout << "BRANCHNEG " << y << endl;
		cout << "BRANCH " << n << endl;
		break;
	case GE:
		left->generate(t);
		right->generate(t);
		cout << "SUB" << endl;
		cout << "BRANCHNEG " << n << endl;
		cout << "BRANCH " << y << endl;
		break;
	case GT:
		right->generate(t);
		left->generate(t);
		cout << "SUB" << endl;
		cout << "BRANCHNEG " << y << endl;
		cout << "BRANCH " << n << endl;
		break;
	case LE:
		right->generate(t);
		left->generate(t);
		cout << "SUB" << endl;
		cout << "BRANCHNEG " << n << endl;
		cout << "BRANCH " << y << endl;
		break;
	default: break;
	}
	return NULL;
}

Info* UnOp::generate(SymbolTable<Info>* t) {
	string y, n, s;
	switch (op) {
	case Neg:
		cout << "CONSTANT 0" << endl;
		expr->generate(t);
		cout << "SUB" << endl;
		break;
	default:
		y = t->newLabel();
		n = t->newLabel();
		s = t->newLabel();
		this->generate(t, y, n);
		cout << "LABEL " << y << endl;
		cout << "CONSTANT 1" << endl;
		cout << "BRANCH " << s << endl;
		cout << "LABEL " << n << endl;
		cout << "CONSTANT 0" << endl;
		cout << "LABEL " << s << endl;
		break;
	}
	return NULL;
}

Info* UnOp::generate(SymbolTable<Info>* t, string y, string n) {
	expr->generate(t, n, y);
	return NULL;
}

Info* Num::generate(SymbolTable<Info>* t) {
	cout << "CONSTANT " << value << endl;
	return NULL;
}

Info* Num::generate(SymbolTable<Info>* t, string y, string n) {
	return NULL;
}

Info* IDExpr::generate(SymbolTable<Info>* t) {
	Info* look_up = t->lookup(id);
	if (look_up->infotype == ConstInfo_Info) 	{
		ConstInfo* info = dynamic_cast<ConstInfo*>(look_up);
		cout << "CONSTANT " << info->constant << endl;
	}
	else {
		lvalue(id, t);
		cout << "LOAD" << endl;
	}
	return NULL;
}

Info* IDExpr::generate(SymbolTable<Info>* t, string y, string n) {
	lvalue(id, t);
	cout << "LOAD" << endl;
	cout << "BRANCHZERO " << n << endl;
	cout << "BRANCH " << y << endl;
	return NULL;
}

Info* True::generate(SymbolTable<Info>* t) {
	cout << "CONSTANT 1" << endl;
	return NULL;
}

Info* True::generate(SymbolTable<Info>* t, string y, string n) {
	cout << "BRANCH " << y << endl;
	return NULL;
}

Info* False::generate(SymbolTable<Info>* t) {
	cout << "CONSTANT 0" << endl;
	return NULL;
}

Info* False::generate(SymbolTable<Info>* t, string y, string n) {
	cout << "BRANCH " << n << endl;
	return NULL;
}

/**************
* lvalue pushes address 
***************/
void lvalue(string id, SymbolTable<Info>* t) {
	Info* look_up = t->lookup(id);
	if (look_up->infotype == VarInfo_Info) 	{
		VarInfo* info = dynamic_cast<VarInfo*>(look_up);
		cout << "ADDRESS " << info->level << ", " << info->offset << endl;
	}
	else {
		RefInfo* info = dynamic_cast<RefInfo*>(look_up);
		cout << "ADDRESS " << info->level << ", " << info->offset << endl;
		cout << "LOAD" << endl;
	}
}

/****************
* Converts string to print char
******************/
void printChar(string str) {
	for (char c : str) 	{
		cout << "CONSTANT " << (int)c << endl;
		cout << "WRITECHAR" << endl;
	}
}