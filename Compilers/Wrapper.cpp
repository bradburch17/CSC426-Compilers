/*
* Created September 17, 2015
* Author: Brad Burch
*/
#include <iostream>
#include "Wrapper.h"
#include "Scanner.h"

using namespace std;

Wrapper::Wrapper() {
	//Scanner scanner();
	//Token token();
}

Token Wrapper::current() {
	return curr;
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
	

	if (token.type = type) {
		token = scanner.next();
	}
	else {
		cout << "Error, yo!" << endl;
	}
}



