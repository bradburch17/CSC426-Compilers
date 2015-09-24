/*
* Created September 17, 2015
* Author: Brad Burch
*/
#ifndef WRAPPER_H_
#define WRAPPER_H_

#include <iosfwd>
#include <iostream>

#include "Token.h"
#include "Scanner.h"

using namespace std;

class Wrapper {
public:
	bool check(Token_Type type); //Check returns true or false if the Token_Type is a match
	Token match(Token_Type type); //Match returns the token and advances to the next
	Wrapper(istream& i); //This is the constructor, it has a scanner in it
	Token skip(); //This returns the current token and advances to the next 

private:
	Token curr;  
	Scanner scanner; 
};

#endif /* WRAPPER_H_ */
