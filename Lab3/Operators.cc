#include "Operators.h"
#include <sstream>

Operator::Operator(Node* left, Node* right)
    : left{left}, right{right}
{
}

Addition::Addition(Node* left, Node* right)
    : Operator{left, right}
{
}

double Addition::evaluate() const
{
    return left->evaluate() + right->evaluate();
}

std::string Addition::prefix() const
{
    std::stringstream ss { };
    ss << "+ " << left->prefix() << " " << right->prefix();
    return ss.str();
}

std::string Addition::infix() const
{
    std::stringstream ss { };
    ss << "( " << left->infix() << " + " << right->infix() << " )";
    return ss.str();
}

std::string Addition::postfix() const
{
    std::stringstream ss { };
    ss << left->postfix() << " " << right->postfix() << " +";
    return ss.str();
}

Subtraction::Subtraction(Node* left, Node* right)
    : Operator{left, right}
{
}

double Subtraction::evaluate() const
{
    return left->evaluate() - right->evaluate();
}

std::string Subtraction::prefix() const
{
    std::stringstream ss { };
    ss << "- " << left->prefix() << " " << right->prefix();
    return ss.str();
}

std::string Subtraction::infix() const
{
    std::stringstream ss { };
    ss << "( " << left->infix() << " - " << right->infix() << " )";
    return ss.str();
}

std::string Subtraction::postfix() const
{
    std::stringstream ss { };
    ss << left->postfix() << " " << right->postfix() << " -";
    return ss.str();
}


Multiplication::Multiplication(Node* left, Node* right)
    : Operator{left, right}
{
}

double Multiplication::evaluate() const
{
    return left->evaluate() * right->evaluate();
}

std::string Multiplication::prefix() const
{
    std::stringstream ss { };
    ss << "* " << left->prefix() << " " << right->prefix();
    return ss.str();
}

std::string Multiplication::infix() const
{
    std::stringstream ss { };
    ss << "( " << left->infix() << " * " << right->infix() << " )";
    return ss.str();
}

std::string Multiplication::postfix() const
{
    std::stringstream ss { };
    ss << left->postfix() << " " << right->postfix() << " *";
    return ss.str();
}


Division::Division(Node* left, Node* right)
    : Operator{left, right}
{
}

double Division::evaluate() const
{
    return left->evaluate() * right->evaluate();
}

std::string Division::prefix() const
{
    std::stringstream ss { };
    ss << "/ " << left->prefix() << " " << right->prefix();
    return ss.str();
}

std::string Division::infix() const
{
    std::stringstream ss { };
    ss << "( " << left->infix() << " / " << right->infix() << " )";
    return ss.str();
}

std::string Division::postfix() const
{
    std::stringstream ss { };
    ss << left->postfix() << " " << right->postfix() << " /";
    return ss.str();
}
