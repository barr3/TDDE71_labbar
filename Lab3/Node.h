#ifndef NODE
#define NODE
#include "Operand.h"

class Node
{
private:
	Node *right;
	Node *left;

public:
	virtual double evaluate();
};

#endif