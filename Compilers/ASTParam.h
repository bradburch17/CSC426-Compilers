/*
* ASTParam.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef ASTParam_H_
#define ASTParam_H_

#include <string>
#include <iosfwd>
#include "ASTType.h"

using namespace std;

class ASTParam {
public:
	ASTParam();
	virtual string render(string indent) = 0;

private:

};

class ValParam : public ASTParam {
public: 
	ValParam(string i, ASTType t);
	string render(string indent);

private: 
	string id;
	ASTType type;

};

class VarParam : public ASTParam {
public:
	VarParam(string i, ASTType t);
	string render(string indent);

private:
	string id;
	ASTType type;

};
#endif /* ASTParam_H_ */
