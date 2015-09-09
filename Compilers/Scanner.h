/*
* Scanner.h
*
*  Created on: Aug 30, 2015
*      Author: Brad Burch
*/

#ifndef SCANNER_H_
#define SCANNER_H_

#include "Token.h"

#include <iosfwd>
#include <string>

using namespace std;

class Scanner {
public:
	Scanner(istream& in);

	Token next();

private:
	istream& in;
	int line_num, column_num;
	string line;

	char current_char();
	bool at_EOF();
	void advance();
};

#endif /* SCANNER_H_ */
