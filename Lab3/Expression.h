#ifndef EXPRESSION
#define EXPRESSION

#include "Node.h"

class Expression 
{
private:
    Node* root;

public:
    Expression(std::string const& e);
    double evaluate() const;
    std::string prefix() const;
    std::string infix() const;
    std::string postfix() const;
};

#endif
