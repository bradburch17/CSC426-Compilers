/*
* Created September 17, 2015
* Author: Brad Burch
*/
#ifndef PARSER_H_
#define PARSER_H_

#include <iosfwd>
#include <unordered_map>
#include <string>

#include "Scanner.h"
#include "ASTStmt.h"

using namespace std;

class Parser {
public:
	Parser();
	void parser();

	ASTStmt parseProgram();


private:
	pair<string, string> constant; //This sets up the pairing for constants. It is not the actual hashmap.
	unordered_map<string, string> con; //This is the actual hashmap that takes in constant. 
};

#endif /* PARSER_H_ */
