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
	Parser parser;
	ASTProgram* start = parser.start();
	string filename;
	ifstream input;

	cout << "Enter your file: ";
	cin >> filename;
	input.open(filename);

	while (input.fail()) {
		input.clear();
		cout << "Not a valid file. Enter valid file: ";
		cin >> filename;
		input.open(filename);
	}

	cout << start->render("");
}
