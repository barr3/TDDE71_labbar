#include "Time.h"
#include <string>
#include <iostream>

int main()
{

    Time test_time = Time("15:05:30");

    std::cout << test_time << std::endl;

    return 0;
}