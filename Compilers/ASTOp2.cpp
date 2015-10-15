#include "ASTOp2.h"

string ASTOp2::nameCheck(Op2 op2)
{
	switch (op2) {
	case EQ: return "EQ";
	case NE: return "NE";
	case LE: return "LE";
	case GE: return "GE";
	case LT: return "LT";
	case GT: return "GT";
	case Plus: return "Plus";
	case Minus: return "Minus";
	case Times: return "Times";
	case Div: return "Div";
	case Mod: return "Mod";
	case And: return "And";
	case Or: return "Or";
	}
}
