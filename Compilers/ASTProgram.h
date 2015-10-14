/*
* ASTProgram.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef ASTProgram_H_
#define ASTProgram_H_

#include <string>
#include <iosfwd>

using namespace std;

class ASTBlock;

class ASTProgram {
public:
	ASTProgram(string n, ASTBlock b);
	string render(string indent);

private:
	string name;
	ASTBlock block;


};
#endif /* ASTProgram_H_ */
