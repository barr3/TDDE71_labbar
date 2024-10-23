#include "Expression.h"
#include "Operands.h"
#include "Operators.h"
#include "postfix.h"
#include <cmath>
#include <memory>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

#include <iostream>

Expression::Expression(std::string const& infix_expression)
  : root{ nullptr }
{
    Postfix postfix_expression{ infix_expression };
    std::istringstream iss{ postfix_expression.to_string() };
    std::stack<std::unique_ptr<Node>> stack{};
    std::string current_element{};

    while (iss >> current_element)
    {
        try
        {
            double d{ std::stod(current_element) };

            if (std::fmod(d, 1.0) == 0.0)
            {
                // Is integer
                stack.push(std::make_unique<Integer>(static_cast<int>(d)));
            }
            else
            {
                // Is real
                stack.push(std::make_unique<Real>(d));
            }
        }
        catch (std::exception const& e)
        {
            if (stack.size() < 2)
            {
                throw std::logic_error("Missing operands for operator");
            }

            std::unique_ptr<Node> first{ std::move(stack.top()) };
            stack.pop();
            std::unique_ptr<Node> second{ std::move(stack.top()) };
            stack.pop();

            if (current_element == "+")
            {
                stack.push(std::make_unique<Addition>(second.release(),
                                                      first.release()));
            }
            else if (current_element == "-")
            {
                stack.push(std::make_unique<Subtraction>(second.release(),
                                                         first.release()));
            }
            else if (current_element == "*")
            {
                stack.push(std::make_unique<Multiplication>(second.release(),
                                                            first.release()));
            }
            else if (current_element == "/")
            {
                stack.push(std::make_unique<Division>(second.release(),
                                                      first.release()));
            }
            else if (current_element == "^")
            {
                stack.push(std::make_unique<Exponentiation>(second.release(),
                                                            first.release()));
            }
            else
            {
                throw std::logic_error("Invalid character in expression");
            }
        }
    }

    if (stack.size() > 1)
    {
        throw std::logic_error("Missing operator");
    }
    else if (stack.size() == 0)
    {
        throw std::logic_error("Empty expression");
    }
    else
    {
        root = stack.top().release();
    }
}

Expression::~Expression()
{
    delete root;
}

// Move constructor
Expression::Expression(Expression&& other)
  : root(other.root)
{
    other.root = nullptr;
}

// Move assignment operator
Expression& Expression::operator=(Expression&& other)
{
    std::swap(other.root, root);
    return *this;
}

double Expression::evaluate() const
{
    return get_root()->evaluate();
}

std::string Expression::to_string() const
{
    return infix();
}

std::string Expression::prefix() const
{
    return get_root()->prefix();
}

std::string Expression::infix() const
{
    return get_root()->infix();
}

std::string Expression::postfix() const
{
    return get_root()->postfix();
}

Node* Expression::get_root() const
{
    if (root != nullptr)
    {
        return root;
    }
    else
    {
        throw std::logic_error("Expression root node is nullptr");
    }
}
