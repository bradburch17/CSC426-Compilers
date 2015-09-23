/*
* Created September 17, 2015
* Author: Brad Burch
*/
#include <iostream>

#include "Wrapper.h"
#include "Scanner.h"

using namespace std;


Wrapper::Wrapper(istream& i) {
	scanner(i);
}

Scanner Wrapper::scanner(istream & i)
{
	return Scanner(i);
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
	if (token.type = NUM) {
		cout << token.lexeme;
		return skip();
	}
	else if (token.type = ID) {
		cout << token.lexeme;
		return skip();
	}
	if (token.type = type) {
		return skip();
	}
	else {
		cout << "Error!" << endl;
	}
}

Token Wrapper::skip() {
	Token tok = curr;
	curr = scanner(cin).next();
	return tok;
	
}



