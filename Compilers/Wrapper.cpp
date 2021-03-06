/*
* Created September 17, 2015
* Author: Brad Burch
*/
#include <iostream>

#include "Wrapper.h"
#include "Scanner.h"

using namespace std;


Wrapper::Wrapper(istream& i): scanner(Scanner(i)) {
	curr = scanner.next();
}

bool Wrapper::check(Token_Type type) {
	if (curr.type == type) {
		return true;
	}
	else {
		return false;
	}
}


Token Wrapper::match(Token_Type type) {
	Token token = curr;

	if (token.type == type) {
		return skip();
	}
	else {
		cout << "Error: Token " << curr << " not expected." << endl;
		exit(1);
	}
}

Token Wrapper::skip() {
	Token tok = curr;
	curr = scanner.next();
	return tok;
	
}



