#include "Expression.h"
#include "Operands.h"
#include "Operators.h"
#include "postfix.h"
#include <cmath>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

Expression::Expression(std::string const& infix_expression)
{
    Postfix postfix_expression{ infix_expression };
    std::istringstream iss{ postfix_expression.to_string() };
    std::stack<Node*> stack{};
    std::string current_element{};

    while (iss >> current_element)
    {
        try
        {
            double d{ std::stod(current_element) };

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

            if (current_element == "+")
            {
                Node* first{ stack.top() };
                stack.pop();
                Node* second{ stack.top() };
                stack.pop();

                stack.push(new Addition{ second, first });
            }
            else if (current_element == "-")
            {
                Node* first{ stack.top() };
                stack.pop();
                Node* second{ stack.top() };
                stack.pop();

                stack.push(new Subtraction{ second, first });
            }
            else if (current_element == "*")
            {
                Node* first{ stack.top() };
                stack.pop();
                Node* second{ stack.top() };
                stack.pop();

                stack.push(new Multiplication{ second, first });
            }
            else if (current_element == "/")
            {
                Node* first{ stack.top() };
                stack.pop();
                Node* second{ stack.top() };
                stack.pop();

                stack.push(new Division{ second, first });
            }
            else if (current_element == "^")
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

    root = stack.top();
}

double Expression::evaluate() const
{
    return root->evaluate();
}

std::string Expression::to_string() const
{
    return infix();    
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
