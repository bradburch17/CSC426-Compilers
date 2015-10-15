#include <iostream>
#include "ASTOp1.h"

using namespace std;

string ASTOp1::nameCheck(Op1 op1)
{
	switch (op1) {
	case Neg: return "Neg";
	case Not: return "Not";
	}
}
