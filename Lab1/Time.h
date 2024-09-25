#ifndef TIME
#define TIME

#include <string>

class Time
{
    public:
        Time();
        Time(unsigned int hour, 
             unsigned int minute, 
             unsigned int second, 
             unsigned int millisecond = 0);
        Time(std::string const &time);
        std::string to_string(std::string const &format = "24h") const;
        bool is_am() const;
        unsigned int get_hour() const;
        unsigned int get_minute() const;
        unsigned int get_second() const;
        unsigned int get_millisecond() const;

        bool operator>(Time const &rhs) const;
        bool operator<(Time const &rhs) const;
        bool operator<=(Time const &rhs) const;
        bool operator>=(Time const &rhs) const;
        bool operator==(Time const &rhs) const;
        bool operator!=(Time const &rhs) const;
        double operator-(Time const &rhs) const;
        Time& operator++(); //prefix
        Time operator++(int); //Postfix


    private:
        unsigned int hour;
        unsigned int minute;
        unsigned int second;
        unsigned int millisecond;
        unsigned int calculate_seconds(unsigned int hour, 
                                       unsigned int minute, 
                                       unsigned int second) const;
        void throw_if_invalid_time() const;
        void add_num_to_ss(std::stringstream &ss, int num) const;
        void add_millisecond_to_ss(std::stringstream &ss, int num) const;
        std::string to_string_24h() const;
        std::string to_string_12h() const;
        void throw_if_invalid_string() const;
};

std::ostream& operator<<(std::ostream& ss, Time const &rhs);

#endif