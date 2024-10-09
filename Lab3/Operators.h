#ifndef OPERATOR
#define OPERATOR
#include "Node.h"

class Operator : public Node
{
protected:
    Node* left;
    Node* right;

public:
    Operator(Node* left, Node* right);
	Operator(Operator const&) = delete;
	Operator& operator=(Operator const&) = delete;

    virtual double evaluate() const = 0;
    virtual std::string prefix() const = 0;
    virtual std::string infix() const = 0;
	virtual std::string postfix() const = 0;
};

class Addition : public Operator
{
public:
    Addition(Node* left, Node* right);
    double evaluate() const;
    std::string prefix() const;
    std::string infix() const;
    std::string postfix() const;
};

class Subtraction : public Operator
{
public:
    Subtraction(Node* left, Node* right);
    double evaluate() const;
    std::string prefix() const;
    std::string infix() const;
    std::string postfix() const;
};

class Multiplication : public Operator
{
public:
    Multiplication(Node* left, Node* right);
    double evaluate() const;
    std::string prefix() const;
    std::string infix() const;
    std::string postfix() const;
};

class Division : public Operator
{
public:
    Division(Node* left, Node* right);
    double evaluate() const;
    std::string prefix() const;
    std::string infix() const;
    std::string postfix() const;
};



#endif