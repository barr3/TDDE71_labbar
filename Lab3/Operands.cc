#include "Operands.h"
#include <iomanip>
#include <sstream>

std::string Operand::infix() const
{
    return prefix();
}

std::string Operand::postfix() const
{
    return infix();
}

Real::Real(double value)
  : value{ value }
{
}

double Real::evaluate() const
{
    return value;
}

std::string Real::prefix() const
{
    std::stringstream ss{};
    ss << std::fixed << std::setprecision(3) << evaluate();
    return ss.str();
}

std::string Integer::prefix() const
{
    std::stringstream ss{};
    ss << evaluate();
    return ss.str();
}

Integer::Integer(int value)
  : value{ value }
{
}

double Integer::evaluate() const
{
    return value;
}
