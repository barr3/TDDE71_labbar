#ifndef OPERANDS
#define OPERANDS

#include "Node.h"

class Operand : public Node
{
  public:
    virtual double evaluate() const = 0;
    virtual std::string prefix() const = 0;
    virtual std::string infix() const = 0;
    virtual std::string postfix() const = 0;
};

class Real : public Operand
{
  private:
    double value;

  public:
    Real(double value);
    double evaluate() const;
    std::string prefix() const;
    std::string infix() const;
    std::string postfix() const;
};

class Integer : public Operand
{
  private:
    int value;

  public:
    Integer(int value);
    double evaluate() const;
    std::string prefix() const;
    std::string infix() const;
    std::string postfix() const;
};

#endif
