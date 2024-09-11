#include <sstream>
#include <string>
#include "Time.h"

Time::Time()
    : hour{0}, minute{0}, second{0}
{
}

Time::Time(unsigned int hour, unsigned int minute, unsigned int second)
    : hour{hour}, minute{minute}, second{second}
{    
}

unsigned int Time::get_hour()
{
    return hour;
}

unsigned int Time::get_minute()
{
    return minute;
}

unsigned int Time::get_second()
{
    return second;
}

/*
// Assumes input is in format hh::mm::ss
Time::Time(std::string time)
{     
    std::stringstream ss {time};
    ss >> hour;
    // Ignore ':'
    ss.ignore(1);
    ss >> minute;
    ss.ignore(1);
    ss >> second;
}
*/