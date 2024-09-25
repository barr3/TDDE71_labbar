#include <sstream>
#include <string>
#include "Time.h"
#include <sstream>

Time::Time()
    : hour{0}, minute{0}, second{0}, millisecond{0}
{
}

Time::Time(unsigned int hour, 
           unsigned int minute, 
           unsigned int second, 
           unsigned int millisecond)
    : hour{hour}, minute{minute}, second{second}, millisecond{millisecond}
{
    throw_if_invalid_time();
}

Time::Time(std::string const &time)
    : hour{}, minute{}, second{}, millisecond{}
{
    std::stringstream ss{time};

    //Checks that string is input in correct format
    if (!(ss >> hour)) 
    {
        throw std::runtime_error("Invalid time string!");
    }
    if (ss.get() != ':') 
    {
        throw std::runtime_error("Invalid time string!");
    }
    if (!(ss >> minute)) 
    {
        throw std::runtime_error("Invalid time string!");
    }
    if (ss.get() != ':') 
    {
        throw std::runtime_error("Invalid time string!");
    }
    if (!(ss >> second)) 
    {
        throw std::runtime_error("Invalid time string!");
    }

    char next {};
    ss.get(next);
    if (!ss.fail()) 
    {
        if (next == '.') 
        {
            if (!(ss >> millisecond)) 
            {
                throw std::runtime_error("Invalid time string!");
            }
        }
        else 
        {
            throw std::runtime_error("Invalid time string!");
        }
    }

    throw_if_invalid_time();
}

std::string Time::to_string(std::string const &format) const
{
    if (format == "24h")
    {
        return to_string_24h();
    }
    else if (format == "12h")
    {
        return to_string_12h();
    }
    else
    {
        throw std::runtime_error("Invalid time format!");
    }
}

bool Time::is_am() const
{
    return hour < 12;
}

unsigned int Time::get_hour() const
{
    return hour;
}

unsigned int Time::get_minute() const
{
    return minute;
}

unsigned int Time::get_second() const
{
    return second;
}

unsigned int Time::get_millisecond() const
{
    return millisecond;
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

double Time::operator-(Time const &rhs) const
{
    double lhs_seconds {};
    double rhs_seconds {}; 

    lhs_seconds = hour*3600.0 
                + minute 
                * 60.0
                + second 
                + millisecond 
                / 1000.0;
    rhs_seconds = rhs.hour 
                * 3600.0 
                + rhs.minute 
                * 60.0
                + rhs.second 
                + rhs.millisecond 
                / 1000.0;

    return lhs_seconds - rhs_seconds;
}

Time& Time::operator++()
{
    if (second == 59)
    {
        second = 0;
        if (minute == 59)
        {
            minute = 0;
            if (hour == 23)
            {
                hour = 0;
            }
            else
            {
                hour++;
            }
        }
        else
        {
            minute++;
        }
    }
    else
    {
        second++;
    }
    
    return *this;
}

Time Time::operator++(int)
{
    Time temp = *this;
    ++*this;
    return temp;
}

unsigned int Time::calculate_seconds(
    unsigned int hour,
    unsigned int minute,
    unsigned int second) const
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
    if (num < 10)
    {
        ss << "0" << num;
    }
    else
    {
        ss << num;
    }
}

void Time::add_millisecond_to_ss(std::stringstream &ss, int num) const
{
    if (num < 100)
    {
        ss << "0";
    }
    if (num < 10)
    {
        ss << "0";
    }
    ss << num;
}

std::string Time::to_string_24h() const
{
    std::stringstream ss{};
    add_num_to_ss(ss, hour);
    ss << ":";
    add_num_to_ss(ss, minute);
    ss << ":";
    add_num_to_ss(ss, second);
    if (millisecond > 0)
    {
        ss << ".";
        add_millisecond_to_ss(ss, millisecond);
    }

    return ss.str();
}

std::string Time::to_string_12h() const
{
    std::stringstream ss{};
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
        else
        {
            add_num_to_ss(ss, hour - 12);
        }
    }
    ss << ":";
    add_num_to_ss(ss, minute);
    ss << ":";
    add_num_to_ss(ss, second);

    if (millisecond > 0)
    {
        ss << ".";
        add_millisecond_to_ss(ss, millisecond);
    }

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

std::ostream &operator<<(std::ostream &out, Time const &t)
{
    out << t.to_string();
    return out;
}