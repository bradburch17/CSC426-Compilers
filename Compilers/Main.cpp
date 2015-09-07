/*
* Main.cpp
*
*  Created on: Aug 31, 2015
*      Author: bhoward and Brad Burch
*	   Modified September 6, 2015 by Brad Burch
*/

#include "Scanner.h"

#include <iostream>
using namespace std;

// Main entry point for the Project 1 Demo -- read all the tokens from standard input
// and print them to standard output.
int main() {
	Scanner scanner(cin);

	Token token;
	do {
		token = scanner.next();
		cout << token << endl;
	} while (token.type != EOFILE);
}
