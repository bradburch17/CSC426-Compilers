/*
* main.cpp
*
*  Created on: Aug 31, 2015
*      Author: Brad Burch
*/

#include "Scanner.h"
#include "Parser.h"

#include <iostream>

using namespace std;

int main() {
	Parser parser;
	ASTProgram* start = parser.start();
	cout << start->render("");
}
