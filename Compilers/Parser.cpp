/*
* Created September 17, 2015
* Author: Brad Burch
*/
#include <iostream>
#include <stack>

#include "Parser.h"
#include "Scanner.h"
#include "Wrapper.h"
#include "Token.h"

using namespace std;

Parser::Parser() {
	
}

/*
* pres is the presidence of the token types. 
*
* @params: Token 
*/
int pres(Token tok) {
	Token_Type type;
	type = tok.type;
	if (type == PRINT) {
		return 0;
	}
	else if (type == PLUS) {
		return 1;
	}
	else if (type == MINUS) {
		return 1;
	}
	else
		return 2;
}

void Parser::parser() {
	
	Wrapper wrapper(cin);
	while (wrapper.check(PRINT)) {
		wrapper.match(PRINT);
		stack<Token> s;
		Token tok;
		tok.type = PRINT;
		s.push(tok);
		Token op;
		while (!wrapper.check(SEMI)) {
			if (wrapper.check(NUM)) {
				cout << wrapper.match(NUM); //only print lexeme
			}
			else if (wrapper.check(ID)) {
				cout << wrapper.match(ID); //only print lexeme
			}
			else if (wrapper.check(PLUS)) { //add the ID, CONST, whatever 
				op = wrapper.match(PLUS);
			}
			else if (wrapper.check(MINUS)) {
				op = wrapper.match(MINUS);
			}
			else if (wrapper.check(STAR)) {
				op = wrapper.match(STAR);
			}
			else if (wrapper.check(ASSIGN)) {
				op = wrapper.match(ASSIGN);
			}
			else if (wrapper.check(PERIOD)) {
				op = wrapper.match(PERIOD);
			}
			else {
				cout << "Error! Unexpected character. Expected NUM, ID, Operator";
			}
			while (pres(s.top()) >= pres(op)) {
				cout << s.top();
				s.pop();
				s.push(op);
			}
		}
		if (wrapper.check(SEMI)) {
			wrapper.match(SEMI);
			while (s.empty() == false) {
				cout << s.top();
				s.pop();
			}
		}
	}
}


/*
while check(PRINT) do:
match(PRINT)
s = new stack
s.push(PRINT)
while not check(SEMI) do:
if check(NUM) then:
print(match(NUM))
else if check(ID) then:
print(lookup(match(ID)))          Make sure this line works. 
else if check(PLUS) or check(MINUS) or ... then:
op = match(... whatever ...)
while prec(s.top) >= prec(op) do:
print(s.pop)
s.push(op)
else: error -- expected NUM, ID, or operator
end if
end while
match(SEMI)
while not s.isEmpty do:
print(s.pop)
end while
end while
*/
