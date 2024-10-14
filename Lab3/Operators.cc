#include "Operators.h"
#include <sstream>
#include <cmath>

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

char Addition::get_symbol() const
{
    return '+';
}

std::string Operator::prefix() const
{
    std::stringstream ss { };
    ss << get_symbol() << " " << left->prefix() << " " << right->prefix();
    return ss.str();
}

std::string Operator::infix() const
{
    std::stringstream ss { };
    ss << "( " << left->infix() << " " << get_symbol() << " " << right->infix() << " )";
    return ss.str();
}

std::string Operator::postfix() const
{
    std::stringstream ss { };
    ss << left->postfix() << " " << right->postfix() << " " << get_symbol();
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

char Subtraction::get_symbol() const
{
    return '-';
}


Multiplication::Multiplication(Node* left, Node* right)
    : Operator{left, right}
{
}

double Multiplication::evaluate() const
{
    return left->evaluate() * right->evaluate();
}

char Multiplication::get_symbol() const
{
    return '*';
}



Division::Division(Node* left, Node* right)
    : Operator{left, right}
{
}

double Division::evaluate() const
{
    double right_value { right->evaluate()};
    if (fmod(right_value, 1.0) == 0.0 
                && static_cast<int>(right_value) == 0)
    {
        throw std::logic_error("Division by zero");
    }

    return left->evaluate() / right->evaluate();
}

char Division::get_symbol() const
{
    return '/';
}

Exponentiation::Exponentiation(Node* left, Node* right)
    : Operator{left, right}
{
}

double Exponentiation::evaluate() const
{
    double left_value { left->evaluate() };
    double right_value { right->evaluate()};

    if ( fmod(left_value, 1.0) == 0.0 
                && static_cast<int>(left_value) == 0 
                && right_value <= 0)
    {
        throw std::logic_error("Invalid exponentiation");
    }
    else if ( left_value < 0 && fmod(right_value, 1.0) != 0.0 )
    {
        throw std::logic_error("Invalid exponentiation");
    }

    return pow(left_value,  right_value);
}

char Exponentiation::get_symbol() const
{
    return '^';
}

