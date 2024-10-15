#include "Expression.h"
#include "Operands.h"
#include "Operators.h"
#include <cmath>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

Expression::Expression(std::string const& expression)
{
    std::stack<Node*> stack{};
    std::istringstream iss{ expression };
    std::string element{};

    while (iss >> element)
    {
        try
        {
            double d{ std::stod(element) };

            if (std::fmod(d, 1.0) == 0.0)
            {
                // Is integer
                stack.push(new Integer{ static_cast<int>(d) });
            }
            else
            {
                // Is real
                stack.push(new Real{ d });
            }
        }
        catch (std::exception e)
        {
            if (stack.size() < 2)
            {
                throw std::logic_error("Missing operands for operator");
            }

            if (element == "+")
            {
                Node* first{ stack.top() };
                stack.pop();
                Node* second{ stack.top() };
                stack.pop();

                stack.push(new Addition{ second, first });
            }
            else if (element == "-")
            {
                Node* first{ stack.top() };
                stack.pop();
                Node* second{ stack.top() };
                stack.pop();

                stack.push(new Subtraction{ second, first });
            }
            else if (element == "*")
            {
                Node* first{ stack.top() };
                stack.pop();
                Node* second{ stack.top() };
                stack.pop();

                stack.push(new Multiplication{ second, first });
            }
            else if (element == "/")
            {
                Node* first{ stack.top() };
                stack.pop();
                Node* second{ stack.top() };
                stack.pop();

                stack.push(new Division{ second, first });
            }
            else if (element == "^")
            {
                Node* first{ stack.top() };
                stack.pop();
                Node* second{ stack.top() };
                stack.pop();

                stack.push(new Exponentiation{ second, first });
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

    root = stack.top();
}

double Expression::evaluate() const
{
    return root->evaluate();
}

std::string Expression::prefix() const
{
    return root->prefix();
}

std::string Expression::infix() const
{
    return root->infix();
}

std::string Expression::postfix() const
{
    return root->postfix();
}
