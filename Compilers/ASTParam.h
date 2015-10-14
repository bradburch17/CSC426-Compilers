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
	virtual string render(string render) = 0;

private:


};
#endif /* ASTParam_H_ */
