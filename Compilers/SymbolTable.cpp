/*
* SymbolTable.cpp
*
*  Created on: November 4, 2015
*      Author: Brad Burch
*/

#include <iostream>
#include "SymbolTable.h"

using namespace std;

SymbolTable::SymbolTable()
{
	scopes = vector<pair<string, map<string, Value*>*>>();
}

/*
* Enter pushes a new id onto the symbol table
*/
void SymbolTable::entertbl(string i)
{
	pair<string, map<string, Value*>* > symbol = make_pair(i, new map<string, Value*>());
	scopes.push_back(symbol);
}

/*
* Exit pops the top off of the symbol table
*/
void SymbolTable::exittbl()
{
	scopes.pop_back();
}

void SymbolTable::bind(string id, Value * v)
{
	map<string, Value*>* current_map = scopes.back().second;
	if (current_map->find(id) == current_map->end())
		current_map->insert(map<string, Value*>::value_type(id, v));
	else
	{
		cout << "Error: " << id << endl;
	}
}

/*
* Lookup returns the the binding for the id and if none found,
* it returns a new value.
*/
Value* SymbolTable::lookup(string id)
{
	for (int i = (int)scopes.size() - 1; i > -1; --i)
	{
		map<string, Value*>* map = scopes.at(i).second;
		if (map->find(id) != map->end())
			return map->at(id);
	}
	return NULL;
}

IntValue::IntValue(int i)
{
	integer = i;
	value = IntegerValue;
}

int IntValue::getIntValue()
{
	return integer;
}

bool IntValue::getBoolValue()
{
	cout << "Error: Cannot retrieve " << checkValueType(BooleanValue) << endl;
	exit(1);
}

void IntValue::setInt(int i)
{
	cout << "Error: Cannot set " << checkValueType(IntegerValue) << endl;
	exit(1);
}

void IntValue::setBool(bool b)
{
	cout << "Error: Cannot set " << checkValueType(BooleanValue) << endl;
	exit(1);
}


BoolValue::BoolValue(bool b)
{
	boolean = b;
	value = BooleanValue;
}

int BoolValue::getIntValue()
{
	cout << "Error: Cannot retrieve " << checkValueType(IntegerValue) << endl;
	exit(1);
}

bool BoolValue::getBoolValue()
{
	return boolean;
}

void BoolValue::setInt(int i)
{
	cout << "Error: Cannot set " << checkValueType(IntegerValue) << endl;
	exit(1);
}

void BoolValue::setBool(bool b)
{
	cout << "Error: Cannot set " << checkValueType(BooleanValue) << endl;
	exit(1);
}

int BoolCell::getIntValue()
{
	cout << "Error: Cannot retrieve " << checkValueType(IntegerValue) << endl;
	exit(1);
}

bool BoolCell::getBoolValue()
{
	return boolean;
}

void IntCell::setInt(int i)
{
	integer = i;
}

void BoolCell::setInt(int i)
{
	cout << "Error: Cannot set " << checkValueType(IntegerValue) << endl;
	exit(1);
}

void BoolCell::setBool(bool b)
{
	boolean = b;
}

int IntCell::getIntValue()
{
	return integer;
}

bool IntCell::getBoolValue()
{
	cout << "Error: Cannot retrieve " << checkValueType(BooleanValue) << endl;
	exit(1);
}

void IntCell::setBool(bool b)
{
	cout << "Error: Cannot set " << checkValueType(BooleanValue) << endl;
	exit(1);
}

int ProcValue::getIntValue()
{
	cout << "Error: Cannot retrieve " << checkValueType(IntegerValue) << endl;
	exit(1);
}

bool ProcValue::getBoolValue()
{
	cout << "Error: Cannot retrieve " << checkValueType(BooleanValue) << endl;
	exit(1);
}

void ProcValue::setInt(int i)
{
	cout << "Error: Cannot set " << checkValueType(IntegerValue) << endl;
	exit(1);
}

void ProcValue::setBool(bool b)
{
	cout << "Error: Cannot set " << checkValueType(BooleanValue) << endl;
	exit(1);
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

/****************
* Templates 
******************/
template <typename T>
T* SymbolTable<T>::lookUp(string ID, int line, int column)
{
	for (int i = (int)symbol_table.size() - 1; i > -1; --i)
	{
		map<string, T*>* map = symbol_table.at(i).second;
		if (map->find(ID) != map->end())
			return map->at(ID);
	}
	return NULL;
}

template <typename T>
T* SymbolTable<T>::lookUp(string ID)
{
	for (int i = (int)symbol_table.size() - 1; i > -1; --i)
	{
		map<string, T*>* map = symbol_table.at(i).second;
		if (map->find(ID) != map->end())
			return map->at(ID);
	}
	return NULL;
}

//-------------------------------//
// Push a new pair of a program's
// ID and its corresponding
// value declerations and values
// maps to the symbol table.
// Only called by Program, Call, Match
//-------------------------------//
template <typename T>
void SymbolTable<T>::enterTable(string ID, int line, int column)
{
	pair<string, map<string, T*>* > symbol = make_pair(ID, new map<string, T*>());
	symbol_table.push_back(symbol);
	level += 1;
}

template <typename T>
void SymbolTable<T>::enterTable(string ID)
{
	pair<string, map<string, T*>* > symbol = make_pair(ID, new map<string, T*>());
	symbol_table.push_back(symbol);
	level += 1;
}


//-------------------------------//
// Push a new pair of
// value decleration and value
// to the last map
//-------------------------------//
template <typename T>
void SymbolTable<T>::bind(string ID, int line, int column, T* v)
{
	map<string, T*>* current_map = symbol_table.back().second;
	if (current_map->find(ID) == current_map->end())
		current_map->insert(pair<string, T*>(ID, v));
	else
	{
		cout << "(!) " << ID << " is defined at " << v->line << ":" << v->column
			<< " and should not be re-defined at " << line << ":" << column << endl;
		exit(1);
	}
}

template <typename T>
void SymbolTable<T>::bind(string ID, T* v)
{
	map<string, T*>* current_map = symbol_table.back().second;
	current_map->insert(pair<string, T*>(ID, v));
}


//-------------------------------//
// Pop the last map
//-------------------------------//
template <typename T>
void SymbolTable<T>::exitTable()
{
	delete symbol_table.back().second;
	symbol_table.pop_back();
	level -= 1;
}


//-------------------------------//
// Return the last scope's stack level
//-------------------------------//
template <typename T>
int SymbolTable<T>::getLevel()
{
	return symbol_table.size() - 1;
}


//-------------------------------//
// Return a unique label
//-------------------------------//
template <typename T>
string SymbolTable<T>::newLabel()
{
	sequence += 1;
	return "_" + to_string(sequence);
}
