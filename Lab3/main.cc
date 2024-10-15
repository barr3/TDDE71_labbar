#include <iostream>
#include "Expression.h"

int main()
{
    std::string line;
    Expression expression{ "0" }; // Initialize expression with zero
    std::cout << "~ ";
    while (getline(std::cin, line))
    {
        if (line == ":calc")
        {
            double result{ expression.evaluate() };
            std::cout << "= " << result << std::endl;
        }
        else if (line == ":prefix")
        {
            std::cout << expression.prefix() << std::endl;
        }
        else if (line == ":infix")
        {
            std::cout << expression.infix() << std::endl;
        }
        else if (line == ":postfix")
        {
            std::cout << expression.postfix() << std::endl;
        }
        else if (line == ":quit" || line == ":exit")
        {
            break;
        }
        else
        {
            try
            {
                expression = Expression{ line };
            }
            catch (std::exception e)
            {
                std::cout << "Invalid input expression" << std::endl;
            }
        }

        std::cout << "~ ";
    }
    return 0;
}
