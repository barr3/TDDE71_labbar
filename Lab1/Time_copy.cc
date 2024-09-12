#include <sstream>
#include <string>
#include "Time.h"

//Delegating constructor?
Time::Time()
    : hour{0}, minute{0}, second{0}
{
}

Time::Time(unsigned int hour, unsigned int minute, unsigned int second)
    : hour{hour}, minute{minute}, second{second}
{    
    throw_if_invalid_time();
}


//Assumes input is in format hh::mm::ss
Time::Time(std::string time)
    : hour{}, minute{}, second{}
{     
    std::stringstream ss {time};
    ss >> hour;
    // Ignore ':'
    ss.ignore(1);
    ss >> minute;
    ss.ignore(1);
    ss >> second;

    throw_if_invalid_time();
}

std::string Time::to_string(std::string format) const
{
    if (format == "24h")
    {
        return to_string_24h();
    }
    else if (format == "12h")
    {
        return to_string_12h();
    }
    else {
        throw std::runtime_error("Invalid time format!");
    }
}

bool Time::is_am() const
{
    return hour < 12;
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

bool Time::operator>(Time const &rhs) const
{
    return calculate_seconds(hour, minute, second) 
         > calculate_seconds(rhs.hour, rhs.minute, rhs.second);
}

bool Time::operator<(Time const &rhs) const
{
    return calculate_seconds(hour, minute, second) 
         < calculate_seconds(rhs.hour, rhs.minute, rhs.second);
}

bool Time::operator<=(Time const &rhs) const
{
    return calculate_seconds(hour, minute, second) 
        <= calculate_seconds(rhs.hour, rhs.minute, rhs.second);
}

bool Time::operator>=(Time const &rhs) const
{
    return calculate_seconds(hour, minute, second) 
        >= calculate_seconds(rhs.hour, rhs.minute, rhs.second);
}

bool Time::operator==(Time const &rhs) const
{
    return calculate_seconds(hour, minute, second) 
        == calculate_seconds(rhs.hour, rhs.minute, rhs.second);
}

bool Time::operator!=(Time const &rhs) const
{
    return calculate_seconds(hour, minute, second) 
        != calculate_seconds(rhs.hour, rhs.minute, rhs.second);
}

unsigned int Time::calculate_seconds
(
    unsigned int hour, 
    unsigned int minute,
    unsigned int second
) const
{
    return hour * 3600 + minute * 60 + second;
}

void Time::throw_if_invalid_time() const
{
    if ((hour >= 24) || (minute >= 60) || (second >= 60)) 
    {
        throw std::runtime_error("Invalid time");
    }
}

// Insert an integer into a stream, adding a leading zero if the number is one-digit
void Time::add_num_to_ss(std::stringstream &ss, int num) const
{
    if(num < 10)
    {
        ss << "0" << num;
    }
    else
    {
        ss << num;
    }
}

std::string Time::to_string_24h() const
{
    std::stringstream ss {};
    add_num_to_ss(ss, hour);
    ss << ":";
    add_num_to_ss(ss, minute);
    ss << ":";
    add_num_to_ss(ss, second);

    return ss.str();
}

std::string Time::to_string_12h() const
{
    std::stringstream ss {};
    if (is_am())
    {
        if (hour == 0)
        {
            add_num_to_ss(ss, 12);
        }
        else
        {
            add_num_to_ss(ss, hour);
        }
    }
    else
    {
        if (hour == 12)
        {
            add_num_to_ss(ss, 12);
        }
        else {
            add_num_to_ss(ss, hour - 12);
        }
    }
    ss << ":";
    add_num_to_ss(ss, minute);
    ss << ":";
    add_num_to_ss(ss, second);

    if (is_am())
    {
        ss << "am";
    }
    else
    {
        ss << "pm";
    }

    return ss.str();
}

std::ostream& operator<<(std::ostream &out, Time const &t)
{
    out << t.to_string();
    return out;
}