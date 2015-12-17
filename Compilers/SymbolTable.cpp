/*
* SymbolTable.cpp
*
*  Created on: November 4, 2015
*      Author: Brad Burch
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "SymbolTable.h"

using namespace std;

string checkValueType(ValueType valueType) {
	switch (valueType) {
	case Undefined:		return "Undefined Value";
	case IntegerValue:	return "Integer Value";
	case BooleanValue:	return "Boolean Value";
	case IntegerCell:	return "Integer Cell";
	case BooleanCell:	return "Boolean Cell";
	case ProcedureValue:return "Procedure Value";
	}
}


/*****************
* Values
*******************/

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

