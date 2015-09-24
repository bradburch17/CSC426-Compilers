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

using namespace std;

class Parser {
public:
	Parser();
	void parser();	

private:
	pair<string, string> constant;
	unordered_map<string, string> con;
};

#endif /* PARSER_H_ */
