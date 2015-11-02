/*
* SymbolTable.h
*
*  Created on: November 1, 2015
*      Author: Brad Burch
*/
#ifndef SymbolTable_H_
#define SymbolTable_H_

#include <iostream>
#include <stdio.h>
#include <stack>
#include <map>

using namespace std;

class SymbolTable {
public: 
	SymbolTable();
	void enter(string i);
	void exit();
	void bind(string id, Value value);
	void lookup(string id);

private:
	stack<pair<string, map<string, Value>>> scopes;

};

class Value {
public:
	Value();
};
#endif /* SYMBOLTABLE_H_ */