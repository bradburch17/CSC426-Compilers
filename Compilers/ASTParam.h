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

using namespace std;

class ASTParam {
public:
	ASTParam();
	virtual string render(string indent) = 0;

private:


};

class ValParam : public ASTParam {
public: 

private: 

};

class VarParam : public ASTParam {
public:

private:

};
#endif /* ASTParam_H_ */
