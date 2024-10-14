#include "Expression.h"
#include "Operators.h"
#include "Operands.h"
#include <stack>
#include <sstream>
#include <string>
#include <cmath>

Expression::Expression(std::string expression)
{
    std::stack<Node*> stack { };
    std::istringstream iss { expression };
    std::string element;

    while (iss >> element)
    {
        try
        {
            double d std::stod(element);

            // Check if element is integer or real 
            if (std::fmod(d, 1.0) == 0.0)
            {
                // Is integer
                stack.push(new Integer { static_cast<int>(d) });
            }
            else 
            {
                // Is real
                stack.push(new Real { d });
            }
        }
        catch
        {
            if (element == "+")
            {
                Node* first { stack.top() };
                stack.pop();
                Node* second { stack.top() };
                stack.pop();

                stack.push(new Addition { first, second });
            }
            else if (element == "-")
            {
                Node* first { stack.top() };
                stack.pop();
                Node* second { stack.top() };
                stack.pop();

                stack.push(new Subtraction { first, second });
            }
        }

        root = stack.top();
    }
}

double Expression::evaluate()
{
    return root->evaluate();
}
