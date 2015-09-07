/*
* Scanner.h
*
*  Created on: Aug 30, 2015
*      Author: bhoward and Brad Burch
*	   Modified September 6, 2015 by Brad Burch
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

	// return the next token from the input stream, or EOFILE if none
	Token next();

private:
	istream& in;
	int line_num, column_num;
	string line;

	char current_char();
	void advance();
};

#endif /* SCANNER_H_ */
