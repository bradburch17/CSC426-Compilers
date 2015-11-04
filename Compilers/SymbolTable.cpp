/*
* SymbolTable.h
*
*  Created on: November 1, 2015
*      Author: Brad Burch
*/

#include <iostream>
#include "SymbolTable.h"
#include "AST.h"

using namespace std;

SymbolTable::SymbolTable()
{
	scopes = stack<pair<string, map<string, Value>>>();
}

void SymbolTable::enter(string i)
{
	pair<string, map<string, Value>> symbols = make_pair(i, map<string, Value>());
	scopes.push(symbols);
}

void SymbolTable::exit()
{
	scopes.pop();
}

