#ifndef OPERATORS
#define OPERATORS

#include "Node.h"

class Operator : public Node
{
  protected:
    Node* left;
    Node* right;

    virtual char get_symbol() const = 0;

  public:
    Operator(Node* left, Node* right);
    ~Operator();
    Operator(Operator const&) = delete;
    Operator& operator=(Operator const&) = delete;

    virtual double evaluate() const = 0;
    virtual std::string prefix() const;
    virtual std::string infix() const;
    virtual std::string postfix() const;
};

class Addition : public Operator
{
  public:
    Addition(Node* left, Node* right);
    using Operator::Operator;

    double evaluate() const;
    char get_symbol() const;
};

class Subtraction : public Operator
{
  public:
    Subtraction(Node* left, Node* right);
    using Operator::Operator;

    double evaluate() const;
    char get_symbol() const;
};

class Multiplication : public Operator
{
  public:
    Multiplication(Node* left, Node* right);
    using Operator::Operator;

    double evaluate() const;
    char get_symbol() const;
};

class Division : public Operator
{
  public:
    Division(Node* left, Node* right);
    using Operator::Operator;

    double evaluate() const;
    char get_symbol() const;
};

class Exponentiation : public Operator
{
  public:
    Exponentiation(Node* left, Node* right);
    using Operator::Operator;

    double evaluate() const;
    char get_symbol() const;
};

#endif
