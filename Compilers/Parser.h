/*
* Created September 17, 2015
* Author: Brad Burch
*/
#ifndef PARSER_H_
#define PARSER_H_

#include <iosfwd>
#include <string>

#include "Token.h"

using namespace std;

class Parser {
public:
	bool check(Token);
	bool match(Token);
	void look();
private:
	
};

#endif /* PARSER_H_ */
