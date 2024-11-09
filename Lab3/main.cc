#include "Expression.h"
#include <iostream>
#include <vector>

int main()
{
    std::string line;
    std::vector<Expression> saved_expressions{};
    Expression expression{ "0" }; // Initialize expression with zero
    std::cout << "~ ";
    while (getline(std::cin, line))
    {
        if (line == ":calc")
        {
            double result{ expression.evaluate() };
            std::cout << "= " << result << std::endl;
            // try 
            // {
            //     double result{ expression.evaluate() };
            //     std::cout << "= " << result << std::endl;
            // }
            // catch (const std::exception& e)
            // {
            //     std::cout << "Undefined expression" << std::endl;
            // }
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
        else if (line == ":save")
        {
            saved_expressions.push_back(Expression{ expression.infix() });
        }
        else if (line == ":list")
        {
            for (unsigned int i{ 0 }; i < saved_expressions.size(); i++)
            {
                std::cout << i + 1 << ": " << saved_expressions[i].infix()
                          << std::endl;
            }
        }
        else if (line.substr(0, line.find(" ")) == ":activate")
        {
            try
            {
                int index_number{ std::stoi(line.substr(10, -1)) - 1 };
                if (index_number < 0)
                {
                    throw std::range_error("Index out of range");
                }

                if (static_cast<unsigned int>(index_number) + 1 >
                    saved_expressions.size())
                {
                    throw std::range_error("Index out of range");
                }

                expression =
                  Expression{ saved_expressions[index_number].infix() };
            }
            catch (const std::exception& e)
            {
                std::cout << "Invalid index number" << std::endl;
            }
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
            catch (std::exception const& e)
            {
                std::cout << "Invalid expression due to: " << e.what() << std::endl;
            }
        }

        std::cout << "~ ";
    }
    return 0;
}
