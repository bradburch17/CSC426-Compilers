/*
* main.cpp
*
*  Created on: Aug 31, 2015
*      Author: Brad Burch
*/

#include "Scanner.h"
#include "Parser.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
	string file;
	ifstream input;
	cout << "Enter the file you would like to run: ";
	cin >> file;
	input.open(file);
	while (input.fail()) {
		cout << "Could not open file. Try again: ";
		cin >> file;
		input.open(file);
	}

	Parser parser(input);
	ASTProgram* start = parser.start();
	start->interpret();
}
