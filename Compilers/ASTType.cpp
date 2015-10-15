#include "ASTType.h"
#include <iostream>

using namespace std;

string ASTType::nameCheck(Type t)
{
	switch (t) {
	case IntType: return "IntType";
	case BoolType: return "BoolType";
	}
}
