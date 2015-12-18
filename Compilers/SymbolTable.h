/*
* SymbolTable.h
*
*  Created on: November 4, 2015
*      Author: Brad Burch
*/
#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <utility>
#include <map>

using namespace std;

enum ValueType { Undefined, IntegerValue, BooleanValue, IntegerCell, BooleanCell, ProcedureValue };
string checkValueType(ValueType type);

class ASTParam;
class ASTBlock;

/***************
* Values
****************/
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
	bool boolean;

};

/****************
* Symbol Table
******************/
template <typename T>
class SymbolTable {
public:
	SymbolTable();
	void entertbl(string id);
	void exittbl();
	void bind(string id, T* v);
	T* lookup(string id);
	int getLevel();
	string newLabel();
	vector<pair<string, map<string, T*>*>> scopes;

	int level;
	int offset;
	int param;
	int sequence;
};

template <typename T>
SymbolTable<T>::SymbolTable()
{
	scopes = vector<pair<string, map<string, T*>* > >();
	level = -1;
	offset = 0;
	param = 0;
	sequence = -1;
}

/*
* Enter pushes a new id onto the symbol table
*/
template <typename T>
void SymbolTable<T>::entertbl(string i) {
	pair<string, map<string, T*>* > symbol = make_pair(i, new map<string, T*>());
	scopes.push_back(symbol);
}

/*
* Exit pops the top off of the symbol table
*/
template <typename T>
void SymbolTable<T>::exittbl() {
	scopes.pop_back();
}

template <typename T>
void SymbolTable<T>::bind(string id, T* v) {
	map<string, T*>* current_map = scopes.back().second;
	if (current_map->find(id) == current_map->end())
		current_map->insert(map<string, T*>::value_type(id, v));
	else {
		if (!id.empty())
			cout << "Error: " << id << endl;
		else
			cout << "Error: No ID." << endl;
	}
}

/*
* Lookup returns the the binding for the id and if none found,
* it returns a new value.
*/
template <typename T>
T* SymbolTable<T>::lookup(string id) {
	for (int i = (int)scopes.size() - 1; i > -1; --i) {
		map<string, T*>* map = scopes.at(i).second;
		if (map->find(id) != map->end())
			return map->at(id);
	}
	return NULL;
}

template <typename T>
int SymbolTable<T>::getLevel() {
	return symbol_table.size() - 1;
}

template <typename T>
string SymbolTable<T>::newLabel() {
	sequence += 1;
	return "_" + to_string(sequence);
}
#endif /*_SymbolTable_H_*/