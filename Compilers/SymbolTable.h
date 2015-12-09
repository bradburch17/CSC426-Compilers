/*
* SymbolTable.h
*
*  Created on: November 4, 2015
*      Author: Brad Burch
*/
#ifndef SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include <iostream>
#include "AST.h"

using namespace std;

enum ValueType { Undefined, IntegerValue, BooleanValue, IntegerCell, BooleanCell, ProcedureValue };
string checkValueType(ValueType type);

/*
* Values
*/
class Value {
public:
	Value();
	ValueType value;
	virtual int getIntValue() = 0;
	virtual bool getBoolValue() = 0;
	virtual void setInt(int i) = 0;
	virtual void setBool(bool b) = 0;
};

class IntValue :public Value {
public:
	IntValue(int i);
	int integer;
	int getIntValue();
	bool getBoolValue();
	void setInt(int i);
	void setBool(bool b);
};

class BoolValue :public Value {
public:
	BoolValue(bool b);
	bool boolean;
	int getIntValue();
	bool getBoolValue();
	void setInt(int i);
	void setBool(bool b);

};

class ProcValue :public Value {
public:
	ProcValue(list<ASTParam*> p, ASTBlock* b);
	list<ASTParam*> param;
	ASTBlock* block;
	int getIntValue();
	bool getBoolValue();
	void setInt(int i);
	void setBool(bool b);
};

class IntCell :public Value {
public:
	IntCell(int i);
	void set(int i);
	int getIntValue();
	bool getBoolValue();
	void setInt(int i);
	void setBool(bool b);
private:
	int integer;

};

class BoolCell :public Value {
public:
	BoolCell(bool b);
	void set(bool b);
	int getIntValue();
	bool getBoolValue();
	void setInt(int i);
	void setBool(bool b);
private:
	bool boolean;

};

/*
* Symbol Table
*/
template <typename T>
class SymbolTable {
public:
	SymbolTable();
	void entertbl(string id);
	void exittbl();
	void bind(string id, Value* v);
	Value* lookup(string id);
	vector<pair<string, map<string, Value*>*>> scopes;
	int getLevel();
	string newLabel();
};
#endif /*SymbolTable_H_*/