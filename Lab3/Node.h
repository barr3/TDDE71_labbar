#ifndef NODE
#define NODE

class Node
{
private:
	Node *right;
	Node *left;

public:
	virtual double evaluate() = 0;
};

#endif

