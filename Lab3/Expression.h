#ifndef EXPRESSION
#define EXPRESSION

#include "Node.h"

class Expression
{
  private:
    Node* root;
    Node* get_root() const;

  public:
    Expression(std::string const& e);
    ~Expression();
    Expression(Expression&& other);            // Move constructor
    Expression& operator=(Expression&& other); // Move assignment operator
    Expression(Expression const&) = delete;
    Expression& operator=(Expression const&) = delete;

    double evaluate() const;
    std::string to_string() const;
    std::string prefix() const;
    std::string infix() const;
    std::string postfix() const;
};

#endif
