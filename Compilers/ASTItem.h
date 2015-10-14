/*
* ASTItem.h
*
*  Created on: October 12, 2015
*      Author: Brad Burch
*/

#ifndef ASTItem_H_
#define ASTItem_H_

#include <string>
#include <iosfwd>

using namespace std;

class ASTItem {
public:
	ASTItem();
	virtual string render(string indent) = 0;

private:


};
#endif /* ASTItem_H_ */
