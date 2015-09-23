/*
* Created September 17, 2015
* Author: Brad Burch
*/
#ifndef WRAPPER_H_
#define WRAPPER_H_

#include <iosfwd>
#include <string>

#include "Token.h"
#include "Scanner.h"

using namespace std;

class Wrapper {
public:
	bool check(Token_Type type); //Check returns true or false if the Token_Type is a match
	Token match(Token_Type type); //Match returns the token 
	Token current();
	Wrapper();
	Token skip();

private:
	Token curr;
	Scanner scanner; //this is causing no default constructor error
};

#endif /* WRAPPER_H_ */
