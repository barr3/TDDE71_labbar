#include "Operands.h"
#include <sstream>
#include <iomanip>


Real::Real(double value) : value{value}
{

}

double Real::evaluate() const
{
	return value;
}

std::string Real::prefix() const
{
    std::stringstream ss {  };
    ss << std::fixed << std::setprecision(3) << value;
    return ss.str();
}

std::string Real::infix() const
{
    return prefix();
}

std::string Real::postfix() const
{
    return prefix();
}

Integer::Integer(int value) : value{value}
{
}

double Integer::evaluate() const
{
	return value;
}

std::string Integer::prefix() const
{
    return std::to_string(value);
}

std::string Integer::infix() const
{
    return prefix();
}

std::string Integer::postfix() const
{
    return infix();
}
