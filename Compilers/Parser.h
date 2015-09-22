/*
* Created September 17, 2015
* Author: Brad Burch
*/
#ifndef PARSER_H_
#define PARSER_H_

#include <iosfwd>
#include <string>

#include "Token.h"
#include "Scanner.h"

using namespace std;

class Parser {
public:
	bool check(Token_Type type);
	Token match(Token_Type type);
	Token current();
	//Wrapper(Scanner scanner);
	Token skip();

private:
	Token curr;
	Scanner scanner;
	
};

#endif /* PARSER_H_ */
